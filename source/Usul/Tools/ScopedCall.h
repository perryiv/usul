
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Scoped function call.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_TOOLS_SCOPED_CALL_H_
#define _USUL_TOOLS_SCOPED_CALL_H_

#include "Usul/Macros/TokenAppend.h"
#include "Usul/Tools/NoCopying.h"

#include <functional>


namespace Usul {
namespace Tools {


struct ScopedCall : public Usul::Tools::NoCopying
{
  typedef std::function < void() > Fun;

  ScopedCall ( const Fun &fun ) :
    _fun ( fun )
  {
  }

  ~ScopedCall()
  {
    _fun();
  }

private:

  Fun _fun;
};


} // namespace Tools
} // namespace Usul


// This is the helper macro to use in your code.
#define USUL_SCOPED_CALL(fun)\
  Usul::Tools::ScopedCall USUL_TOKEN_APPEND ( scoped_call_at_line_, __LINE__ ) ( fun )


#endif // _USUL_TOOLS_SCOPED_CALL_H_
