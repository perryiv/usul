
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, 2019, Perry L Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
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
