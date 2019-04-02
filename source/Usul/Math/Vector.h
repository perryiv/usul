
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Vector math functions.
//
//  Passing ScalarType by value because of this discussion:
//  https://stackoverflow.com/questions/14013139/is-it-counter-productive-to-pass-primitive-types-by-reference
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_VECTOR_FUNCTIONS_H_
#define _USUL_MATH_VECTOR_FUNCTIONS_H_

#include <cmath>


namespace Usul {
namespace Math {


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
//  Details for distance squared.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  template < class PointType, unsigned int > struct DistanceSquared{};
  template < class PointType > struct DistanceSquared < PointType, 2 >
  {
    static typename PointType::value_type calculate ( const PointType &a, const PointType &b )
    {
      return (
        ( ( a[0] - b[0] ) * ( a[0] - b[0] ) ) +
        ( ( a[1] - b[1] ) * ( a[1] - b[1] ) ) );
    }
  };
  template < class PointType > struct DistanceSquared < PointType, 3 >
  {
    static typename PointType::value_type calculate ( const PointType &a, const PointType &b )
    {
      return (
        ( ( a[0] - b[0] ) * ( a[0] - b[0] ) ) +
        ( ( a[1] - b[1] ) * ( a[1] - b[1] ) ) +
        ( ( a[2] - b[2] ) * ( a[2] - b[2] ) ) );
    }
  };
  template < class PointType > struct DistanceSquared < PointType, 4 >
  {
    static typename PointType::value_type calculate ( const PointType &a, const PointType &b )
    {
      return (
        ( ( a[0] - b[0] ) * ( a[0] - b[0] ) ) +
        ( ( a[1] - b[1] ) * ( a[1] - b[1] ) ) +
        ( ( a[2] - b[2] ) * ( a[2] - b[2] ) ) +
        ( ( a[3] - b[3] ) * ( a[3] - b[3] ) ) );
    }
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  Calculate the squared distance between the two points.
//
///////////////////////////////////////////////////////////////////////////////

template < class PointType >
inline typename PointType::value_type distanceSquared ( const PointType &a, const PointType &b )
{
  typedef Detail::DistanceSquared < PointType, PointType::SIZE > DistanceSquared;
  return DistanceSquared::calculate ( a, b );
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


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_VECTOR_FUNCTIONS_H_
