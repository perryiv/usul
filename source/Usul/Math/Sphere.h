
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2009, 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Sphere class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_SPHERE_H_
#define _USUL_MATH_SPHERE_H_

#include "Usul/Errors/Check.h"
#include "Usul/Math/Vector3.h"


namespace Usul {
namespace Math {


template
<
  typename T,
  typename IndexType = unsigned int
>
class Sphere
{
public:

  /////////////////////////////////////////////////////////////////////////////
  //
  //  Useful typedefs.
  //
  /////////////////////////////////////////////////////////////////////////////

  typedef T value_type;
  typedef IndexType size_type;
  typedef Sphere < T, IndexType > ThisType;
  typedef Usul::Math::Vector3 < T, IndexType > Point;
  typedef Point vec_type;


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Default constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Sphere() :
    _center ( 0,  0,  0 ),
    _radius ( 1 )
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Sphere ( const Point &center, const T &radius ) :
    _center ( center ),
    _radius ( radius )
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Copy constructor.
  //
  /////////////////////////////////////////////////////////////////////////////

  Sphere ( const Sphere &sphere ) :
    _center ( sphere._center ),
    _radius ( sphere._radius )
  {
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const Sphere &sphere )
  {
    this->setCenter ( sphere._center );
    this->setRadius ( sphere._radius );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set the value.
  //
  /////////////////////////////////////////////////////////////////////////////

  void set ( const Point &center, const T &radius )
  {
    this->setCenter ( center );
    this->setRadius ( radius );
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set/get the center
  //
  /////////////////////////////////////////////////////////////////////////////

  void setCenter ( const Point &c )
  {
    _center = c;
  }
  const Point &getCenter() const
  {
    return _center;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Set/get the rad
  //
  /////////////////////////////////////////////////////////////////////////////

  void setRadius ( const T &r )
  {
    _radius = r;
  }
  const T &getRadius() const
  {
    return _radius;
  }


  /////////////////////////////////////////////////////////////////////////////
  //
  //  Return true if the spheres are equal.
  //
  /////////////////////////////////////////////////////////////////////////////

  static bool equal ( const Sphere &a, const Sphere &b )
  {
    const Point &ca ( a.getCenter() );
    const Point &ra ( a.getRadius() );

    const Point &cb ( b.getCenter() );
    const Point &rb ( b.getRadius() );

    return (
      ( ca[0] == cb[0] ) &&
      ( ca[1] == cb[1] ) &&
      ( ca[2] == cb[2] ) &&
      ( ra == rb )
    );
  }


private:

  Point _center;
  T _radius;
};


/////////////////////////////////////////////////////////////////////////////
//
//  Return true if the spheres are equal.
//
/////////////////////////////////////////////////////////////////////////////

template < class T >
inline bool equal ( const Sphere < T > &a, const Sphere < T > &b )
{
  typedef Sphere < T > SphereType;
  return ( SphereType::equal ( a, b ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Useful typedefs.
//
///////////////////////////////////////////////////////////////////////////////

typedef Sphere < float          > Spheref;
typedef Sphere < double         > Sphered;
typedef Sphere < long double    > Sphereld;


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_SPHERE_H_