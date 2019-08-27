
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Macro for appending one token to another.
//
//  For discussion of why and when this is needed, see:
//
//  https://stackoverflow.com/questions/1597007/creating-c-macro-with-and-line-token-concatenation-with-positioning-macr
//  https://stackoverflow.com/questions/19343205/c-concatenating-file-and-line-macros/19343239
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MACROS_TOKEN_APPEND_H_
#define _USUL_MACROS_TOKEN_APPEND_H_


// This macros is the implementation details.
#define USUL_TOKEN_APPEND_DETAILS(x, y) x ## y

// This is the one to use in your code.
#define USUL_TOKEN_APPEND(x, y) USUL_TOKEN_APPEND_DETAILS(x, y)


#endif // _USUL_MACROS_TOKEN_APPEND_H_
