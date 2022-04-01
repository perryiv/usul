
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Generate points, normals, and indices for a surface-of-revolution.
//
//  This is a generalized version of:
//  https://github.com/perryiv/cadkit/blob/master/Usul/Algorithms/Cylinder.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_ALGORITHMS_SURFACE_OF_REVOLUTION_H_
#define _USUL_ALGORITHMS_SURFACE_OF_REVOLUTION_H_

#include "Usul/Errors/Check.h"
#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Strings/Format.h"

#include <stdexcept>
#include <type_traits>


namespace Usul {
namespace Algorithms {
namespace Revolution {


//////////////////////////////////////////////////////////////////////////
//
//  Helper function.
//
//////////////////////////////////////////////////////////////////////////

namespace { namespace Details
{
  template <
    class Source,
    class Matrix,
    class UnsignedInteger,
    class Target
  >
  inline void appendVec3 (
    const Source &source,
    const Matrix &matrix,
    const UnsignedInteger i,
    Target &target
  )
  {
    // Shortcuts.
    typedef typename Matrix::value_type RealNumber;
    typedef typename Source::value_type SourceVec3;
    typedef typename Target::value_type TargetVec3;
    typedef Usul::Math::Vector3 < RealNumber > RealVec3;

    // Should be true.
    static_assert ( true == std::is_floating_point < RealNumber > ::value, "Real number type is not floating point" );
    static_assert ( true == std::is_floating_point < typename SourceVec3::value_type > ::value, "Source vector value type is not floating point" );
    static_assert ( true == std::is_floating_point < typename TargetVec3::value_type > ::value, "Target vector value type is not floating point" );

    // Get the source value in the same precision as the matrix.
    const SourceVec3 &s = source.at ( i );
    const RealVec3 sr ( s[0], s[1], s[2] );

    // Calculate the target value in the same precision as the matrix.
    const RealVec3 tr = Usul::Math::multiply ( matrix, sr );

    // Convert to the target's precision.
    const TargetVec3 t (
      static_cast < typename TargetVec3::value_type > ( tr[0] ),
      static_cast < typename TargetVec3::value_type > ( tr[1] ),
      static_cast < typename TargetVec3::value_type > ( tr[2] )
    );

    // Save the target.
    target.push_back ( t );
  }
} }


//////////////////////////////////////////////////////////////////////////
//
//  Generate the surface-of-revolution data by rotating the given curve
//  about the x-axis.
//
//////////////////////////////////////////////////////////////////////////

template <
  class Axis,
  class UnsignedInteger,
  class RealNumber,
  class CurvePoints,
  class CurveNormals,
  class SurfacePoints,
  class SurfaceNormals,
  class SurfaceIndices
>
inline void generate (
  const Axis &dir,
  const CurvePoints &curvePoints,
  const CurveNormals &curveNormals,
  const UnsignedInteger numPointsRadial,
  const RealNumber startAngle,
  const RealNumber endAngle,
  SurfacePoints &points,
  SurfaceNormals &normals,
  SurfaceIndices &indices
)
{
  // Typedefs.
  typedef Usul::Math::Matrix44 < RealNumber > Matrix44;
  typedef Usul::Math::Vector3 < RealNumber > Vec3;
  typedef typename SurfaceIndices::value_type SurfaceIndex;

  // Shortcuts.
  constexpr RealNumber zero  = static_cast < RealNumber >   ( 0 );
  constexpr SurfaceIndex one = static_cast < SurfaceIndex > ( 1 );
  constexpr Matrix44 identity;

  // Check.
  USUL_CHECK_AND_THROW ( ( curvePoints.size() >= 2 ), "Fewer than 2 curve points" );
  USUL_CHECK_AND_THROW ( ( curvePoints.size() == curveNormals.size() ), "Inconsistent number of curve and normal points" );
  USUL_CHECK_AND_THROW ( ( numPointsRadial >= 2 ), "Fewer than 2 radial points" );
  USUL_CHECK_AND_THROW ( ( endAngle > startAngle ), "The end angle is not smaller than the start angle" );
  USUL_CHECK_AND_THROW ( ( false == ( ( zero == dir[0] ) && ( zero == dir[1] ) && ( zero == dir[2] ) ) ), "Zero vector given for axis" );

  // Shortcuts.
  const UnsignedInteger numPointsAxial = static_cast < UnsignedInteger > ( curvePoints.size() );
  const RealNumber deltaAngle = endAngle - startAngle;
  SurfaceIndex index0 = static_cast < SurfaceIndex > ( 0 );
  SurfaceIndex index1 = index0 + static_cast < SurfaceIndex > ( numPointsAxial );
  const Vec3 axis ( dir[0], dir[1], dir[2] );

  // The first row is just the given points and normals rotated to the starting angle.
  {
    Matrix44 matrix = Usul::Math::rotate ( identity, axis, startAngle );
    for ( UnsignedInteger i = 0; i < numPointsAxial; ++i )
    {
      Details::appendVec3 ( curvePoints,  matrix, i, points  );
      Details::appendVec3 ( curveNormals, matrix, i, normals );
    }
  }

  // Now loop through the remaining rows of rotated curves.
  for ( UnsignedInteger i = 1; i < numPointsRadial; ++i )
  {
    // Figure out the angle we're at and the corresponding rotation matrix.
    const RealNumber u = ( static_cast < RealNumber > ( i ) / static_cast < RealNumber > ( numPointsRadial - 1 ) );
    const RealNumber angle = startAngle + ( u * deltaAngle );
    const Matrix44 matrix = Usul::Math::rotate ( identity, axis, angle );

    // Save the first point and normal on this rotated curve.
    Details::appendVec3 ( curvePoints,  matrix, 0u, points  );
    Details::appendVec3 ( curveNormals, matrix, 0u, normals );

    // Loop through the remaining points on this rotated curve.
    for ( UnsignedInteger j = 1; j < numPointsAxial; ++j )
    {
      // Get the next point and normal on this rotated curve.
      Details::appendVec3 ( curvePoints,  matrix, j, points  );
      Details::appendVec3 ( curveNormals, matrix, j, normals );

      // The other indices.
      const SurfaceIndex index2 = index0 + one;
      const SurfaceIndex index3 = index1 + one;

      // 0 2 --> Two first two points on the previous rotated curve.
      // 1 3 --> Two first two points on this rotated curve.

      // Add indices for one triangle.
      indices.push_back ( index0 );
      indices.push_back ( index1 );
      indices.push_back ( index3 );

      // Add indices for the other triangle.
      indices.push_back ( index0 );
      indices.push_back ( index3 );
      indices.push_back ( index2 );

      // Go to the next column, which means we increment in the axial direction.
      index0 = index2;
      index1 = index3;
    }

    // Go to the next rows.
    index0 = static_cast < SurfaceIndex > ( i * numPointsAxial );
    index1 = index0 + static_cast < SurfaceIndex > ( numPointsAxial );
  }
}


} // namespace Revolution
} // namespace Algorithms
} // namespace Usul


#endif // _USUL_ALGORITHMS_SURFACE_OF_REVOLUTION_H_
