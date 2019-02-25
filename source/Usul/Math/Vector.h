
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
//  Return the dot-product.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  template < class VectorType, unsigned int > struct DotProduct{};
  template < class VectorType > struct DotProduct < VectorType, 2 >
  {
    static typename VectorType::value_type calculate ( const VectorType &a, const VectorType &b )
    {
      return (
        ( a[0] * b[0] ) +
        ( a[1] * b[1] ) );
    }
  };
  template < class VectorType > struct DotProduct < VectorType, 3 >
  {
    static typename VectorType::value_type calculate ( const VectorType &a, const VectorType &b )
    {
      return (
        ( a[0] * b[0] ) +
        ( a[1] * b[1] ) +
        ( a[2] * b[2] ) );
    }
  };
  template < class VectorType > struct DotProduct < VectorType, 4 >
  {
    static typename VectorType::value_type calculate ( const VectorType &a, const VectorType &b )
    {
      return (
        ( a[0] * b[0] ) +
        ( a[1] * b[1] ) +
        ( a[2] * b[2] ) +
        ( a[3] * b[3] ) );
    }
  };
}
template < class VectorType >
inline typename VectorType::value_type dot ( const VectorType &a, const VectorType &b )
{
  typedef Detail::DotProduct < VectorType, VectorType::SIZE > DotProduct;
  return DotProduct::calculate ( a, b );
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
  typedef typename VectorType::value_type ValueType;
  return ( static_cast < ValueType > ( std::sqrt ( dot ( v, v ) ) ) );
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


///////////////////////////////////////////////////////////////////////////////
//
//  Details for normalizing vectors.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  template < class VectorType, unsigned int > struct Normalize{};
  template < class VectorType > struct Normalize < VectorType, 2 >
  {
    static void calculate ( const VectorType &v, VectorType &n, typename VectorType::value_type *originalLength )
    {
      const auto currentLength ( length ( v ) );
      const auto invLength ( 1 / currentLength );

      if ( originalLength )
      {
        *originalLength = currentLength;
      }

      n[0] = v[0] * invLength;
      n[1] = v[1] * invLength;
    }
    static VectorType calculate ( const VectorType &v )
    {
      const auto invLength ( 1 / length ( v ) );
      return VectorType ( v[0] * invLength, v[1] * invLength );
    }
  };
  template < class VectorType > struct Normalize < VectorType, 3 >
  {
    static void calculate ( const VectorType &v, VectorType &n, typename VectorType::value_type *originalLength )
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
    static VectorType calculate ( const VectorType &v )
    {
      const auto invLength ( 1 / length ( v ) );
      return VectorType ( v[0] * invLength, v[1] * invLength, v[2] * invLength );
    }
  };
  template < class VectorType > struct Normalize < VectorType, 4 >
  {
    static void calculate ( const VectorType &v, VectorType &n, typename VectorType::value_type *originalLength )
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
      n[3] = v[3] * invLength;
    }
    static VectorType calculate ( const VectorType &v )
    {
      const auto invLength ( 1 / length ( v ) );
      return VectorType ( v[0] * invLength, v[1] * invLength, v[2] * invLength, v[3] * invLength );
    }
  };
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
  typedef Detail::Normalize < VectorType, VectorType::SIZE > Normalize;
  Normalize::calculate ( v, n, originalLength );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return a normalized vector.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline VectorType normalize ( const VectorType &v )
{
  typedef Detail::Normalize < VectorType, VectorType::SIZE > Normalize;
  return Normalize::calculate ( v );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Details for the equal function.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  template < class VectorType, unsigned int > struct IsEqual{};
  template < class VectorType > struct IsEqual < VectorType, 2 >
  {
    static bool check ( const VectorType &a, const VectorType &b )
    {
      return (
        ( a[0] == b[0] ) &&
        ( a[1] == b[1] ) );
    }
  };
  template < class VectorType > struct IsEqual < VectorType, 3 >
  {
    static bool check ( const VectorType &a, const VectorType &b )
    {
      return (
        ( a[0] == b[0] ) &&
        ( a[1] == b[1] ) &&
        ( a[2] == b[2] ) );
    }
  };
  template < class VectorType > struct IsEqual < VectorType, 4 >
  {
    static bool check ( const VectorType &a, const VectorType &b )
    {
      return (
        ( a[0] == b[0] ) &&
        ( a[1] == b[1] ) &&
        ( a[2] == b[2] ) &&
        ( a[3] == b[3] ) );
    }
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if they are equal.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
bool equal ( const VectorType &a, const VectorType &b )
{
  typedef Detail::IsEqual < VectorType, VectorType::SIZE > IsEqual;
  return IsEqual::check ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Details for the "for each" function.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  template < class VectorType, class Fun, unsigned int > struct ForEach{};
  template < class VectorType, class Fun > struct ForEach < VectorType, Fun, 2 >
  {
    static void execute ( const VectorType &v, Fun f )
    {
      f ( v[0] );
      f ( v[1] );
    }
  };
  template < class VectorType, class Fun > struct ForEach < VectorType, Fun, 3 >
  {
    static void execute ( const VectorType &v, Fun f )
    {
      f ( v[0] );
      f ( v[1] );
      f ( v[2] );
    }
  };
  template < class VectorType, class Fun > struct ForEach < VectorType, Fun, 4 >
  {
    static void execute ( const VectorType &v, Fun f )
    {
      f ( v[0] );
      f ( v[1] );
      f ( v[2] );
      f ( v[3] );
    }
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  Call the given function for each value.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType, class Fun >
void each ( const VectorType &v, Fun f )
{
  typedef Detail::ForEach < VectorType, Fun, VectorType::SIZE > ForEach;
  ForEach::execute ( v, f );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Details for vector addition.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  template < class VectorType, unsigned int > struct Addition{};
  template < class VectorType > struct Addition < VectorType, 2 >
  {
    static void calculate ( const VectorType &a, const VectorType &b, VectorType &c )
    {
      c[0] = a[0] + b[0];
      c[1] = a[1] + b[1];
    }
    static VectorType calculate ( const VectorType &a, const VectorType &b )
    {
      return VectorType ( a[0] + b[0], a[1] + b[1] );
    }
  };
  template < class VectorType > struct Addition < VectorType, 3 >
  {
    static void calculate ( const VectorType &a, const VectorType &b, VectorType &c )
    {
      c[0] = a[0] + b[0];
      c[1] = a[1] + b[1];
      c[2] = a[2] + b[2];
    }
    static VectorType calculate ( const VectorType &a, const VectorType &b )
    {
      return VectorType ( a[0] + b[0], a[1] + b[1], a[2] + b[2] );
    }
  };
  template < class VectorType > struct Addition < VectorType, 4 >
  {
    static void calculate ( const VectorType &a, const VectorType &b, VectorType &c )
    {
      c[0] = a[0] + b[0];
      c[1] = a[1] + b[1];
      c[2] = a[2] + b[2];
      c[3] = a[3] + b[3];
    }
    static VectorType calculate ( const VectorType &a, const VectorType &b )
    {
      return VectorType ( a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3] );
    }
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  Addition.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline void add ( const VectorType &a, const VectorType &b, VectorType &c )
{
  typedef Detail::Addition < VectorType, VectorType::SIZE > Addition;
  Addition::calculate ( a, b, c );
}
template < class VectorType >
inline VectorType add ( const VectorType &a, const VectorType &b )
{
  typedef Detail::Addition < VectorType, VectorType::SIZE > Addition;
  return Addition::calculate ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Details for vector subtraction.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  template < class VectorType, unsigned int > struct Subtraction{};
  template < class VectorType > struct Subtraction < VectorType, 2 >
  {
    static void calculate ( const VectorType &a, const VectorType &b, VectorType &c )
    {
      c[0] = a[0] - b[0];
      c[1] = a[1] - b[1];
    }
    static VectorType calculate ( const VectorType &a, const VectorType &b )
    {
      return VectorType ( a[0] - b[0], a[1] - b[1] );
    }
  };
  template < class VectorType > struct Subtraction < VectorType, 3 >
  {
    static void calculate ( const VectorType &a, const VectorType &b, VectorType &c )
    {
      c[0] = a[0] - b[0];
      c[1] = a[1] - b[1];
      c[2] = a[2] - b[2];
    }
    static VectorType calculate ( const VectorType &a, const VectorType &b )
    {
      return VectorType ( a[0] - b[0], a[1] - b[1], a[2] - b[2] );
    }
  };
  template < class VectorType > struct Subtraction < VectorType, 4 >
  {
    static void calculate ( const VectorType &a, const VectorType &b, VectorType &c )
    {
      c[0] = a[0] - b[0];
      c[1] = a[1] - b[1];
      c[2] = a[2] - b[2];
      c[3] = a[3] - b[3];
    }
    static VectorType calculate ( const VectorType &a, const VectorType &b )
    {
      return VectorType ( a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3] );
    }
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  Subtraction.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline void subtract ( const VectorType &a, const VectorType &b, VectorType &c )
{
  typedef Detail::Subtraction < VectorType, VectorType::SIZE > Subtraction;
  Subtraction::calculate ( a, b, c );
}
template < class VectorType >
inline VectorType subtract ( const VectorType &a, const VectorType &b )
{
  typedef Detail::Subtraction < VectorType, VectorType::SIZE > Subtraction;
  return Subtraction::calculate ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Details for vector scaling.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  template < class VectorType, class ScalarType, unsigned int > struct Scale{};
  template < class VectorType, class ScalarType > struct Scale < VectorType, ScalarType, 2 >
  {
    static void calculate ( const VectorType &v, const ScalarType s, VectorType &a )
    {
      a[0] = v[0] * s;
      a[1] = v[1] * s;
    }
    static VectorType calculate ( const VectorType &v, const ScalarType s )
    {
      return VectorType ( v[0] * s, v[1] * s );
    }
  };
  template < class VectorType, class ScalarType > struct Scale < VectorType, ScalarType, 3 >
  {
    static void calculate ( const VectorType &v, const ScalarType s, VectorType &a )
    {
      a[0] = v[0] * s;
      a[1] = v[1] * s;
      a[2] = v[2] * s;
    }
    static VectorType calculate ( const VectorType &v, const ScalarType s )
    {
      return VectorType ( v[0] * s, v[1] * s, v[2] * s );
    }
  };
  template < class VectorType, class ScalarType > struct Scale < VectorType, ScalarType, 4 >
  {
    static void calculate ( const VectorType &v, const ScalarType s, VectorType &a )
    {
      a[0] = v[0] * s;
      a[1] = v[1] * s;
      a[2] = v[2] * s;
      a[3] = v[3] * s;
    }
    static VectorType calculate ( const VectorType &v, const ScalarType s )
    {
      return VectorType ( v[0] * s, v[1] * s, v[2] * s, v[3] * s );
    }
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  Scale.
//
///////////////////////////////////////////////////////////////////////////////

template < class VectorType, class ScalarType >
inline void scale ( const VectorType &v, const ScalarType s, VectorType &a )
{
  typedef Detail::Scale < VectorType, ScalarType, VectorType::SIZE > Scale;
  Scale::calculate ( v, s, a );
}
template < class VectorType, class ScalarType >
inline VectorType scale ( const VectorType &v, const ScalarType s )
{
  typedef Detail::Scale < VectorType, ScalarType, VectorType::SIZE > Scale;
  return Scale::calculate ( v, s );
}


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_VECTOR_FUNCTIONS_H_
