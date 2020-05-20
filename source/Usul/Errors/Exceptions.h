
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Exception classes that can optionally include a call stack.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_ERRORS_EXCEPTIONS_H_
#define _USUL_ERRORS_EXCEPTIONS_H_

#ifdef USUL_EXCEPTIONS_USE_BOOST_STACK_TRACE
# define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
# include "boost/stacktrace.hpp"
#endif

#include <stdexcept>
#include <string>


namespace Usul {
namespace Errors {


///////////////////////////////////////////////////////////////////////////////
//
//  Template exception class.
//
///////////////////////////////////////////////////////////////////////////////

template < typename T >
class Exception
{
public:

  typedef T BaseClass;

  #ifdef USUL_EXCEPTIONS_USE_BOOST_STACK_TRACE
  typedef boost::stacktrace::stacktrace StackType;
  #else
  typedef std::string StackType;
  #endif

  Exception ( const std::string &message = std::string() ) : BaseClass ( message ) :
    _stack()
  {
  }

  const StackType &stack() const { return _stack; }

private:

  StackType _stack;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Predefined exception types.
//
///////////////////////////////////////////////////////////////////////////////

typedef Exception < std::logic_error >      LogicError;
typedef Exception < std::invalid_argument > InvalidArgument;
typedef Exception < std::domain_error >     DomainError;
typedef Exception < std::length_error >     LengthError;
typedef Exception < std::out_of_range >     OutOfRange;
typedef Exception < std::runtime_error >    RuntimeError;
typedef Exception < std::range_error >      RangeError;
typedef Exception < std::overflow_error >   OverflowError;
typedef Exception < std::underflow_error >  UnderflowError;


} // namespace Errors
} // namespace Usul


#endif // _USUL_ERRORS_EXCEPTIONS_H_
