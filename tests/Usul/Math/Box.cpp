
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the bounds class.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Math/Box.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the bounds.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Box class", "",
  float,
  double,
  ( long double ) )
{
  typedef Usul::Math::Box < TestType > Box;
  typedef typename Box::Vec3 Vec3;
  typedef typename Box::Limits Limits;

  constexpr Vec3 defaultMin (  Limits::max(),  Limits::max(),  Limits::max() );
  constexpr Vec3 defaultMax ( -Limits::max(), -Limits::max(), -Limits::max() );

  SECTION ( "Default constructor" )
  {
    const Box a;
    REQUIRE ( false == a.valid() );
    REQUIRE ( true == Usul::Math::equal ( defaultMin, a.getMin() ) );
    REQUIRE ( true == Usul::Math::equal ( defaultMax, a.getMax() ) );
  }

  SECTION ( "Constructor from min and max" )
  {
    const Box a ( Vec3 ( 0, 0, 0 ), Vec3 ( 1, 1, 1 ) );
    REQUIRE ( true == a.valid() );

    const Box b ( Vec3 ( 1, 1, 1 ), Vec3 ( 0, 0, 0 ) );
    REQUIRE ( false == b.valid() );
  }

  SECTION ( "Copy constructor" )
  {
    const Box a ( Vec3 ( 10, 10, 10 ), Vec3 ( 11, 11, 11 ) );
    REQUIRE ( true == a.valid() );

    const Box b ( a );
    REQUIRE ( true == b.valid() );
    REQUIRE ( true == Usul::Math::equal ( b, a ) );
    REQUIRE ( b == a );

    const Box c = a;
    REQUIRE ( true == c.valid() );
    REQUIRE ( true == Usul::Math::equal ( c, a ) );
    REQUIRE ( c == a );
  }

  SECTION ( "Assignment" )
  {
    const Box a ( Vec3 ( 10, 10, 10 ), Vec3 ( 11, 11, 11 ) );
    REQUIRE ( true == a.valid() );

    Box b;
    REQUIRE ( false == b.valid() );
    REQUIRE ( true == Usul::Math::equal ( defaultMin, b.getMin() ) );
    REQUIRE ( true == Usul::Math::equal ( defaultMax, b.getMax() ) );

    b = a;
    REQUIRE ( true == b.valid() );
    REQUIRE ( true == Usul::Math::equal ( b, a ) );
    REQUIRE ( b == a );
  }

  SECTION ( "Can grow the box by points" )
  {
    Box a;
    REQUIRE ( false == a.valid() );

    const Vec3 p0 ( 0, 0, 0 );
    const Vec3 p1 ( 1, 1, 1 );
    const Vec3 pn1 ( -1, -1, -1 );

    a.grow ( p0 );
    REQUIRE ( true == a.valid() );
    REQUIRE ( true == Usul::Math::equal ( p0, a.getMin() ) );
    REQUIRE ( true == Usul::Math::equal ( p0, a.getMax() ) );

    a.grow ( p1 );
    REQUIRE ( true == a.valid() );
    REQUIRE ( true == Usul::Math::equal ( p0, a.getMin() ) );
    REQUIRE ( true == Usul::Math::equal ( p1, a.getMax() ) );

    a.grow ( pn1 );
    REQUIRE ( true == a.valid() );
    REQUIRE ( true == Usul::Math::equal ( pn1, a.getMin() ) );
    REQUIRE ( true == Usul::Math::equal ( p1,  a.getMax() ) );
  }

  SECTION ( "Can grow the box by other boxes" )
  {
    Box a;
    REQUIRE ( false == a.valid() );

    const Vec3 p0 ( 0, 0, 0 );
    const Vec3 p1 ( 1, 1, 1 );
    const Vec3 pn1 ( -1, -1, -1 );

    Box b ( p0, p1 );
    REQUIRE ( true == b.valid() );
    REQUIRE ( true == Usul::Math::equal ( p0, b.getMin() ) );
    REQUIRE ( true == Usul::Math::equal ( p1, b.getMax() ) );

    b.grow ( Box ( pn1, p0 ) );
    REQUIRE ( true == b.valid() );
    REQUIRE ( true == Usul::Math::equal ( pn1, b.getMin() ) );
    REQUIRE ( true == Usul::Math::equal ( p1,  b.getMax() ) );
  }

  SECTION ( "Can get the size" )
  {
    const Box a ( Vec3 ( -1, -1, -1 ), Vec3 ( 1, 1, 1 ) );
    REQUIRE ( true == a.valid() );
    REQUIRE ( true == Usul::Math::equal ( Vec3 ( 2, 2, 2 ), a.getSize() ) );
  }

  SECTION ( "Can get the center" )
  {
    const Box a ( Vec3 ( -1, -1, -1 ), Vec3 ( 1, 1, 1 ) );
    REQUIRE ( true == a.valid() );
    REQUIRE ( true == Usul::Math::equal ( Vec3 ( 0, 0, 0 ), a.getCenter() ) );

    const Box b ( Vec3 ( 0, 0, 0 ), Vec3 ( 10, 10, 10 ) );
    REQUIRE ( true == b.valid() );
    REQUIRE ( true == Usul::Math::equal ( Vec3 ( 5, 5, 5 ), b.getCenter() ) );
  }

  SECTION ( "Can get the radius" )
  {
    const Box a ( Vec3 ( 0, 0, 0 ), Vec3 ( 3, 4, 0 ) );
    REQUIRE ( 2.5 == a.getRadius() );

    const Box b ( Vec3 ( 0, 0, 0 ), Vec3 ( 0, 9, 40 ) );
    REQUIRE ( 20.5 == b.getRadius() );
  }
}
