
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Math functions for lines.
//
//  Passing ScalarType by value because of this discussion:
//  https://stackoverflow.com/questions/14013139/is-it-counter-productive-to-pass-primitive-types-by-reference
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_LINE_FUNCTIONS_H_
#define _USUL_MATH_LINE_FUNCTIONS_H_

#include "Usul/Math/Vector.h"


namespace Usul {
namespace Math {


///////////////////////////////////////////////////////////////////////////////
//
//  Set the line from an origin and direction.
//
///////////////////////////////////////////////////////////////////////////////

template < class LineType >
inline void setFromOriginAndDirection (
  LineType &line,
  const typename LineType::Point &pt,
  const typename LineType::Vec &dir
)
{
  typedef typename LineType::Point Point;

  const Point &p0 ( pt );
  const Point p1 = Usul::Math::add ( pt, dir );

  line.set ( p0 );
  line.set ( p1 );
}


/////////////////////////////////////////////////////////////////////////////
//
//  Return the origin.
//
/////////////////////////////////////////////////////////////////////////////

template < class LineType >
inline const typename LineType::Point &getOrigin (
  const LineType &line
)
{
  return line[0];
}
template < class LineType >
inline typename LineType::Point &getOrigin (
  LineType &line
)
{
  return line[0];
}


/////////////////////////////////////////////////////////////////////////////
//
//  Return the direction vector.
//
/////////////////////////////////////////////////////////////////////////////

template < class LineType >
inline typename LineType::Point getDirection (
  const LineType &line
)
{
  typedef typename LineType::Point Point;

  const Point &p0 ( line[0] );
  const Point &p1 ( line[1] );

  return Usul::Math::subtract ( p1, p0 );
}


/////////////////////////////////////////////////////////////////////////////
//
//  Return a unit direction vector.
//
/////////////////////////////////////////////////////////////////////////////

template < class LineType >
inline typename LineType::Point getUnitDirection (
  const LineType &line
)
{
  return Usul::Math::normalize ( line.getDirection() );
}


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_LINE_FUNCTIONS_H_
