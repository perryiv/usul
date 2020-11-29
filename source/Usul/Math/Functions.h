
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Misc math functions.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_MISC_FUNCTIONS_H_
#define _USUL_MATH_MISC_FUNCTIONS_H_

#include "Usul/Math/Constants.h"

#include <cmath>
#include <type_traits>


namespace Usul {
namespace Math {


///////////////////////////////////////////////////////////////////////////////
//
//  Round to the nearest decimal.
//  https://stackoverflow.com/questions/1343890/rounding-number-to-2-decimal-places-in-c
//
///////////////////////////////////////////////////////////////////////////////

template < class FloatType, class UnsignedInteger >
inline FloatType round ( const FloatType value, const UnsignedInteger numDecimals )
{
  const FloatType factor = static_cast < FloatType > ( std::pow ( 10, numDecimals ) );
  return static_cast < FloatType > ( std::round ( value * factor ) / factor );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Truncate to the nearest decimal.
//  https://stackoverflow.com/questions/1343890/rounding-number-to-2-decimal-places-in-c
//
///////////////////////////////////////////////////////////////////////////////

template < class FloatType, class UnsignedInteger >
inline FloatType trunc ( const FloatType value, const UnsignedInteger numDecimals )
{
  const FloatType factor = static_cast < FloatType > ( std::pow ( 10, numDecimals ) );
  return static_cast < FloatType > ( std::trunc ( value * factor ) / factor );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Convert the angle.
//
///////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline ScalarType radToDeg ( const ScalarType angle )
{
  return ( angle * ( static_cast < ScalarType > ( Usul::Math::RAD_TO_DEG ) ) );
}
template < class ScalarType > inline ScalarType degToRad ( const ScalarType angle )
{
  return ( angle * ( static_cast < ScalarType > ( Usul::Math::DEG_TO_RAD ) ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return e^(-u)
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
inline T decay ( T u )
{
  static_assert ( std::is_floating_point < T >::value, "Not a floating point type" );

  // Keep the compiler happy.
  const T zero   ( static_cast < T > (  0 ) );
  const T one    ( static_cast < T > (  1 ) );
  const T three  ( static_cast < T > (  3 ) );
  const T six    ( static_cast < T > (  6 ) );
  const T twenty ( static_cast < T > ( 20 ) );

  // Handle when input is out of range.
  if ( u < zero )
  {
    return zero;
  }
  if ( u > one )
  {
    return one;
  }

  // See http://www.wolframalpha.com/input/?i=y%3De^-x
  u *= six;
  u -= three;
  u = std::exp ( -u );
  u /= twenty;

  // Return modified value.
  return u;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Fix the given angle by keeping it in the given range.
//  http://stackoverflow.com/questions/1628386/normalise-orientation-between-0-and-360
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
inline T fixAngle ( const T &angle, const T &low, const T &high )
{
  const T width = high - low;
  const T offsetValue = angle - low;
  return ( offsetValue - ( std::floor ( offsetValue / width ) * width ) ) + low;
}


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_MISC_FUNCTIONS_H_
