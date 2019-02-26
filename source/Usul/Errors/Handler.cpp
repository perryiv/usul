
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Error handler module.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Errors/Handler.h"
#include "Usul/Tools/NoThrow.h"

#include <functional>
#include <sstream>
#include <stdexcept>

namespace Usul {
namespace Details {


///////////////////////////////////////////////////////////////////////////////
//
//  The default error callback.
//
///////////////////////////////////////////////////////////////////////////////

void defaultErrorCallback ( const std::string &message, const char *filename, unsigned int line )
{
  std::ostringstream out;
  out << message;

  if ( filename )
  {
    out << ", File: " << filename << ", Line: " << line;
  }

  throw std::runtime_error ( out.str() );
};


///////////////////////////////////////////////////////////////////////////////
//
//  The current error callback.
//
///////////////////////////////////////////////////////////////////////////////

Errors::Callback _callback = &defaultErrorCallback;


} // namespace Details


///////////////////////////////////////////////////////////////////////////////
//
//  Get the error callback.
//
///////////////////////////////////////////////////////////////////////////////

Errors::Callback Errors::getErrorCallback()
{
  return Details::_callback;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the error callback.
//
///////////////////////////////////////////////////////////////////////////////

void Errors::setErrorCallback ( Callback callback )
{
  Details::_callback = callback;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Reset the default error callback.
//
///////////////////////////////////////////////////////////////////////////////

void Errors::setDefaultErrorCallback()
{
  Details::_callback = &Details::defaultErrorCallback;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Handle the error.
//
///////////////////////////////////////////////////////////////////////////////

void Errors::handle ( const std::string &message, const char *filename, unsigned int line, bool allowThrow )
{
  if ( Details::_callback )
  {
    if ( allowThrow )
    {
      Details::_callback ( message, filename, line );
    }
    else
    {
      USUL_TOOLS_NO_THROW ( std::bind ( Details::_callback, message, filename, line ) );
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Check for an error.
//
///////////////////////////////////////////////////////////////////////////////

void Errors::check ( bool expression, const char *filename, unsigned int line, bool allowThrow )
{
  if ( false == expression )
  {
    Errors::handle ( "Expression is false", filename, line, allowThrow );
  }
}


} // namespace Usul
