
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
  typedef std::function < void () > Callback;
  typedef std::shared_ptr < Job > Ptr;

  // Constructors
  Job();
  explicit Job ( Callback );
  Job ( const std::string &name, double priority, Callback );

  // Get/set the flag that says we are cancelled.
  // This is a hint; the job can ignore it.
  void cancel();
  bool isCancelled() const;

  // Get/set the flag that says we are done.
  void done();
  bool isDone() const;

  // Get the id.
  unsigned long getID() const { return _id; } // No need to guard.

  // Get/set the name.
  std::string getName() const;
  void        setName ( const std::string & );

  // Get/set the priority.
  double getPriority() const;
  void   setPriority ( double );

  // Get/set the callback.
  Callback getCallback();
  void     setCallback ( Callback );

private:

  mutable Mutex _mutex;
  const unsigned long _id;
  std::string _name;
  double _priority;
  Callback _callback;
  bool _cancelled;
  bool _done;
};


} // namespace Jobs
} // namespace Usul


#endif // _USUL_JOBS_JOB_CLASS_H_
