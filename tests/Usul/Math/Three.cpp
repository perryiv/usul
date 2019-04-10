
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

#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Three.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Math/Vector4.h"
#include "Usul/Strings/Format.h"

#include "catch2/catch.hpp"

#include <cmath>


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
    const Vec4 viewport ( 0, 0, 1600, 1058 );
    const T x ( std::round ( viewport[2] * T ( 0.5 ) ) );
    const T y ( std::round ( viewport[3] * T ( 0.5 ) ) );
    const Vec3 screen ( x, y, 0 );
    const Matrix viewMatrix;
    const Matrix projMatrix (
      T ( 2.4678185965049204 ), T ( 0 ), T ( 0 ), T ( 0 ),
      T ( 0 ), T ( 3.7320508075688776 ), T ( 0 ), T ( 0 ),
      T ( 0 ), T ( 0 ), T ( -1.0002000200020005 ), T ( -0.06487231313253677 ),
      T ( 0 ), T ( 0 ), T ( -1 ), T ( 0 )
    );

    Vec3 answer;
    const bool result = Usul::Math::unProject ( screen, viewMatrix, projMatrix, viewport, answer );

    REQUIRE ( true == result );

    const std::string expect ( Usul::Strings::formatVector3 ( Vec3 ( 0, 0, T ( -0.03243291126899654 ) ) ) );
    const std::string actual ( Usul::Strings::formatVector3 ( answer ) );

    REQUIRE ( expect == actual );
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
