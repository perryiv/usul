
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

#ifndef _USUL_FUNCTIONS_NO_THROW_H_
#define _USUL_FUNCTIONS_NO_THROW_H_

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

template < class F > void noThrow ( F function, const char *filename, unsigned int line )
{
  try
  {
    function();
  }

  // If the user wants to capture this error they can redirect stderr.
  // We output one string because that works best when multi-threaded.

  catch ( const std::exception &e )
  {
    std::clog << ( Usul::Strings::format (
      "Standard exception caught: ", e.what(),
      ", File: ", filename,
      ", Line: ", line
    ) ) << std::endl;
  }

  catch ( ... )
  {
    std::clog << ( Usul::Strings::format (
      "Unknown exception caught",
      ", File: ", filename,
      ", Line: ", line
    ) ) << std::endl;
  }
}


} // namespace Tools
} // namespace Usul


///////////////////////////////////////////////////////////////////////////////
//
//  Convenience macro that adds the file name and line number.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_TOOLS_NO_THROW(function) \
  Usul::Tools::noThrow ( function, __FILE__, __LINE__ )


#endif // _USUL_FUNCTIONS_NO_THROW_H_
