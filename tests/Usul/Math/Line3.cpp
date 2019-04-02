
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

#include "Usul/Math/Functions.h"
#include "Usul/Math/Line3.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Line3 template math functions", "",
  float, double, ( long double ) )
{
  typedef typename Usul::Math::Line3 < TestType > LineType;
  typedef typename LineType::Point PointType;
  typedef typename LineType::Vec VecType;

  SECTION ( "Default constructor works" )
  {
    const LineType a;

    REQUIRE (  0 == a[0][0] );
    REQUIRE (  0 == a[0][1] );
    REQUIRE (  0 == a[0][2] );

    REQUIRE (  0 == a[1][0] );
    REQUIRE (  0 == a[1][1] );
    REQUIRE ( -1 == a[1][2] );

    REQUIRE ( Usul::Math::equal (
      LineType ( PointType ( 0, 0, 0 ), PointType ( 0, 0, -1 ) ), a )
    );
  }

  SECTION ( "Constructor that takes 2 points works" )
  {
    const LineType a ( PointType ( 1, 2, 3 ), PointType ( 4, 5, 6 ) );

    REQUIRE ( 1 == a[0][0] );
    REQUIRE ( 2 == a[0][1] );
    REQUIRE ( 3 == a[0][2] );

    REQUIRE ( 4 == a[1][0] );
    REQUIRE ( 5 == a[1][1] );
    REQUIRE ( 6 == a[1][2] );
  }

  SECTION ( "Copy constructor works" )
  {
    LineType a ( PointType ( 1, 2, 3 ), PointType ( 4, 5, 6 ) );
    const LineType b ( a ); // Copy constructor.

    // Should be the same.
    REQUIRE ( a[0][0] == b[0][0] );
    REQUIRE ( a[0][1] == b[0][1] );
    REQUIRE ( a[0][2] == b[0][2] );

    REQUIRE ( a[1][0] == b[1][0] );
    REQUIRE ( a[1][1] == b[1][1] );
    REQUIRE ( a[1][2] == b[1][2] );

    // Is it different memory?
    a[0][0] = 8; // Changing one value.
    REQUIRE ( 8 == a[0][0] ); // It should be different.
    REQUIRE ( 1 == b[0][0] ); // It should be original value.
  }

  SECTION ( "Equal lines are equal" )
  {
    REQUIRE ( true == Usul::Math::equal ( LineType(), LineType() ) );
  }

  SECTION ( "Different lines are not equal" )
  {
    LineType a ( PointType ( 1, 2, 3 ), PointType ( 4, 5, 6 ) );
    LineType b ( PointType ( 4, 5, 6 ), PointType ( 7, 8, 9 ) );
    REQUIRE ( false == Usul::Math::equal ( a, b ) );
  }

  SECTION ( "Assigning is making a copy" )
  {
    LineType a ( PointType ( 1, 2, 3 ), PointType ( 4, 5, 6 ) );
    const LineType b = a; // Assignment operator.

    // Should be the same.
    REQUIRE ( a[0][0] == b[0][0] );
    REQUIRE ( a[0][1] == b[0][1] );
    REQUIRE ( a[0][2] == b[0][2] );

    REQUIRE ( a[1][0] == b[1][0] );
    REQUIRE ( a[1][1] == b[1][1] );
    REQUIRE ( a[1][2] == b[1][2] );

    // Is it different memory?
    a[0][0] = 8; // Changing one value.
    REQUIRE ( 8 == a[0][0] ); // It should be different.
    REQUIRE ( 1 == b[0][0] ); // It should be original value.
  }

  SECTION ( "Setter functions work" )
  {
    LineType a, b;
    REQUIRE ( Usul::Math::equal ( a, b ) );

    REQUIRE (  0 == a[0][0] );
    REQUIRE (  0 == a[0][1] );
    REQUIRE (  0 == a[0][2] );

    REQUIRE (  0 == a[1][0] );
    REQUIRE (  0 == a[1][1] );
    REQUIRE ( -1 == a[1][2] );

    a.set ( LineType ( PointType ( 1, 2, 3 ), PointType ( 4, 5, 6 ) ) );
    REQUIRE ( false == Usul::Math::equal ( a, b ) );

    REQUIRE ( 1 == a[0][0] );
    REQUIRE ( 2 == a[0][1] );
    REQUIRE ( 3 == a[0][2] );

    REQUIRE ( 4 == a[1][0] );
    REQUIRE ( 5 == a[1][1] );
    REQUIRE ( 6 == a[1][2] );
  }

  SECTION ( "Set the line from an origin and direction" )
  {
    LineType a;
    a.setFromOriginAndDirection ( PointType ( 1, 2, 3 ), VecType ( 1, 2, 3 ) );

    LineType b ( PointType ( 1, 2, 3 ), PointType ( 2, 4, 6 ) );
    REQUIRE ( Usul::Math::equal ( a, b ) );
  }

  SECTION ( "Return the origin" )
  {
    const PointType origin ( 1, 2, 3 );
    LineType a ( origin, PointType ( 2, 4, 6 ) );
    REQUIRE ( Usul::Math::equal ( origin, a.getOrigin() ) );
  }

  SECTION ( "Return the direction vector" )
  {
    LineType a;
    const PointType dir ( 2, 4, 6 );
    a.setFromOriginAndDirection ( PointType ( 1, 2, 3 ), dir );
    REQUIRE ( Usul::Math::equal ( dir, a.getDirection() ) );
  }

  SECTION ( "Return the unit direction vector" )
  {
    LineType a;
    const PointType dir ( 1, 2, 3 );
    a.setFromOriginAndDirection ( PointType ( 1, 2, 3 ), dir );
    REQUIRE ( Usul::Math::equal ( Usul::Math::normalize ( dir ), a.getUnitDirection() ) );
  }
}
