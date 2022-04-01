
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

#include <iostream>
#include <stdexcept>
#include <sstream>


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
//  Handle no message
//
///////////////////////////////////////////////////////////////////////////////

namespace Usul
{
  namespace Errors
  {
    namespace Details
    {
      inline std::string getMessage ( const std::string &message, const char *file, unsigned int line )
      {
        if ( true == message.empty() )
        {
          std::ostringstream out;
          out << "Expression is false";
          out << ", line: " << line;
          out << ", file: " << ( ( nullptr == file ) ? "" : file );
          return out.str();
        }
        else
        {
          return message;
        }
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Throw an exception if the expression is false.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_CHECK_AND_THROW(expression,message) \
  if ( false == ( expression ) ) \
  { \
    throw std::runtime_error ( Usul::Errors::Details::getMessage ( message, __FILE__, __LINE__ ) ); \
  }


///////////////////////////////////////////////////////////////////////////////
//
//  Throw an error if the expression is false, but only in a debug build.
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define USUL_CHECK_AND_THROW_DEBUG(expression,message) USUL_CHECK_AND_THROW ( expression, message )
#else
#define USUL_CHECK_AND_THROW_DEBUG(expression,message)
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  Log an error if the expression is false.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_CHECK_AND_LOG(expression,message) \
if ( false == ( expression ) ) \
{ \
  std::clog << ( Usul::Errors::Details::getMessage ( message, __FILE__, __LINE__ ) + "\n" ) << std::flush; \
}


///////////////////////////////////////////////////////////////////////////////
//
//  Log an error if the expression is false, but only in a debug build.
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define USUL_CHECK_AND_LOG_DEBUG(expression,message) USUL_CHECK_AND_LOG ( expression, message )
#else
#define USUL_CHECK_AND_LOG_DEBUG(expression,message)
#endif


#endif // _USUL_ERRORS_CHECK_H_
