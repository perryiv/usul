
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Generate points, normals, and indices for a general surface-of-revolution.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_ALGORITHMS_SURFACE_OF_REVOLUTION_H_
#define _USUL_ALGORITHMS_SURFACE_OF_REVOLUTION_H_

#include "Usul/Errors/Check.h"
#include "Usul/Math/Matrix44.h"

#include <stdexcept>


namespace Usul {
namespace Algorithms {
namespace Revolution {


//////////////////////////////////////////////////////////////////////////
//
//  Generate the surface-of-revolution data.
//
//////////////////////////////////////////////////////////////////////////

template <
  class Axis,
  class UnsignedInteger,
  class RealNumber,
  class Points,
  class Normals,
  class Indices
>
inline void generate (
  const Axis &axis,
  const Points &curve,
  UnsignedInteger numPointsRadial,
  RealNumber startAngle,
  RealNumber endAngle,
  bool, // triStrips, // Pass false for a sequence of triangles.
  Points &points,
  Normals &,
  Indices &indices
)
{
  typedef Usul::Math::Matrix44 < RealNumber > Matrix44;

  // constexpr RealNumber zero  = static_cast < RealNumber > ( 0 );
  constexpr Matrix44 identity;

  // typedef typename Points::value_type Point;
  // typedef typename Normals::value_type Normal;
  typedef typename Indices::value_type Index;

  const UnsignedInteger numPointsAxial = static_cast < UnsignedInteger > ( curve.size() );
  const RealNumber deltaAngle = endAngle - startAngle;
  Matrix44 matrix0 = Usul::Math::rotate ( identity, axis, startAngle );
  Index index0 = static_cast < Index > ( 0 );
  Index index1 = index0 + static_cast < Index > ( numPointsAxial );

  // The first row of points in the axial direction is just the curve
  // rotated to the starting angle.
  for ( UnsignedInteger i = 0; i < numPointsAxial; ++i )
  {
    points.push_back ( Usul::Math::multiply ( matrix0, curve.at ( i ) ) );
  }

  // Now loop through the remaining rotated curves.
  for ( UnsignedInteger i = 1; i < numPointsRadial; ++i )
  {
    // Figure out the angle we're at the the corresponding rotation matrix.
    const RealNumber u = ( static_cast < RealNumber > ( i ) / ( numPointsRadial - 1 ) );
    const RealNumber angle = startAngle + ( u * deltaAngle );
    const Matrix44 matrix1 = Usul::Math::rotate ( identity, axis, angle );

    // Get the first point on this rotated curve.
    points.push_back ( Usul::Math::multiply ( matrix1, curve.at ( 0 ) ) );

    // Loop through the remaining points on this rotated curve.
    for ( UnsignedInteger j = 1; j < numPointsAxial; ++j )
    {
      // Get the next point on this rotated curve.
      points.push_back ( Usul::Math::multiply ( matrix1, curve.at ( i ) ) );

      // The other indices.
      const Index index2 = index0 + static_cast < Index > ( 1 );
      const Index index3 = index1 + static_cast < Index > ( 1 );

      // 0 2 --> Two points on curve rotated with matrix0.
      // 1 3 --> Two points on curve rotated with matrix1.

      // Add indices for one triangle.
      indices.push_back ( index0 );
      indices.push_back ( index1 );
      indices.push_back ( index3 );

      // Add indices for the other triangle.
      indices.push_back ( index0 );
      indices.push_back ( index3 );
      indices.push_back ( index2 );
    }

    matrix0 = matrix1;
  }
}


} // namespace Revolution
} // namespace Algorithms
} // namespace Usul


#endif // _USUL_ALGORITHMS_SURFACE_OF_REVOLUTION_H_
