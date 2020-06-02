
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

#define IS_WORKER_THREAD_OR_THROW \
  if ( false == this->isWorkerThread() ) \
  { \
    throw std::runtime_error ( "The current thread should be the worker thread" ); \
  }
#define IS_NOT_WORKER_THREAD_OR_THROW \
  if ( true == this->isWorkerThread() ) \
  { \
    throw std::runtime_error ( "The current thread should not be the worker thread" ); \
  }


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
  unsigned int getDefaultMaxNumThreadsAllowed()
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
//  Constructor
//
///////////////////////////////////////////////////////////////////////////////

Manager::Manager() :
  _mutex(),
  _workerThread(),
  _workerID(),
  _queuedJobs(),
  _runningJobs(),
  _maxNumThreadsAllowed ( Details::getDefaultMaxNumThreadsAllowed() ),
  _numMillisecondsToSleep ( 10 ),
  _shouldRunWorkerThread ( true ),
  _isBeingDestroyed ( false )
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

  // Do some cleanup.
  this->clearQueuedJobs();
  this->cancelAll();

  // Wait for any jobs that are still running.
  this->waitAll();

  // Stop the worker thread.
  this->_stopWorkerThread();

  // We're done with our worker thread.
  _workerThread = nullptr;

  // Clear the containers.
  _queuedJobs.clear();
  _runningJobs.clear();
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
  IS_NOT_WORKER_THREAD_OR_THROW;
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

  // Sort the queue.
  this->sortQueuedJobs();

  #ifdef _DEBUG
  std::cout << "Added job " << job->getID() << " to the queue" << std::endl;
  #endif

  // Make sure the worker thread is started.
  this->_startWorkerThread();
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
//  Cancel all the jobs.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::cancelAll()
{
  IS_NOT_WORKER_THREAD_OR_THROW;

  // Needed below.
  QueuedJobs queued;

  {
    // Guard the copying and clearing of the queue.
    Guard guard ( _mutex );

    // Make a copy of the queue.
    queued = _queuedJobs;

    // Clear the queue.
    _queuedJobs.clear();
  }

  // Loop through the queued jobs and cancel them.
  std::for_each ( queued.begin(), queued.end(), [] ( JobPtr job )
  {
    job->cancel();
  } );

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
  _queuedJobs.clear();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the names of the running jobs.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::getRunningJobNames ( Names &names ) const
{
  IS_NOT_WORKER_THREAD_OR_THROW;
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
  IS_NOT_WORKER_THREAD_OR_THROW;
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

  // Return the number of both queued and running jobs.
  return ( this->getNumJobsQueued() + this->getNumJobsRunning() );
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

void Manager::waitAll()
{
  IS_NOT_WORKER_THREAD_OR_THROW;

  // We could guard this function so that no new jobs are queued and start
  // running while we are in here. On the other hand, we could make the mutex
  // available and let the user decide if that is desired.

  // Shortcut
  const unsigned int numMillisecondsToSleep = this->getNumMillisecondsToSleep();

  // #ifdef _DEBUG
  // std::cout << "Waiting for all jobs to finish" << std::endl;
  // #endif

  // Loop until there are no queued or running jobs.
  while ( this->getNumJobs() > 0 )
  {
    #ifdef _DEBUG
    std::ostringstream out;
    out << "Waiting for " << this->getNumJobs() << " jobs to finish\n";
    std::cout << out.str() << std::flush;
    #endif

    // Sleep some so that we don't spike the cpu.
    std::this_thread::sleep_for ( std::chrono::milliseconds ( numMillisecondsToSleep ) );
  }

  // #ifdef _DEBUG
  // std::cout << "Done waiting for all jobs to finish" << std::endl;
  // #endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Is this the worker thread?
//
///////////////////////////////////////////////////////////////////////////////

bool Manager::isWorkerThread() const
{
  return ( std::this_thread::get_id() == _workerID );
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
    // Make the new thread.
    _workerThread = ThreadPtr ( new std::thread ( std::bind ( &Manager::_threadStarted, this ) ) );

    // Save this separately to help avoid deadlock.
    _workerID = _workerThread->get_id();
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

  #ifdef _DEBUG
  std::cout << "Asking the worker thread to stop" << std::endl;
  #endif

  // The worker thread should break out of its loop.
  this->_setShouldRunWorkerThread ( false );

  #ifdef _DEBUG
  std::cout << "Done asking the worker thread to stop" << std::endl;
  #endif

  // Make a copy of the worker thread pointer then make it null.
  ThreadPtr worker = nullptr;
  {
    Guard guard ( _mutex );
    worker = _workerThread;
    _workerThread = nullptr;
    _workerID = std::thread::id();
  }

  // We're done with our worker thread.
  if ( nullptr != worker.get() )
  {
    #ifdef _DEBUG
    std::cout << "Joining with the worker thread" << std::endl;
    #endif

    worker->join();

    #ifdef _DEBUG
    std::cout << "Done joining with the worker thread" << std::endl;
    #endif

    worker = nullptr;
  }

  #ifdef _DEBUG
  std::cout << "The worker thread has stopped" << std::endl;
  #endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when the internal thread starts.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_threadStarted()
{
  IS_WORKER_THREAD_OR_THROW;

  // Do not lock mutex here!

  #ifdef _DEBUG
  std::cout << "Entering worker thread function" << std::endl;
  #endif

  // If an exception sneaks through it will bring down the house.
  try
  {
    // Loop until told otherwise.
    while ( true == this->_getShouldRunWorkerThread() )
    {
      // Note: A try-catch block in here will create an infinite loop if the
      // worker thread throws an exception.

      #ifdef _DEBUG
      std::ostringstream out;
      out << "There are " << this->getNumJobsQueued() << " queued jobs and " << this->getNumJobsRunning() << " running jobs\n";
      std::cout << out.str() << std::flush;
      #endif

      // Check the running jobs and remove any that are done.
      this->_checkRunningJobs();

      // Check the queue and maybe start a new job.
      this->_checkQueuedJobs();

      // Sleep some so that we don't spike the cpu.
      std::this_thread::sleep_for ( std::chrono::milliseconds ( this->getNumMillisecondsToSleep() ) );
    }
  }
  USUL_TOOLS_CATCH_AND_LOG ( 1591049996, &std::clog )

  #ifdef _DEBUG
  std::cout << "Exiting worker thread function" << std::endl;
  #endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Check the queue and maybe start a new job.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_checkQueuedJobs()
{
  IS_WORKER_THREAD_OR_THROW;

  // One thread at a time.
  Guard guard ( _mutex );

  // Do we have enough running jobs already?
  if ( _runningJobs.size() >= this->getMaxNumThreadsAllowed() )
  {
    return;
  }

  // Do we have any jobs in the queue?
  if ( true == _queuedJobs.empty() )
  {
    return;
  }

  // Get the last job. It should have the highest priority.
  JobPtr job = _queuedJobs.back();
  _queuedJobs.pop_back();

  // This should never happen but make sure.
  if ( nullptr == job.get() )
  {
    throw std::runtime_error ( "Invalid job in queue" );
  }

  // Does the job have a callback function?
  if ( !job->getCallback() ) // Do not compare to nullptr.
  {
    return;
  }

  // Start a new thread and have it run the job.
  ThreadPtr thread ( new std::thread ( [ job ] ()
  {
    // If an exception sneaks through it will bring down the house.
    try
    {
      #ifdef _DEBUG
      std::cout << "Entering job thread function" << std::endl;
      #endif

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
          fun();
        }
      }
      USUL_TOOLS_CATCH_AND_LOG ( 1591073635, &std::clog )

      #ifdef _DEBUG
      std::cout << "Exiting job thread function" << std::endl;
      #endif
    }
    USUL_TOOLS_CATCH_AND_LOG ( 1591071534, &std::clog )
  } ) );

  // Add the job to the container of running jobs.
  _runningJobs.insert ( RunningInfo ( thread, job ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Check the running jobs and remove any that are finished.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_checkRunningJobs()
{
  IS_WORKER_THREAD_OR_THROW;

  // One thread at a time.
  Guard guard ( _mutex );

  // This is the set of jobs we will remove.
  RunningJobs removeMe;

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
    #ifdef _DEBUG
    std::cout << "Joining with the job thread" << std::endl;
    #endif

    // Wait for the thread. Since the job is done this should return immediately.
    i->first->join();

    #ifdef _DEBUG
    std::cout << "Done joining with the job thread" << std::endl;
    #endif

    // Remove this item from the container of running jobs.
    _runningJobs.erase ( *i );
  }
}


} // namespace Jobs
} // namespace Usul
