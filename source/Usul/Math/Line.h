
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
inline void setFromOriginAndDirection ( LineType &line,
  const typename LineType::Point &pt, const typename LineType::Vec &dir )
{
  line.set ( pt, Usul::Math::add ( pt, dir ) );
}


/////////////////////////////////////////////////////////////////////////////
//
//  Return the origin.
//
/////////////////////////////////////////////////////////////////////////////

template < class LineType >
inline const typename LineType::Point &getOrigin ( const LineType &line )
{
  return line[0];
}
template < class LineType >
inline typename LineType::Point &getOrigin ( LineType &line )
{
  return line[0];
}


/////////////////////////////////////////////////////////////////////////////
//
//  Return the direction vector.
//
/////////////////////////////////////////////////////////////////////////////

template < class LineType >
inline typename LineType::Point getDirection ( const LineType &line )
{
  return Usul::Math::subtract ( line[1], line[0] );
}


/////////////////////////////////////////////////////////////////////////////
//
//  Return a unit direction vector.
//
/////////////////////////////////////////////////////////////////////////////

template < class LineType >
inline typename LineType::Point getUnitDirection ( const LineType &line )
{
  return Usul::Math::normalize ( getDirection ( line ) );
}


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_LINE_FUNCTIONS_H_
