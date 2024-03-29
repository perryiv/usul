
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  2D vector class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_VECTOR_2D_H_
#define _USUL_MATH_VECTOR_2D_H_

#include "Usul/Errors/Check.h"
#include "Usul/Math/Base.h"

#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <type_traits>


namespace Usul {
namespace Math {


template
<
  typename T,
  typename IndexType = unsigned int
>
class Vector2
{
public:

  /////////////////////////////////////////////////////////////////////////////
  //
  //  Useful typedefs.
  //
  /////////////////////////////////////////////////////////////////////////////

  typedef T value_type;
  typedef IndexType size_type;
  typedef Vector2 < T, IndexType > ThisType;


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Enums.
  //
  /////////////////////////////////////////////////////////////////////////////

  enum
  {
    SIZE = 2,
    LAST = SIZE - 1
  };


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Default constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  constexpr Vector2() : _v { T(), T() }
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Copy constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  constexpr Vector2 ( const ThisType &v ) :
    _v { v._v[0], v._v[1] }
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  constexpr explicit Vector2 ( const T v[SIZE] ) :
    _v { v[0], v[1] }
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  constexpr Vector2 ( T v0, T v1 ) :
    _v { v0, v1 }
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Assignment.
  //
  /////////////////////////////////////////////////////////////////////////////

  Vector2 &operator = ( const Vector2 &v )
  {
    this->set ( v );
    return *this;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const Vector2 &v )
  {
    _v[0] = v[0];
    _v[1] = v[1];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const T v[SIZE] )
  {
    _v[0] = v[0];
    _v[1] = v[1];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( T v0, T v1 )
  {
    _v[0] = v0;
    _v[1] = v1;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Bracket operators.
  //
  /////////////////////////////////////////////////////////////////////////////

  T &operator [] ( size_type i )
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, i, "Index out of range in Vector2 [] operator" );
    return _v[i];
  }
  const T &operator [] ( size_type i ) const
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, i, "Index out of range in Vector2 [] operator" );
    return _v[i];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Get the internal array. Use with caution.
  //
  /////////////////////////////////////////////////////////////////////////////

  const T *get() const { return _v; }
  T *      get()       { return _v; }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Added for compatability reasons.
  //
  /////////////////////////////////////////////////////////////////////////////

  const T *ptr() const { return this->get(); }
  T *      ptr()       { return this->get(); }


private:

  T _v[SIZE];
};


///////////////////////////////////////////////////////////////////////////////
//
//  Add the two vectors.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void add ( const Vector2 < T, I > &a, const Vector2 < T, I > &b, Vector2 < T, I > &c )
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
}
template < class T, class I >
inline Vector2 < T, I > add ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  return Vector2 < T, I > ( a[0] + b[0], a[1] + b[1] );
}
template < class T, class I >
inline Vector2 < T, I > operator + ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  return add ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Subtract the two vectors.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void subtract ( const Vector2 < T, I > &a, const Vector2 < T, I > &b, Vector2 < T, I > &c )
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
}
template < class T, class I >
inline Vector2 < T, I > subtract ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  return Vector2 < T, I > ( a[0] - b[0], a[1] - b[1] );
}
template < class T, class I >
inline Vector2 < T, I > operator - ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  return subtract ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Scale the vector.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void scale ( const Vector2 < T, I > &v, const T &s, Vector2 < T, I > &a )
{
  a[0] = v[0] * s;
  a[1] = v[1] * s;
}
template < class T, class I >
inline Vector2 < T, I > scale ( const Vector2 < T, I > &v, const T &s )
{
  return Vector2 < T, I > ( v[0] * s, v[1] * s );
}
template < class T, class I >
inline Vector2 < T, I > operator * ( const Vector2 < T, I > &v, const T &s )
{
  return scale ( v, s );
}




