
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Compile-time definitions.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_COMPILE_TIME_DEFINITIONS_H_
#define _USUL_COMPILE_TIME_DEFINITIONS_H_


///////////////////////////////////////////////////////////////////////////////
//
//  Determine the standard being used.
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _MSVC_LANG
  #define USUL_CPP_STANDARD_FULL _MSVC_LANG
#else
  #define USUL_CPP_STANDARD_FULL __cplusplus
#endif

#if ( USUL_CPP_STANDARD_FULL >= 202002L )
  #define USUL_CPP_STANDARD 20
#elif ( USUL_CPP_STANDARD_FULL >= 201703L )
  #define USUL_CPP_STANDARD 17
#elif ( USUL_CPP_STANDARD_FULL >= 201402L )
  #define USUL_CPP_STANDARD 14
#elif ( USUL_CPP_STANDARD_FULL >= 201103L )
  #define USUL_CPP_STANDARD 11
#else
  #define USUL_CPP_STANDARD -1
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  Make sure we set a valid standard.
//
///////////////////////////////////////////////////////////////////////////////

#if ( USUL_CPP_STANDARD == -1 )
  #ifdef _DEBUG
    #error Unknown C++ standard
  #endif
#endif


#endif // _USUL_COMPILE_TIME_DEFINITIONS_H_
