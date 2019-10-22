
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  A 4x4 matrix class that uses a 1D array of length 16.
//  The matrix is represented column-major:
//
//    0,  4,  8, 12,
//    1,  5,  9, 13,
//    2,  6, 10, 14,
//    3,  7, 11, 15
//
//  In the internal 1D array, indices 0-3 are interpreted as the first column,
//  not the first row.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_4_BY_4_MATRIX_CLASS_H_
#define _USUL_MATH_4_BY_4_MATRIX_CLASS_H_

#include "Usul/Errors/Check.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Math/Vector4.h"

#include <cmath>
#include <stdexcept>


namespace Usul {
namespace Math {


// For readability below.
const unsigned int R0C0 (  0 );
const unsigned int R1C0 (  1 );
const unsigned int R2C0 (  2 );
const unsigned int R3C0 (  3 );
const unsigned int R0C1 (  4 );
const unsigned int R1C1 (  5 );
const unsigned int R2C1 (  6 );
const unsigned int R3C1 (  7 );
const unsigned int R0C2 (  8 );
const unsigned int R1C2 (  9 );
const unsigned int R2C2 ( 10 );
const unsigned int R3C2 ( 11 );
const unsigned int R0C3 ( 12 );
const unsigned int R1C3 ( 13 );
const unsigned int R2C3 ( 14 );
const unsigned int R3C3 ( 15 );


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
  //  Enumerations.
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

  constexpr Matrix44 ( bool initialize = true )
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

  constexpr explicit Matrix44 ( const T m[SIZE] )
  {
    this->set ( m );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  constexpr Matrix44 (
    T m00, T m01, T m02, T m03,
    T m10, T m11, T m12, T m13,
    T m20, T m21, T m22, T m23,
    T m30, T m31, T m32, T m33 )
  {
    this->set (
      m00, m01, m02, m03,
      m10, m11, m12, m13,
      m20, m21, m22, m23,
      m30, m31, m32, m33 );
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
    _m[ 0] = m[ 0];
    _m[ 1] = m[ 1];
    _m[ 2] = m[ 2];
    _m[ 3] = m[ 3];
    _m[ 4] = m[ 4];
    _m[ 5] = m[ 5];
    _m[ 6] = m[ 6];
    _m[ 7] = m[ 7];
    _m[ 8] = m[ 8];
    _m[ 9] = m[ 9];
    _m[10] = m[10];
    _m[11] = m[11];
    _m[12] = m[12];
    _m[13] = m[13];
    _m[14] = m[14];
    _m[15] = m[15];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( T m00, T m01, T m02, T m03,
             T m10, T m11, T m12, T m13,
             T m20, T m21, T m22, T m23,
             T m30, T m31, T m32, T m33 )
  {
    _m[R0C0] = m00; _m[R0C1] = m01; _m[R0C2] = m02; _m[R0C3] = m03;
    _m[R1C0] = m10; _m[R1C1] = m11; _m[R1C2] = m12; _m[R1C3] = m13;
    _m[R2C0] = m20; _m[R2C1] = m21; _m[R2C2] = m22; _m[R2C3] = m23;
    _m[R3C0] = m30; _m[R3C1] = m31; _m[R3C2] = m32; _m[R3C3] = m33;
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
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, i, "Index out of range in Matrix44 [] operator" );
    return _m[i];
  }
  const T &operator [] ( size_type i ) const
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, i, "Index out of range in Matrix44 [] operator" );
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
    USUL_CHECK_INDEX_RANGE ( ThisType::DIMENSION, i, "Index out of range in Matrix44 () operator" );
    USUL_CHECK_INDEX_RANGE ( ThisType::DIMENSION, j, "Index out of range in Matrix44 () operator" );

    const size_type index ( j * ThisType::DIMENSION + i );
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, index, "Index out of range in Matrix44 () operator" );

