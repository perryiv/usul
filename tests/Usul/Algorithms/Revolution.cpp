
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the functions for surface-of-revolution.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Algorithms/Revolution.h"
#include "Usul/Math/Constants.h"
#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector3.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the reference-counted base class.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Functions for surface-of-revolution", "",
  float, double, ( long double ) )
{
  namespace Revolution = Usul::Algorithms::Revolution;
  // typedef Usul::Math::Matrix44 < TestType > Matrix44;
  typedef Usul::Math::Vector3 < TestType > Vec3;
  typedef std::vector < Vec3 > Points;
  typedef std::vector < Vec3 > Normals;
  typedef std::vector < unsigned int > Indices;

  SECTION ( "Can generate a cylinder" )
  {
    // These are the input.
    const Vec3 axis ( 1, 0, 0 );
    const Points curvePoints {
      Vec3 ( 0, 1, 0 ),
      Vec3 ( 1, 1, 0 ),
      Vec3 ( 2, 1, 0 ),
      Vec3 ( 3, 1, 0 ),
      Vec3 ( 4, 1, 0 )
    };
    const Points curveNormals {
      Vec3 ( 0, 1, 0 ),
      Vec3 ( 0, 1, 0 ),
      Vec3 ( 0, 1, 0 ),
      Vec3 ( 0, 1, 0 ),
      Vec3 ( 0, 1, 0 ),
    };
    const unsigned int numPointsAxial = static_cast < unsigned int > ( curvePoints.size() );
    const unsigned int numPointsRadial = 5;
    const TestType startAngle = 0;
    const TestType endAngle = static_cast < TestType > ( Usul::Math::TWO_PI );

    // These are the output.
    Points points;
    Normals normals;
    Indices indices;

    // Generate the data.
    Revolution::generate (
      axis, curvePoints, curveNormals, numPointsRadial, startAngle, endAngle,
      points, normals, indices
    );

    // Needed below.
    const unsigned int totalNumPoints = numPointsAxial * numPointsRadial;
    const unsigned int numQuads = ( numPointsAxial - 1 ) * ( numPointsRadial - 1 );
    const unsigned int numTriangles = numQuads * 2;

    // Should be true.
    REQUIRE ( totalNumPoints == points.size()  );
    REQUIRE ( totalNumPoints == normals.size() );
    REQUIRE ( ( 3 * numTriangles ) == indices.size() );
  }
}
