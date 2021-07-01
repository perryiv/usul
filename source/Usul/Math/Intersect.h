
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Intersection functions.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_INTERSECTION_FUNCTIONS_H_
#define _USUL_MATH_INTERSECTION_FUNCTIONS_H_

#include "Usul/Math/Line3.h"
#include "Usul/Math/Sphere.h"

#include <cmath>
#include <type_traits>


namespace Usul {
namespace Math {


///////////////////////////////////////////////////////////////////////////////
//
//  Intersect a line with a sphere.
//  Returns the number of intersections, which could be 0, 1, or 2.
//  http://paulbourke.net/geometry/circlesphere/index.html#linesphere
//
///////////////////////////////////////////////////////////////////////////////

template < class Line, class Sphere >
inline unsigned int intersectLineWithSphere (
  const Line &line,
  const Sphere &sphere,
  typename Line::value_type &u1,
  typename Line::value_type &u2,
  const typename Line::value_type tolerance = 1e-6 )
{
  typedef typename Line::value_type Number;
  typedef typename Line::Point Point;

  // Make sure everybody has the same value type.
  static_assert ( std::is_same < Number, typename Sphere::value_type >::value, "Not the same value type" );
  static_assert ( std::is_same < Point, typename Sphere::Point >::value, "Not the same point type" );

  // Make sure we're working with a floating point number type.
  static_assert ( std::is_floating_point < Number >::value, "Not a floating-point number type" );

  // Get the line's two points.
  const Point &pt1 ( line.start() );
  const Point &pt2 ( line.end() );

  // Get the sphere's center and radius.
  const Point &center ( sphere.getCenter() );
  const Number r ( sphere.getRadius() );

  // Shortcuts.
  const Number x1 ( pt1[0] );
  const Number y1 ( pt1[1] );
  const Number z1 ( pt1[2] );

  const Number x2 ( pt2[0] );
  const Number y2 ( pt2[1] );
  const Number z2 ( pt2[2] );

  const Number x3 ( center[0] );
  const Number y3 ( center[1] );
  const Number z3 ( center[2] );

  // Keep the compiler happy.
  const Number zero ( static_cast < Number > ( 0 ) );
  const Number one  ( static_cast < Number > ( 1 ) );
  const Number two  ( static_cast < Number > ( 2 ) );

  // Do the math.
  const Number a (
    ( ( x2 - x1 ) * ( x2 - x1 ) ) +
    ( ( y2 - y1 ) * ( y2 - y1 ) ) +
    ( ( z2 - z1 ) * ( z2 - z1 ) )
  );

  const Number b (
    ( ( ( x2 - x1 ) * ( x1 - x3 ) ) +
    ( ( y2 - y1 ) * ( y1 - y3 ) ) +
    ( ( z2 - z1 ) * ( z1 - z3 ) ) ) * two
  );

  const Number c (
    ( x3 * x3 ) + ( y3 * y3 ) + ( z3 * z3 ) +
    ( x1 * x1 ) + ( y1 * y1 ) + ( z1 * z1 ) -
    ( ( ( x3 * x1 ) + ( y3 * y1 ) + ( z3 * z1 ) ) * two ) - ( r * r )
  );

  // a^2 * u + b^2 * u + c = 0
  const Number inner ( ( b * b ) - ( a * c * 4 ) );

  // The line is tangent to the sphere, so only one intersection.
  if ( ( inner < tolerance ) && ( inner > -tolerance ) )
  {
    u1 = -b / ( a * two );
    return 1;
  }

  // The line missed the sphere.
  if ( inner < zero )
  {
    return 0;
  }

  // The line hits the sphere, so two intersection points.
  const Number sqrtInner ( std::sqrt ( inner ) );
  const Number denom = one / ( a * two );
  u1 = ( -b - sqrtInner ) * denom;
  u2 = ( -b + sqrtInner ) * denom;
  return 2;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Intersect a line with a plane.
//  The answer is the parametric coordinate on the given line.
//  Returns false if the line and plane are parallel.
//  http://paulbourke.net/geometry/pointlineplane/
//
///////////////////////////////////////////////////////////////////////////////

template < class Line, class Plane >
inline bool intersectLineWithPlane (
  const Line &line,
  const Plane &plane,
  typename Line::value_type &u )
{
  typedef typename Line::value_type Number;
  typedef typename Line::Point Point;

  // Make sure everybody has the same value type.
  static_assert ( std::is_same < Number, typename Plane::value_type >::value, "Not the same value type" );

  // Make sure we're working with a floating point number type.
  static_assert ( std::is_floating_point < Number >::value, "Not a floating-point number type" );

  // Get the line's two points.
  const Point &p1 = line.start();
  const Point &p2 = line.end();

  // Shortcuts.
  const Number x1 = p1[0];
  const Number y1 = p1[1];
  const Number z1 = p1[2];
  const Number x2 = p2[0];
  const Number y2 = p2[1];
  const Number z2 = p2[2];

  // Get the plane's coefficients.
  const Number A = plane[0];
  const Number B = plane[1];
  const Number C = plane[2];
  const Number D = plane[3];

  // Calculate the denominator.
  const Number denom = ( A * ( x1 - x2 ) ) + ( B * ( y1 - y2 ) ) + ( C * ( z1 - z2 ) );

  // Is the line and the plane parallel?
  if ( 0.0 == denom )
  {
    return false;
  }

  // If we get to here then they are not parallel, so finish the calculation.
  const Number numer = ( A * x1 ) + ( B * y1 ) + ( C * z1 ) + D;
  u = numer / denom;

  // It worked.
  return true;
};


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_INTERSECTION_FUNCTIONS_H_
