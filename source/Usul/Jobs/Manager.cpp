
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Job manager class.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Jobs/Manager.h"
#include "Usul/Errors/Check.h"
#include "Usul/Tools/NoThrow.h"
#include "Usul/Tools/ScopedCall.h"

#include <algorithm>
#include <chrono>
#include <functional>
#include <sstream>
#include <stdexcept>


namespace Usul {
namespace Jobs {


///////////////////////////////////////////////////////////////////////////////
//
//  Macros used below.
//
///////////////////////////////////////////////////////////////////////////////

#define IS_WORKER_THREAD_OR_THROW this->_isWorkerThreadOrThrow()
#define IS_NOT_WORKER_THREAD_OR_THROW this->_isNotWorkerThreadOrThrow()


///////////////////////////////////////////////////////////////////////////////
//
//  Details for this class.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  std::mutex mutex;
  Manager *_instance = nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the default maximum number of threads.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  inline unsigned int getDefaultMaxNumThreadsAllowed()
  {
    // Keep one available for the worker as well as any user-interface thread.
    const unsigned int keep = 2u;

    // This is how many threads the hardware can run at the same time.
    const unsigned int has = std::thread::hardware_concurrency();

    // If we can, return the difference, otherwise return the bare minimum.
    return ( ( has > keep ) ? ( has - keep ) : 1u );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Helper functions to handle standard exception.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class IdType >
  inline void handleStandardException ( Manager &me, Manager::JobPtr job, const std::exception &e, IdType id )
  {
    Manager::ErrorHandler handler = me.getErrorHandler();
    if ( handler )
    {
      handler ( job, e );
    }
    else
    {
      Usul::Tools::Details::logStandardException ( e, id, &std::clog );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Helper functions to handle unknown exception.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class IdType >
  inline void handleUnknownException ( Manager &me, Manager::JobPtr job, IdType id )
  {
    Manager::ErrorHandler handler = me.getErrorHandler();
    if ( handler )
    {
      std::runtime_error e ( Usul::Strings::format ( "Unknown exception caught at location ", id ) );
      handler ( job, e );
    }
    else
    {
      Usul::Tools::Details::logUnknownException ( id, &std::clog );
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Macro used below in try-catch blocks.
//
///////////////////////////////////////////////////////////////////////////////

#define JOB_MANAGER_CATCH_EXCEPTIONS(id,job) \
  catch ( const std::exception &e ) \
  { \
    Details::handleStandardException ( *this, job, e, id ); \
  } \
  catch ( ... ) \
  { \
    Details::handleUnknownException ( *this, job, id ); \
  }


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor
//
///////////////////////////////////////////////////////////////////////////////

Manager::Manager() :
  _mutex(),
  _workerThread(),
  _workerID(),
  _queuedJobs(),
  _runningJobs(),
  _errorHandler(),
  _maxNumThreadsAllowed ( Details::getDefaultMaxNumThreadsAllowed() ),
  _numMillisecondsToSleep ( 10 ),
  _shouldRunWorkerThread ( true ),
  _isBeingDestroyed ( false ),
  _hasJobInTransition ( false )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor
//
///////////////////////////////////////////////////////////////////////////////

Manager::~Manager()
{
  USUL_TOOLS_NO_THROW ( 1591069652, std::bind ( &Manager::_destroyManager, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_destroyManager()
{
  IS_NOT_WORKER_THREAD_OR_THROW;

  // Set this first.
  _isBeingDestroyed = true;

  // Do not lock the mutex! Other threads may be running and you have to wait
  // for them, and they might need to lock the mutex.

  // Local function to sleep some to hopefully side-step a somewhat rare crash
  // that is difficult to reproduce and (as far as I know) only happens when
  // the job-manager is being deleted while it was busy.
  auto pause = [] ()
  {
    std::this_thread::sleep_for ( std::chrono::milliseconds ( 5 ) );
  };

  // Do some cleanup.
  this->clearQueuedJobs();
  this->cancelRunningJobs();

  pause();

  // Wait for any jobs that are still running.
  this->waitAll();

  pause();

  // Clear the containers.
  _queuedJobs.clear();
  _runningJobs.clear();

  pause();

  // Stop the worker thread.
  this->_stopWorkerThread();

  pause();

  // We're done with our worker thread. This is probably already null.
  _workerThread = nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Singleton construction.
//
///////////////////////////////////////////////////////////////////////////////

Manager &Manager::instance()
{
  std::lock_guard < std::mutex > guard ( Details::mutex );
  if ( nullptr == Details::_instance )
  {
    Details::_instance = new Manager();
  }
  return *Details::_instance;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Singleton destruction.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::destroy()
{
  std::lock_guard < std::mutex > guard ( Details::mutex );
  delete Details::_instance;
  Details::_instance = nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Sort the queue.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::sortQueuedJobs()
{
  Guard guard ( _mutex );
  std::sort ( _queuedJobs.begin(), _queuedJobs.end(), [] ( JobPtr a, JobPtr b )
  {
    return ( a->getPriority() < b->getPriority() );
  } );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Add a job to the queue.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::addJob ( JobPtr job )
{
  IS_NOT_WORKER_THREAD_OR_THROW;

  // Check input.
  if ( nullptr == job.get() )
  {
    throw std::runtime_error ( "Cannot add null job" );
  }

  // Do nothing if we are being destroyed.
  if ( true == _isBeingDestroyed )
  {
    throw std::runtime_error ( "Cannot add job to manager that is being destroyed" );
  }

  // Need a local scope for the lock.
  {
    // One thread at a time.
    Guard guard ( _mutex );

    // Do not allow more jobs than the unsigned int max.
    typedef std::numeric_limits < unsigned int > Limits;
    if ( _queuedJobs.size() >= Limits::max() )
    {
      std::ostringstream out;
      out << "Exceeded maximum size of job queue: " << Limits::max();
      throw std::runtime_error ( out.str() );
    }

    // Add the job to the queue.
    _queuedJobs.push_back ( job );

    // Sort the queue now while the mutex is locked to keep it consistent.
    this->sortQueuedJobs();
  }

  // Make sure the worker thread is started.
  this->_startWorkerThread();
}
Manager::JobPtr Manager::addJob ( Callback cb )
{
  JobPtr job ( new Job ( cb ) );
  this->addJob ( job );
  return job;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Remove the queued job. Has no effect on running jobs.
//
///////////////////////////////////////////////////////////////////////////////

bool Manager::removeQueuedJob ( JobPtr j1 )
{
  IS_NOT_WORKER_THREAD_OR_THROW;

  // One thread at a time.
  Guard guard ( _mutex );

  // Shortcut
  QueuedJobs &q = _queuedJobs;

  // Get the number of queued jobs before we do anything.
  const QueuedJobs::size_type numBefore = q.size();

  // Erase all the jobs that are the given job.
  q.erase ( std::remove_if ( q.begin(), q.end(), [ &j1 ] ( JobPtr j2 )
  {
    return ( j1 == j2 );
  } ),
  q.end() );

  // Get the number of queued jobs now that we (may) have erase one.
  const QueuedJobs::size_type numAfter = q.size();

  // How many did we erase?
  const QueuedJobs::size_type numErased = numBefore - numAfter;

  // Make sure we erased either one or zero.
  if ( ( 0 != numErased ) && ( 1 != numErased ) )
  {
    std::ostringstream out;
    out << "Erased " << numErased << " jobs";
    throw std::runtime_error ( out.str() );
  }

  // Return true if we erased one.
  return ( 1 == numErased );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Cancel the running jobs.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::cancelRunningJobs()
{
  IS_NOT_WORKER_THREAD_OR_THROW;
  Guard guard ( _mutex );

  // Loop through the running jobs and cancel them.
  // Note: They stay in the container. The normal mechanism will remove them.
  std::for_each ( _runningJobs.begin(), _runningJobs.end(), [] ( RunningInfo info )
  {
    info.second->cancel();
  } );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Clear any jobs that are in the queue.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::clearQueuedJobs()
{
  IS_NOT_WORKER_THREAD_OR_THROW;
  Guard guard ( _mutex );

  // If the jobs are still in the queue then there is no need to cancel them.
  _queuedJobs.clear();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the names of the running jobs.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::getRunningJobNames ( Names &names ) const
{
  Guard guard ( _mutex );
  std::for_each ( _runningJobs.begin(), _runningJobs.end(), [ &names ] ( RunningInfo info )
  {
    names.push_back ( info.second->getName() );
  } );
}
Manager::Names Manager::getRunningJobNames() const
{
  Names names;
  this->getRunningJobNames ( names );
  return names;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the names of the queued jobs.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::getQueuedJobNames ( Names &names ) const
{
  Guard guard ( _mutex );
  std::for_each ( _queuedJobs.begin(), _queuedJobs.end(), [ &names ] ( JobPtr job )
  {
    names.push_back ( job->getName() );
  } );
}
Manager::Names Manager::getQueuedJobNames() const
{
  Names names;
  this->getQueuedJobNames ( names );
  return names;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the number of jobs.
//
///////////////////////////////////////////////////////////////////////////////

unsigned int Manager::getNumJobs() const
{
  // The mutex is recursive so guard here to return a number that is
  // accurate for the time this function was called.
  Guard guard ( _mutex );

  // Return the number of queued jobs, jobs, and in transition.
  // A job is in transition if it has been taken out of the queue
  // but not yet put into the list of running jobs.
  const unsigned int numQueued = this->getNumJobsQueued();
  const unsigned int numRunning = this->getNumJobsRunning();
  const unsigned int numInTransition = ( _hasJobInTransition ? 1 : 0 );
  return ( numQueued + numRunning + numInTransition );
}
unsigned int Manager::getNumJobsRunning() const
{
  Guard guard ( _mutex );
  return static_cast < unsigned int > ( _runningJobs.size() );
}
unsigned int Manager::getNumJobsQueued() const
{
  Guard guard ( _mutex );
  return static_cast < unsigned int > ( _queuedJobs.size() );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the maximum number of threads allowed. If more threads are
//  currently running than the new maximum, it does not stop them.
//
///////////////////////////////////////////////////////////////////////////////

unsigned int Manager::getMaxNumThreadsAllowed() const
{
  return _maxNumThreadsAllowed; // This is atomic.
}
void Manager::setMaxNumThreadsAllowed ( unsigned int num )
{
  IS_NOT_WORKER_THREAD_OR_THROW;
  _maxNumThreadsAllowed = num; // This is atomic.
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the number of milliseconds to sleep.
//
///////////////////////////////////////////////////////////////////////////////

unsigned int Manager::getNumMillisecondsToSleep() const
{
  return _numMillisecondsToSleep; // This is atomic.
}
void Manager::setNumMillisecondsToSleep ( unsigned int num )
{
  IS_NOT_WORKER_THREAD_OR_THROW;
  _numMillisecondsToSleep = num; // This is atomic.
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the flag that says we should run the worker thread.
//
///////////////////////////////////////////////////////////////////////////////

bool Manager::_getShouldRunWorkerThread() const
{
  return _shouldRunWorkerThread; // This is atomic.
}
void Manager::_setShouldRunWorkerThread ( bool state )
{
  IS_NOT_WORKER_THREAD_OR_THROW;
  _shouldRunWorkerThread = state; // This is atomic.
}


///////////////////////////////////////////////////////////////////////////////
//
//  Wait for all jobs to complete.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::waitAll ( unsigned int extraMilliseconds )
{
  IS_NOT_WORKER_THREAD_OR_THROW;

  // We could guard this function so that no new jobs are queued and start
  // running while we are in here. On the other hand, we could make the mutex
  // available and let the user decide if that is desired.

  // Shortcut
  const unsigned int numMillisecondsToSleep = this->getNumMillisecondsToSleep();

  // Loop until there are no queued or running jobs.
  while ( this->getNumJobs() > 0 )
  {
    // Sleep some so that we don't spike the cpu.
    std::this_thread::sleep_for ( std::chrono::milliseconds ( numMillisecondsToSleep ) );
  }

  // Try to prevent test failures that look like this:
  // /some/path/usul/tests/Usul/Jobs/Manager.cpp:92: FAILED:
  //   REQUIRE( numJobs == count )
  // with expansion:
  //   100 == 100
  if ( extraMilliseconds > 0 )
  {
    std::this_thread::sleep_for ( std::chrono::milliseconds ( extraMilliseconds ) );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Functions for checking threads.
//
///////////////////////////////////////////////////////////////////////////////

bool Manager::_isWorkerThread() const
{
  return ( std::this_thread::get_id() == _workerID );
}
void Manager::_isWorkerThreadOrThrow() const
{
  if ( false == this->_isWorkerThread() )
  {
    throw std::runtime_error ( "The current thread should be the worker thread" );
  }
}
void Manager::_isNotWorkerThreadOrThrow() const
{
  if ( true == this->_isWorkerThread() )
  {
    throw std::runtime_error ( "The current thread should not be the worker thread" );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Start the worker thread.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_startWorkerThread()
{
  IS_NOT_WORKER_THREAD_OR_THROW;

  // One thread at a time.
  Guard guard ( _mutex );

  // Do not start the worker thread if it's already running.
  if ( nullptr == _workerThread.get() )
  {
    // Make the new thread. Need a lambda here that assigns _workerID before
    // calling the thread's function. Otherwise, it could start executing the
    // thread before it assigns _workerID below, and then _isWorkerThreadOrThrow()
    // will throw an exception when it should not.
    _workerThread = ThreadPtr ( new std::thread ( [ this ] ()
    {
      // If an exception sneaks through it will bring down the house.
      try
      {
        // Assign the thread-id of this worker-thread. It is an atomic
        // std::thread::id so no need to lock the mutex to access it.
        // This helps avoid deadlock.
        _workerID = std::this_thread::get_id();

        // TODO: At one point, without this _isWorkerThreadOrThrow() would
        // throw an exception. Is this still needed?
        // std::this_thread::sleep_for ( std::chrono::milliseconds ( this->getNumMillisecondsToSleep() ) );

        // Now run this new thread.
        this->_threadStarted();
      }
      JOB_MANAGER_CATCH_EXCEPTIONS ( 1591247240, JobPtr() )
    } ) );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Stop the worker thread.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_stopWorkerThread()
{
  IS_NOT_WORKER_THREAD_OR_THROW;

  // The worker thread should break out of its loop.
  this->_setShouldRunWorkerThread ( false );

  // Make a copy of the worker thread pointer then make it null.
  ThreadPtr worker = nullptr;
  {
    Guard guard ( _mutex );
    worker = _workerThread;
    _workerThread = nullptr;
  }

  // We're done with our worker thread.
  if ( nullptr != worker.get() )
  {
    // Wait for it to finish.
    worker->join();

    // Now we can do this, but not before.
    _workerID = std::thread::id();

    // This should be the last reference so it will get deleted.
    worker = nullptr;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the internal thread starts.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_threadStarted()
{
  // If an exception sneaks through it will bring down the house.
  try
  {
    IS_WORKER_THREAD_OR_THROW;

    // Do not lock mutex here!

    // Loop until told otherwise.
    while ( true == this->_getShouldRunWorkerThread() )
    {
      // Note: A try-catch block in here will create an infinite loop if the
      // worker thread throws an exception.

      // Check the running jobs and remove any that are done.
      this->_checkRunningJobs();

      // Check the queue and maybe start a new job.
      this->_checkQueuedJobs();

      // Sleep some so that we don't spike the cpu.
      std::this_thread::sleep_for ( std::chrono::milliseconds ( this->getNumMillisecondsToSleep() ) );
    }
  }
  JOB_MANAGER_CATCH_EXCEPTIONS ( 1591049996, JobPtr() )
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the next job in the queue or null if the queue is empty.
//
///////////////////////////////////////////////////////////////////////////////

Manager::JobPtr Manager::_getNextQueuedJob()
{
  IS_WORKER_THREAD_OR_THROW;
  Guard guard ( _mutex );

  // Should not happen but make sure.
  USUL_CHECK_AND_THROW ( ( false == _hasJobInTransition ), "There is already a job in transition" );

  // Handle an empty queue.
  if ( true == _queuedJobs.empty() )
  {
    return JobPtr();
  }

  // Get the last job. It should have the highest priority.
  JobPtr job = _queuedJobs.back();

  // We now have a job in transition.
  _hasJobInTransition = true;

  // Pop the job from the queue.
  _queuedJobs.pop_back();

  // Return the job.
  return job;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Check the queue and maybe start a new job.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_checkQueuedJobs()
{
  IS_WORKER_THREAD_OR_THROW;

  // Do we have enough running jobs already?
  if ( this->getNumJobsRunning() >= this->getMaxNumThreadsAllowed() )
  {
    return;
  }

  // Get the next job.
  JobPtr job = this->_getNextQueuedJob();

  // When we're done in here we no longer have a job in transition.
  USUL_SCOPED_CALL ( [ this ] ()
  {
    _hasJobInTransition = false; // This variable is atomic.
  } );

  // This means the queue is empty.
  if ( nullptr == job.get() )
  {
    return;
  }

  // If the job does not have a callback function then skip it.
  if ( !job->getCallback() )
  {
    return;
  }

  // If the job has been cancelled then skip it.
  if ( true == job->isCancelled() )
  {
    return;
  }

  // If for some reason the job is done then skip it.
  if ( true == job->isDone() )
  {
    return;
  }

  // Start a new thread and have it run the job.
  ThreadPtr thread ( new std::thread ( [ job, this ] ()
  {
    // If an exception sneaks through it will bring down the house.
    try
    {
      // This should never happen but check anyway.
      if ( nullptr == job.get() )
      {
        throw std::runtime_error ( "Invalid job in thread" );
      }

      // Always set the job as done before we leave here.
      USUL_SCOPED_CALL ( std::bind ( &Job::done, job ) );

      try
      {
        // Get the callback function.
        Job::Callback fun = job->getCallback();

        // Make sure it is valid.
        if ( fun )
        {
          // Call the function.
          fun ( job );
        }
      }
      JOB_MANAGER_CATCH_EXCEPTIONS ( 1591073635, job )
    }
    JOB_MANAGER_CATCH_EXCEPTIONS ( 1591071534, job )
  } ) );

  // Add the job to the container of running jobs.
  {
    Guard guard ( _mutex );
    _runningJobs.insert ( RunningInfo ( thread, job ) );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Check the running jobs and remove any that are finished.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_checkRunningJobs()
{
  IS_WORKER_THREAD_OR_THROW;

  // This is the set of jobs we will remove.
  RunningJobs removeMe;

  // We do these separate steps to avoid invalidating iterators while looping.
  {
    // One thread at a time in here.
    Guard guard ( _mutex );

    // Loop through the running jobs.
    for ( auto i = _runningJobs.begin(); i != _runningJobs.end(); ++i )
    {
      // If the job is done then put it in the local container.
      if ( true == i->second->isDone() )
      {
        removeMe.insert ( *i );
      }
    }

    // Loop through the set we are supposed to remove.
    for ( auto i = removeMe.begin(); i != removeMe.end(); ++i )
    {
      // Remove this item from the container of running jobs.
      _runningJobs.erase ( *i );
    }
  }

  // Loop through the set we are supposed to remove.
  for ( auto i = removeMe.begin(); i != removeMe.end(); ++i )
  {
    // Wait for the thread. Since the job is done this should return immediately.
    i->first->join();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the error handler.
//
///////////////////////////////////////////////////////////////////////////////

Manager::ErrorHandler Manager::getErrorHandler() const
{
  Guard guard ( _mutex );
  return _errorHandler;
}
void Manager::setErrorHandler ( ErrorHandler handler )
{
  Guard guard ( _mutex );
  _errorHandler = handler;
}


} // namespace Jobs
} // namespace Usul
