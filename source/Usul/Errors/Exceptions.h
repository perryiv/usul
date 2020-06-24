
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Exception classes that include a stack trace.
//  If you include this header file you will need to link to Boost.Stacktrace.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_ERRORS_EXCEPTIONS_H_
#define _USUL_ERRORS_EXCEPTIONS_H_

#include "Usul/Errors/StackTrace.h"

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
class Exception : public T
{
public:

  typedef T BaseClass;

  Exception ( const std::string &message = std::string() ) : BaseClass ( message ),
    _stack ( std::string ( "\nstack:\n" ) + Usul::Errors::StackTrace::get() )
  {
  }

  const std::string &stack() const { return _stack; }

private:

  const std::string _stack;
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
