
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

#ifndef _USUL_ERRORS_HANDLER_H_
#define _USUL_ERRORS_HANDLER_H_

#include "Usul/Export.h"

#include <string>


namespace Usul {


struct USUL_EXPORT Errors
{
  // The error callback type.
  typedef void ( *Callback ) ( const std::string &message, const char *filename, unsigned int line );

  // Get the error callback.
  static Callback getErrorCallback();

  // Set the error callback.
  static void setErrorCallback ( Callback callback );

  // Reset the default error callback.
  static void setDefaultErrorCallback();

  // Handle the error.
  static void handle ( const std::string &message, const char *filename = nullptr, unsigned int line = 0, bool allowThrow = true );

  // Check for an error and handle it if needed.
  static void check ( bool expression, const char *filename = nullptr, unsigned int line = 0, bool allowThrow = true );
};


} // namespace Usul


// Macro that makes it easier to pass the file and line number.
#define USUL_ERROR_HANDLER(message)\
  Usul::Errors::handle ( message, __FILE__, __LINE__, true )

#define USUL_ERROR_CHECKER(expression)\
  Usul::Errors::check ( expression, __FILE__, __LINE__, true )

#define USUL_ERROR_CHECKER_NO_THROW(expression)\
  Usul::Errors::check ( expression, __FILE__, __LINE__, false )

#endif // _USUL_ERRORS_HANDLER_H_
