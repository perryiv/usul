
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
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

TEMPLATE_TEST_CASE ( "Absolute value template function with signed types", "",
  char,
  short,
  int,
  long,
  float,
  double,
  ( long double ) )
{
  typedef std::numeric_limits < TestType > Limits;

  SECTION ( "Can get the absolute value" )
  {
    // We use the numeric_limits class to get several numbers for each type.
    testAbsoluteValue ( TestType ( 1 ) );
    testAbsoluteValue ( TestType ( 10 ) );
    testAbsoluteValue ( TestType ( 100 ) );
    testAbsoluteValue ( Limits::max() );
    testAbsoluteValue ( Limits::epsilon() );
    testAbsoluteValue ( Limits::round_error() );
    testAbsoluteValue ( Limits::infinity() );
    testAbsoluteValue ( Limits::denorm_min() );
  }
}
