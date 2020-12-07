
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Math/Base.h"

#include "catch2/catch.hpp"

#include <limits>


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function.
//
////////////////////////////////////////////////////////////////////////////////

template < class T > inline void testAbsoluteValue ( const T value )
{
  REQUIRE ( value == Usul::Math::abs (  value ) );
  REQUIRE ( value == Usul::Math::abs ( -value ) );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef __GNUC__
TEMPLATE_TEST_CASE ( "Absolute value template function with signed types", "",
  int, long, float, double, ( long double ) )
#else
TEMPLATE_TEST_CASE ( "Absolute value template function with signed types", "",
  char, short,
  int, long, float, double, ( long double ) )
#endif
{
  // We use the numeric_limits class to get several numbers for each type.
  typedef std::numeric_limits < TestType > Limits;

  SECTION ( "Can get the absolute value" )
  {
    testAbsoluteValue ( static_cast < TestType > ( 1 ) );
    testAbsoluteValue ( static_cast < TestType > ( 10 ) );
    testAbsoluteValue ( static_cast < TestType > ( 100 ) );
    testAbsoluteValue ( Limits::max() );
    testAbsoluteValue ( Limits::epsilon() );
    testAbsoluteValue ( Limits::round_error() );
    testAbsoluteValue ( Limits::infinity() );
    testAbsoluteValue ( Limits::denorm_min() );
  }
}


TEST_CASE ( "Clamp function" )
{
  SECTION ( "Can clamp the value" )
  {
    REQUIRE ( 0.5 == Usul::Math::clamp (  0.5, 0.0, 1.0  ) );
    REQUIRE ( 0.0 == Usul::Math::clamp ( -0.5, 0.0, 1.0  ) );
    REQUIRE ( 1.0 == Usul::Math::clamp (  1.5, 0.0, 1.0  ) );

    REQUIRE ( 0.5f == Usul::Math::clamp (  0.5f, 0.0f, 1.0f  ) );
    REQUIRE ( 0.0f == Usul::Math::clamp ( -0.5f, 0.0f, 1.0f  ) );
    REQUIRE ( 1.0f == Usul::Math::clamp (  1.5f, 0.0f, 1.0f  ) );

    REQUIRE (  5 == Usul::Math::clamp (  5, 0, 10 ) );
    REQUIRE (  0 == Usul::Math::clamp ( -5, 0, 10 ) );
    REQUIRE ( 10 == Usul::Math::clamp ( 15, 0, 10 ) );
  }
}
