
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

#include "Usul/Jobs/Job.h"


namespace Usul {
namespace Jobs {


///////////////////////////////////////////////////////////////////////////////
//
//  Get the next job id. This will also increment the internal counter.
//
///////////////////////////////////////////////////////////////////////////////

namespace { namespace Details
{
  unsigned long getNextID()
  {
    static std::atomic < unsigned long > _nextID ( 0 );
    return ++_nextID;
  }
} }


///////////////////////////////////////////////////////////////////////////////
//
//  Constructors
//
///////////////////////////////////////////////////////////////////////////////

Job::Job ( const std::string &name, double priority, Callback cb ) :
  _mutex(),
  _id ( Details::getNextID() ),
  _name ( name ),
  _priority ( priority ),
  _callback ( cb ),
  _cancelled ( false ),
  _done ( false )
{
}
Job::Job ( const std::string &name, Callback cb ) : Job ( name, 0, cb )
{
}
Job::Job ( Callback cb ) : Job ( std::string(), 0, cb )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the flag that says we are cancelled.
//  This is a hint; the job can ignore it.
//
///////////////////////////////////////////////////////////////////////////////

void Job::cancel()
{
  Guard guard ( _mutex );
  _cancelled = true;
}
bool Job::isCancelled() const
{
  Guard guard ( _mutex );
  return _cancelled;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the flag that says we are done.
//
///////////////////////////////////////////////////////////////////////////////

void Job::done()
{
  Guard guard ( _mutex );
  _done = true;
}
bool Job::isDone() const
{
  Guard guard ( _mutex );
  return _done;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get/set the priority.
//
///////////////////////////////////////////////////////////////////////////////

double Job::getPriority() const
{
  return _priority; // This is atomic.
}
void Job::setPriority ( double priority )
{
  _priority = priority; // This is atomic.
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the callback.
//
///////////////////////////////////////////////////////////////////////////////

Job::Callback Job::getCallback()
{
  Guard guard ( _mutex );
  return _callback;
}


} // namespace Jobs
} // namespace Usul
