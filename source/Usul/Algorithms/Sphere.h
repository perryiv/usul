
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Sphere sub-division algorithm.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_ALGORITHMS_SPHERE_SUB_DIVISION_H_
#define _USUL_ALGORITHMS_SPHERE_SUB_DIVISION_H_

#include <cmath>
#include <functional>
#include <stdexcept>


namespace Usul {
namespace Algorithms {
namespace Sphere {


///////////////////////////////////////////////////////////////////////////////
//
//  Sub-divide a sphere.
//
///////////////////////////////////////////////////////////////////////////////

namespace { namespace Details
{
  template < class Real, class Callback >
  inline void subdivide (
    Real x1, Real y1, Real z1,
    Real x2, Real y2, Real z2,
    Real x3, Real y3, Real z3,
    unsigned int &numPoints,
    unsigned int depth,
    Callback fun )
  {
    // If we are at the requested depth.
    if ( 0 == depth )
    {
      // Determine the indices.
      const unsigned int i1 = numPoints++;
      const unsigned int i2 = numPoints++;
      const unsigned int i3 = numPoints++;

      // Call the function.
      fun ( x1, y1, z1, x2, y2, z2, x3, y3, z3, i1, i2, i3 );
    }

    // Otherwise...
    else
    {
      // Make three new points.
      Real x12 = x1 + x2;
      Real y12 = y1 + y2;
      Real z12 = z1 + z2;
      Real x23 = x2 + x3;
      Real y23 = y2 + y3;
      Real z23 = z2 + z3;
      Real x31 = x3 + x1;
      Real y31 = y3 + y1;
      Real z31 = z3 + z1;

      // Adjust the first point.
      const Real one ( static_cast < Real > ( 1 ) );
      Real d ( std::sqrt ( x12 * x12 + y12 * y12 + z12 * z12 ) );
      if ( 0 == d )
      {
        throw std::runtime_error ( "Error 1622864301, divide by zero" );
      }
      Real invd = one / d;
      x12 *= invd;
      y12 *= invd;
      z12 *= invd;

      // Adjust the second point.
      d = std::sqrt ( x23 * x23 + y23 * y23 + z23 * z23 );
      if ( 0 == d )
      {
        throw std::runtime_error ( "Error 3368459612, divide by zero" );
      }
      invd = one / d;
      x23 *= invd;
      y23 *= invd;
      z23 *= invd;

      // Adjust the third point.
      d = std::sqrt ( x31 * x31 + y31 * y31 + z31 * z31 );
      if ( 0 == d )
      {
        throw std::runtime_error ( "Error 2610396704, divide by zero" );
      }
      invd = one / d;
      x31 *= invd;
      y31 *= invd;
      z31 *= invd;

      // Divide again.
      --depth;
      Details::subdivide < Real > (  x1,  y1,  z1, x12, y12, z12, x31, y31, z31, numPoints, depth, fun );
      Details::subdivide < Real > (  x2,  y2,  z2, x23, y23, z23, x12, y12, z12, numPoints, depth, fun );
      Details::subdivide < Real > (  x3,  y3,  z3, x31, y31, z31, x23, y23, z23, numPoints, depth, fun );
      Details::subdivide < Real > ( x12, y12, z12, x23, y23, z23, x31, y31, z31, numPoints, depth, fun );
    }
  }
} }


///////////////////////////////////////////////////////////////////////////////
//
//  Make a sequence of triangles that define a unit sphere.
//  Subdivide n times. The points are also the normals.
//
///////////////////////////////////////////////////////////////////////////////

template < class Real >
inline void generate (
  unsigned int n,
  std::function < void (
    Real, Real, Real, Real, Real, Real, Real, Real, Real,
    unsigned int, unsigned int, unsigned int ) > fun
  )
{
  // Handle invalid callback.
  if ( !fun )
  {
    return;
  }

  // Declare these constants used in the subdivision algorithm.
  const Real X ( static_cast < Real > ( 0.525731112119133606 ) );
  const Real Z ( static_cast < Real > ( 0.8506508083528655993 ) );

  // We need to count the points as we go.
  unsigned int numPoints = 0;

  // Call the function to subdivide.
  Details::subdivide < Real > ( -X,  0,  Z,  X,  0,  Z,  0,  Z,  X, numPoints, n, fun );
  Details::subdivide < Real > ( -X,  0,  Z,  0,  Z,  X, -Z,  X,  0, numPoints, n, fun );
  Details::subdivide < Real > ( -Z,  X,  0,  0,  Z,  X,  0,  Z, -X, numPoints, n, fun );
  Details::subdivide < Real > (  0,  Z,  X,  Z,  X,  0,  0,  Z, -X, numPoints, n, fun );
  Details::subdivide < Real > (  0,  Z,  X,  X,  0,  Z,  Z,  X,  0, numPoints, n, fun );
  Details::subdivide < Real > (  Z,  X,  0,  X,  0,  Z,  Z, -X,  0, numPoints, n, fun );
  Details::subdivide < Real > (  Z,  X,  0,  Z, -X,  0,  X,  0, -Z, numPoints, n, fun );
  Details::subdivide < Real > (  0,  Z, -X,  Z,  X,  0,  X,  0, -Z, numPoints, n, fun );
  Details::subdivide < Real > (  0,  Z, -X,  X,  0, -Z, -X,  0, -Z, numPoints, n, fun );
  Details::subdivide < Real > ( -X,  0, -Z,  X,  0, -Z,  0, -Z, -X, numPoints, n, fun );
  Details::subdivide < Real > (  0, -Z, -X,  X,  0, -Z,  Z, -X,  0, numPoints, n, fun );
  Details::subdivide < Real > (  0, -Z, -X,  Z, -X,  0,  0, -Z,  X, numPoints, n, fun );
  Details::subdivide < Real > (  0, -Z, -X,  0, -Z,  X, -Z, -X,  0, numPoints, n, fun );
  Details::subdivide < Real > ( -Z, -X,  0,  0, -Z,  X, -X,  0,  Z, numPoints, n, fun );
  Details::subdivide < Real > ( -X,  0,  Z,  0, -Z,  X,  X,  0,  Z, numPoints, n, fun );
  Details::subdivide < Real > (  0, -Z,  X,  Z, -X,  0,  X,  0,  Z, numPoints, n, fun );
  Details::subdivide < Real > ( -Z,  X,  0, -Z, -X,  0, -X,  0,  Z, numPoints, n, fun );
  Details::subdivide < Real > ( -Z,  X,  0, -X,  0, -Z, -Z, -X,  0, numPoints, n, fun );
  Details::subdivide < Real > ( -Z,  X,  0,  0,  Z, -X, -X,  0, -Z, numPoints, n, fun );
  Details::subdivide < Real > (  0, -Z, -X, -Z, -X,  0, -X,  0, -Z, numPoints, n, fun );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Reserve space in the containers.
//
///////////////////////////////////////////////////////////////////////////////

inline void reserve (
  unsigned int n,
  std::function < void ( unsigned int, unsigned int ) > fun )
{
  // Handle invalid callback.
  if ( !fun )
  {
    return;
  }

  // This works out to 60 * 4 ^ n.
  const unsigned int numPoints = 60 * ( static_cast < unsigned int > (
    std::pow ( 4.0, static_cast < double > ( n ) ) ) );

  // Dividing by 2 instead of 3 to increase the chances that we allocate enough.
  const unsigned int numIndices = numPoints / 2;

  // Call the given function.
  fun ( numPoints, numIndices );
}


} // namespace Sphere
} // namespace Algorithms
} // namespace Usul


#endif // _USUL_ALGORITHMS_SPHERE_SUB_DIVISION_H_
