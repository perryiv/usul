
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Math/Functions.h"
#include "Usul/Math/Vector2.h"

#include "catch2/catch.hpp"

#include <sstream>
#include <iomanip>

// Pythagorean triples.
// http://mathworld.wolfram.com/PythagoreanTriple.html
const unsigned int numPythagoreanTriples = 4;
const unsigned char pythagoreanTriples[numPythagoreanTriples][4] = {
  { 3,  4,  5 },
  { 5, 12, 13 },
  { 8, 15, 17 },
  { 7, 24, 25 }
};


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to check the length.
//
////////////////////////////////////////////////////////////////////////////////

template < class ScalarType > inline void checkLength (
  ScalarType v0, ScalarType v1, ScalarType len )
{
  typedef typename Usul::Math::Vector2 < ScalarType > VectorType;
  REQUIRE ( len == Usul::Math::length ( VectorType ( v0, v1 ) ) );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to check the angle between two vectors.
//
////////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline void testAngle ( const VectorType &a, const VectorType &b,
  const typename VectorType::value_type &expected, unsigned int numDecimals )
{
  REQUIRE ( expected == Usul::Math::trunc ( Usul::Math::radToDeg ( Usul::Math::angle ( a, b ) ), numDecimals ) );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef __GNUC__
TEMPLATE_TEST_CASE ( "Vector2 template math functions with all primitive types", "",
  int, long, ( unsigned int ), ( unsigned long ),
  float, double, ( long double ) )
#else
TEMPLATE_TEST_CASE ( "Vector2 template math functions with all primitive types", "",
  char, short, ( unsigned char ), ( unsigned short ),
  int, long, ( unsigned int ), ( unsigned long ),
  float, double, ( long double ) )
#endif
{
  typedef typename Usul::Math::Vector2 < TestType > VectorType;

  SECTION ( "Default constructor works" )
  {
    const VectorType a;

    REQUIRE ( 0 == a[0] );
    REQUIRE ( 0 == a[1] );
  }

  SECTION ( "Constructor that takes 3 values works" )
  {
    const VectorType a ( 1, 2 );

    REQUIRE ( 1 == a[0] );
    REQUIRE ( 2 == a[1] );
  }

  SECTION ( "Constructor that takes an array works" )
  {
    const VectorType a ( { 1, 2 } );

    REQUIRE ( 1 == a[0] );
    REQUIRE ( 2 == a[1] );
  }

  SECTION ( "Default copy constructor works" )
  {
    VectorType a ( 1, 2 );
    const VectorType b ( a ); // Copy constructor.

    // Should be the same.
    REQUIRE ( a[0] == b[0] );
    REQUIRE ( a[1] == b[1] );

    // Is it different memory?
    a[0] = 4; // Changing one value.
    REQUIRE ( 4 == a[0] ); // It should be different.
    REQUIRE ( 1 == b[0] ); // It should be original value.
  }

  SECTION ( "Can call a function for all values" )
  {
    unsigned int count = 0;
    Usul::Math::each ( VectorType ( 1, 2 ), [&] ( TestType value )
    {
      ++count;

      // Need the static cast here to satisfy strict warnings.
      // Not making count a TestType because I want to make sure
      // a reliable interger type is being incremented.
      REQUIRE ( ( static_cast < TestType > ( count ) ) == value );
    } );
    REQUIRE ( VectorType::SIZE == count );
  }

  SECTION ( "Equal vectors are equal" )
  {
    REQUIRE ( true == Usul::Math::equal ( VectorType ( 1, 2 ), VectorType ( 1, 2 ) ) );
  }

  SECTION ( "Different vectors are not equal" )
  {
    VectorType a ( 1, 2 );
    REQUIRE ( false == Usul::Math::equal ( a, VectorType ( 3, 2 ) ) );
    REQUIRE ( false == Usul::Math::equal ( a, VectorType ( 1, 3 ) ) );
    REQUIRE ( false == Usul::Math::equal ( a, VectorType ( 4, 5 ) ) );
  }

  SECTION ( "Can scale a vector" )
  {
    const VectorType a ( 1, 2 );
    const TestType scale ( static_cast < TestType > ( 10 ) );

    VectorType b;
    Usul::Math::scale ( a, scale, b );

    REQUIRE ( 10 == b[0] );
    REQUIRE ( 20 == b[1] );

    const VectorType c = Usul::Math::scale ( a, scale );

    REQUIRE ( 10 == c[0] );
    REQUIRE ( 20 == c[1] );
  }

  SECTION ( "Assigning is making a copy" )
  {
    VectorType a ( 1, 2 );
    VectorType b;
    b = a; // Assignment operator.

    // Should be the same.
    REQUIRE ( a[0] == b[0] );
    REQUIRE ( a[1] == b[1] );

    // Is it different memory?
    a[0] = 4; // Changing one value.
    REQUIRE ( 4 == a[0] ); // It should be different.
    REQUIRE ( 1 == b[0] ); // It should be original value.
  }

  SECTION ( "Setter functions work" )
  {
    VectorType a;

    REQUIRE ( 0 == a[0] );
    REQUIRE ( 0 == a[1] );

    a.set ( VectorType ( 1, 2 ) );

    REQUIRE ( 1 == a[0] );
    REQUIRE ( 2 == a[1] );

    a.set ( { 4, 5 } );

    REQUIRE ( 4 == a[0] );
    REQUIRE ( 5 == a[1] );

    a.set ( 7, 8 );

    REQUIRE ( 7 == a[0] );
    REQUIRE ( 8 == a[1] );
  }

  SECTION ( "Can add two vectors" )
  {
    const VectorType a ( 1, 2 );
    const VectorType b ( 4, 5 );

    VectorType c;
    Usul::Math::add ( a, b, c );

    REQUIRE ( 5 == c[0] );
    REQUIRE ( 7 == c[1] );

    const VectorType d = Usul::Math::add ( a, b );

    REQUIRE ( 5 == d[0] );
    REQUIRE ( 7 == d[1] );

    const VectorType e = a + b;

    REQUIRE ( 5 == e[0] );
    REQUIRE ( 7 == e[1] );
  }

  SECTION ( "Can subtract two vectors" )
  {
    const VectorType a ( 4, 5 );
    const VectorType b ( 1, 2 );

    VectorType c;
    Usul::Math::subtract ( a, b, c );

    REQUIRE ( 3 == c[0] );
    REQUIRE ( 3 == c[1] );

    const VectorType d = Usul::Math::subtract ( a, b );

    REQUIRE ( 3 == d[0] );
    REQUIRE ( 3 == d[1] );

    const VectorType e = a - b;

    REQUIRE ( 3 == e[0] );
    REQUIRE ( 3 == e[1] );
  }

  SECTION ( "Can scale a vector" )
  {
    const VectorType a ( 1, 2 );
    const TestType scale ( static_cast <  TestType> ( 10 ) );

    VectorType b;
    Usul::Math::scale ( a, scale, b );

    REQUIRE ( 10 == b[0] );
    REQUIRE ( 20 == b[1] );

    const VectorType c = Usul::Math::scale ( a, scale );

    REQUIRE ( 10 == c[0] );
    REQUIRE ( 20 == c[1] );

    const VectorType d = a * scale;

    REQUIRE ( 10 == d[0] );
    REQUIRE ( 20 == d[1] );
  }

  SECTION ( "Can get the dot product" )
  {
    REQUIRE ( 11 == Usul::Math::dot ( VectorType ( 1, 2 ), VectorType ( 3, 4 ) ) );
    REQUIRE ( 14 == Usul::Math::dot ( VectorType ( 1, 2 ), VectorType ( 4, 5 ) ) );
    REQUIRE ( 17 == Usul::Math::dot ( VectorType ( 1, 2 ), VectorType ( 5, 6 ) ) );
  }

  SECTION ( "Can get the distance squared between two points" )
  {
    REQUIRE (  8 == Usul::Math::distanceSquared ( VectorType (  0,  0 ), VectorType ( 2, 2 ) ) );
    REQUIRE ( 18 == Usul::Math::distanceSquared ( VectorType (  0,  0 ), VectorType ( 3, 3 ) ) );
    REQUIRE ( 18 == Usul::Math::distanceSquared ( VectorType (  1,  2 ), VectorType ( 4, 5 ) ) );
    REQUIRE ( 32 == Usul::Math::distanceSquared ( VectorType (  0,  0 ), VectorType ( 4, 4 ) ) );
    REQUIRE ( 50 == Usul::Math::distanceSquared ( VectorType (  0,  0 ), VectorType ( 5, 5 ) ) );
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef __GNUC__
TEMPLATE_TEST_CASE ( "Vector2 template math functions with signed primitive types", "",
  int, long, float, double, ( long double ) )
#else
TEMPLATE_TEST_CASE ( "Vector2 template math functions with signed primitive types", "",
  short,
  int, long, float, double, ( long double ) )
#endif
{
  typedef typename Usul::Math::Vector2 < TestType > VectorType;

  SECTION ( "Can get the absolute value of a vector" )
  {
    const VectorType a (  1,  2 );
    const VectorType b ( -1, -2 );
    REQUIRE ( false == Usul::Math::equal ( a, b ) );
    REQUIRE (  true == Usul::Math::equal ( a, Usul::Math::absolute ( b ) ) );
  }

  SECTION ( "Can get the dot product" )
  {
    REQUIRE ( -11 == Usul::Math::dot ( VectorType ( 1, 2 ), VectorType ( -3, -4 ) ) );
    REQUIRE ( -14 == Usul::Math::dot ( VectorType ( 1, 2 ), VectorType ( -4, -5 ) ) );
    REQUIRE ( -17 == Usul::Math::dot ( VectorType ( 1, 2 ), VectorType ( -5, -6 ) ) );
  }

  SECTION ( "Can get the distance squared between two points" )
  {
    REQUIRE ( 18 == Usul::Math::distanceSquared(VectorType ( -1, -1 ), VectorType ( 2, 2 ) ) );
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Vector2 template math functions with floating point types", "",
  float, double, ( long double ) )
{
  typedef typename Usul::Math::Vector2 < TestType > VectorType;

  SECTION ( "Can get the length" )
  {
    checkLength < TestType > ( 3,  4,  5 );
    checkLength < TestType > ( 5, 12, 13 );
    checkLength < TestType > ( 8, 15, 17 );
    checkLength < TestType > ( 7, 24, 25 );
  }

  SECTION ( "Can get the length of pythagorean quadruples" )
  {
    // Test all pythagorean quadruples.
    for ( unsigned int i = 0; i < numPythagoreanTriples; ++i )
    {
      const auto q = pythagoreanTriples[i];
      checkLength (
        static_cast < TestType > ( q[0] ),
        static_cast < TestType > ( q[1] ),
        static_cast < TestType > ( q[2] )
      );
    }
  }

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
    for ( unsigned int i = 0; i < numPythagoreanTriples; ++i )
    {
      const auto q = pythagoreanTriples[i];
      const VectorType a (
        static_cast < TestType > ( q[0] ),
        static_cast < TestType > ( q[1] )
      );
      const TestType len = static_cast < TestType > ( q[2] );
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

  SECTION ( "Can get the distance between two points" )
  {
    const VectorType a ( 1, 2 );
    const VectorType b ( 3, 4 );

    // Got the answer from here using "distance between two points":
    // https://www.wolframalpha.com
    const std::string expected ( "2.82843" );

    // We need the answer with only so many decimals.
    std::ostringstream answer;
    answer << std::fixed << std::setprecision ( 5 )
      << Usul::Math::distance ( a, b );

    REQUIRE ( expected == answer.str() );
  }
}

TEST_CASE ( "Angle between two vectors" )
{
  SECTION ( "Can get the angle between two vectors of floats" )
  {
    typedef float TestType;
    typedef typename Usul::Math::Vector2 < TestType > VectorType;

    testAngle ( VectorType ( 5, 24 ), VectorType ( 1, 3 ),
      static_cast < TestType > ( 6.6666 ), 4 );
  }

  SECTION ( "Can get the angle between two vectors of doubles" )
  {
    typedef double TestType;
    typedef typename Usul::Math::Vector2 < TestType > VectorType;

    testAngle ( VectorType ( 5, 24 ), VectorType ( 1, 3 ),
      static_cast < TestType > ( 6.66665989 ), 8 );
  }

  // SECTION ( "Can get the angle between two vectors of long doubles" )
  // {
  //   typedef long double TestType;
  //   typedef typename Usul::Math::Vector2 < TestType > VectorType;
  //
  //   // Why doesn't this one work?
  //   testAngle ( VectorType ( 5, 24 ), VectorType ( 1, 3 ),
  //     static_cast < TestType > ( 6.66665989 ), 8 );
  // }
}
