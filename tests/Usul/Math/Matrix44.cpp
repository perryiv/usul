
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

#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector4.h"
#include "Usul/Math/Vector3.h"

#include "catch2/catch.hpp"

#include <vector>


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to compare the matrices.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class M1, class M2 >
  inline void compareMatrices ( const M1 &m1, const M2 &m2 )
  {
    REQUIRE ( m1[ 0] == m2[ 0] );
    REQUIRE ( m1[ 1] == m2[ 1] );
    REQUIRE ( m1[ 2] == m2[ 2] );
    REQUIRE ( m1[ 3] == m2[ 3] );

    REQUIRE ( m1[ 4] == m2[ 4] );
    REQUIRE ( m1[ 5] == m2[ 5] );
    REQUIRE ( m1[ 6] == m2[ 6] );
    REQUIRE ( m1[ 7] == m2[ 7] );

    REQUIRE ( m1[ 8] == m2[ 8] );
    REQUIRE ( m1[ 9] == m2[ 9] );
    REQUIRE ( m1[10] == m2[10] );
    REQUIRE ( m1[11] == m2[11] );

    REQUIRE ( m1[12] == m2[12] );
    REQUIRE ( m1[13] == m2[13] );
    REQUIRE ( m1[14] == m2[14] );
    REQUIRE ( m1[15] == m2[15] );
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Matrix44 template math functions", "",
  float, double, ( long double ) )
{
  typedef typename Usul::Math::Matrix44 < TestType > MatrixType;
  // typedef typename Usul::Math::Vector4  < TestType > Vector4Type;
  // typedef typename Usul::Math::Vector3  < TestType > Vector3Type;

  const std::vector < TestType > IDENTITY ( {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  } );

  const std::vector < TestType > MATRIX_A ( {
    1, 0, 0, 1,
    0, 2, 0, 0,
    0, 1, 3, 0,
    0, 0, 0, 4
  } );

  const std::vector < TestType > MATRIX_B ( {
    5, 0, 3, 0,
    0, 6, 0, 0,
    0, 0, 7, 0,
    1, 0, 0, 8
  } );

  const std::vector < TestType > MATRIX_C ( {
     0,  1,  2,  3,
    10, 11, 12, 13,
    20, 21, 22, 23,
    30, 31, 32, 33
  } );

  // Used www.wolframalpha.com with this input:
  // { { 1, 0, 0, 1 }, { 0, 2, 0, 0 }, { 0, 1, 3, 0 }, { 0, 0, 0, 4 } }
  // { { 5, 0, 3, 0 }, { 0, 6, 0, 0 }, { 0, 0, 7, 0 }, { 1, 0, 0, 8 } }
  const std::vector < TestType > MATRIX_A_X_B ( {
    6,  0,  3,  8,
    0, 12,  0,  0,
    0,  6, 21,  0,
    4,  0,  0, 32
  } );

  // Used www.wolframalpha.com with this input:
  // { { 0, 1, 2, 3 }, { 10, 11, 12, 13 }, { 20, 21, 22, 23 }, { 30, 31, 32, 33 } }
  const std::vector < TestType > MATRIX_C_X_C ( {
     140,  146,  152,  158,
     740,  786,  832,  878,
    1340, 1426, 1512, 1598,
    1940, 2066, 2192, 2318
  } );

  SECTION ( "Default constructor works" )
  {
    const MatrixType a;
    Details::compareMatrices ( a, IDENTITY );
  }

  SECTION ( "Constructor that takes an array works" )
  {
    const MatrixType a ( &MATRIX_A[0] );
    Details::compareMatrices ( a, MATRIX_A );
  }

  SECTION ( "Copy constructor works" )
  {
    MatrixType a ( &MATRIX_A[0] );
    const MatrixType b ( a ); // Copy constructor.
    Details::compareMatrices ( a, b );

    // Is it different memory?
    a[0] = 4; // Changing one value.
    REQUIRE ( 4 == a[0] ); // It should be different.
    REQUIRE ( 1 == b[0] ); // It should be original value.
  }

  SECTION ( "Equal matrices are equal" )
  {
    const MatrixType a ( &MATRIX_A[0] );
    const MatrixType b ( &MATRIX_A[0] );
    REQUIRE ( true == Usul::Math::equal ( a, b ) );
  }

  SECTION ( "Different matrices are not equal" )
  {
    const MatrixType a ( &IDENTITY[0] );
    const MatrixType b ( &MATRIX_A[0] );
    REQUIRE ( false == Usul::Math::equal ( a, b ) );
  }

  SECTION ( "Assigning is making a copy" )
  {
    MatrixType a ( &MATRIX_A[0] );
    MatrixType b;
    b = a; // Assignment operator.
    Details::compareMatrices ( a, b );

    // Is it different memory?
    a[0] = 4; // Changing one value.
    REQUIRE ( 4 == a[0] ); // It should be different.
    REQUIRE ( 1 == b[0] ); // It should be original value.
  }

  SECTION ( "Setter functions work" )
  {
    MatrixType a;
    Details::compareMatrices ( a, IDENTITY );

    a.set ( MatrixType ( &MATRIX_A[0] ) );
    Details::compareMatrices ( a, MATRIX_A );

    a.set ( &MATRIX_B[0] );
    Details::compareMatrices ( a, MATRIX_B );
  }

  SECTION ( "Can multiply two matrices" )
  {
    {
      const MatrixType a ( &MATRIX_C[0] );
      const MatrixType b ( &MATRIX_C[0] );
      MatrixType c;
      Usul::Math::multiply ( a, b, c );
      Details::compareMatrices ( c, MATRIX_C_X_C );
    }
    {
      const MatrixType a ( &MATRIX_A[0] );
      const MatrixType b ( &MATRIX_B[0] );
      MatrixType c;
      Usul::Math::multiply ( a, b, c );
      Details::compareMatrices ( c, MATRIX_A_X_B );
    }
    {
      const MatrixType a ( &MATRIX_C[0] );
      const MatrixType b ( &MATRIX_C[0] );
      const MatrixType c = Usul::Math::multiply ( a, b );
      Details::compareMatrices ( c, MATRIX_C_X_C );
    }
    {
      const MatrixType a ( &MATRIX_A[0] );
      const MatrixType b ( &MATRIX_B[0] );
      const MatrixType c = Usul::Math::multiply ( a, b );
      Details::compareMatrices ( c, MATRIX_A_X_B );
    }
    {
      const MatrixType a ( &MATRIX_C[0] );
      const MatrixType b ( &MATRIX_C[0] );
      const MatrixType c = Usul::Math::multiply ( a, b );
      Details::compareMatrices ( c, MATRIX_C_X_C );
    }
    {
      const MatrixType a ( &MATRIX_A[0] );
      const MatrixType b ( &MATRIX_B[0] );
      const MatrixType c = Usul::Math::multiply ( a, b );
      Details::compareMatrices ( c, MATRIX_A_X_B );
    }
    {
      const MatrixType a ( &MATRIX_C[0] );
      const MatrixType b ( &MATRIX_C[0] );
      const MatrixType c = a * b;
      Details::compareMatrices ( c, MATRIX_C_X_C );
    }
    {
      const MatrixType a ( &MATRIX_A[0] );
      const MatrixType b ( &MATRIX_B[0] );
      const MatrixType c = a * b;
      Details::compareMatrices ( c, MATRIX_A_X_B );
    }
  }

//   SECTION ( "Can subtract two vectors" )
//   {
//     const VectorType a ( 4, 5, 6, 7 );
//     const VectorType b ( 1, 2, 3, 4 );
//
//     VectorType c;
//     Usul::Math::subtract ( a, b, c );
//
//     REQUIRE ( 3 == c[0] );
//     REQUIRE ( 3 == c[1] );
//     REQUIRE ( 3 == c[2] );
//     REQUIRE ( 3 == c[3] );
//
//     const VectorType d = Usul::Math::subtract ( a, b );
//
//     REQUIRE ( 3 == d[0] );
//     REQUIRE ( 3 == d[1] );
//     REQUIRE ( 3 == d[2] );
//     REQUIRE ( 3 == d[3] );
//
//     const VectorType e = a - b;
//
//     REQUIRE ( 3 == e[0] );
//     REQUIRE ( 3 == e[1] );
//     REQUIRE ( 3 == e[2] );
//     REQUIRE ( 3 == e[3] );
//   }
//
//   SECTION ( "Can scale a vector" )
//   {
//     const VectorType a ( 1, 2, 3, 4 );
//     const TestType scale ( static_cast < TestType > ( 10 ) );
//
//     VectorType b;
//     Usul::Math::scale ( a, scale, b );
//
//     REQUIRE ( 10 == b[0] );
//     REQUIRE ( 20 == b[1] );
//     REQUIRE ( 30 == b[2] );
//     REQUIRE ( 40 == b[3] );
//
//     const VectorType c = Usul::Math::scale ( a, scale );
//
//     REQUIRE ( 10 == c[0] );
//     REQUIRE ( 20 == c[1] );
//     REQUIRE ( 30 == c[2] );
//     REQUIRE ( 40 == c[3] );
//
//     const VectorType d = a * scale;
//
//     REQUIRE ( 10 == d[0] );
//     REQUIRE ( 20 == d[1] );
//     REQUIRE ( 30 == d[2] );
//     REQUIRE ( 40 == d[3] );
//   }
//
//   SECTION ( "Can get the dot product" )
//   {
//     REQUIRE ( 50 == Usul::Math::dot ( VectorType ( 1, 2, 3, 4 ), VectorType ( 3, 4, 5, 6 ) ) );
//     REQUIRE ( 60 == Usul::Math::dot ( VectorType ( 1, 2, 3, 4 ), VectorType ( 4, 5, 6, 7 ) ) );
//     REQUIRE ( 70 == Usul::Math::dot ( VectorType ( 1, 2, 3, 4 ), VectorType ( 5, 6, 7, 8 ) ) );
//   }
//
//   SECTION ( "Can get the distance squared between two points" )
//   {
//     REQUIRE (  16 == Usul::Math::distanceSquared ( VectorType (  0,  0,  0,  0 ), VectorType ( 2, 2, 2, 2 ) ) );
//     REQUIRE (  36 == Usul::Math::distanceSquared ( VectorType (  0,  0,  0,  0 ), VectorType ( 3, 3, 3, 3 ) ) );
//     REQUIRE (  36 == Usul::Math::distanceSquared ( VectorType (  1,  2,  3,  4 ), VectorType ( 4, 5, 6, 7 ) ) );
//     REQUIRE (  64 == Usul::Math::distanceSquared ( VectorType (  0,  0,  0,  0 ), VectorType ( 4, 4, 4, 4 ) ) );
//     REQUIRE ( 100 == Usul::Math::distanceSquared ( VectorType (  0,  0,  0,  0 ), VectorType ( 5, 5, 5, 5 ) ) );
//   }
// }
//
//
// ////////////////////////////////////////////////////////////////////////////////
// //
// //  Test the math functions.
// //
// ////////////////////////////////////////////////////////////////////////////////
//
// #ifdef __GNUC__
// TEMPLATE_TEST_CASE ( "Vector4 template math functions with signed primitive types", "",
//   int, long, float, double, ( long double ) )
// #else
// TEMPLATE_TEST_CASE ( "Vector4 template math functions with signed primitive types", "",
//   short,
//   int, long, float, double, ( long double ) )
// #endif
// {
//   typedef typename Usul::Math::Vector4 < TestType > VectorType;
//
//   SECTION ( "Can get the dot product" )
//   {
//     REQUIRE ( -50 == Usul::Math::dot ( VectorType ( 1, 2, 3, 4 ), VectorType ( -3, -4, -5, -6 ) ) );
//     REQUIRE ( -60 == Usul::Math::dot ( VectorType ( 1, 2, 3, 4 ), VectorType ( -4, -5, -6, -7 ) ) );
//     REQUIRE ( -70 == Usul::Math::dot ( VectorType ( 1, 2, 3, 4 ), VectorType ( -5, -6, -7, -8 ) ) );
//   }
//
//   SECTION ( "Can get the distance squared between two points" )
//   {
//     REQUIRE (  36 == Usul::Math::distanceSquared ( VectorType ( -1, -1, -1, -1 ), VectorType ( 2, 2, 2, 2 ) ) );
//   }
// }
//
//
// ////////////////////////////////////////////////////////////////////////////////
// //
// //  Test the math functions.
// //
// ////////////////////////////////////////////////////////////////////////////////
//
// TEMPLATE_TEST_CASE ( "Vector4 template math functions with floating point types", "",
//   float, double, ( long double ) )
// {
//   typedef typename Usul::Math::Vector4 < TestType > VectorType;
//
//   SECTION ( "Can get the length" )
//   {
//     // 3-4-5 right triangle.
//     checkLength < TestType > (  3,  4,  0,  0,  5 );
//     checkLength < TestType > (  5, 12,  0,  0, 13 );
//     checkLength < TestType > (  8, 15,  0,  0, 17 );
//
//     // One pythagorean quadruple.
//     checkLength < TestType > ( 1, 2, 2, 0, 3 );
//   }
//
//   SECTION ( "Can get the length of pythagorean quadruples" )
//   {
//     // Test all pythagorean quadruples.
//     for ( unsigned int i = 0; i < numPythagoreanQuintuples; ++i )
//     {
//       const auto q = pythagoreanQuintuples[i];
//       checkLength (
//         static_cast < TestType > ( q[0] ),
//         static_cast < TestType > ( q[1] ),
//         static_cast < TestType > ( q[2] ),
//         static_cast < TestType > ( q[3] ),
//         static_cast < TestType > ( q[4] )
//       );
//     }
//   }
//
//   SECTION ( "Can normalize" )
//   {
//     // They are almost never exact so we have to convert to a string to compare.
//     auto isUnitLength = [] ( const VectorType &v )
//     {
//       const TestType len = Usul::Math::length ( v );
//       std::ostringstream s;
//       s << len;
//       REQUIRE ( "1" == s.str() );
//     };
//
//     // Test all pythagorean quadruples.
//     for ( unsigned int i = 0; i < numPythagoreanQuintuples; ++i )
//     {
//       const auto q = pythagoreanQuintuples[i];
//       const VectorType a (
//         static_cast < TestType > ( q[0] ),
//         static_cast < TestType > ( q[1] ),
//         static_cast < TestType > ( q[2] ),
//         static_cast < TestType > ( q[3] )
//       );
//       const TestType len = static_cast < TestType > ( q[4] );
//       REQUIRE ( len == Usul::Math::length ( a ) );
//
//       // We want the original length.
//       VectorType b;
//       TestType originalLength = 0;
//       Usul::Math::normalize ( a, b, &originalLength );
//       REQUIRE ( len == originalLength );
//       isUnitLength ( b );
//
//       // We do not want the original length.
//       VectorType c;
//       Usul::Math::normalize ( a, c );
//       isUnitLength ( c );
//
//       // We want a new vector.
//       const VectorType d = Usul::Math::normalize ( a );
//       REQUIRE ( len == Usul::Math::length ( a ) );
//       isUnitLength ( d );
//     }
//   }
//
//   SECTION ( "Can get the angle between two vectors" )
//   {
//     const VectorType a ( 2,  5,  1,  0 );
//     const VectorType b ( 9, -3,  6,  0 );
//
//     // Got the answer from here:
//     // https://socratic.org/questions/how-do-i-calculate-the-angle-between-two-vectors
//     const std::string expected ( "81.5825" );
//
//     // We need the answer with only so many decimals.
//     std::ostringstream answer;
//     answer << std::fixed << std::setprecision ( 4 )
//       << Usul::Math::radToDeg ( Usul::Math::angle ( a, b ) );
//
//     REQUIRE ( expected == answer.str() );
//   }
//
//   SECTION ( "Can get the distance between two points" )
//   {
//     const VectorType a ( 1, 2, 3, 4 );
//     const VectorType b ( 4, 5, 6, 7 );
//
//     // Got the answer from here using "distance between two points":
//     // https://www.wolframalpha.com
//     REQUIRE ( 6 == Usul::Math::distance ( a, b ) );
//   }
}
