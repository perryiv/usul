
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
#include "Usul/Base/ObjectMap.h"
#include "Usul/Interfaces/IUnknown.h"
#include "Usul/Strings/Format.h"

#include <iostream>
#include <typeinfo>


namespace Usul {
namespace Base {


///////////////////////////////////////////////////////////////////////////////
//
//  Macro used to automatically add instances of the referenced class to the
//  map when created, and remove them when they are deleted.
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
  #ifdef USUL_REFERENCED_CLASS_DEBUG_KEEP_TRACK
    #define USUL_REFERENCED_CLASS_ADD_THIS    ObjectMap::getSingleton().add ( this )
    #define USUL_REFERENCED_CLASS_REMOVE_THIS ObjectMap::getSingleton().remove ( this )
  #else
    #define USUL_REFERENCED_CLASS_ADD_THIS
    #define USUL_REFERENCED_CLASS_REMOVE_THIS
  #endif
#else
  #define USUL_REFERENCED_CLASS_ADD_THIS
  #define USUL_REFERENCED_CLASS_REMOVE_THIS
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Referenced::Referenced() :
  _refCount ( 0 )
{
  USUL_REFERENCED_CLASS_ADD_THIS;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Referenced::Referenced ( const Referenced & ) :
  _refCount ( 0 )
{
  USUL_REFERENCED_CLASS_ADD_THIS;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Referenced::~Referenced()
{
  USUL_REFERENCED_CLASS_REMOVE_THIS;

  if ( _refCount > 0 )
  {
    // We're inside of a destructor so we can't throw an exception.
    // If the user wants to capture this error they can redirect stderr.
    // We output one string because that works best when multi-threaded.
    std::cerr << Usul::Strings::format
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
//  Get this referenced object as an IUnknown pointer, which may return null.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Interfaces::IUnknown *Referenced::asUnknown()
{
  return this->queryInterface ( Usul::Interfaces::IUnknown::IID );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Provided as a convenience for inheriting classes.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Interfaces::IUnknown *Referenced::queryInterface ( unsigned long )
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

  // We're not in a destructor so we could throw an exception. However, given
  // where this function gets called from it's probably best that we do not.
  // If the user wants to capture this error they can redirect stderr.
  // We output one string because that works best when multi-threaded.

  catch ( const std::exception &e )
  {
    std::cerr << ( Usul::Strings::format (
      "Deleting ", self, " caused a standard exception: ", e.what(),
      ", Class: ", ( name ? name : "" ),
      ", ID: ", 1568933858
    ) ) << std::endl;
  }

  catch ( ... )
  {
    std::cerr << ( Usul::Strings::format (
      "Deleting ", self, " caused an unknown exception",
      ", Class: ", ( name ? name : "" ),
      ", ID: ", 1568933859
    ) ) << std::endl;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Safely get the type name.
//
///////////////////////////////////////////////////////////////////////////////

const char* Referenced::getTypeName ( const Referenced* obj )
{
  try
  {
    if ( nullptr == obj )
    {
      return nullptr;
    }

    return ( typeid ( *obj ) ).name();
  }
  catch ( ... )
  {
    return nullptr;
  }
}


} // namespace Base
} // namespace Usul
