
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the random number generator functions.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Math/Random.h"
#include "Usul/Math/Vector2.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Math/Vector4.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the 3D math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Template random number functions", "",
  float, double, ( long double ) )
{
  typedef TestType T;
  typedef Usul::Math::Vector2 < T > Vec2;
  typedef Usul::Math::Vector3 < T > Vec3;
  typedef Usul::Math::Vector4 < T > Vec4;

  const T mn = static_cast < T > ( 0.2 );
  const T mx = static_cast < T > ( 0.8 );

  SECTION ( "Generation of random scalar" )
  {
    for ( unsigned int i = 0; i < 100; ++i )
    {
      const T value = Usul::Math::random ( mn, mx );
      REQUIRE ( value >= mn );
      REQUIRE ( value <= mx );
    }
  }

  SECTION ( "Generation of random Vec2" )
  {
    Vec2 value;
    for ( unsigned int i = 0; i < 100; ++i )
    {
      Usul::Math::random ( value, mn, mx );
      REQUIRE ( value[0] >= mn );
      REQUIRE ( value[0] <= mx );
      REQUIRE ( value[1] >= mn );
      REQUIRE ( value[1] <= mx );
    }
  }

  SECTION ( "Generation of random Vec3" )
  {
    Vec3 value;
    for ( unsigned int i = 0; i < 100; ++i )
    {
      Usul::Math::random ( value, mn, mx );
      REQUIRE ( value[0] >= mn );
      REQUIRE ( value[0] <= mx );
      REQUIRE ( value[1] >= mn );
      REQUIRE ( value[1] <= mx );
      REQUIRE ( value[2] >= mn );
      REQUIRE ( value[2] <= mx );
    }
  }

  SECTION ( "Generation of random Vec4" )
  {
    Vec4 value;
    for ( unsigned int i = 0; i < 100; ++i )
    {
      Usul::Math::random ( value, mn, mx );
      REQUIRE ( value[0] >= mn );
      REQUIRE ( value[0] <= mx );
      REQUIRE ( value[1] >= mn );
      REQUIRE ( value[1] <= mx );
      REQUIRE ( value[2] >= mn );
      REQUIRE ( value[2] <= mx );
      REQUIRE ( value[3] >= mn );
      REQUIRE ( value[3] <= mx );
    }
  }
}
