
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  A 4x4 matrix class that uses a 1D array of 16.
//  The matrix is stored row-major as follows:
//
//    [ 0,  1,  2,  3,
//      4,  5,  6,  7,
//      8,  9, 10, 11,
//     12, 13, 14, 15 ]
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_4_BY_4_MATRIX_CLASS_H_
#define _USUL_MATH_4_BY_4_MATRIX_CLASS_H_

#include "Usul/Math/ErrorChecker.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Math/Vector4.h"

// For readability below.
#define R0C0  0
#define R0C1  1
#define R0C2  2
#define R0C3  3
#define R1C0  4
#define R1C1  5
#define R1C2  6
#define R1C3  7
#define R2C0  8
#define R2C1  9
#define R2C2 10
#define R2C3 11
#define R3C0 12
#define R3C1 13
#define R3C2 14
#define R3C3 15


namespace Usul {
namespace Math {


template
<
  typename T,
  typename IndexType = unsigned int
>
class Matrix44
{
public:

  /////////////////////////////////////////////////////////////////////////////
  //
  //  Useful typedefs.
  //
  /////////////////////////////////////////////////////////////////////////////

  typedef T value_type;
  typedef IndexType size_type;
  typedef Matrix44 < T, IndexType > ThisType;


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Enumerations, some to help with indices.
  //
  //    0  4   8  12
  //    1  5   9  13
  //    2  6  10  14
  //    3  7  11  15
  //
  /////////////////////////////////////////////////////////////////////////////

  enum
  {
    DIMENSION       = 4,
    SIZE            = 16,
    LAST            = SIZE - 1,
    TRANSLATION_X   = R0C3,
    TRANSLATION_Y   = R1C3,
    TRANSLATION_Z   = R2C3,
    SCALE_X         = R0C0,
    SCALE_Y         = R1C1,
    SCALE_Z         = R2C2,
  };


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Default constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Matrix44 ( bool initialize = true )
  {
    if ( initialize )
    {
      _m[R0C0] = 1; _m[R0C1] = 0; _m[R0C2] = 0; _m[R0C3] = 0;
      _m[R1C0] = 0; _m[R1C1] = 1; _m[R1C2] = 0; _m[R1C3] = 0;
      _m[R2C0] = 0; _m[R2C1] = 0; _m[R2C2] = 1; _m[R2C3] = 0;
      _m[R3C0] = 0; _m[R3C1] = 0; _m[R3C2] = 0; _m[R3C3] = 1;
    }
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  explicit Matrix44 ( const T m[SIZE] )
  {
    this->set ( m );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Copy constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Matrix44 ( const ThisType &m )
  {
    this->set ( m );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const T m[SIZE] )
  {
    _m[R0C0] = m[R0C0];
    _m[R0C1] = m[R0C1];
    _m[R0C2] = m[R0C2];
    _m[R0C3] = m[R0C3];

    _m[R1C0] = m[R1C0];
    _m[R1C1] = m[R1C1];
    _m[R1C2] = m[R1C2];
    _m[R1C3] = m[R1C3];

    _m[R2C0] = m[R2C0];
    _m[R2C1] = m[R2C1];
    _m[R2C2] = m[R2C2];
    _m[R2C3] = m[R2C3];

    _m[R3C0] = m[R3C0];
    _m[R3C1] = m[R3C1];
    _m[R3C2] = m[R3C2];
    _m[R3C3] = m[R3C3];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const ThisType &m )
  {
    this->set ( m._m );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Bracket operators.
  //
  /////////////////////////////////////////////////////////////////////////////

  T &operator [] ( size_type i )
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, i );
    return _m[i];
  }
  const T &operator [] ( size_type i ) const
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, i );
    return _m[i];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Access the i'th row and j'th column of the matrix as if it were a 2D
  //  array, like matrix(i,j).
  //
  /////////////////////////////////////////////////////////////////////////////

  T &operator () ( size_type i, size_type j )
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::DIMENSION, i );
    USUL_CHECK_INDEX_RANGE ( ThisType::DIMENSION, j );

    const size_type index ( j * ThisType::DIMENSION + i );
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, index );

    return _m[index];
  }
  const T &operator () ( size_type i, size_type j ) const
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::DIMENSION, i );
    USUL_CHECK_INDEX_RANGE ( ThisType::DIMENSION, j );

    const size_type index ( j * ThisType::DIMENSION + i );
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, index );

    return _m[index];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Get the internal array. Use with caution.
  //
  /////////////////////////////////////////////////////////////////////////////

  const T *get() const { return _m; }
  T *      get()       { return _m; }


private:

  T _m[SIZE];
};


