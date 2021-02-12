
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

#ifndef _USUL_JOBS_JOB_MANAGER_CLASS_H_
#define _USUL_JOBS_JOB_MANAGER_CLASS_H_

#include "Usul/Export.h"
#include "Usul/Config.h" // Ignore the 4251 warning.
#include "Usul/Jobs/Job.h"
#include "Usul/Tools/NoCopying.h"

#include <atomic>
#include <functional>
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <vector>


namespace Usul {
namespace Jobs {


class USUL_EXPORT Manager : public Usul::Tools::NoCopying
{
public:

  typedef std::recursive_mutex Mutex;
  typedef std::lock_guard < Mutex > Guard;
  typedef Job::Callback Callback;
  typedef Job::Ptr JobPtr;
  typedef std::vector < JobPtr > QueuedJobs;
  typedef std::shared_ptr < std::thread > ThreadPtr;
  typedef std::pair < ThreadPtr, JobPtr > RunningInfo;
  typedef std::set < RunningInfo > RunningJobs;
  typedef std::function < void ( JobPtr, const std::exception & ) > ErrorHandler;
  typedef std::vector < std::string > Names;
  typedef std::atomic < unsigned int > AtomicUnsignedInt;
  typedef std::atomic < bool > AtomicBool;
  typedef std::atomic < std::thread::id > AtomicThreadID;

  // Constructor and destructor. Use as a singleton or as individual objects.
  Manager();
  ~Manager();

  // Add a job to the queue.
  void   addJob ( JobPtr );
  JobPtr addJob ( Callback );

  // Cancel all the running jobs. This is a hint; the jobs can ignore it.
  void cancelRunningJobs();

  // Clear any jobs that are in the queue.
  void clearQueuedJobs();

  // This will delete the singleton instance, if any.
  static void destroy();

  // Get/set the error handler.
  ErrorHandler getErrorHandler() const;
  void         setErrorHandler ( ErrorHandler );

  // Get the names of the running jobs.
  Names getRunningJobNames() const;
  void  getRunningJobNames ( Names & ) const;

  // Get the names of the queued jobs.
  Names getQueuedJobNames() const;
  void  getQueuedJobNames ( Names & ) const;

  // Get the singleton.
  static Manager &instance();

  // Get the number of jobs.
  unsigned int getNumJobs() const;
  unsigned int getNumJobsRunning() const;
  unsigned int getNumJobsQueued() const;

  // Get/set the maximum number of threads allowed. If more threads are
  // currently running than the new maximum, it does not stop them.
  unsigned int getMaxNumThreadsAllowed() const;
  void         setMaxNumThreadsAllowed ( unsigned int );

  // Get/set the number of milliseconds to sleep.
  unsigned int getNumMillisecondsToSleep() const;
  void         setNumMillisecondsToSleep ( unsigned int );

  // Direct access to the mutex. Use with caution.
  Mutex &mutex() { return _mutex; }

  // Remove the queued job. Has no effect on running jobs.
  bool removeQueuedJob ( JobPtr );

  // Sort the queue. Call this if you change a job's priority after adding it.
  // This function has no effect on a running job.
  void sortQueuedJobs();

  // Wait for all jobs to complete.
  void waitAll ( unsigned int extraMilliseconds = 50 );

protected:

  void _checkQueuedJobs();
  void _checkRunningJobs();
  void _checkThreads();

  JobPtr _getNextQueuedJob();

  bool _getShouldRunWorkerThread() const;
  void _setShouldRunWorkerThread ( bool );

  bool _isWorkerThread() const;
  void _isWorkerThreadOrThrow() const;
  void _isNotWorkerThreadOrThrow() const;

  void _startWorkerThread();
  void _stopWorkerThread();

  void _threadStarted();

private:

  void _destroyManager();

  mutable Mutex _mutex;
  ThreadPtr _workerThread;
  AtomicThreadID _workerID;
  QueuedJobs _queuedJobs;
  RunningJobs _runningJobs;
  ErrorHandler _errorHandler;
  AtomicUnsignedInt _maxNumThreadsAllowed;
  AtomicUnsignedInt _numMillisecondsToSleep;
  AtomicBool _shouldRunWorkerThread;
  AtomicBool _isBeingDestroyed;
  AtomicBool _hasJobInTransition;
};


} // namespace Jobs
} // namespace Usul


#endif // _USUL_JOBS_JOB_MANAGER_CLASS_H_
