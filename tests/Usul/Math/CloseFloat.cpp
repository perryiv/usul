
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the function(s) for floating point tolerance.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Math/CloseFloat.h"

#include "catch2/catch.hpp"

#include <limits>
#include <type_traits>


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function.
//
////////////////////////////////////////////////////////////////////////////////

template < class FloatType, class UnsignedIntegerType >
inline void isCloseFloat ( bool expected, FloatType a, FloatType b, UnsignedIntegerType numAdjacentValues )
{
  typedef std::numeric_limits < FloatType > FloatLimits;
  typedef std::numeric_limits < UnsignedIntegerType > IntegerLimits;

  static_assert ( false == FloatLimits::is_integer, "Can not be an integer type" );
  static_assert ( true == IntegerLimits::is_integer, "Has to be an integer type" );

  REQUIRE ( expected == Usul::Math::isCloseFloat ( a, b, numAdjacentValues ) );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper functions.
//
////////////////////////////////////////////////////////////////////////////////

template < class T > inline void isEqualFloat ( bool expected, T a, T b )
{
  isCloseFloat ( expected, a, b, 0 );
}
template < class T > inline void isEqualFloat ( bool expected, T value )
{
  isEqualFloat ( expected, value, value );
}
template < class T > inline void isEqualFloatPosNeg ( bool expected, T value )
{
  isEqualFloat ( expected,  value,  value );
  isEqualFloat ( expected, -value, -value );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//  https://en.cppreference.com/w/cpp/types/numeric_limits
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Tolerance function that measures closeness of non-real numbers", "",
  float, double )
{
  typedef TestType FloatType;
  typedef std::numeric_limits < FloatType > Limits;

  SECTION ( "Can compare the closeness of two non-real floating point numbers" )
  {
    isEqualFloatPosNeg (  true, Limits::min() );
    isEqualFloatPosNeg (  true, Limits::lowest() );
    isEqualFloatPosNeg (  true, Limits::max() );
    isEqualFloatPosNeg (  true, Limits::epsilon() );
    isEqualFloatPosNeg (  true, Limits::round_error() );
    isEqualFloatPosNeg (  true, Limits::infinity() );
    isEqualFloatPosNeg ( false, Limits::quiet_NaN() );
    isEqualFloatPosNeg ( false, Limits::signaling_NaN() );
    isEqualFloatPosNeg (  true, Limits::denorm_min() );
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Tolerance function that measures closeness of real numbers" )
{
  SECTION ( "Can compare the closeness of two real floating point numbers" )
  {
    isEqualFloat < float > ( true,  0.12345678 );
    isEqualFloat < float > ( true,  0.1234567 );
    isEqualFloat < float > ( true,  0.1 );
    isEqualFloat < float > ( true, -0.1 );
    isEqualFloat < float > ( true,  0 );

    isEqualFloat < double > ( true,  0.1234567890123456 );
    isEqualFloat < double > ( true,  0.123456789012345 );
    isEqualFloat < double > ( true,  0.1 );
    isEqualFloat < double > ( true, -0.1 );
    isEqualFloat < double > ( true,  0 );

    isCloseFloat < float > (  true, 0.12345678, 0.12345677, 2 );
    isCloseFloat < float > ( false, 0.12345678, 0.12345677, 1 );

    isCloseFloat < float > (  true, 0.1234567, 0.1234566, 14 );
    isCloseFloat < float > ( false, 0.1234567, 0.1234566, 13 );

    isCloseFloat < double > (  true, 0.1234567890123456, 0.1234567890123455, 7 );
    isCloseFloat < double > ( false, 0.1234567890123456, 0.1234567890123455, 6 );

    isCloseFloat < double > (  true, 0.123456789012345, 0.123456789012344, 72 );
    isCloseFloat < double > ( false, 0.123456789012345, 0.123456789012344, 71 );
  }
}
