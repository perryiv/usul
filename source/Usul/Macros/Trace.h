
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Macro for using std::cout only in debug build.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MACROS_TRACE_H_
#define _USUL_MACROS_TRACE_H_


#include <iostream>


#ifdef _DEBUG
  #define USUL_TRACE std::cout
#else
  #define USUL_TRACE if ( false ) std::cout
#endif


#endif // _USUL_MACROS_TRACE_H_
