
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

#include <iostream>
#include <stdexcept>


namespace Usul {
namespace Tools {


///////////////////////////////////////////////////////////////////////////////
//
//  Convenience function that prevents any exception from propagating.
//
///////////////////////////////////////////////////////////////////////////////

template < class F > bool noThrow ( F function, const char *filename, unsigned int line, std::ostream *out = nullptr )
{
  // Set the output stream if we were not given one.
  if ( nullptr == out )
  {
    out = &std::clog;
  }

  // Try to call the function. We return true if it worked.
  try
  {
    function();
    return true;
  }

  // If the user wants to capture this error they can redirect stderr.
  // We output one string because that works best when multi-threaded.

  catch ( const std::exception &e )
  {
    *out << ( Usul::Strings::format (
      "Standard exception caught: ", e.what(),
      ", File: ", filename,
      ", Line: ", line
    ) ) << std::endl;
  }

  catch ( ... )
  {
    *out << ( Usul::Strings::format (
      "Unknown exception caught",
      ", File: ", filename,
      ", Line: ", line
    ) ) << std::endl;
  }

  // If we get to here then it did not work.
  return false;
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


#endif // _USUL_TOOLS_NO_THROW_H_