///////////////////////////////////////////////////////////////////////////////
//
//  Overloaded less-than operator so that it can be a key in std::map.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline bool operator < ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  // Same algorithm as osg::Vec3f.
  if ( a[0] < b[0] )
  {
    return true;
  }
  else if ( a[0] > b[0] )
  {
    return false;
  }
  else
  {
    return ( a[1] < b[1] );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Call the given function for each value.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I, class Fun >
inline void each ( const Vector2 < T, I > &v, Fun f )
{
  f ( v[0] );
  f ( v[1] );
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if they are equal.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline bool equal ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  return (
    ( a[0] == b[0] ) &&
    ( a[1] == b[1] ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the dot product.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline T dot ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  return (
    ( a[0] * b[0] ) +
    ( a[1] * b[1] ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the length.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline T length ( const Vector2 < T, I > &v )
{
  return std::sqrt ( dot ( v, v ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the absolute value of the given vector.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline Vector2 < T, I > absolute ( const Vector2 < T, I > &v )
{
  return Vector2 < T, I > (
    Usul::Math::absolute ( v[0] ),
    Usul::Math::absolute ( v[1] )
  );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Normalize the vector.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void normalize ( const Vector2 < T, I > &v, Vector2 < T, I > &n, T *originalLength = nullptr )
{
  const T currentLength ( length ( v ) );
  const T invLength ( static_cast < T > ( 1 ) / currentLength );

  if ( originalLength )
  {
    *originalLength = currentLength;
  }

  n[0] = v[0] * invLength;
  n[1] = v[1] * invLength;
}
template < class T, class I >
inline Vector2 < T, I > normalize ( const Vector2 < T, I > &v )
{
  const T invLength ( static_cast < T > ( 1 ) / length ( v ) );
  return Vector2 < T, I > ( v[0] * invLength, v[1] * invLength );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the angle between the two vectors.
//  theta = acos ( A dot B / |A||B| )
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline T angle ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  const T AdotB ( dot ( a, b ) );
  const T lengthA ( length ( a ) );
  const T lengthB ( length ( b ) );
  return std::acos ( AdotB / ( lengthA * lengthB ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the square of the distance between the two points.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
static T distanceSquared ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  return (
    ( ( a[0] - b[0] ) * ( a[0] - b[0] ) ) +
    ( ( a[1] - b[1] ) * ( a[1] - b[1] ) ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the distance between the two points.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline T distance ( const Vector2 < T, I > &a, const Vector2 < T, I > &b )
{
  return std::sqrt ( distanceSquared ( a, b ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the linear interpolation between the two given vectors.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void lerp ( const Vector2 < T, I > &a, const Vector2 < T, I > &b, const T &u, Vector2 < T, I > &c )
{
  c[0] = ( a[0] + u * ( b[0] - a[0] ) );
  c[1] = ( a[1] + u * ( b[1] - a[1] ) );
}
template < class T, class I >
inline Vector2 < T, I > lerp ( const Vector2 < T, I > &a, const Vector2 < T, I > &b, const T &u )
{
  return Vector2 < T, I > (
    ( a[0] + u * ( b[0] - a[0] ) ),
    ( a[1] + u * ( b[1] - a[1] ) )
  );
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if the vector elements are finite.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline bool isFinite ( const Vector2 < T, I > &v )
{
  // Get the raw array for speed.
  const T *va ( v.get() );

  return (
    std::isfinite ( va[0] ) &&
    std::isfinite ( va[1] )
  );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Generate a vector with random numbers between the given range.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void random ( Vector2 < T, I > &v, const T &mn = 0, const T &mx = 1 )
{
  // Make sure we're working with a floating point number type.
  static_assert ( std::is_floating_point < T >::value, "Not a floating-point number type" );

  // Shortcut.
  const T randMax = static_cast < T > ( RAND_MAX );

  // Assign random numbers in the range.
  v[0] = ( mn + ( ( static_cast < T > ( std::rand() ) / randMax ) * ( mx - mn ) ) );
  v[1] = ( mn + ( ( static_cast < T > ( std::rand() ) / randMax ) * ( mx - mn ) ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Clamp the vector to the given range.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void clamp ( Vector2 < T, I > &v, const T &mn, const T &mx )
{
  v[0] = Usul::Math::clamp ( v[0], mn, mx );
  v[1] = Usul::Math::clamp ( v[1], mn, mx );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the average of the vector's components.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline T average ( const Vector2 < T, I > &v )
{
  constexpr T denom = static_cast < T > ( Vector2 < T, I > :: SIZE );
  return ( ( v[0] + v[1] ) / denom );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Useful typedefs.
//
///////////////////////////////////////////////////////////////////////////////

typedef Vector2 < char           > Vec2c;
typedef Vector2 < short          > Vec2s;
typedef Vector2 < int            > Vec2i;
typedef Vector2 < long           > Vec2l;

typedef Vector2 < unsigned char  > Vec2uc;
typedef Vector2 < unsigned short > Vec2us;
typedef Vector2 < unsigned int   > Vec2ui;
typedef Vector2 < unsigned long  > Vec2ul;

typedef Vector2 < float          > Vec2f;
typedef Vector2 < double         > Vec2d;
typedef Vector2 < long double    > Vec2ld;


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_VECTOR_2D_H_
