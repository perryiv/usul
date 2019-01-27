
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
//  Helper function to add vectors.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testAddVec3()
{
  typedef typename Usul::Math::Vector3 < ScalarType > VectorType;

  const VectorType a ( 1, 2, 3 );
  const VectorType b ( 4, 5, 6 );

  VectorType c;
  Usul::Math::add ( a, b, c );

  REQUIRE ( 5 == c[0] );
  REQUIRE ( 7 == c[1] );
  REQUIRE ( 9 == c[2] );

  VectorType d = Usul::Math::add ( a, b );

  REQUIRE ( 5 == d[0] );
  REQUIRE ( 7 == d[1] );
  REQUIRE ( 9 == d[2] );
}

////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to add arrays.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testAddArray3()
{
  const ScalarType a[3] = { 1, 2, 3 };
  const ScalarType b[3] = { 4, 5, 6 };

  ScalarType c[3];
  Usul::Math::add ( a, b, c );

  REQUIRE ( 5 == c[0] );
  REQUIRE ( 7 == c[1] );
  REQUIRE ( 9 == c[2] );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to subtract vectors.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testSubtractVec3()
{
  typedef typename Usul::Math::Vector3 < ScalarType > VectorType;

  const VectorType a ( 4, 5, 6 );
  const VectorType b ( 1, 2, 3 );

  VectorType c;
  Usul::Math::subtract ( a, b, c );

  REQUIRE ( 3 == c[0] );
  REQUIRE ( 3 == c[1] );
  REQUIRE ( 3 == c[2] );

  VectorType d = Usul::Math::subtract ( a, b );

  REQUIRE ( 3 == d[0] );
  REQUIRE ( 3 == d[1] );
  REQUIRE ( 3 == d[2] );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to subtract arrays.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testSubtractArray3()
{
  const ScalarType a[3] = { 4, 5, 6 };
  const ScalarType b[3] = { 1, 2, 3 };

  ScalarType c[3];
  Usul::Math::subtract ( a, b, c );

  REQUIRE ( 3 == c[0] );
  REQUIRE ( 3 == c[1] );
  REQUIRE ( 3 == c[2] );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to scale vectors.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testScaleVec3()
{
  typedef typename Usul::Math::Vector3 < ScalarType > VectorType;

  const VectorType a ( 1, 2, 3 );

  VectorType b;
  Usul::Math::scale ( a, 10, b );

  REQUIRE ( 10 == b[0] );
  REQUIRE ( 20 == b[1] );
  REQUIRE ( 30 == b[2] );

  const VectorType c = Usul::Math::scale ( a, 10 );

  REQUIRE ( 10 == c[0] );
  REQUIRE ( 20 == c[1] );
  REQUIRE ( 30 == c[2] );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to scale arrays.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testScaleArray3()
{
  const ScalarType a[3] = { 1, 2, 3 };

  ScalarType b[3];
  Usul::Math::scale ( a, 10, b );

  REQUIRE ( 10 == b[0] );
  REQUIRE ( 20 == b[1] );
  REQUIRE ( 30 == b[2] );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to normalize vectors.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testNormalizeVec3()
{
  typedef typename Usul::Math::Vector3 < ScalarType > VectorType;

  const VectorType a ( 3, 4, 0 ); // 3-4-5 right triangle.

  REQUIRE ( 5 == Usul::Math::length ( a ) );

  VectorType b;
  ScalarType originalLength = 0;
  Usul::Math::normalize ( a, b, &originalLength ); // We want the original length.

  REQUIRE ( 5 == originalLength );
  REQUIRE ( 1 == Usul::Math::length ( b ) );

  VectorType c;
  Usul::Math::normalize ( a, c ); // We do not want the original length.

  REQUIRE ( 1 == Usul::Math::length ( c ) );

  const VectorType d = Usul::Math::normalize ( VectorType ( 3, 4, 0 ) );
  REQUIRE ( 1 == Usul::Math::length ( d ) );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to normalize arrays.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testNormalizeArray3()
{
  const ScalarType a[3] = { 3, 4, 0 }; // 3-4-5 right triangle.

  REQUIRE ( 5 == Usul::Math::length ( a ) );

  ScalarType b[3] = { 0, 0, 0 };
  ScalarType originalLength = 0;
  Usul::Math::normalize ( a, b, &originalLength ); // We want the original length.

  REQUIRE ( 5 == originalLength );
  REQUIRE ( 1 == Usul::Math::length ( b ) );

  ScalarType c[3] = { 0, 0, 0 };
  Usul::Math::normalize ( a, c ); // We do not want the original length.

  REQUIRE ( 1 == Usul::Math::length ( c ) );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to test array length.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testLengthArray3()
{
  const ScalarType a[3] = { 3, 4, 0 }; // 3-4-5 right triangle.
  REQUIRE ( 5 == Usul::Math::length ( a ) );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to test vector length.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void testLengthVec3()
{
  typedef typename Usul::Math::Vector3 < ScalarType > VectorType;
  const VectorType a ( 3, 4, 0 ); // 3-4-5 right triangle.
  REQUIRE ( 5 == Usul::Math::length ( a ) );
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
    SECTION ( "Default constructor works" )
    {
      const Usul::Math::Vec3d a;

      REQUIRE ( 0 == a[0] );
      REQUIRE ( 0 == a[1] );
      REQUIRE ( 0 == a[2] );
    }

    SECTION ( "Constructor that takes 3 values works" )
    {
      const Usul::Math::Vec3d a ( 1, 2, 3 );

      REQUIRE ( 1 == a[0] );
      REQUIRE ( 2 == a[1] );
      REQUIRE ( 3 == a[2] );
    }

    SECTION ( "Constructor that takes an array works" )
    {
      const Usul::Math::Vec3d a ( { 1, 2, 3 } );

      REQUIRE ( 1 == a[0] );
      REQUIRE ( 2 == a[1] );
      REQUIRE ( 3 == a[2] );
    }

    SECTION ( "Default copy constructor works" )
    {
      Usul::Math::Vec3d a ( 1, 2, 3 );
      const Usul::Math::Vec3d b ( a ); // Copy constructor.

      // Should be the same.
      REQUIRE ( a[0] == b[0] );
      REQUIRE ( a[1] == b[1] );
      REQUIRE ( a[2] == b[2] );

      // Is it different memory?
      a[0] = 4; // Changing one value.
      REQUIRE ( 4 == a[0] ); // It should be different.
      REQUIRE ( 1 == b[0] ); // It should be original value.
    }

    SECTION ( "Assigning is making a copy" )
    {
      Usul::Math::Vec3d a ( 1, 2, 3 );
      const Usul::Math::Vec3d b = a; // Assignment operator.

      // Should be the same.
      REQUIRE ( a[0] == b[0] );
      REQUIRE ( a[1] == b[1] );
      REQUIRE ( a[2] == b[2] );

      // Is it different memory?
      a[0] = 4; // Changing one value.
      REQUIRE ( 4 == a[0] ); // It should be different.
      REQUIRE ( 1 == b[0] ); // It should be original value.
    }

    SECTION ( "Setter functions work" )
    {
      {
        Usul::Math::Vec3d a;

        REQUIRE ( 0 == a[0] );
        REQUIRE ( 0 == a[1] );
        REQUIRE ( 0 == a[2] );

        a.set ( Usul::Math::Vec3d ( 1, 2, 3 ) );

        REQUIRE ( 1 == a[0] );
        REQUIRE ( 2 == a[1] );
        REQUIRE ( 3 == a[2] );
      }

      {
        Usul::Math::Vec3d a;

        REQUIRE ( 0 == a[0] );
        REQUIRE ( 0 == a[1] );
        REQUIRE ( 0 == a[2] );

        a.set ( { 1, 2, 3 } );

        REQUIRE ( 1 == a[0] );
        REQUIRE ( 2 == a[1] );
        REQUIRE ( 3 == a[2] );
      }

      {
        Usul::Math::Vec3d a;

        REQUIRE ( 0 == a[0] );
        REQUIRE ( 0 == a[1] );
        REQUIRE ( 0 == a[2] );

        a.set ( 1, 2, 3 );

        REQUIRE ( 1 == a[0] );
        REQUIRE ( 2 == a[1] );
        REQUIRE ( 3 == a[2] );
      }
    }

    SECTION ( "Can add two vectors" )
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

      testAddArray3 < float >  ();
      testAddArray3 < double > ();
    }

    SECTION ( "Can subtract two vectors" )
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

      testSubtractArray3 < float >  ();
      testSubtractArray3 < double > ();
    }

    SECTION ( "Can scale a vector" )
    {
      testScaleVec3 < char           > ();
      testScaleVec3 < short          > ();
      testScaleVec3 < int            > ();
      testScaleVec3 < long           > ();

      testScaleVec3 < unsigned char  > ();
      testScaleVec3 < unsigned short > ();
      testScaleVec3 < unsigned int   > ();
      testScaleVec3 < unsigned long  > ();

      testScaleVec3 < float          > ();
      testScaleVec3 < double         > ();
      testScaleVec3 < long double    > ();

      testScaleArray3 < float >  ();
      testScaleArray3 < double > ();
    }

    SECTION ( "Can call a function for all values" )
    {
      typedef Usul::Math::Vec3d VectorType;
      typedef typename VectorType::value_type ValueType;

      unsigned int count = 0;

      Usul::Math::each ( Usul::Math::Vec3d ( 1, 2, 3 ), [&] ( ValueType value )
      {
        ++count;
        REQUIRE ( count == value );
      } );

      REQUIRE ( 3 == count );
    }

    SECTION ( "Equal vectors are equal" )
    {
      typedef Usul::Math::Vec3d VectorType;
      REQUIRE ( true == Usul::Math::equal ( VectorType ( 1, 2, 3 ), VectorType ( 1, 2, 3 ) ) );
    }

    SECTION ( "Different vectors are not equal" )
    {
      typedef Usul::Math::Vec3d VectorType;
      VectorType a ( 1, 2, 3 );
      REQUIRE ( false == Usul::Math::equal ( a, VectorType ( 4, 2, 3 ) ) );
      REQUIRE ( false == Usul::Math::equal ( a, VectorType ( 4, 5, 3 ) ) );
      REQUIRE ( false == Usul::Math::equal ( a, VectorType ( 4, 5, 6 ) ) );
    }

    SECTION ( "Can get the length" )
    {
      testLengthVec3 < float       > ();
      testLengthVec3 < double      > ();
      testLengthVec3 < long double > ();

      testLengthArray3 < float       > ();
      testLengthArray3 < double      > ();
      testLengthArray3 < long double > ();
    }

    SECTION ( "Can normalize" )
    {
      testNormalizeVec3 < float       > ();
      testNormalizeVec3 < double      > ();
      testNormalizeVec3 < long double > ();

      testNormalizeArray3 < float       > ();
      testNormalizeArray3 < double      > ();
      testNormalizeArray3 < long double > ();
    }
  }
}
