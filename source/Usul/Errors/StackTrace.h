
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Return a stack trace as a string.
//  If you include this header file you will need to link to Boost.Stacktrace.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_ERRORS_STACK_TRACE_H_
#define _USUL_ERRORS_STACK_TRACE_H_

#ifdef _WIN32
# define NOMINMAX
# define VC_EXTRALEAN
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif

#define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
#include "boost/stacktrace.hpp"

#include <sstream>
#include <string>


namespace Usul {
namespace Errors {
namespace StackTrace {


inline std::string get()
{
  std::ostringstream out;
  out << boost::stacktrace::stacktrace();
  return out.str();
}

inline std::string get ( unsigned int index )
{
  std::ostringstream out;
  out << boost::stacktrace::stacktrace().as_vector().at ( index );
  return out.str();
}


} // namespace StackTrace
} // namespace Errors
} // namespace Usul


#endif // _USUL_ERRORS_STACK_TRACE_H_
