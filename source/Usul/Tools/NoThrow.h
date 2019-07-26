
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Wraps a function call with a try-catch block.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_TOOLS_NO_THROW_H_
#define _USUL_TOOLS_NO_THROW_H_

#include "Usul/Strings/Format.h"

#include <stdexcept>
#include <iostream> // The macro below uses std::clog.


namespace Usul {
namespace Tools {


///////////////////////////////////////////////////////////////////////////////
//
//  Helper function for logging a standard exception.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class OutputStream >
  inline void logStandardException ( const std::exception &e, const char *filename, unsigned int line, OutputStream *out )
  {
    if ( out )
    {
      // We output one string because that works best when multi-threaded.
      *out << ( Usul::Strings::format (
        "Standard exception caught: ", e.what(),
        ", File: ", filename,
        ", Line: ", line
      ) ) << std::endl;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Helper function for logging an unknown exception.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class OutputStream >
  inline void logUnknownException ( const char *filename, unsigned int line, OutputStream *out )
  {
    if ( out )
    {
      // We output one string because that works best when multi-threaded.
      *out << ( Usul::Strings::format (
        "Unknown exception caught",
        ", File: ", filename,
        ", Line: ", line
      ) ) << std::endl;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Convenience function that prevents any exception from propagating.
//
///////////////////////////////////////////////////////////////////////////////

template < class Function, class OutputStream >
inline bool noThrow ( Function function, const char *filename, unsigned int line, OutputStream *out )
{
  // Try to call the function. We return true if it worked.
  try
  {
    function();
    return true;
  }

  // To capture this error pass an appropriate stream.
  // We output one string because that works best when multi-threaded.

  catch ( const std::exception &e )
  {
    Details::logStandardException ( e, filename, line, out );
  }

  catch ( ... )
  {
    Details::logUnknownException ( filename, line, out );
  }

  // If we get to here then it did not work.
  return false;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Helping the compiler ...
//
///////////////////////////////////////////////////////////////////////////////

template < class Function >
inline bool noThrow ( Function function, const char *filename, unsigned int line )
{
  std::ostream *stream = nullptr;
  return noThrow ( function, filename, line, stream );
}


} // namespace Tools
} // namespace Usul


///////////////////////////////////////////////////////////////////////////////
//
//  Convenience macro that adds the file name and line number.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_TOOLS_NO_THROW(function) \
  Usul::Tools::noThrow ( function, __FILE__, __LINE__, &std::clog )


///////////////////////////////////////////////////////////////////////////////
//
//  Macro used to catch all exceptions and log them.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_TOOLS_CATCH_AND_LOG(stream) \
  catch ( const std::exception &e ) \
  { \
    Usul::Tools::Details::logStandardException ( e, __FILE__, __LINE__, stream ); \
  } \
  catch ( ... ) \
  { \
    Usul::Tools::Details::logUnknownException ( __FILE__, __LINE__, stream ); \
  }


#endif // _USUL_TOOLS_NO_THROW_H_
