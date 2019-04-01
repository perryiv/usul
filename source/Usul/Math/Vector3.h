
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  3D vector class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_VECTOR_3D_H_
#define _USUL_MATH_VECTOR_3D_H_

#include "Usul/Math/ErrorChecker.h"


namespace Usul {
namespace Math {


template
<
  typename T,
  typename IndexType = unsigned int
>
class Vector3
{
public:

  /////////////////////////////////////////////////////////////////////////////
  //
  //  Useful typedefs.
  //
  /////////////////////////////////////////////////////////////////////////////

  typedef T value_type;
  typedef IndexType size_type;
  typedef Vector3 < T, IndexType > ThisType;


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Enums.
  //
  /////////////////////////////////////////////////////////////////////////////

  enum
  {
    SIZE = 3,
    LAST = SIZE - 1
  };


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Default constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Vector3()
  {
    _v[0] = T();
    _v[1] = T();
    _v[2] = T();
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  explicit Vector3 ( const T v[SIZE] )
  {
    _v[0] = v[0];
    _v[1] = v[1];
    _v[2] = v[2];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Vector3 ( T v0, T v1, T v2 )
  {
    _v[0] = v0;
    _v[1] = v1;
    _v[2] = v2;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const Vector3 &v )
  {
    _v[0] = v[0];
    _v[1] = v[1];
    _v[2] = v[2];
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
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( T v0, T v1, T v2 )
  {
    _v[0] = v0;
    _v[1] = v1;
    _v[2] = v2;
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
inline void add ( const Vector3 < T, I > &a, const Vector3 < T, I > &b, Vector3 < T, I > &c )
{
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
}
template < class T, class I >
inline Vector3 < T, I > add ( const Vector3 < T, I > &a, const Vector3 < T, I > &b )
{
  return Vector3 < T, I > ( a[0] + b[0], a[1] + b[1], a[2] + b[2] );
}
template < class T, class I >
inline Vector3 < T, I > operator + ( const Vector3 < T, I > &a, const Vector3 < T, I > &b )
{
  return add ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Subtract the two vectors.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void subtract ( const Vector3 < T, I > &a, const Vector3 < T, I > &b, Vector3 < T, I > &c )
{
  c[0] = a[0] - b[0];
  c[1] = a[1] - b[1];
  c[2] = a[2] - b[2];
}
template < class T, class I >
inline Vector3 < T, I > subtract ( const Vector3 < T, I > &a, const Vector3 < T, I > &b )
{
  return Vector3 < T, I > ( a[0] - b[0], a[1] - b[1], a[2] - b[2] );
}
template < class T, class I >
inline Vector3 < T, I > operator - ( const Vector3 < T, I > &a, const Vector3 < T, I > &b )
{
  return subtract ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Scale the vector.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void scale ( const Vector3 < T, I > &v, const T &s, Vector3 < T, I > &a )
{
  a[0] = v[0] * s;
  a[1] = v[1] * s;
  a[2] = v[2] * s;
}
template < class T, class I >
inline Vector3 < T, I > scale ( const Vector3 < T, I > &v, const T &s )
{
  return Vector3 < T, I > ( v[0] * s, v[1] * s, v[2] * s );
}
template < class T, class I >
inline Vector3 < T, I > operator * ( const Vector3 < T, I > &v, const T &s )
{
  return scale ( v, s );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Useful typedefs.
//
///////////////////////////////////////////////////////////////////////////////

typedef Vector3 < char           > Vec3c;
typedef Vector3 < short          > Vec3s;
typedef Vector3 < int            > Vec3i;
typedef Vector3 < long           > Vec3l;

typedef Vector3 < unsigned char  > Vec3uc;
typedef Vector3 < unsigned short > Vec3us;
typedef Vector3 < unsigned int   > Vec3ui;
typedef Vector3 < unsigned long  > Vec3ul;

typedef Vector3 < float          > Vec3f;
typedef Vector3 < double         > Vec3d;
typedef Vector3 < long double    > Vec3ld;


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_VECTOR_3D_H_
