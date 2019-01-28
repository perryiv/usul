
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Math functions.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_FUNCTIONS_H_
#define _USUL_MATH_FUNCTIONS_H_

#include "Usul/Math/Constants.h"

#include <cmath>


namespace Usul {
namespace Math {


///////////////////////////////////////////////////////////////////////////////
//
//  Convert the angle.
//
///////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline ScalarType radToDeg ( const ScalarType &angle )
{
  return ( angle * Usul::Math::RAD_TO_DEG );
}
template < class ScalarType > inline ScalarType degToRad ( const ScalarType &angle )
{
  return ( angle * Usul::Math::DEG_TO_RAD );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the dot-product.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline typename VectorType::value_type dot ( const VectorType &a, const VectorType &b )
{
  return (
    ( a[0] * b[0] ) +
    ( a[1] * b[1] ) +
    ( a[2] * b[2] ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the cross-product.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline void cross ( const VectorType &a, const VectorType &b, VectorType &c )
{
  c[0] = ( a[1] * b[2] ) - ( a[2] * b[1] );
  c[1] = ( a[2] * b[0] ) - ( a[0] * b[2] );
  c[2] = ( a[0] * b[1] ) - ( a[1] * b[0] );
}
template < class VectorType >
inline VectorType cross ( const VectorType &a, const VectorType &b )
{
  return VectorType (
    ( a[1] * b[2] ) - ( a[2] * b[1] ),
    ( a[2] * b[0] ) - ( a[0] * b[2] ),
    ( a[0] * b[1] ) - ( a[1] * b[0] ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the angle between the two vectors.
//  theta = acos ( A dot B / |A||B| )
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline typename VectorType::value_type angle ( const VectorType &a, const VectorType &b )
{
  const auto AdotB ( dot ( a, b ) );
  const auto lengthA ( length ( a ) );
  const auto lengthB ( length ( b ) );
  return std::acos ( AdotB / ( lengthA * lengthB ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the length.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline typename VectorType::value_type length ( const VectorType &v )
{
  return std::sqrt ( dot ( v, v ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Calculate the squared distance between the two points.
//
///////////////////////////////////////////////////////////////////////////////

template < class PointType >
inline typename PointType::value_type distanceSquared ( const PointType &a, const PointType &b )
{
  return (
    ( ( a[0] - b[0] ) * ( a[0] - b[0] ) ) +
    ( ( a[1] - b[1] ) * ( a[1] - b[1] ) ) +
    ( ( a[2] - b[2] ) * ( a[2] - b[2] ) ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Calculate the distance between the two vectors.
//
///////////////////////////////////////////////////////////////////////////////

template < class PointType >
inline typename PointType::value_type distance ( const PointType &a, const PointType &b )
{
  return std::sqrt ( distanceSquared ( a, b ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Normalize the vector and, if the caller wants it, set the length
//  prior to normalization.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline void normalize ( const VectorType &v, VectorType &n, typename VectorType::value_type *originalLength = nullptr )
{
  const auto currentLength ( length ( v ) );
  const auto invLength ( 1 / currentLength );

  if ( originalLength )
  {
    *originalLength = currentLength;
  }

  n[0] = v[0] * invLength;
  n[1] = v[1] * invLength;
  n[2] = v[2] * invLength;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return a normalized vector.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline VectorType normalize ( const VectorType &v )
{
  const auto invLength ( 1 / length ( v ) );
  return VectorType ( v[0] * invLength, v[1] * invLength, v[2] * invLength );
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if they are equal.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
bool equal ( const VectorType &a, const VectorType &b )
{
  return (
    ( a[0] == b[0] ) &&
    ( a[1] == b[1] ) &&
    ( a[2] == b[2] ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Call the given function for each value.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType, class Fun >
void each ( const VectorType &v, Fun f )
{
  f ( v[0] );
  f ( v[1] );
  f ( v[2] );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Addition.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline void add ( const VectorType &a, const VectorType &b, VectorType &c )
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
}
template < class VectorType >
inline VectorType add ( const VectorType &a, const VectorType &b )
{
  VectorType answer;
  add ( a, b, answer );
  return answer;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Subtraction.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline void subtract ( const VectorType &a, const VectorType &b, VectorType &c )
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
}
template < class VectorType >
inline VectorType subtract ( const VectorType &a, const VectorType &b )
{
  VectorType answer;
  subtract ( a, b, answer );
  return answer;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Scale.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType, class ScalarType >
inline void scale ( const VectorType &v, const ScalarType &s, VectorType &a )
{
  a[0] = v[0] * s;
  a[1] = v[1] * s;
  a[2] = v[2] * s;
}
template < class VectorType, class ScalarType >
inline VectorType scale ( const VectorType &v, const ScalarType &s )
{
  VectorType answer;
  scale ( v, s, answer );
  return answer;
}


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_FUNCTIONS_H_