    return _m[index];
  }
  const T &operator () ( size_type i, size_type j ) const
  {
    USUL_CHECK_INDEX_RANGE ( ThisType::DIMENSION, i, "Index out of range in Matrix44 () operator" );
    USUL_CHECK_INDEX_RANGE ( ThisType::DIMENSION, j, "Index out of range in Matrix44 () operator" );

    const size_type index ( j * ThisType::DIMENSION + i );
    USUL_CHECK_INDEX_RANGE ( ThisType::SIZE, index, "Index out of range in Matrix44 () operator" );

    return _m[index];
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  this = this * rhs
  //
  /////////////////////////////////////////////////////////////////////////////

  ThisType &operator *= ( const ThisType &rhs )
  {
    ThisType &me ( *this );
    me = rhs * me;
    return me;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Get the internal array. Use with caution.
  //
  /////////////////////////////////////////////////////////////////////////////

  const T *get() const { return _m; }
  T *      get()       { return _m; }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Added for compatability reasons.
  //
  /////////////////////////////////////////////////////////////////////////////

  const T *ptr() const { return this->get(); }
  T *      ptr()       { return this->get(); }


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
  f ( m[R0C0] ); f ( m[R0C1] ); f ( m[R0C2] ); f ( m[R0C3] );
  f ( m[R1C0] ); f ( m[R1C1] ); f ( m[R1C2] ); f ( m[R1C3] );
  f ( m[R2C0] ); f ( m[R2C1] ); f ( m[R2C2] ); f ( m[R2C3] );
  f ( m[R3C0] ); f ( m[R3C1] ); f ( m[R3C2] ); f ( m[R3C3] );
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
    ( a[R0C0] == b[R0C0] ) && ( a[R0C1] == b[R0C1] ) && ( a[R0C2] == b[R0C2] ) && ( a[R0C3] == b[R0C3] ) &&
    ( a[R1C0] == b[R1C0] ) && ( a[R1C1] == b[R1C1] ) && ( a[R1C2] == b[R1C2] ) && ( a[R1C3] == b[R1C3] ) &&
    ( a[R2C0] == b[R2C0] ) && ( a[R2C1] == b[R2C1] ) && ( a[R2C2] == b[R2C2] ) && ( a[R2C3] == b[R2C3] ) &&
    ( a[R3C0] == b[R3C0] ) && ( a[R3C1] == b[R3C1] ) && ( a[R3C2] == b[R3C2] ) && ( a[R3C3] == b[R3C3] ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Transpose the matrix.
//  https://github.com/toji/gl-matrix
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void transpose ( const Matrix44 < T, I > &a, Matrix44 < T, I > &b )
{
  // Get the raw arrays for speed.
  const T *aa ( a.get() );
  T *ba ( b.get() );

  ba[R0C0] = aa[R0C0]; ba[R0C1] = aa[R1C0]; ba[R0C2] = aa[R2C0]; ba[R0C3] = aa[R3C0];
  ba[R1C0] = aa[R0C1]; ba[R1C1] = aa[R1C1]; ba[R1C2] = aa[R2C1]; ba[R1C3] = aa[R3C1];
  ba[R2C0] = aa[R0C2]; ba[R2C1] = aa[R1C2]; ba[R2C2] = aa[R2C2]; ba[R2C3] = aa[R3C2];
  ba[R3C0] = aa[R0C3]; ba[R3C1] = aa[R1C3]; ba[R3C2] = aa[R2C3]; ba[R3C3] = aa[R3C3];
}
template < class T, class I >
inline Matrix44 < T, I > transpose ( const Matrix44 < T, I > &a )
{
  Matrix44 < T, I > b ( false ); // Do not initialize it to identity.
  transpose ( a, b );
  return b;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Make a translation matrix.
//  https://github.com/toji/gl-matrix
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void translate ( const Matrix44 < T, I > &a, const Vector3 < T, I > &v, Matrix44 < T, I > &b )
{
  // Get the raw arrays for speed.
  const T *aa ( a.get() );
  const T *va ( v.get() );
  T *ba ( b.get() );

  // For speed.
  const T x ( va[0] );
  const T y ( va[1] );
  const T z ( va[2] );

  const T a00 ( aa[R0C0] );
  const T a10 ( aa[R1C0] );
  const T a20 ( aa[R2C0] );
  const T a30 ( aa[R3C0] );

  const T a01 ( aa[R0C1] );
  const T a11 ( aa[R1C1] );
  const T a21 ( aa[R2C1] );
  const T a31 ( aa[R3C1] );

  const T a02 ( aa[R0C2] );
  const T a12 ( aa[R1C2] );
  const T a22 ( aa[R2C2] );
  const T a32 ( aa[R3C2] );

  ba[R0C0] = a00;
  ba[R1C0] = a10;
  ba[R2C0] = a20;
  ba[R3C0] = a30;

  ba[R0C1] = a01;
  ba[R1C1] = a11;
  ba[R2C1] = a21;
  ba[R3C1] = a31;

  ba[R0C2] = a02;
  ba[R1C2] = a12;
  ba[R2C2] = a22;
  ba[R3C2] = a32;

  ba[R0C3] = ( a00 * x ) + ( a01 * y ) + ( a02 * z ) + aa[R0C3];
  ba[R1C3] = ( a10 * x ) + ( a11 * y ) + ( a12 * z ) + aa[R1C3];
  ba[R2C3] = ( a20 * x ) + ( a21 * y ) + ( a22 * z ) + aa[R2C3];
  ba[R3C3] = ( a30 * x ) + ( a31 * y ) + ( a32 * z ) + aa[R3C3];
}
template < class T, class I >
inline Matrix44 < T, I > translate ( const Matrix44 < T, I > &a, const Vector3 < T, I > &v )
{
  Matrix44 < T, I > b ( false ); // Do not initialize it to identity.
  translate ( a, v, b );
  return b;
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

  ca[R0C0] = ( a00 * b00 ) + ( a01 * b10 ) + ( a02 * b20 ) + ( a03 * b30 );
  ca[R0C1] = ( a00 * b01 ) + ( a01 * b11 ) + ( a02 * b21 ) + ( a03 * b31 );
  ca[R0C2] = ( a00 * b02 ) + ( a01 * b12 ) + ( a02 * b22 ) + ( a03 * b32 );
  ca[R0C3] = ( a00 * b03 ) + ( a01 * b13 ) + ( a02 * b23 ) + ( a03 * b33 );

  ca[R1C0] = ( a10 * b00 ) + ( a11 * b10 ) + ( a12 * b20 ) + ( a13 * b30 );
  ca[R1C1] = ( a10 * b01 ) + ( a11 * b11 ) + ( a12 * b21 ) + ( a13 * b31 );
  ca[R1C2] = ( a10 * b02 ) + ( a11 * b12 ) + ( a12 * b22 ) + ( a13 * b32 );
  ca[R1C3] = ( a10 * b03 ) + ( a11 * b13 ) + ( a12 * b23 ) + ( a13 * b33 );

  ca[R2C0] = ( a20 * b00 ) + ( a21 * b10 ) + ( a22 * b20 ) + ( a23 * b30 );
  ca[R2C1] = ( a20 * b01 ) + ( a21 * b11 ) + ( a22 * b21 ) + ( a23 * b31 );
  ca[R2C2] = ( a20 * b02 ) + ( a21 * b12 ) + ( a22 * b22 ) + ( a23 * b32 );
  ca[R2C3] = ( a20 * b03 ) + ( a21 * b13 ) + ( a22 * b23 ) + ( a23 * b33 );

  ca[R3C0] = ( a30 * b00 ) + ( a31 * b10 ) + ( a32 * b20 ) + ( a33 * b30 );
  ca[R3C1] = ( a30 * b01 ) + ( a31 * b11 ) + ( a32 * b21 ) + ( a33 * b31 );
  ca[R3C2] = ( a30 * b02 ) + ( a31 * b12 ) + ( a32 * b22 ) + ( a33 * b32 );
  ca[R3C3] = ( a30 * b03 ) + ( a31 * b13 ) + ( a32 * b23 ) + ( a33 * b33 );
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

  const T w ( ( ma[R3C0] * x ) + ( ma[R3C1] * y ) + ( ma[R3C2] * z ) + ( ma[R3C3] ) );
  const T one ( static_cast < T > ( 1 ) );
  const T iw ( one / w );

  ba[0] = ( ( ma[R0C0] * x ) + ( ma[R0C1] * y ) + ( ma[R0C2] * z ) + ( ma[R0C3] ) ) * iw;
  ba[1] = ( ( ma[R1C0] * x ) + ( ma[R1C1] * y ) + ( ma[R1C2] * z ) + ( ma[R1C3] ) ) * iw;
  ba[2] = ( ( ma[R2C0] * x ) + ( ma[R2C1] * y ) + ( ma[R2C2] * z ) + ( ma[R2C3] ) ) * iw;
}
template < class T, class I >
inline Vector3 < T, I > multiply ( const Matrix44 < T, I > &m, const Vector3 < T, I > &a )
{
  Vector3 < T, I > b ( false ); // Do not initialize.
  multiply ( m, a, b );
  return b;
}
template < class T, class I >
inline Vector3 < T, I > operator * ( const Matrix44 < T, I > &m, const Vector3 < T, I > &a )
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

  ba[0] = ( ma[R0C0] * x ) + ( ma[R0C1] * y ) + ( ma[R0C2] * z ) + ( ma[R0C3] * w );
  ba[1] = ( ma[R1C0] * x ) + ( ma[R1C1] * y ) + ( ma[R1C2] * z ) + ( ma[R1C3] * w );
  ba[2] = ( ma[R2C0] * x ) + ( ma[R2C1] * y ) + ( ma[R2C2] * z ) + ( ma[R2C3] * w );
  ba[3] = ( ma[R3C0] * x ) + ( ma[R3C1] * y ) + ( ma[R3C2] * z ) + ( ma[R3C3] * w );
}
template < class T, class I >
inline Vector4 < T, I > multiply ( const Matrix44 < T, I > &m, const Vector4 < T, I > &a )
{
  Vector4 < T, I > b ( false ); // Do not initialize.
  multiply ( m, a, b );
  return b;
}
template < class T, class I >
inline Vector4 < T, I > operator * ( const Matrix44 < T, I > &m, const Vector4 < T, I > &a )
{
  return multiply ( m, a );
}


/////////////////////////////////////////////////////////////////////////////
//
//  Get the determinant of the matrix.
//  https://github.com/toji/gl-matrix
//
/////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline T determinant ( const Matrix44 < T, I > &m )
{
  const T a00 ( m[R0C0] ), a01 ( m[R0C1] ), a02 ( m[R0C2] ), a03 ( m[R0C3] );
  const T a10 ( m[R1C0] ), a11 ( m[R1C1] ), a12 ( m[R1C2] ), a13 ( m[R1C3] );
  const T a20 ( m[R2C0] ), a21 ( m[R2C1] ), a22 ( m[R2C2] ), a23 ( m[R2C3] );
  const T a30 ( m[R3C0] ), a31 ( m[R3C1] ), a32 ( m[R3C2] ), a33 ( m[R3C3] );

  return (
    ( a30 * a21 * a12 * a03 ) - ( a20 * a31 * a12 * a03 ) - ( a30 * a11 * a22 * a03 ) + ( a10 * a31 * a22 * a03 ) +
    ( a20 * a11 * a32 * a03 ) - ( a10 * a21 * a32 * a03 ) - ( a30 * a21 * a02 * a13 ) + ( a20 * a31 * a02 * a13 ) +
    ( a30 * a01 * a22 * a13 ) - ( a00 * a31 * a22 * a13 ) - ( a20 * a01 * a32 * a13 ) + ( a00 * a21 * a32 * a13 ) +
    ( a30 * a11 * a02 * a23 ) - ( a10 * a31 * a02 * a23 ) - ( a30 * a01 * a12 * a23 ) + ( a00 * a31 * a12 * a23 ) +
    ( a10 * a01 * a32 * a23 ) - ( a00 * a11 * a32 * a23 ) - ( a20 * a11 * a02 * a33 ) + ( a10 * a21 * a02 * a33 ) +
    ( a20 * a01 * a12 * a33 ) - ( a00 * a21 * a12 * a33 ) - ( a10 * a01 * a22 * a33 ) + ( a00 * a11 * a22 * a33 )
  );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Calculate the inverse of the given matrix.
//  https://github.com/toji/gl-matrix
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline bool inverse ( const Matrix44 < T, I > &a, Matrix44 < T, I > &b )
{
  // Get the raw arrays for speed.
  const T *aa ( a.get() );
  T *ba ( b.get() );

  const T a00 ( aa[R0C0] ), a01 ( aa[R0C1] ), a02 ( aa[R0C2] ), a03 ( aa[R0C3] );
  const T a10 ( aa[R1C0] ), a11 ( aa[R1C1] ), a12 ( aa[R1C2] ), a13 ( aa[R1C3] );
  const T a20 ( aa[R2C0] ), a21 ( aa[R2C1] ), a22 ( aa[R2C2] ), a23 ( aa[R2C3] );
  const T a30 ( aa[R3C0] ), a31 ( aa[R3C1] ), a32 ( aa[R3C2] ), a33 ( aa[R3C3] );

  const T b00 ( ( a00 * a11 ) - ( a01 * a10 ) );
  const T b01 ( ( a00 * a12 ) - ( a02 * a10 ) );
  const T b02 ( ( a00 * a13 ) - ( a03 * a10 ) );
  const T b03 ( ( a01 * a12 ) - ( a02 * a11 ) );
  const T b04 ( ( a01 * a13 ) - ( a03 * a11 ) );
  const T b05 ( ( a02 * a13 ) - ( a03 * a12 ) );
  const T b06 ( ( a20 * a31 ) - ( a21 * a30 ) );
  const T b07 ( ( a20 * a32 ) - ( a22 * a30 ) );
  const T b08 ( ( a20 * a33 ) - ( a23 * a30 ) );
  const T b09 ( ( a21 * a32 ) - ( a22 * a31 ) );
  const T b10 ( ( a21 * a33 ) - ( a23 * a31 ) );
  const T b11 ( ( a22 * a33 ) - ( a23 * a32 ) );

  const T det ( ( b00 * b11 ) - ( b01 * b10 ) + ( b02 * b09 ) +
                ( b03 * b08 ) - ( b04 * b07 ) + ( b05 * b06 ) );

  if ( 0 == det )
  {
    return false;
  }

  const T invDet = ( 1 / det );

  if ( 0 == invDet ) // Could this happen if det is very small?
  {
    return false;
  }

  ba[R0C0] = ( (  a11 * b11 ) - ( a12 * b10 ) + ( a13 * b09 ) ) * invDet;
  ba[R0C1] = ( ( -a01 * b11 ) + ( a02 * b10 ) - ( a03 * b09 ) ) * invDet;
  ba[R0C2] = ( (  a31 * b05 ) - ( a32 * b04 ) + ( a33 * b03 ) ) * invDet;
  ba[R0C3] = ( ( -a21 * b05 ) + ( a22 * b04 ) - ( a23 * b03 ) ) * invDet;
  ba[R1C0] = ( ( -a10 * b11 ) + ( a12 * b08 ) - ( a13 * b07 ) ) * invDet;
  ba[R1C1] = ( (  a00 * b11 ) - ( a02 * b08 ) + ( a03 * b07 ) ) * invDet;
  ba[R1C2] = ( ( -a30 * b05 ) + ( a32 * b02 ) - ( a33 * b01 ) ) * invDet;
  ba[R1C3] = ( (  a20 * b05 ) - ( a22 * b02 ) + ( a23 * b01 ) ) * invDet;
  ba[R2C0] = ( (  a10 * b10 ) - ( a11 * b08 ) + ( a13 * b06 ) ) * invDet;
  ba[R2C1] = ( ( -a00 * b10 ) + ( a01 * b08 ) - ( a03 * b06 ) ) * invDet;
  ba[R2C2] = ( (  a30 * b04 ) - ( a31 * b02 ) + ( a33 * b00 ) ) * invDet;
  ba[R2C3] = ( ( -a20 * b04 ) + ( a21 * b02 ) - ( a23 * b00 ) ) * invDet;
  ba[R3C0] = ( ( -a10 * b09 ) + ( a11 * b07 ) - ( a12 * b06 ) ) * invDet;
  ba[R3C1] = ( (  a00 * b09 ) - ( a01 * b07 ) + ( a02 * b06 ) ) * invDet;
  ba[R3C2] = ( ( -a30 * b03 ) + ( a31 * b01 ) - ( a32 * b00 ) ) * invDet;
  ba[R3C3] = ( (  a20 * b03 ) - ( a21 * b01 ) + ( a22 * b00 ) ) * invDet;

  return true;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the rotation portion of the given matrix.
//  https://github.com/toji/gl-matrix
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void rotation ( const Matrix44 < T, I > &m, Matrix44 < T, I > &r )
{
  // Get the raw arrays for speed.
  const T *ma ( m.get() );
  T *ra ( r.get() );

  // Make the compiler happy.
  const T zero ( static_cast < T > ( 0 ) );
  const T one  ( static_cast < T > ( 1 ) );

  ra[R0C0] = ma[R0C0]; ra[R0C1] = ma[R0C1]; ra[R0C2] = ma[R0C2]; ra[R0C3] = zero;
  ra[R1C0] = ma[R1C0]; ra[R1C1] = ma[R1C1]; ra[R1C2] = ma[R1C2]; ra[R1C3] = zero;
  ra[R2C0] = ma[R2C0]; ra[R2C1] = ma[R2C1]; ra[R2C2] = ma[R2C2]; ra[R2C3] = zero;
  ra[R3C0] = ma[R3C0]; ra[R3C1] = ma[R3C1]; ra[R3C2] = ma[R3C2]; ra[R3C3] = one;
}
template < class T, class I >
inline Matrix44 < T, I > rotation ( const Matrix44 < T, I > &m )
{
  Matrix44 < T, I > r ( false ); // Do not initialize.
  rotation ( m, r );
  return r;
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if the matrix elements are finite.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline bool isFinite ( const Matrix44 < T, I > &m )
{
  // Get the raw array for speed.
  const T *ma ( m.get() );

  return (
    std::isfinite ( ma[R0C0] ) &&
    std::isfinite ( ma[R0C1] ) &&
    std::isfinite ( ma[R0C2] ) &&
    std::isfinite ( ma[R0C3] ) &&
    std::isfinite ( ma[R1C0] ) &&
    std::isfinite ( ma[R1C1] ) &&
    std::isfinite ( ma[R1C2] ) &&
    std::isfinite ( ma[R1C3] ) &&
    std::isfinite ( ma[R2C0] ) &&
    std::isfinite ( ma[R2C1] ) &&
    std::isfinite ( ma[R2C2] ) &&
    std::isfinite ( ma[R2C3] ) &&
    std::isfinite ( ma[R3C0] ) &&
    std::isfinite ( ma[R3C1] ) &&
    std::isfinite ( ma[R3C2] ) &&
    std::isfinite ( ma[R3C3] )
  );
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
// #undef R0C0
// #undef R1C0
// #undef R2C0
// #undef R3C0
// #undef R0C1
// #undef R1C1
// #undef R2C1
// #undef R3C1
// #undef R0C2
// #undef R1C2
// #undef R2C2
// #undef R3C2
// #undef R0C3
// #undef R1C3
// #undef R2C3
// #undef R3C3


#endif // _USUL_MATH_4_BY_4_MATRIX_CLASS_H_
