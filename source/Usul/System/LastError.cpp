
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Class that represents the system's per-thread last error.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/System/LastError.h"
#include "Usul/Tools/Cast.h"

#include <algorithm>
#include <cerrno>  // For errno
#include <cstring> // For strerror()
#include <type_traits>

#ifdef _WIN32
# define NOMINMAX
# define VC_EXTRALEAN
# define WIN32_LEAN_AND_MEAN
# include <windows.h> // For GetLastError()
#else
# include <dlfcn.h>   // For dlerror()
#endif

namespace Usul {
namespace System {


///////////////////////////////////////////////////////////////////////////////
//
//  Initialize the last error.
//
///////////////////////////////////////////////////////////////////////////////

void LastError::init()
{
  // Initialize standard error number.
  errno = 0;

#ifdef _WIN32

  // This will make ::GetLastError() return ERROR_SUCCESS.
  ::SetLastError ( ERROR_SUCCESS );

#else

  // This will make subsequent calls to dlerror() return null.
  ::dlerror();

#endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the number of the last error.
//
///////////////////////////////////////////////////////////////////////////////

LastError::Number LastError::number()
{
#ifdef _WIN32

  static_assert ( std::is_same < DWORD, unsigned long >::value, "Types are not identical" );
  static_assert ( std::is_same < DWORD, LastError::Number >::value, "Types are not identical" );

  // Getting also initializes, so we have to immediately set again.
  const DWORD error ( ::GetLastError() );
  ::SetLastError ( error );

  // Return error.
  return error;

#else

  static_assert ( std::is_same < int, LastError::Number >::value, "Types are not identical" );
  return errno;

#endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the last error message.
//
///////////////////////////////////////////////////////////////////////////////

std::string LastError::message()
{
  return LastError::message ( LastError::number() );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the last error message.
//
///////////////////////////////////////////////////////////////////////////////

std::string LastError::message ( Number number )
{
#ifdef _WIN32

  // The buffer to write to. It will be allocated.
  LPVOID buffer ( nullptr );

  // Format the message.
  ::FormatMessage (
    FORMAT_MESSAGE_ALLOCATE_BUFFER |
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    nullptr,
    number,
    MAKELANGID ( LANG_NEUTRAL, SUBLANG_DEFAULT ), // Default language.
    Usul::Tools::unsafeCast < LPTSTR > ( &buffer ),
    0,
    nullptr );

  // Copy the message.
  std::string message ( buffer ? reinterpret_cast < LPCTSTR > ( buffer ) : "" );

  // Free the buffer.
  ::LocalFree ( buffer );

  // Remove all carriage-return characters.
  message.erase ( std::remove ( message.begin(), message.end(), '\r' ), message.end() );

  // Remove all trailing new-line characters.
  while ( ( false == message.empty() ) && ( '\n' == message.at ( message.size() - 1 ) ) )
  {
    message.erase ( message.size() - 1 );
  }

  // Return the message.
  return message;

#else

  // First, see if the error is from loading a dynamic library.
  const char *buf = ::dlerror();

  // If so, then return it.
  if ( buf )
  {
    return std::string ( buf );
  }

  // Otherwise, get the message associated with the current error number.
  buf = std::strerror ( number );

  // Return the error message. Handle the null case.
  return std::string ( ( buf ) ? buf : "" );

#endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Is there an error?
//
///////////////////////////////////////////////////////////////////////////////

bool LastError::has()
{
#ifdef _WIN32

  const DWORD error ( LastError::number() );
  return ( ERROR_SUCCESS != error );

#else

  return ( 0 != errno );

#endif
}


} // namespace System
} // namespace Usul
