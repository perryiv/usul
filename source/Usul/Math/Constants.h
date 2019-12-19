
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Constant values.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_CONSTANTS_H_
#define _USUL_MATH_CONSTANTS_H_


namespace Usul {
namespace Math {


// Unit conversions.
constexpr double RAD_TO_DEG   ( 57.295779513082320876798161804285 );
constexpr double DEG_TO_RAD   ( 0.017453292519943295769236905555556 );

// Trig.
constexpr double PI           ( 3.141592653589793238462643 );
constexpr double PI_OVER_2    ( Usul::Math::PI / 2.0 );
constexpr double TWO_PI       ( Usul::Math::PI * 2.0 );

// Square root.
constexpr double SQRT_2       ( 1.41421356237309504880 );
constexpr double SQRT_3       ( 1.73205080757 );
constexpr double INV_SQRT_2   ( 0.70710678118654752440 );


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_CONSTANTS_H_
