
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Job class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_JOBS_JOB_CLASS_H_
#define _USUL_JOBS_JOB_CLASS_H_

#include "Usul/Export.h"
#include "Usul/Config.h" // Ignore the 4251 warning.

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <string>


namespace Usul {
namespace Jobs {


class USUL_EXPORT Job
{
public:

  typedef std::recursive_mutex Mutex;
  typedef std::lock_guard < Mutex > Guard;
  typedef std::shared_ptr < Job > Ptr;
  typedef std::function < void ( Ptr ) > Callback;
  typedef std::atomic < double > AtomicDouble;

  // Constructors
  Job ( const std::string &name, double priority, Callback );
  Job ( const std::string &name, Callback );
  explicit Job ( Callback cb = Callback() );

  // Get/set the flag that says we are cancelled.
  // This is a hint; the job can ignore it.
  void cancel();
  bool isCancelled() const;

  // Get/set the flag that says we are done.
  void done();
  bool isDone() const;

  // Get the id.
  unsigned long getID() const { return _id; } // No need to guard.

  // Get the name.
  std::string getName() const { return _name; } // No need to guard.

  // Get/set the priority.
  double getPriority() const;
  void   setPriority ( double );

  // Get the callback.
  Callback getCallback();

private:

  mutable Mutex _mutex;
  const unsigned long _id;
  const std::string _name;
  AtomicDouble _priority;
  Callback _callback;
  bool _cancelled;
  bool _done;
};


} // namespace Jobs
} // namespace Usul


#endif // _USUL_JOBS_JOB_CLASS_H_
