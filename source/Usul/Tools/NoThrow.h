
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

#include "Usul/Errors//Handler.h"

#include <stdexcept>


namespace Usul {
namespace Tools {


///////////////////////////////////////////////////////////////////////////////
//
//  Convenience function for making non-throwing function call.
//
///////////////////////////////////////////////////////////////////////////////

template < class F > void noThrow ( F function, const char *filename, unsigned int line )
{
  // If there is an exception then we call the error handler.
  // However, we prevent the error handler from throwing its own exception.
  const bool allowThrow ( false );

  try
  {
    function();
  }
  catch ( const std::exception &e )
  {
    Usul::Errors::handle ( e.what(), filename, line, allowThrow );
  }
  catch ( ... )
  {
    Usul::Errors::handle ( "Unknown exception caught", filename, line, allowThrow );
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
