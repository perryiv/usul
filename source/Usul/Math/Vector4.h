
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  4D vector class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_VECTOR_4D_H_
#define _USUL_MATH_VECTOR_4D_H_

#include "Usul/Math/ErrorChecker.h"

#include <cmath>


namespace Usul {
namespace Math {


template
<
  typename T,
  typename IndexType = unsigned int
>
class Vector4
{
public:

  /////////////////////////////////////////////////////////////////////////////
  //
  //  Useful typedefs.
  //
  /////////////////////////////////////////////////////////////////////////////

  typedef T value_type;
  typedef IndexType size_type;
  typedef Vector4 < T, IndexType > ThisType;


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Enums.
  //
  /////////////////////////////////////////////////////////////////////////////

  enum
  {
    SIZE = 4,
    LAST = SIZE - 1
  };


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Default constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Vector4()
  {
    _v[0] = T();
    _v[1] = T();
    _v[2] = T();
    _v[3] = T();
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  explicit Vector4 ( const T v[SIZE] )
  {
    _v[0] = v[0];
    _v[1] = v[1];
    _v[2] = v[2];
    _v[3] = v[3];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Vector4 ( T v0, T v1, T v2, T v3 )
  {
    _v[0] = v0;
    _v[1] = v1;
    _v[2] = v2;
    _v[3] = v3;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const Vector4 &v )
  {
    _v[0] = v[0];
    _v[1] = v[1];
    _v[2] = v[2];
    _v[3] = v[3];
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
    _v[2] = v[2];
    _v[3] = v[3];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( T v0, T v1, T v2, T v3 )
  {
    _v[0] = v0;
    _v[1] = v1;
    _v[2] = v2;
    _v[3] = v3;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Bracket operators.
  //
  /////////////////////////////////////////////////////////////////////////////

  T &operator [] ( size_type i )
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, i );
    return _v[i];
  }
  const T &operator [] ( size_type i ) const
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, i );
    return _v[i];
  }


private:

  T _v[SIZE];
};


///////////////////////////////////////////////////////////////////////////////
//
//  Add the two vectors.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void add ( const Vector4 < T, I > &a, const Vector4 < T, I > &b, Vector4 < T, I > &c )
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
  c[3] = a[3] + b[3];
}
template < class T, class I >
inline Vector4 < T, I > add ( const Vector4 < T, I > &a, const Vector4 < T, I > &b )
{
  return Vector4 < T, I > ( a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3] );
}
template < class T, class I >
inline Vector4 < T, I > operator + ( const Vector4 < T, I > &a, const Vector4 < T, I > &b )
{
  return add ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Subtract the two vectors.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void subtract ( const Vector4 < T, I > &a, const Vector4 < T, I > &b, Vector4 < T, I > &c )
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
  c[3] = a[3] - b[3];
}
template < class T, class I >
inline Vector4 < T, I > subtract ( const Vector4 < T, I > &a, const Vector4 < T, I > &b )
{
  return Vector4 < T, I > ( a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3] );
}
template < class T, class I >
inline Vector4 < T, I > operator - ( const Vector4 < T, I > &a, const Vector4 < T, I > &b )
{
  return subtract ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Scale the vector.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void scale ( const Vector4 < T, I > &v, const T &s, Vector4 < T, I > &a )
{
  a[0] = v[0] * s;
  a[1] = v[1] * s;
  a[2] = v[2] * s;
  a[3] = v[3] * s;
}
template < class T, class I >
inline Vector4 < T, I > scale ( const Vector4 < T, I > &v, const T &s )
{
  return Vector4 < T, I > ( v[0] * s, v[1] * s, v[2] * s, v[3] * s );
}
template < class T, class I >
inline Vector4 < T, I > operator * ( const Vector4 < T, I > &v, const T &s )
{
  return scale ( v, s );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Call the given function for each value.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I, class Fun >
inline void each ( const Vector4 < T, I > &v, Fun f )
{
  f ( v[0] );
  f ( v[1] );
  f ( v[2] );
  f ( v[3] );
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if they are equal.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline bool equal ( const Vector4 < T, I > &a, const Vector4 < T, I > &b )
{
  return (
    ( a[0] == b[0] ) &&
    ( a[1] == b[1] ) &&
    ( a[2] == b[2] ) &&
    ( a[3] == b[3] ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the dot product.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline T dot ( const Vector4 < T, I > &a, const Vector4 < T, I > &b )
{
  return (
    ( a[0] * b[0] ) +
    ( a[1] * b[1] ) +
    ( a[2] * b[2] ) +
    ( a[3] * b[3] ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the length.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline T length ( const Vector4 < T, I > &v )
{
  return std::sqrt ( dot ( v, v ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Normalize the vector.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void normalize ( const Vector4 < T, I > &v, Vector4 < T, I > &n, T *originalLength = nullptr )
{
  const T currentLength ( length ( v ) );
  const T invLength ( static_cast < T > ( 1 ) / currentLength );

  if ( originalLength )
  {
    *originalLength = currentLength;
  }

  n[0] = v[0] * invLength;
  n[1] = v[1] * invLength;
  n[2] = v[2] * invLength;
  n[3] = v[3] * invLength;
}
template < class T, class I >
inline Vector4 < T, I > normalize ( const Vector4 < T, I > &v )
{
  const T invLength ( static_cast < T > ( 1 ) / length ( v ) );
  return Vector4 < T, I > ( v[0] * invLength, v[1] * invLength, v[2] * invLength, v[3] * invLength );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Useful typedefs.
//
///////////////////////////////////////////////////////////////////////////////

typedef Vector4 < char           > Vec4c;
typedef Vector4 < short          > Vec4s;
typedef Vector4 < int            > Vec4i;
typedef Vector4 < long           > Vec4l;

typedef Vector4 < unsigned char  > Vec4uc;
typedef Vector4 < unsigned short > Vec4us;
typedef Vector4 < unsigned int   > Vec4ui;
typedef Vector4 < unsigned long  > Vec4ul;

typedef Vector4 < float          > Vec4f;
typedef Vector4 < double         > Vec4d;
typedef Vector4 < long double    > Vec4ld;


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_VECTOR_4D_H_
