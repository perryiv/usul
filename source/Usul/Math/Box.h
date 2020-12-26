
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Class representing a bounding box.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_BOX_CLASS_H_
#define _USUL_MATH_BOX_CLASS_H_

#include "Usul/Math/Vector3.h"

#include <limits>


namespace Usul {
namespace Math {


template
<
  class T,
  typename IndexType = unsigned int
>
class Box
{
public:

  /////////////////////////////////////////////////////////////////////////////
  //
  //  Useful typedefs.
  //
  /////////////////////////////////////////////////////////////////////////////

  typedef T value_type;
  typedef Box < T, IndexType > ThisType;
  typedef Usul::Math::Vector3 < T, IndexType > Vec3;
  typedef std::numeric_limits < T > Limits;


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructors.
  //
  /////////////////////////////////////////////////////////////////////////////

  constexpr Box() :
    _min (  Limits::max(),  Limits::max(),  Limits::max() ), // These are correct.
    _max ( -Limits::max(), -Limits::max(), -Limits::max() )
  {
  }
  constexpr Box ( const Vec3 &mn, const Vec3 &mx ) :
    _min ( mn ),
    _max ( mx )
  {
  }
  constexpr Box ( const Box &box ) :
    _min ( box._min ),
    _max ( box._max )
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Assignment.
  //
  /////////////////////////////////////////////////////////////////////////////

  Box &operator = ( const Box &rhs )
  {
    _min = rhs._min;
    _max = rhs._max;
    return *this;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Is the box valid?
  //
  /////////////////////////////////////////////////////////////////////////////

  bool valid() const
  {
    // We use <= because a point has a valid bounding box but zero size.
    return ( ( _min[0] <= _max[0] ) && ( _min[1] <= _max[1] ) && ( _min[2] <= _max[2] ) );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Get/set the min and max.
  //
  /////////////////////////////////////////////////////////////////////////////

  const Vec3 &getMin() const
  {
    return _min;
  }
  void setMin ( const Vec3 &v )
  {
    _min = v;
  }
  const Vec3 &getMax() const
  {
    return _max;
  }
  void setMax ( const Vec3 &v )
  {
    _max = v;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Get the size.
  //
  /////////////////////////////////////////////////////////////////////////////

  Vec3 getSize() const
  {
    return Vec3 (
      ( _max[0] - _min[0] ),
      ( _max[1] - _min[1] ),
      ( _max[2] - _min[2] )
    );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Get the center.
  //
  /////////////////////////////////////////////////////////////////////////////

  Vec3 getCenter() const
  {
    constexpr value_type half = static_cast < value_type > ( 0.5 );
    return ( Usul::Math::scale ( ( _min + _max ), half ) );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Get the radius.
  //
  /////////////////////////////////////////////////////////////////////////////

  value_type getRadius() const
  {
    constexpr value_type half = static_cast < value_type > ( 0.5 );
    return ( half * Usul::Math::distance ( _min, _max ) );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Grow the box.
  //
  /////////////////////////////////////////////////////////////////////////////

  void grow ( const Vec3 &v )
  {
    this->_grow ( v, 0 );
    this->_grow ( v, 1 );
    this->_grow ( v, 2 );
  }
  void grow ( const ThisType &box )
  {
    this->grow ( box._min );
    this->grow ( box._max );
  }


protected:

  /////////////////////////////////////////////////////////////////////////////
  //
  //  Grow the box.
  //
  /////////////////////////////////////////////////////////////////////////////

  void _grow ( const Vec3 &v, unsigned int index )
  {
    const value_type &value = v[index];

    // Do both of these because if the box is invalid and it's grown by a
    // single point, then that point is both the new min and max.
    if ( value < _min[index] )
    {
      _min[index] = value;
    }
    if ( value > _max[index] )
    {
      _max[index] = value;
    }
  }


private:

  Vec3 _min;
  Vec3 _max;
};


///////////////////////////////////////////////////////////////////////////////
//
//  See if they are equal.
//
///////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline bool equal ( const Box < T, I > &a, const Box < T, I > &b )
{
  return ( Usul::Math::equal ( a.getMin(), b.getMin() ) &&
           Usul::Math::equal ( a.getMax(), b.getMax() ) );
}
template < class T, class I >
inline bool operator == ( const Box < T, I > &a, const Box < T, I > &b )
{
  return ( true == Usul::Math::equal ( a, b ) );
}
template < class T, class I >
inline bool operator != ( const Box < T, I > &a, const Box < T, I > &b )
{
  return ( false == Usul::Math::equal ( a, b ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Useful typedefs.
//
///////////////////////////////////////////////////////////////////////////////

typedef Box < float  > Boxf;
typedef Box < double > Boxd;


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_BOX_CLASS_H_
