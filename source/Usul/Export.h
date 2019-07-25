
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Defines what USUL_EXPORT means.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_DLL_EXPORT_H_
#define _USUL_DLL_EXPORT_H_

#ifndef USUL_STATIC_DEFINE
# ifdef _WIN32
#  ifdef COMPILING_USUL
#   define USUL_EXPORT __declspec ( dllexport ) // We are compiling this library so the classes are exported.
#  else
#   define USUL_EXPORT __declspec ( dllimport ) // The classes will be imported into the client's code.
#  endif
# else
#  ifdef COMPILING_USUL
#   define USUL_EXPORT __attribute__ (( visibility ( "default" ) ))
#  endif
# endif
#endif

#ifndef USUL_EXPORT
# define USUL_EXPORT
#endif

#endif // _USUL_DLL_EXPORT_H_
