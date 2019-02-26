
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
#include "Usul/Errors/Handler.h"
#include "Usul/Strings/Format.h"


namespace Usul {
namespace Base {


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Referenced::~Referenced()
{
  // Should be true.
  USUL_ERROR_CHECKER_NO_THROW ( 0 == _refCount );
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
//  Delete this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Referenced::_deleteThis()
{
#ifdef _DEBUG

  const Referenced *self = nullptr;
  const char *name = nullptr;

  try
  {
    self = this;
    name = typeid ( *this ).name();
    delete this;
  }

  catch ( const std::exception &e )
  {
    USUL_ERROR_HANDLER ( Usul::Strings::format (
      "Deleting this instance caused a standard exception",
      ", Message: ", e.what(),
      ", Address: ", self,
      ", Class: ", ( name ? name : "" ) ) );
  }

  catch ( ... )
  {
    USUL_ERROR_HANDLER ( Usul::Strings::format (
      "Deleting this instance caused an unknown exception",
      ", Message: ", e.what(),
      ", Address: ", self,
      ", Class: ", ( name ? name : "" ) ) );
  }

#else

  delete this;

#endif
}


} // namespace Base
} // namespace Usul
