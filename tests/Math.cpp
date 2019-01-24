
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Math/Functions.h"
#include "Usul/Math/Vector3.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to test 3D vectors.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testVec3()
{
  typedef typename Usul::Math::Vector3 < ScalarType > Vec3;

  Vec3 a ( 1, 2, 3 );
  Vec3 b ( 4, 5, 6 );

  Vec3 c;
  Usul::Math::add ( a, b, c );

  REQUIRE ( 5 == c[0] );
  REQUIRE ( 7 == c[1] );
  REQUIRE ( 9 == c[2] );

  Vec3 d = Usul::Math::add ( a, b );

  REQUIRE ( 5 == d[0] );
  REQUIRE ( 7 == d[1] );
  REQUIRE ( 9 == d[2] );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Math functions" )
{
  SECTION ( "Vectors" )
  {
    SECTION ( "Can add two 3D vectors" )
    {
      testVec3 < char           > ();
      testVec3 < short          > ();
      testVec3 < int            > ();
      testVec3 < long           > ();

      testVec3 < unsigned char  > ();
      testVec3 < unsigned short > ();
      testVec3 < unsigned int   > ();
      testVec3 < unsigned long  > ();

      testVec3 < float          > ();
      testVec3 < double         > ();
      testVec3 < long double    > ();
    }
  }
}
