
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Error-checking macros.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_ERRORS_CHECK_H_
#define _USUL_ERRORS_CHECK_H_

// Put these in the source files that actually use these macros.
// #include "Usul/Strings/Format.h"
// #include <iostream>
// #include <stdexcept>


///////////////////////////////////////////////////////////////////////////////
//
//  See if the index is in range.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_CHECK_INDEX_RANGE(size,index,message) \
{ \
  if ( ( index < 0 ) || ( index >= size ) ) \
  { \
    throw std::out_of_range ( message ); \
  } \
}


///////////////////////////////////////////////////////////////////////////////
//
//  Throw an exception if the expression is false.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_CHECK_AND_THROW(expression) \
  if ( false == expression ) \
  { \
    throw std::runtime_error ( Usul::Strings::format ( "Expression is false", \
      ", File: ", __FILE__, \
      ", Line: ", __LINE__ \
    ) ); \
  }


///////////////////////////////////////////////////////////////////////////////
//
//  Log an error if the expression is false.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_CHECK_AND_LOG(expression)\
if ( false == expression ) \
{ \
  std::clog << ( Usul::Strings::format ( "Expression is false", \
    ", File: ", __FILE__, \
    ", Line: ", __LINE__ \
  ) ) << std::endl; \
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the default error checker.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_CHECK USUL_CHECK_AND_THROW


#endif // _USUL_ERRORS_CHECK_H_
