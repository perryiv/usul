
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

#include "Usul/Math/Constants.h"
#include "Usul/Math/Functions.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Misc template math functions with floating point types", "",
  float, double )
{
  SECTION ( "Can convert radians to degrees" )
  {
    {
      const TestType deg1 ( 180 );
      const TestType rad ( Usul::Math::PI );
      const TestType deg2 ( Usul::Math::radToDeg ( rad ) );
      REQUIRE ( deg1 == deg2 );
    }
    {
      const TestType deg1 ( 90 );
      const TestType rad ( Usul::Math::PI_OVER_2 );
      const TestType deg2 ( Usul::Math::radToDeg ( rad ) );
      REQUIRE ( deg1 == deg2 );
    }
    {
      const TestType deg1 ( 45 );
      const TestType rad ( Usul::Math::PI_OVER_2 / 2 );
      const TestType deg2 ( Usul::Math::radToDeg ( rad ) );
      REQUIRE ( deg1 == deg2 );
    }
  }

  SECTION ( "Can convert degrees to radians" )
  {
    {
      const TestType rad1 ( Usul::Math::PI );
      const TestType deg ( 180 );
      const TestType rad2 ( Usul::Math::degToRad ( deg ) );
      REQUIRE ( rad1 == rad2 );
    }
    {
      const TestType rad1 ( Usul::Math::PI_OVER_2 );
      const TestType deg ( 90 );
      const TestType rad2 ( Usul::Math::degToRad ( deg ) );
      REQUIRE ( rad1 == rad2 );
    }
    {
      const TestType rad1 ( Usul::Math::PI_OVER_2 / 2 );
      const TestType deg ( 45 );
      const TestType rad2 ( Usul::Math::degToRad ( deg ) );
      REQUIRE ( rad1 == rad2 );
    }
  }

  SECTION ( "Can round to the nearest decimal" )
  {
    const TestType value = static_cast < TestType > ( 10.123456789 );
    REQUIRE ( Usul::Math::round ( value, 1 ) == static_cast < TestType > ( 10.1 ) );
    REQUIRE ( Usul::Math::round ( value, 2 ) == static_cast < TestType > ( 10.12 ) );
    REQUIRE ( Usul::Math::round ( value, 3 ) == static_cast < TestType > ( 10.123 ) );
    REQUIRE ( Usul::Math::round ( value, 4 ) == static_cast < TestType > ( 10.1235 ) );
    REQUIRE ( Usul::Math::round ( value, 5 ) == static_cast < TestType > ( 10.12346 ) );
    REQUIRE ( Usul::Math::round ( value, 6 ) == static_cast < TestType > ( 10.123457 ) );
    REQUIRE ( Usul::Math::round ( value, 7 ) == static_cast < TestType > ( 10.1234568 ) );
    REQUIRE ( Usul::Math::round ( value, 8 ) == static_cast < TestType > ( 10.12345679 ) );
  }

  SECTION ( "Can truncate to the nearest decimal" )
  {
    const TestType value = static_cast < TestType > ( 10.123456789 );
    REQUIRE ( Usul::Math::trunc ( value, 1 ) == static_cast < TestType > ( 10.1 ) );
    REQUIRE ( Usul::Math::trunc ( value, 2 ) == static_cast < TestType > ( 10.12 ) );
    REQUIRE ( Usul::Math::trunc ( value, 3 ) == static_cast < TestType > ( 10.123 ) );
    REQUIRE ( Usul::Math::trunc ( value, 4 ) == static_cast < TestType > ( 10.1234 ) );
    REQUIRE ( Usul::Math::trunc ( value, 5 ) == static_cast < TestType > ( 10.12345 ) );
    // REQUIRE ( Usul::Math::trunc ( value, 6 ) == static_cast < TestType > ( 10.123456 ) ); // Does not work for type float.
    REQUIRE ( Usul::Math::trunc ( value, 7 ) == static_cast < TestType > ( 10.1234567 ) );
    REQUIRE ( Usul::Math::trunc ( value, 8 ) == static_cast < TestType > ( 10.12345678 ) );
  }
}
