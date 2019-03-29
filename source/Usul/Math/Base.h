
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Basic math functions that should be in cmath but are not.
//  I wish this file were not needed.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_MISSING_BASIC_FUNCTION_H_
#define _USUL_MATH_MISSING_BASIC_FUNCTION_H_

#include <cmath>
#include <type_traits>


namespace Usul {
namespace Math {


///////////////////////////////////////////////////////////////////////////////
//
//  Return the absolute value.
//
///////////////////////////////////////////////////////////////////////////////

template < class T > inline T absolute ( T value )
{
  static_assert ( std::is_arithmetic < T >::value, "Not an arithmetic type" );
  static_assert ( std::is_signed < T >::value, "Not a signed number" );
  return ( ( value < 0 ) ? ( -value ) : value );
}
template < class T > inline T abs ( T value )
{
  return absolute ( value );
}


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_MISSING_BASIC_FUNCTION_H_
