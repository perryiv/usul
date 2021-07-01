
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  3D line class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_LINE_3D_H_
#define _USUL_MATH_LINE_3D_H_

#include "Usul/Errors/Check.h"
#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector3.h"

#include <stdexcept>


namespace Usul {
namespace Math {


template
<
  typename T,
  typename IndexType = unsigned int
>
class Line3
{
public:

  /////////////////////////////////////////////////////////////////////////////
  //
  //  Useful typedefs.
  //
  /////////////////////////////////////////////////////////////////////////////

  typedef T value_type;
  typedef IndexType size_type;
  typedef Line3 < T, IndexType > ThisType;
  typedef Usul::Math::Vector3 < T, IndexType > Vec;
  typedef Vec Point;
  typedef Vec vec_type;


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Default constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  constexpr Line3() :
    _p0 ( 0,  0,  0 ),
    _p1 ( 0,  0, -1 )
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  constexpr Line3 ( const Point &p0, const Point &p1 ) :
    _p0 ( p0 ),
    _p1 ( p1 )
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Copy constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Line3 ( const Line3 &line ) :
    _p0 ( line._p0 ),
    _p1 ( line._p1 )
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Assignment.
  //
  /////////////////////////////////////////////////////////////////////////////

  Line3 &operator = ( const Line3 &line )
  {
    this->set ( line );
    return *this;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const Line3 &line )
  {
    _p0.set ( line._p0 );
    _p1.set ( line._p1 );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const Point &p0, const Point &p1 )
  {
    _p0.set ( p0 );
    _p1.set ( p1 );
  }


  ///////////////////////////////////////////////////////////////////////////////
  //
  //  Set the line from an origin and direction.
  //
  ///////////////////////////////////////////////////////////////////////////////

  void setFromOriginAndDirection ( const Point &pt, const Vec &dir )
  {
    this->set ( pt, Usul::Math::add ( pt, dir ) );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Return the origin.
  //
  /////////////////////////////////////////////////////////////////////////////

  const Point &getOrigin() const
  {
    return _p0;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Return the direction vector.
  //
  /////////////////////////////////////////////////////////////////////////////

  Vec getDirection() const
  {
    return Usul::Math::subtract ( _p1, _p0 );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Return a unit direction vector.
  //
  /////////////////////////////////////////////////////////////////////////////

  Vec getUnitDirection() const
  {
    return Usul::Math::normalize ( this->getDirection() );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Get the point at the given parametric value.
  //
  /////////////////////////////////////////////////////////////////////////////

  Point getPoint ( value_type u ) const
  {
    const value_type x0 = _p0[0];
    const value_type y0 = _p0[1];
    const value_type z0 = _p0[2];

    return Point (
      ( x0 + u * ( _p1[0] - x0 ) ),
      ( y0 + u * ( _p1[1] - y0 ) ),
      ( z0 + u * ( _p1[2] - z0 ) )
    );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Normalize the line by making the points one unit apart.
  //
  /////////////////////////////////////////////////////////////////////////////

  void normalize()
  {
    const Vec dir = this->getUnitDirection();
    _p1 = _p0 + dir;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Get the start and end of the line.
  //
  /////////////////////////////////////////////////////////////////////////////

  const Point &start() const
  {
    return _p0;
  }
  const Point &end() const
  {
    return _p1;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Bracket operators.
  //
  /////////////////////////////////////////////////////////////////////////////

  Point &operator [] ( size_type i )
  {
    USUL_CHECK_INDEX_RANGE ( 2, i, "Index out of range in Line3 [] operator" );
    return ( ( 0 == i ) ? _p0 : _p1 );
  }
  const Point &operator [] ( size_type i ) const
  {
    USUL_CHECK_INDEX_RANGE ( 2, i, "Index out of range in Line3 [] operator" );
    return ( ( 0 == i ) ? _p0 : _p1 );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Return true if the lines are equal.
  //
  /////////////////////////////////////////////////////////////////////////////

  static bool equal ( const Line3 &a, const Line3 &b )
  {
    const Point &a0 ( a[0] );
    const Point &a1 ( a[1] );

    const Point &b0 ( b[0] );
    const Point &b1 ( b[1] );

    return (
      ( ( a0[0] == b0[0] ) && ( a0[1] == b0[1] ) && ( a0[2] == b0[2] ) ) &&
      ( ( a1[0] == b1[0] ) && ( a1[1] == b1[1] ) && ( a1[2] == b1[2] ) )
    );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Is the line valid?
  //
  /////////////////////////////////////////////////////////////////////////////

  bool valid() const
  {
    // It is valid if the two points are not equal.
    return ( false == Usul::Math::equal ( _p0, _p1 ) );
  }


private:

  Point _p0;
  Point _p1;
};


/////////////////////////////////////////////////////////////////////////////
//
//  Return true if the lines are equal.
//
/////////////////////////////////////////////////////////////////////////////

template < class T >
inline bool equal ( const Line3 < T > &a, const Line3 < T > &b )
{
  typedef Line3 < T > LineType;
  return ( LineType::equal ( a, b ) );
}


/////////////////////////////////////////////////////////////////////////////
//
//  Transform the line.
//
/////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void transform ( const Matrix44 < T, I > &m, const Line3 < T > &a, Line3 < T > &b )
{
  b.set (
    Usul::Math::multiply ( m, a.start() ),
    Usul::Math::multiply ( m, a.end() )
  );
}
template < class T, class I >
inline Line3 < T > transform ( const Matrix44 < T, I > &m, const Line3 < T > &a )
{
  return Line3 < T > (
    Usul::Math::multiply ( m, a.start() ),
    Usul::Math::multiply ( m, a.end() )
  );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Useful typedefs.
//
///////////////////////////////////////////////////////////////////////////////

typedef Line3 < float          > Line3f;
typedef Line3 < double         > Line3d;
typedef Line3 < long double    > Line3ld;


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_LINE_3D_H_
