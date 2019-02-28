
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Reference-counting base class.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Base/Referenced.h"
#include "Usul/Strings/Format.h"

#include <iostream>

namespace Usul {
namespace Base {


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Referenced::Referenced() : BaseClass(),
  _refCount ( 0 )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Referenced::Referenced ( const Referenced &r ) : BaseClass ( r ),
  _refCount ( 0 )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Referenced::~Referenced()
{
  if ( _refCount > 0 )
  {
    // We're inside of a destructor so we can't throw an exception.
    // If the user wants to capture this error they can redirect stderr.
    // We output one string because that works best when multi-threaded.
    std::clog << Usul::Strings::format
      ( "Deleting ", this, " with a reference count of ", _refCount )
      << std::endl;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Assignment.
//
///////////////////////////////////////////////////////////////////////////////

Referenced &Referenced::operator = ( const Referenced & )
{
  // We define this function to make sure the compiler does not.
  // A compiler-generated operator would probably assign the reference count,
  // which does not make any sense.
  return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Classes that inherit can overload and return an IUnknown.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Interfaces::IUnknown *Referenced::asUnknown()
{
	return nullptr;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Reference this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Referenced::ref()
{
  ++_refCount;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Dereference this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Referenced::unref ( bool allowDeletion )
{
  if ( ( 0 == --_refCount ) && allowDeletion )
  {
    this->_deleteMe();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the reference count.
//
///////////////////////////////////////////////////////////////////////////////

Referenced::CounterType Referenced::getReferenceCount() const
{
  return _refCount;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Delete this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Referenced::_deleteMe()
{
  const Referenced *self = nullptr;
  const char *name = nullptr;

  try
  {
    self = this;
    name = typeid ( *this ).name();
    delete this;
  }

  // We're not in a destructor so we coult throw an exception. However, given
  // where this function gets called from it's probably best that we do not.
  // If the user wants to capture this error they can redirect stderr.
  // We output one string because that works best when multi-threaded.

  catch ( const std::exception &e )
  {
    std::clog << ( Usul::Strings::format (
      "Deleting ", self, " caused a standard exception: ", e.what(),
      ", Class: ", ( name ? name : "" ),
      ", File: ", __FILE__,
      ", Line: ", __LINE__
    ) ) << std::endl;
  }

  catch ( ... )
  {
    std::clog << ( Usul::Strings::format (
      "Deleting ", self, " caused an unknown exception",
      ", Class: ", ( name ? name : "" ),
      ", File: ", __FILE__,
      ", Line: ", __LINE__
    ) ) << std::endl;
  }
}


} // namespace Base
} // namespace Usul
