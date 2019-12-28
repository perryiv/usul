
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the functions for a sequence.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Math/Sequence.h"
#include "Usul/Math/Constants.h"
#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector3.h"

#include "catch2/catch.hpp"

#include <sstream>
#include <vector>

#define SC static_cast < T >


////////////////////////////////////////////////////////////////////////////////
//
//  See if the values are equal when converted to strings.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class T >
  inline void isEqualString ( const T &a, const T &b )
  {
    std::ostringstream ssa, ssb;
    ssa << a;
    ssb << b;
    const std::string sa = ssa.str();
    const std::string sb = ssb.str();
    REQUIRE ( sa == sb );
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Functions for a sequence", "", float, double )
{
  typedef TestType T;
  typedef Usul::Math::Matrix44 < T > Matrix44;
  typedef Usul::Math::Vector3 < T > Vec3;
  typedef std::vector < Vec3 > Sequence;

  SECTION ( "Can transform a sequence of vec3 into a new sequence" )
  {
    const Matrix44 m = Usul::Math::rotate ( Matrix44(), Vec3 ( SC ( 1 ), SC ( 0 ), SC ( 0 ) ), SC ( Usul::Math::PI_OVER_2 ) );
    const Sequence a ( {
      { Vec3 ( SC ( 0 ), SC ( 1 ), SC ( 2 ) ) },
      { Vec3 ( SC ( 1 ), SC ( 2 ), SC ( 3 ) ) },
      { Vec3 ( SC ( 2 ), SC ( 3 ), SC ( 4 ) ) },
      { Vec3 ( SC ( 3 ), SC ( 4 ), SC ( 5 ) ) }
    } );
    Sequence b;

    Usul::Math::transform ( m, a, b );

    Details::isEqualString ( b[0][0], SC (  0 ) );
    Details::isEqualString ( b[0][1], SC ( -2 ) );
    Details::isEqualString ( b[0][2], SC (  1 ) );

    Details::isEqualString ( b[1][0], SC (  1 ) );
    Details::isEqualString ( b[1][1], SC ( -3 ) );
    Details::isEqualString ( b[1][2], SC (  2 ) );

    Details::isEqualString ( b[2][0], SC (  2 ) );
    Details::isEqualString ( b[2][1], SC ( -4 ) );
    Details::isEqualString ( b[2][2], SC (  3 ) );

    Details::isEqualString ( b[3][0], SC (  3 ) );
    Details::isEqualString ( b[3][1], SC ( -5 ) );
    Details::isEqualString ( b[3][2], SC (  4 ) );
  }

  SECTION ( "Can transform a sequence of vec3 in place" )
  {
    const Matrix44 m = Usul::Math::rotate ( Matrix44(), Vec3 ( SC ( 1 ), SC ( 0 ), SC ( 0 ) ), SC ( Usul::Math::PI_OVER_2 ) );
    Sequence b ( {
      { Vec3 ( SC ( 0 ), SC ( 1 ), SC ( 2 ) ) },
      { Vec3 ( SC ( 1 ), SC ( 2 ), SC ( 3 ) ) },
      { Vec3 ( SC ( 2 ), SC ( 3 ), SC ( 4 ) ) },
      { Vec3 ( SC ( 3 ), SC ( 4 ), SC ( 5 ) ) }
    } );

    Usul::Math::transform ( m, b );

    Details::isEqualString ( b[0][0], SC (  0 ) );
    Details::isEqualString ( b[0][1], SC ( -2 ) );
    Details::isEqualString ( b[0][2], SC (  1 ) );

    Details::isEqualString ( b[1][0], SC (  1 ) );
    Details::isEqualString ( b[1][1], SC ( -3 ) );
    Details::isEqualString ( b[1][2], SC (  2 ) );

    Details::isEqualString ( b[2][0], SC (  2 ) );
    Details::isEqualString ( b[2][1], SC ( -4 ) );
    Details::isEqualString ( b[2][2], SC (  3 ) );

    Details::isEqualString ( b[3][0], SC (  3 ) );
    Details::isEqualString ( b[3][1], SC ( -5 ) );
    Details::isEqualString ( b[3][2], SC (  4 ) );
  }

  SECTION ( "Can normalize a sequence of vec3 into a new sequence" )
  {
    const Sequence a ( {
      { Vec3 ( SC ( 2 ), SC ( 0 ), SC ( 0 ) ) },
      { Vec3 ( SC ( 0 ), SC ( 2 ), SC ( 0 ) ) },
      { Vec3 ( SC ( 0 ), SC ( 0 ), SC ( 2 ) ) },
      { Vec3 ( SC ( 1 ), SC ( 1 ), SC ( 1 ) ) }
    } );
    Sequence b;

    Usul::Math::normalize ( a, b );

    Details::isEqualString ( b[0][0], SC ( 1 ) );
    Details::isEqualString ( b[0][1], SC ( 0 ) );
    Details::isEqualString ( b[0][2], SC ( 0 ) );

    Details::isEqualString ( b[1][0], SC ( 0 ) );
    Details::isEqualString ( b[1][1], SC ( 1 ) );
    Details::isEqualString ( b[1][2], SC ( 0 ) );

    Details::isEqualString ( b[2][0], SC ( 0 ) );
    Details::isEqualString ( b[2][1], SC ( 0 ) );
    Details::isEqualString ( b[2][2], SC ( 1 ) );

    const TestType oneOverSquareRootOfThree = SC ( 1 ) / SC ( std::pow ( SC ( 3 ), SC ( 0.5 ) ) );
    Details::isEqualString ( b[3][0], oneOverSquareRootOfThree );
    Details::isEqualString ( b[3][1], oneOverSquareRootOfThree );
    Details::isEqualString ( b[3][2], oneOverSquareRootOfThree );
  }

  SECTION ( "Can normalize a sequence of vec3 in place" )
  {
    Sequence b ( {
      { Vec3 ( SC ( 2 ), SC ( 0 ), SC ( 0 ) ) },
      { Vec3 ( SC ( 0 ), SC ( 2 ), SC ( 0 ) ) },
      { Vec3 ( SC ( 0 ), SC ( 0 ), SC ( 2 ) ) },
      { Vec3 ( SC ( 1 ), SC ( 1 ), SC ( 1 ) ) }
    } );

    Usul::Math::normalize ( b );

    Details::isEqualString ( b[0][0], SC ( 1 ) );
    Details::isEqualString ( b[0][1], SC ( 0 ) );
    Details::isEqualString ( b[0][2], SC ( 0 ) );

    Details::isEqualString ( b[1][0], SC ( 0 ) );
    Details::isEqualString ( b[1][1], SC ( 1 ) );
    Details::isEqualString ( b[1][2], SC ( 0 ) );

    Details::isEqualString ( b[2][0], SC ( 0 ) );
    Details::isEqualString ( b[2][1], SC ( 0 ) );
    Details::isEqualString ( b[2][2], SC ( 1 ) );

    const TestType oneOverSquareRootOfThree = SC ( 1 ) / SC ( std::pow ( SC ( 3 ), SC ( 0.5 ) ) );
    Details::isEqualString ( b[3][0], oneOverSquareRootOfThree );
    Details::isEqualString ( b[3][1], oneOverSquareRootOfThree );
    Details::isEqualString ( b[3][2], oneOverSquareRootOfThree );
  }
}
