
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

#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector4.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Math/Vector2.h"

#include <algorithm>
#include <type_traits>


namespace Usul {
namespace Math {


///////////////////////////////////////////////////////////////////////////////
//
//  Unproject the screen point into a 3D point.
//  https://github.com/toji/gl-matrix
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline bool unProject (
  const Usul::Math::Vector3 < T, I > &screen,
  const Usul::Math::Matrix44 < T, I > &viewMatrix,
  const Usul::Math::Matrix44 < T, I > &projMatrix,
  const Usul::Math::Vector4 < T, I > &viewport,
  Usul::Math::Vector3 < T, I > &point )
{
  // Make sure we're working with a floating point number type.
  static_assert ( std::is_floating_point < T >::value, "Not a floating-point number type" );

  // Typedefs.
  typedef Usul::Math::Matrix44 < T, I > Matrix;
  typedef Usul::Math::Vector4 < T, I > Vec4;
  typedef T Number;

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
  const T ib3 = one / b[3];

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

template < class T, class I >
inline bool makeLine (
  const T &x, const T &y,
  const Usul::Math::Matrix44 < T, I > &viewMatrix,
  const Usul::Math::Matrix44 < T, I > &projMatrix,
  const Usul::Math::Vector4 < T, I > &viewport,
  Usul::Math::Line3 < T, I > &line )
{
  // Make sure we're working with a floating point number type.
  static_assert ( std::is_floating_point < T >::value, "Not a floating-point number type" );

  // Typedefs.
  typedef Usul::Math::Vector3 < T, I > Vec3;
  typedef T Number;

  // Keep the compiler happy.
  const Number one  ( static_cast < Number > ( 1 ) );

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
