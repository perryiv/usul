
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
#include "Usul/Math/Vector.h"
#include "Usul/Math/Vector3.h"

#include "catch2/catch.hpp"

#include <sstream>
#include <iomanip>

// Pythagorean quadruples.
// https://plus.maths.org/content/triples-and-quadruples
// https://en.wikipedia.org/wiki/Pythagorean_quadruple
const unsigned int numPythagoreanQuadruples = 31;
const unsigned char pythagoreanQuadruples[numPythagoreanQuadruples][4] = {
  {  1,  2,  2,  3 }, {  2, 10, 11, 15 },
  {  4, 13, 16, 21 }, {  2, 10, 25, 27 },
  {  2,  3,  6,  7 }, {  1, 12, 12, 17 },
  {  8, 11, 16, 21 }, {  2, 14, 23, 27 },
  {  1,  4,  8,  9 }, {  8,  9, 12, 17 },
  {  3,  6, 22, 23 }, {  7, 14, 22, 27 },
  {  4,  4,  7,  9 }, {  1,  6, 18, 19 },
  {  3, 14, 18, 23 }, { 10, 10, 23, 27 },
  {  2,  6,  9, 11 }, {  6,  6, 17, 19 },
  {  6, 13, 18, 23 }, {  3, 16, 24, 29 },
  {  6,  6,  7, 11 }, {  6, 10, 15, 19 },
  {  9, 12, 20, 25 }, { 11, 12, 24, 29 },
  {  3,  4, 12, 13 }, {  4,  5, 20, 21 },
  { 12, 15, 16, 25 }, { 12, 16, 21, 29 },
  {  2,  5, 14, 15 }, {  4,  8, 19, 21 },
  {  2,  7, 26, 27 }
};


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to check the length.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void checkLength (
  ScalarType v0, ScalarType v1, ScalarType v2, ScalarType len )
{
  typedef typename Usul::Math::Vector3 < ScalarType > VectorType;
  REQUIRE ( len == Usul::Math::length ( VectorType ( v0, v1, v2 ) ) );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Vector3 template math functions with all primitive types", "",
  char, short, int, long, ( unsigned char ), ( unsigned short ),
  ( unsigned int ), ( unsigned long ), float, double, ( long double ) )
{
  typedef typename Usul::Math::Vector3 < TestType > VectorType;

  SECTION ( "Default constructor works" )
  {
    const VectorType a;

    REQUIRE ( 0 == a[0] );
    REQUIRE ( 0 == a[1] );
    REQUIRE ( 0 == a[2] );
  }

  SECTION ( "Constructor that takes 3 values works" )
  {
    const VectorType a ( 1, 2, 3 );

    REQUIRE ( 1 == a[0] );
    REQUIRE ( 2 == a[1] );
    REQUIRE ( 3 == a[2] );
  }

  SECTION ( "Constructor that takes an array works" )
  {
    const VectorType a ( { 1, 2, 3 } );

    REQUIRE ( 1 == a[0] );
    REQUIRE ( 2 == a[1] );
    REQUIRE ( 3 == a[2] );
  }

  SECTION ( "Default copy constructor works" )
  {
    VectorType a ( 1, 2, 3 );
    const VectorType b ( a ); // Copy constructor.

    // Should be the same.
    REQUIRE ( a[0] == b[0] );
    REQUIRE ( a[1] == b[1] );
    REQUIRE ( a[2] == b[2] );

    // Is it different memory?
    a[0] = 4; // Changing one value.
    REQUIRE ( 4 == a[0] ); // It should be different.
    REQUIRE ( 1 == b[0] ); // It should be original value.
  }

  SECTION ( "Can call a function for all values" )
  {
    unsigned int count = 0;
    Usul::Math::each ( VectorType ( 1, 2, 3 ), [&] ( TestType value )
    {
      ++count;

      // Need the static cast here to satisfy strict warnings.
      // Not making count a TestType because I want to make sure
      // a reliable interger type is being incremented.
      REQUIRE ( ( static_cast < TestType > ( count ) ) == value );
    } );
    REQUIRE ( 3 == count );
  }

  SECTION ( "Equal vectors are equal" )
  {
    REQUIRE ( true == Usul::Math::equal ( VectorType ( 1, 2, 3 ), VectorType ( 1, 2, 3 ) ) );
  }

  SECTION ( "Different vectors are not equal" )
  {
    VectorType a ( 1, 2, 3 );
    REQUIRE ( false == Usul::Math::equal ( a, VectorType ( 4, 2, 3 ) ) );
    REQUIRE ( false == Usul::Math::equal ( a, VectorType ( 4, 5, 3 ) ) );
    REQUIRE ( false == Usul::Math::equal ( a, VectorType ( 4, 5, 6 ) ) );
  }

  SECTION ( "Can scale a vector" )
  {
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

  SECTION ( "Assigning is making a copy" )
  {
    VectorType a ( 1, 2, 3 );
    const VectorType b = a; // Assignment operator.

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
      VectorType a;

      REQUIRE ( 0 == a[0] );
      REQUIRE ( 0 == a[1] );
      REQUIRE ( 0 == a[2] );

      a.set ( VectorType ( 1, 2, 3 ) );

      REQUIRE ( 1 == a[0] );
      REQUIRE ( 2 == a[1] );
      REQUIRE ( 3 == a[2] );

      a.set ( { 4, 5, 6 } );

      REQUIRE ( 4 == a[0] );
      REQUIRE ( 5 == a[1] );
      REQUIRE ( 6 == a[2] );

      a.set ( 7, 8, 9 );

      REQUIRE ( 7 == a[0] );
      REQUIRE ( 8 == a[1] );
      REQUIRE ( 9 == a[2] );
    }
  }

  SECTION ( "Can add two vectors" )
  {
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

  SECTION ( "Can subtract two vectors" )
  {
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

  SECTION ( "Can scale a vector" )
  {
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

  SECTION ( "Can get the length" )
  {
    // 3-4-5 right triangle.
    checkLength (  3,  4,  0,  5 );
    checkLength (  5, 12,  0, 13 );
    checkLength (  8, 15,  0, 17 );

    // One pythagorean quadruple.
    checkLength ( 1, 2, 2, 3 );
  }

  SECTION ( "Can get the dot product" )
  {
    REQUIRE ( 26 == Usul::Math::dot ( VectorType ( 1, 2, 3 ), VectorType ( 3, 4, 5 ) ) );
    REQUIRE ( 32 == Usul::Math::dot ( VectorType ( 1, 2, 3 ), VectorType ( 4, 5, 6 ) ) );
    REQUIRE ( 38 == Usul::Math::dot ( VectorType ( 1, 2, 3 ), VectorType ( 5, 6, 7 ) ) );
  }

  SECTION ( "Can get the distance squared between two points" )
  {
    REQUIRE ( 12 == Usul::Math::distanceSquared ( VectorType (  0,  0,  0 ), VectorType ( 2, 2, 2 ) ) );
    REQUIRE ( 27 == Usul::Math::distanceSquared ( VectorType (  0,  0,  0 ), VectorType ( 3, 3, 3 ) ) );
    REQUIRE ( 27 == Usul::Math::distanceSquared ( VectorType ( -1, -1, -1 ), VectorType ( 2, 2, 2 ) ) );
    REQUIRE ( 27 == Usul::Math::distanceSquared ( VectorType (  1,  2,  3 ), VectorType ( 4, 5, 6 ) ) );
    REQUIRE ( 48 == Usul::Math::distanceSquared ( VectorType (  0,  0,  0 ), VectorType ( 4, 4, 4 ) ) );
    REQUIRE ( 75 == Usul::Math::distanceSquared ( VectorType (  0,  0,  0 ), VectorType ( 5, 5, 5 ) ) );
  }
}

TEMPLATE_TEST_CASE ( "Vector3 template math functions with signed primitive types", "",
  short, int, long, float, double, ( long double ) )
{
  typedef typename Usul::Math::Vector3 < TestType > VectorType;

  SECTION ( "Can get the dot product" )
  {
    REQUIRE ( -26 == Usul::Math::dot ( VectorType ( 1, 2, 3 ), VectorType ( -3, -4, -5 ) ) );
    REQUIRE ( -32 == Usul::Math::dot ( VectorType ( 1, 2, 3 ), VectorType ( -4, -5, -6 ) ) );
    REQUIRE ( -38 == Usul::Math::dot ( VectorType ( 1, 2, 3 ), VectorType ( -5, -6, -7 ) ) );
  }

  SECTION ( "Can get the cross product" )
  {
    const VectorType a ( 1, 2, 3 );
    const VectorType b ( 4, 5, 6 );

    // Got the answer from here:
    // https://www.wolframalpha.com/input/?i=cross+product+calculator&lk=2
    const VectorType expected ( -3, 6, -3 );

    VectorType c;
    Usul::Math::cross ( a, b, c );
    REQUIRE ( true == Usul::Math::equal ( expected, c ) );

    const VectorType d = Usul::Math::cross ( a, b );
    REQUIRE ( true == Usul::Math::equal ( expected, d ) );
  }
}

TEMPLATE_TEST_CASE ( "Vector3 template math functions with larger primitive types", "",
  short, int, long, ( unsigned short ),
  ( unsigned int ), ( unsigned long ), float, double, ( long double ) )
{
  SECTION ( "Can get the length" )
  {
    // Test all pythagorean quadruples.
    for ( unsigned int i = 0; i < numPythagoreanQuadruples; ++i )
    {
      const auto q = pythagoreanQuadruples[i];
      checkLength (
        static_cast < TestType > ( q[0] ),
        static_cast < TestType > ( q[1] ),
        static_cast < TestType > ( q[2] ),
        static_cast < TestType > ( q[3] )
      );
    }
  }
}

TEMPLATE_TEST_CASE ( "Vector3 template math functions with floating point types", "",
  float, double, ( long double ) )
{
  typedef typename Usul::Math::Vector3 < TestType > VectorType;

  SECTION ( "Can normalize" )
  {
    // They are almost never exact so we have to convert to a string to compare.
    auto isUnitLength = [] ( const VectorType &v )
    {
      const TestType len = Usul::Math::length ( v );
      std::ostringstream s;
      s << len;
      REQUIRE ( "1" == s.str() );
    };

    // Test all pythagorean quadruples.
    for ( unsigned int i = 0; i < numPythagoreanQuadruples; ++i )
    {
      const auto q = pythagoreanQuadruples[i];
      const VectorType a (
        static_cast < TestType > ( q[0] ),
        static_cast < TestType > ( q[1] ),
        static_cast < TestType > ( q[2] )
      );
      const TestType len = static_cast < TestType > ( q[3] );
      REQUIRE ( len == Usul::Math::length ( a ) );

      // We want the original length.
      VectorType b;
      TestType originalLength = 0;
      Usul::Math::normalize ( a, b, &originalLength );
      REQUIRE ( len == originalLength );
      isUnitLength ( b );

      // We do not want the original length.
      VectorType c;
      Usul::Math::normalize ( a, c );
      isUnitLength ( c );

      // We want a new vector.
      const VectorType d = Usul::Math::normalize ( a );
      REQUIRE ( len == Usul::Math::length ( a ) );
      isUnitLength ( d );
    }
  }

  SECTION ( "Can get the angle between two vectors" )
  {
    const VectorType a ( 2,  5, 1 );
    const VectorType b ( 9, -3, 6 );

    // Got the answer from here:
    // https://socratic.org/questions/how-do-i-calculate-the-angle-between-two-vectors
    const std::string expected ( "81.5825" );

    // We need the answer with only so many decimals.
    std::ostringstream answer;
    answer << std::fixed << std::setprecision ( 4 )
      << Usul::Math::radToDeg ( Usul::Math::angle ( a, b ) );

    REQUIRE ( expected == answer.str() );
  }

  SECTION ( "Can get the distance between two points" )
  {
    const VectorType a ( 1, 2, 3 );
    const VectorType b ( 4, 5, 6 );

    // Got the answer from here using "distance between two points":
    // https://www.wolframalpha.com
    const std::string expected ( "5.19615" );

    // We need the answer with only so many decimals.
    std::ostringstream answer;
    answer << std::fixed << std::setprecision ( 5 )
      << Usul::Math::distance ( a, b );

    REQUIRE ( expected == answer.str() );
  }
}
