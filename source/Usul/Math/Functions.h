
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


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_MISC_FUNCTIONS_H_
