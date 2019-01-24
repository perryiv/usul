
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
//  Helper function to add 3D vectors.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testAddVec3()
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
//  Helper function to subtract 3D vectors.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testSubtractVec3()
{
  typedef typename Usul::Math::Vector3 < ScalarType > Vec3;

  Vec3 a ( 4, 5, 6 );
  Vec3 b ( 1, 2, 3 );

  Vec3 c;
  Usul::Math::subtract ( a, b, c );

  REQUIRE ( 3 == c[0] );
  REQUIRE ( 3 == c[1] );
  REQUIRE ( 3 == c[2] );

  Vec3 d = Usul::Math::subtract ( a, b );

  REQUIRE ( 3 == d[0] );
  REQUIRE ( 3 == d[1] );
  REQUIRE ( 3 == d[2] );
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
      testAddVec3 < char           > ();
      testAddVec3 < short          > ();
      testAddVec3 < int            > ();
      testAddVec3 < long           > ();

      testAddVec3 < unsigned char  > ();
      testAddVec3 < unsigned short > ();
      testAddVec3 < unsigned int   > ();
      testAddVec3 < unsigned long  > ();

      testAddVec3 < float          > ();
      testAddVec3 < double         > ();
      testAddVec3 < long double    > ();
    }

    SECTION ( "Can subtract two 3D vectors" )
    {
      testSubtractVec3 < char           > ();
      testSubtractVec3 < short          > ();
      testSubtractVec3 < int            > ();
      testSubtractVec3 < long           > ();

      testSubtractVec3 < unsigned char  > ();
      testSubtractVec3 < unsigned short > ();
      testSubtractVec3 < unsigned int   > ();
      testSubtractVec3 < unsigned long  > ();

      testSubtractVec3 < float          > ();
      testSubtractVec3 < double         > ();
      testSubtractVec3 < long double    > ();
    }
  }
}
