
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
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
  #if ( _MSVC_LANG < 201402L )
    #define USUL_CPP_STANDARD 11
  #elif ( _MSVC_LANG == 201402L )
    #define USUL_CPP_STANDARD 14
  #elif ( _MSVC_LANG == 201703L )
    #define USUL_CPP_STANDARD 17
  #else
    #define USUL_CPP_STANDARD -1
  #endif
#else
  #if ( __cplusplus < 201402L )
    #define USUL_CPP_STANDARD 11
  #elif ( __cplusplus == 201402L )
    #define USUL_CPP_STANDARD 14
  #elif ( __cplusplus == 201703L )
    #define USUL_CPP_STANDARD 17
  #else
    #define USUL_CPP_STANDARD -1
  #endif
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
