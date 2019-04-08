
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  3D math functions.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_3D_FUNCTIONS_H_
#define _USUL_MATH_3D_FUNCTIONS_H_

#include "Usul/Math/Line3.h"
#include "Usul/Math/Matrix44.h" // For Usul::Math::inverse
#include "Usul/Math/Vector3.h"  // For Vector3

#include <type_traits>


namespace Usul {
namespace Math {


///////////////////////////////////////////////////////////////////////////////
//
//  Unproject the screen point into a 3D point.
//  https://github.com/toji/gl-matrix
//
///////////////////////////////////////////////////////////////////////////////

template < class Vec3, class Vec4, class Matrix >
inline bool unProject (
  const Vec3 &screen,
  const Matrix &viewMatrix,
  const Matrix &projMatrix,
  const Vec4 &viewport,
  Vec3 &point )
{
  // Make sure they all have the same value type.
  typedef typename Matrix::value_type Number;
  static_assert ( std::is_same < Number, typename Vec3::value_type >::value, "Not the same value type" );
  static_assert ( std::is_same < Number, typename Vec4::value_type >::value, "Not the same value type" );

  // Make sure we're working with a floating point number type.
  static_assert ( std::is_floating_point < Number >::value, "Not a floating-point number type" );

  // Keep the compiler happy.
  const Number zero ( static_cast < Number > ( 0 ) );
  const Number one  ( static_cast < Number > ( 1 ) );
  const Number two  ( static_cast < Number > ( 2 ) );

  // Make the homogeneous, normalized point.
  // All three, x, y, and z, will be in the range [-1,1].
  const Vec4 a (
    ( screen[0] - viewport[0] ) * two / viewport[2] - one,
    ( screen[1] - viewport[1] ) * two / viewport[3] - one,
    two * screen[2] - one,
    one
  );

  // Combine the view and projection matrices.
  const Matrix m = projMatrix * viewMatrix;

  // Get the inverse and handle when it does not exist.
  Matrix im;
  if ( false == Usul::Math::inverse ( m, im ) )
  {
    return false;
  }

  // Transform the 4D point.
  const Vec4 b = im * a;

  // Make sure it worked.
  if ( zero == b[3] )
  {
    return false;
  }

  // Shortcut.
  const Number ib3 = one / b[3];

  // Write to the answer.
  point[0] = b[0] * ib3;
  point[1] = b[1] * ib3;
  point[2] = b[2] * ib3;

  // It worked.
  return true;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Make a 3D line from the 2D screen coordinate.
//
///////////////////////////////////////////////////////////////////////////////

template < class Number, class Vec4, class Matrix, class Line3 >
inline bool makeLine (
  const Number &x, const Number &y,
  const Matrix &viewMatrix,
  const Matrix &projMatrix,
  const Vec4 &viewport,
  Line3 &line )
{
  // Make sure they all have the same value type.
  static_assert ( std::is_same < Number, typename Vec4::value_type >::value, "Not the same value type" );
  static_assert ( std::is_same < Number, typename Line3::value_type >::value, "Not the same value type" );
  static_assert ( std::is_same < Number, typename Matrix::value_type >::value, "Not the same value type" );

  // Make sure we're working with a floating point number type.
  static_assert ( std::is_floating_point < Number >::value, "Not a floating-point number type" );

  // Typedefs.
  typedef Usul::Math::Vector3 < Number > Vec3;

  // Keep the compiler happy.
  const Number one ( static_cast < Number > ( 1 ) );

  // Get the 3D point on the near plane.
  Vec3 nearPoint;
  if ( false == unProject ( Vec3 ( x, viewport[3] - y, -one ), viewMatrix, projMatrix, viewport, nearPoint ) )
  {
    return false;
  }

  // Get the 3D point on the far plane.
  Vec3 farPoint;
  if ( false == unProject ( Vec3 ( x, viewport[3] - y, one ), viewMatrix, projMatrix, viewport, farPoint ) )
  {
    return false;
  }

  // Set the line.
  line.set ( nearPoint, farPoint );

  // It worked.
  return true;
};


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_3D_FUNCTIONS_H_