///////////////////////////////////////////////////////////////////////////////
//
//  Call the given function for each value.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I, class Fun >
inline void each ( const Matrix44 < T, I > &m, Fun f )
{
  f ( m[ 0] );
  f ( m[ 1] );
  f ( m[ 2] );
  f ( m[ 3] );

  f ( m[ 4] );
  f ( m[ 5] );
  f ( m[ 6] );
  f ( m[ 7] );

  f ( m[ 8] );
  f ( m[ 9] );
  f ( m[10] );
  f ( m[11] );

  f ( m[12] );
  f ( m[13] );
  f ( m[14] );
  f ( m[15] );
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if they are equal.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline bool equal ( const Matrix44 < T, I > &a, const Matrix44 < T, I > &b )
{
  return (
    ( a[ 0] == b[ 0] ) &&
    ( a[ 1] == b[ 1] ) &&
    ( a[ 2] == b[ 2] ) &&
    ( a[ 3] == b[ 3] ) &&
    ( a[ 4] == b[ 4] ) &&
    ( a[ 5] == b[ 5] ) &&
    ( a[ 6] == b[ 6] ) &&
    ( a[ 7] == b[ 7] ) &&
    ( a[ 8] == b[ 8] ) &&
    ( a[ 9] == b[ 9] ) &&
    ( a[10] == b[10] ) &&
    ( a[11] == b[11] ) &&
    ( a[12] == b[12] ) &&
    ( a[13] == b[13] ) &&
    ( a[14] == b[14] ) &&
    ( a[15] == b[15] ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Multiply the two matrices, c = a * b.
//  https://github.com/toji/gl-matrix
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void multiply ( const Matrix44 < T, I > &a, const Matrix44 < T, I > &b, Matrix44 < T, I > &c )
{
  // Get the raw arrays for speed.
  const T *aa ( a.get() );
  const T *ba ( b.get() );
  T *ca ( c.get() );

  // This was copied from JavaScript, and using local variables is faster there.
  // TODO: Is that true for C++ too ?
  const T a00 ( aa[R0C0] ), a01 ( aa[R0C1] ), a02 ( aa[R0C2] ), a03 ( aa[R0C3] );
  const T a10 ( aa[R1C0] ), a11 ( aa[R1C1] ), a12 ( aa[R1C2] ), a13 ( aa[R1C3] );
  const T a20 ( aa[R2C0] ), a21 ( aa[R2C1] ), a22 ( aa[R2C2] ), a23 ( aa[R2C3] );
  const T a30 ( aa[R3C0] ), a31 ( aa[R3C1] ), a32 ( aa[R3C2] ), a33 ( aa[R3C3] );

  const T b00 ( ba[R0C0] ), b01 ( ba[R0C1] ), b02 ( ba[R0C2] ), b03 ( ba[R0C3] );
  const T b10 ( ba[R1C0] ), b11 ( ba[R1C1] ), b12 ( ba[R1C2] ), b13 ( ba[R1C3] );
  const T b20 ( ba[R2C0] ), b21 ( ba[R2C1] ), b22 ( ba[R2C2] ), b23 ( ba[R2C3] );
  const T b30 ( ba[R3C0] ), b31 ( ba[R3C1] ), b32 ( ba[R3C2] ), b33 ( ba[R3C3] );

  //  a00 a01 a02 a03   b00 b01 b02 b03
  //  a10 a11 a12 a13 * b10 b11 b12 b13
  //  a20 a21 a22 a23   b20 b21 b22 b23
  //  a30 a31 a32 a33   b30 b31 b32 b33

  ca[R0C0] = a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30;
  ca[R0C1] = a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31;
  ca[R0C2] = a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32;
  ca[R0C3] = a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33;

  ca[R1C0] = a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30;
  ca[R1C1] = a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31;
  ca[R1C2] = a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32;
  ca[R1C3] = a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33;

  ca[R2C0] = a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30;
  ca[R2C1] = a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31;
  ca[R2C2] = a20 * b02 + a21 * b12 + a22 * b22 + a23 * b32;
  ca[R2C3] = a20 * b03 + a21 * b13 + a22 * b23 + a23 * b33;

  ca[R3C0] = a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30;
  ca[R3C1] = a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31;
  ca[R3C2] = a30 * b02 + a31 * b12 + a32 * b22 + a33 * b32;
  ca[R3C3] = a30 * b03 + a31 * b13 + a32 * b23 + a33 * b33;
}
template < class T, class I >
inline Matrix44 < T, I > multiply ( const Matrix44 < T, I > &a, const Matrix44 < T, I > &b )
{
  Matrix44 < T, I > c ( false ); // Do not initialize it to identity.
  multiply ( a, b, c );
  return c;
}
template < class T, class I >
inline Matrix44 < T, I > operator * ( const Matrix44 < T, I > &a, const Matrix44 < T, I > &b )
{
  return multiply ( a, b );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Transform the vector by the matrix, b = m * a.
//  https://github.com/toji/gl-matrix
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void multiply ( const Matrix44 < T, I > &m, const Vector3 < T, I > &a, Vector3 < T, I > &b )
{
  // Get the raw arrays for speed.
  const T *ma ( m.get() );
  const T *aa ( a.get() );
  T *ba ( b.get() );

  const T x ( aa[0] );
  const T y ( aa[1] );
  const T z ( aa[2] );

  //  m00 m01 m02 m03   x
  //  m10 m11 m12 m13 * y
  //  m20 m21 m22 m23   z
  //  m30 m31 m32 m33   1

  ba[0] = ( ma[R0C0] * x ) + ( ma[R0C1] * y ) + ( ma[R0C2] * z ) + ( ma[R0C3] );
  ba[1] = ( ma[R1C0] * x ) + ( ma[R1C1] * y ) + ( ma[R1C2] * z ) + ( ma[R1C3] );
  ba[2] = ( ma[R2C0] * x ) + ( ma[R2C1] * y ) + ( ma[R2C2] * z ) + ( ma[R2C3] );
}
template < class T, class I >
inline Matrix44 < T, I > multiply ( const Matrix44 < T, I > &m, const Vector3 < T, I > &a )
{
  Vector3 < T, I > b ( false ); // Do not initialize.
  multiply ( m, a, b );
  return b;
}
template < class T, class I >
inline Matrix44 < T, I > operator * ( const Matrix44 < T, I > &m, const Vector3 < T, I > &a )
{
  return multiply ( m, a );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Transform the vector by the matrix, b = m * a.
//  https://github.com/toji/gl-matrix
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void multiply ( const Matrix44 < T, I > &m, const Vector4 < T, I > &a, Vector4 < T, I > &b )
{
  // Get the raw arrays for speed.
  const T *ma ( m.get() );
  const T *aa ( a.get() );
  T *ba ( b.get() );

  const T x ( aa[0] );
  const T y ( aa[1] );
  const T z ( aa[2] );
  const T w ( aa[3] );

  //  m00 m01 m02 m03   x
  //  m10 m11 m12 m13 * y
  //  m20 m21 m22 m23   z
  //  m30 m31 m32 m33   w

  ba[0] = ( ma[ 0] * x ) + ( ma[ 4] * y ) + ( ma[ 8] * z ) + ( ma[12] * w );
  ba[1] = ( ma[ 1] * x ) + ( ma[ 5] * y ) + ( ma[ 9] * z ) + ( ma[13] * w );
  ba[2] = ( ma[ 2] * x ) + ( ma[ 6] * y ) + ( ma[10] * z ) + ( ma[14] * w );
  ba[3] = ( ma[ 3] * x ) + ( ma[ 7] * y ) + ( ma[11] * z ) + ( ma[15] * w );
}
template < class T, class I >
inline Matrix44 < T, I > multiply ( const Matrix44 < T, I > &m, const Vector4 < T, I > &a )
{
  Vector4 < T, I > b ( false ); // Do not initialize.
  multiply ( m, a, b );
  return b;
}
template < class T, class I >
inline Matrix44 < T, I > operator * ( const Matrix44 < T, I > &m, const Vector4 < T, I > &a )
{
  return multiply ( m, a );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Useful typedefs.
//
///////////////////////////////////////////////////////////////////////////////

typedef Matrix44 < char           > Matrix44c;
typedef Matrix44 < short          > Matrix44s;
typedef Matrix44 < int            > Matrix44i;
typedef Matrix44 < long           > Matrix44l;

typedef Matrix44 < unsigned char  > Matrix44uc;
typedef Matrix44 < unsigned short > Matrix44us;
typedef Matrix44 < unsigned int   > Matrix44ui;
typedef Matrix44 < unsigned long  > Matrix44ul;

typedef Matrix44 < float          > Matrix44f;
typedef Matrix44 < double         > Matrix44d;
typedef Matrix44 < long double    > Matrix44ld;


} // namespace Math
} // namespace Usul


// Clean up.
#undef R0C0
#undef R1C0
#undef R2C0
#undef R3C0
#undef R0C1
#undef R1C1
#undef R2C1
#undef R3C1
#undef R0C2
#undef R1C2
#undef R2C2
#undef R3C2
#undef R0C3
#undef R1C3
#undef R2C3
#undef R3C3


#endif // _USUL_MATH_4_BY_4_MATRIX_CLASS_H_
