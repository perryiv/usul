
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

#include "Usul/Math/CloseFloat.h"
#include "Usul/Math/Constants.h"
#include "Usul/Math/Functions.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Misc template math functions with floating point types", "",
  float, double, ( long double ) )
{
  SECTION ( "Can convert radians to degrees" )
  {
    REQUIRE ( ( static_cast < TestType > ( 180 ) ) == Usul::Math::radToDeg ( static_cast < TestType > ( Usul::Math::PI ) ) );
  }

  SECTION ( "Can convert degrees to radians" )
  {
    REQUIRE ( ( static_cast < TestType > ( Usul::Math::PI ) ) == Usul::Math::degToRad ( static_cast < TestType > ( 180 ) ) );
  }

  SECTION ( "Can round to the nearest decimal" )
  {
    const TestType value = static_cast < TestType > ( 10.123456789 );
    REQUIRE ( Usul::Math::round ( static_cast < TestType > ( value ), 1 ) == 10.1 );
    REQUIRE ( Usul::Math::round ( static_cast < TestType > ( value ), 2 ) == 10.12 );
    REQUIRE ( Usul::Math::round ( static_cast < TestType > ( value ), 3 ) == 10.123 );
    REQUIRE ( Usul::Math::round ( static_cast < TestType > ( value ), 4 ) == 10.1235 );
    REQUIRE ( Usul::Math::round ( static_cast < TestType > ( value ), 5 ) == 10.12346 );
    REQUIRE ( Usul::Math::round ( static_cast < TestType > ( value ), 6 ) == 10.123467 );
    REQUIRE ( Usul::Math::round ( static_cast < TestType > ( value ), 7 ) == 10.1234678 );
    REQUIRE ( Usul::Math::round ( static_cast < TestType > ( value ), 8 ) == 10.12346789 );
  }
}
