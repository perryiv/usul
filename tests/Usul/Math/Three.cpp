
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the 3D math functions.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Math/Three.h"
#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Math/Vector4.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the 3D math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "3D template math functions", "",
  float, double, ( long double ) )
{
  typedef TestType T;
  typedef typename Usul::Math::Line3 < T > Line3;
  typedef typename Usul::Math::Matrix44 < T > Matrix;
  typedef typename Usul::Math::Vector3 < T > Vec3;
  typedef typename Usul::Math::Vector4 < T > Vec4;

  SECTION ( "Un-projecting works" )
  {
    const Vec3 screen ( 100, 100, 0 );
    const Matrix viewMatrix;
    const Matrix projMatrix;
    const Vec4 viewport ( 0, 0, 1000, 1000 );
    Vec3 answer;

    // Not testing real numbers yet, just making sure the template arguments work.
    const bool result = Usul::Math::unProject ( screen, viewMatrix, projMatrix, viewport, answer );

    REQUIRE ( true == result );
  }

  SECTION ( "Making a line works" )
  {
    const T x ( 100 );
    const T y ( 100 );
    const Matrix viewMatrix;
    const Matrix projMatrix;
    const Vec4 viewport ( 0, 0, 1000, 1000 );
    Line3 answer;

    // Not testing real numbers yet, just making sure the template arguments work.
    const bool result = Usul::Math::makeLine ( x, y, viewMatrix, projMatrix, viewport, answer );

    REQUIRE ( true == result );
  }
}
