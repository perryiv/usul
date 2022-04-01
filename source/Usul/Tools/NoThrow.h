
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
  template < class IdType, class OutputStream >
  inline void logStandardException ( const std::exception &e, IdType id, OutputStream *out )
  {
    if ( out )
    {
      // We output one string because that works best when multi-threaded.
      *out << ( Usul::Strings::format (
        "Standard exception caught",
        ", ID: ", id,
        ", ", e.what()
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
  template < class IdType, class OutputStream >
  inline void logUnknownException ( IdType id, OutputStream *out )
  {
    if ( out )
    {
      // We output one string because that works best when multi-threaded.
      *out << ( Usul::Strings::format (
        "Unknown exception caught",
        ", ID: ", id
      ) ) << std::endl;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Convenience function that prevents any exception from propagating.
//
///////////////////////////////////////////////////////////////////////////////

template < class IdType, class Function, class OutputStream >
inline bool noThrow ( IdType id, Function function, OutputStream *out )
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
    Details::logStandardException ( e, id, out );
  }

  catch ( ... )
  {
    Details::logUnknownException ( id, out );
  }

  // If we get to here then it did not work.
  return false;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Helping the compiler ...
//
///////////////////////////////////////////////////////////////////////////////

template < class IdType, class Function >
inline bool noThrow ( IdType id, Function function )
{
  std::ostream *stream = nullptr;
  return noThrow ( id, function, stream );
}


} // namespace Tools
} // namespace Usul


///////////////////////////////////////////////////////////////////////////////
//
//  Convenience macro.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_TOOLS_NO_THROW(id,function) \
  Usul::Tools::noThrow ( id, function, &std::clog )


///////////////////////////////////////////////////////////////////////////////
//
//  Macro used to catch all exceptions and log them.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_TOOLS_CATCH_AND_LOG(id,stream) \
  catch ( const std::exception &e ) \
  { \
    Usul::Tools::Details::logStandardException ( e, id, stream ); \
  } \
  catch ( ... ) \
  { \
    Usul::Tools::Details::logUnknownException ( id, stream ); \
  }


#endif // _USUL_TOOLS_NO_THROW_H_
