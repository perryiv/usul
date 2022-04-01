
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

#include "Usul/Math/Constants.h"
#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector4.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Strings/Format.h"

#include "catch2/catch.hpp"

#include <string>

// For readability below.
constexpr unsigned int R0C0 = Usul::Math::R0C0;
constexpr unsigned int R1C0 = Usul::Math::R1C0;
constexpr unsigned int R2C0 = Usul::Math::R2C0;
constexpr unsigned int R3C0 = Usul::Math::R3C0;
constexpr unsigned int R0C1 = Usul::Math::R0C1;
constexpr unsigned int R1C1 = Usul::Math::R1C1;
constexpr unsigned int R2C1 = Usul::Math::R2C1;
constexpr unsigned int R3C1 = Usul::Math::R3C1;
constexpr unsigned int R0C2 = Usul::Math::R0C2;
constexpr unsigned int R1C2 = Usul::Math::R1C2;
constexpr unsigned int R2C2 = Usul::Math::R2C2;
constexpr unsigned int R3C2 = Usul::Math::R3C2;
constexpr unsigned int R0C3 = Usul::Math::R0C3;
constexpr unsigned int R1C3 = Usul::Math::R1C3;
constexpr unsigned int R2C3 = Usul::Math::R2C3;
constexpr unsigned int R3C3 = Usul::Math::R3C3;


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to compare the matrices.
//
////////////////////////////////////////////////////////////////////////////////

namespace { namespace Details
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
} }


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Matrix44 template math functions", "",
  float, double, ( long double ) )
{
  typedef TestType T;
  typedef typename Usul::Math::Matrix44 < T > MatrixType;
  typedef typename Usul::Math::Vector4  < T > Vector4Type;
  typedef typename Usul::Math::Vector3  < T > Vector3Type;

  const MatrixType IDENTITY (
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  );

  const MatrixType MATRIX_A (
    0,   4,   8,  12,
    1,   5,   9,  13,
    2,   6,  10,  14,
    3,   7,  11,  15
  );

  const MatrixType MATRIX_A_TRANSPOSED (
    0,   1,   2,   3,
    4,   5,   6,   7,
    8,   9,  10,  11,
   12,  13,  14,  15
  );

  const MatrixType MATRIX_B (
    7,   4,   8,   2,
    2,   5,   3,   3,
    1,   6,   8,   4,
    5,   7,   6,   5
  );

  const MatrixType MATRIX_B_INVERSE (
    T (  0.089743589743 ), T ( -0.051282051282 ), T ( -0.166666666666 ), T (  0.128205128205 ),
    T (  0.160256410256 ), T (  1.051282051282 ), T ( -0.083333333333 ), T ( -0.628205128205 ),
    T (  0.064102564102 ), T ( -0.179487179487 ), T (  0.166666666666 ), T ( -0.051282051282 ),
    T ( -0.391025641025 ), T ( -1.205128205128 ), T (  0.083333333333 ), T (  1.012820512820 )
  );

  const MatrixType MATRIX_A_X_B (
    76, 152, 148, 104,
    91, 174, 173, 118,
   106, 196, 198, 132,
   121, 218, 223, 146
  );

  const MatrixType MATRIX_B_X_A (
    26, 110, 194, 278,
    20,  72, 124, 176,
    34, 110, 186, 262,
    34, 126, 218, 310
  );

  const MatrixType MATRIX_C (
    1,   0,   0,   7,
    0,   1,   0,   6,
    0,   0,   1,   5,
    0,   0,   0,   1
  );

  const MatrixType MATRIX_C_INVERSE (
    1,   0,   0,  -7,
    0,   1,   0,  -6,
    0,   0,   1,  -5,
    0,   0,   0,   1
  );

  SECTION ( "Indices are as expected" )
  {
    REQUIRE ( R0C0 ==  0 );
    REQUIRE ( R1C0 ==  1 );
    REQUIRE ( R2C0 ==  2 );
    REQUIRE ( R3C0 ==  3 );
    REQUIRE ( R0C1 ==  4 );
    REQUIRE ( R1C1 ==  5 );
    REQUIRE ( R2C1 ==  6 );
    REQUIRE ( R3C1 ==  7 );
    REQUIRE ( R0C2 ==  8 );
    REQUIRE ( R1C2 ==  9 );
    REQUIRE ( R2C2 == 10 );
    REQUIRE ( R3C2 == 11 );
    REQUIRE ( R0C3 == 12 );
    REQUIRE ( R1C3 == 13 );
    REQUIRE ( R2C3 == 14 );
    REQUIRE ( R3C3 == 15 );
  }

  SECTION ( "Default constructor works" )
  {
    const MatrixType a;
    Details::compareMatrices ( a, IDENTITY );
  }

  SECTION ( "Constructor that takes an array works" )
  {
    const MatrixType a ( MATRIX_A.get() );
    Details::compareMatrices ( a, MATRIX_A );
  }

  SECTION ( "Constructor that takes 16 values works" )
  {
    MatrixType a (
      MATRIX_A[R0C0], MATRIX_A[R0C1], MATRIX_A[R0C2], MATRIX_A[R0C3],
      MATRIX_A[R1C0], MATRIX_A[R1C1], MATRIX_A[R1C2], MATRIX_A[R1C3],
      MATRIX_A[R2C0], MATRIX_A[R2C1], MATRIX_A[R2C2], MATRIX_A[R2C3],
      MATRIX_A[R3C0], MATRIX_A[R3C1], MATRIX_A[R3C2], MATRIX_A[R3C3]
    );
    Details::compareMatrices ( a, MATRIX_A );
  }

  SECTION ( "Copy constructor works" )
  {
    MatrixType a ( MATRIX_A.get() );
    const MatrixType b ( a ); // Copy constructor.
    Details::compareMatrices ( a, b );

    // Is it different memory?
    const TestType original ( a[0] );
    a[0] = original + 1; // Changing one value.
    REQUIRE ( a[0] == original + 1 ); // It should be different.
    REQUIRE ( b[0] == original ); // It should be original value.
  }

  SECTION ( "Setter functions work" )
  {
    {
      MatrixType a;
      Details::compareMatrices ( a, IDENTITY );
      a.set ( MATRIX_A );
      Details::compareMatrices ( a, MATRIX_A );
    }
    {
      MatrixType a;
      Details::compareMatrices ( a, IDENTITY );
      a.set ( MATRIX_A.get() );
      Details::compareMatrices ( a, MATRIX_A );
    }
    {
      MatrixType a;
      Details::compareMatrices ( a, IDENTITY );
      a.set (
        MATRIX_A[R0C0], MATRIX_A[R0C1], MATRIX_A[R0C2], MATRIX_A[R0C3],
        MATRIX_A[R1C0], MATRIX_A[R1C1], MATRIX_A[R1C2], MATRIX_A[R1C3],
        MATRIX_A[R2C0], MATRIX_A[R2C1], MATRIX_A[R2C2], MATRIX_A[R2C3],
        MATRIX_A[R3C0], MATRIX_A[R3C1], MATRIX_A[R3C2], MATRIX_A[R3C3]
      );
      Details::compareMatrices ( a, MATRIX_A );
    }
  }

  SECTION ( "Operator [] works" )
  {
    const MatrixType a ( MATRIX_A );
    const TestType *aa ( a.get() );
    REQUIRE ( a[ 0] == aa[ 0] );
    REQUIRE ( a[ 1] == aa[ 1] );
    REQUIRE ( a[ 2] == aa[ 2] );
    REQUIRE ( a[ 3] == aa[ 3] );
    REQUIRE ( a[ 4] == aa[ 4] );
    REQUIRE ( a[ 5] == aa[ 5] );
    REQUIRE ( a[ 6] == aa[ 6] );
    REQUIRE ( a[ 7] == aa[ 7] );
    REQUIRE ( a[ 8] == aa[ 8] );
    REQUIRE ( a[ 9] == aa[ 9] );
    REQUIRE ( a[10] == aa[10] );
    REQUIRE ( a[11] == aa[11] );
    REQUIRE ( a[12] == aa[12] );
    REQUIRE ( a[13] == aa[13] );
    REQUIRE ( a[14] == aa[14] );
    REQUIRE ( a[15] == aa[15] );
  }

  SECTION ( "Operator () works" )
  {
    const MatrixType a ( MATRIX_A );
    REQUIRE ( a[R0C0] == a(0,0) );
    REQUIRE ( a[R1C0] == a(1,0) );
    REQUIRE ( a[R2C0] == a(2,0) );
    REQUIRE ( a[R3C0] == a(3,0) );
    REQUIRE ( a[R0C1] == a(0,1) );
    REQUIRE ( a[R1C1] == a(1,1) );
    REQUIRE ( a[R2C1] == a(2,1) );
    REQUIRE ( a[R3C1] == a(3,1) );
    REQUIRE ( a[R0C2] == a(0,2) );
    REQUIRE ( a[R1C2] == a(1,2) );
    REQUIRE ( a[R2C2] == a(2,2) );
    REQUIRE ( a[R3C2] == a(3,2) );
    REQUIRE ( a[R0C3] == a(0,3) );
    REQUIRE ( a[R1C3] == a(1,3) );
    REQUIRE ( a[R2C3] == a(2,3) );
    REQUIRE ( a[R3C3] == a(3,3) );
  }

  SECTION ( "Can assign with operator []" )
  {
    MatrixType a ( MATRIX_A );
    const unsigned int index = 5;
    const TestType original ( a[index] );
    a[index] = original + 1;
    REQUIRE ( a[index] == ( original + 1 ) );
  }

  SECTION ( "Operator [] throws an exception" )
  {
    try
    {
      MatrixType a ( MATRIX_A );
      a[0] = a[16];
      REQUIRE ( false ); // Should not get to this line.
    }
    catch ( const std::out_of_range &e )
    {
      REQUIRE ( std::string ( e.what() ) == "Index out of range in Matrix44 [] operator" );
    }
    catch ( const std::exception & )
    {
      REQUIRE ( false ); // Should not be here.
    }
  }

  SECTION ( "Operator () throws an exception" )
  {
    try
    {
      MatrixType a ( MATRIX_A );
      a(0,0) = a(0,16);
      REQUIRE ( false ); // Should not get to this line.
    }
    catch ( const std::out_of_range &e )
    {
      REQUIRE ( std::string ( e.what() ) == "Index out of range in Matrix44 () operator" );
    }
    catch ( const std::exception & )
    {
      REQUIRE ( false ); // Should not be here.
    }
  }

  SECTION ( "Equal matrices are equal" )
  {
    const MatrixType a ( MATRIX_A );
    const MatrixType b ( MATRIX_A );
    REQUIRE ( true == Usul::Math::equal ( a, b ) );
  }

  SECTION ( "Different matrices are not equal" )
  {
    const MatrixType a ( IDENTITY );
    const MatrixType b ( MATRIX_A );
    REQUIRE ( false == Usul::Math::equal ( a, b ) );
  }

  SECTION ( "Assigning is making a copy" )
  {
    MatrixType a ( MATRIX_A );
    MatrixType b;
    b = a; // Assignment operator.
    Details::compareMatrices ( a, b );

    // Is it different memory?
    const TestType original ( a[0] );
    a[0] = original + 1; // Changing one value.
    REQUIRE ( a[0] == original + 1 ); // It should be different.
    REQUIRE ( b[0] == original ); // It should be original value.
  }

  SECTION ( "Transposing works" )
  {
    {
      const MatrixType a ( MATRIX_A );
      MatrixType b;
      Usul::Math::transpose ( a, b );
      Details::compareMatrices ( b, MATRIX_A_TRANSPOSED );
    }
    {
      const MatrixType a ( MATRIX_A );
      const MatrixType b = Usul::Math::transpose ( a );
      Details::compareMatrices ( b, MATRIX_A_TRANSPOSED );
    }
  }

  SECTION ( "Translating works" )
  {
    const Vector3Type v ( 10, 20, 30 );

    MatrixType e;
    e[MatrixType::TRANSLATION_X] = v[0];
    e[MatrixType::TRANSLATION_Y] = v[1];
    e[MatrixType::TRANSLATION_Z] = v[2];

    {
      const MatrixType a ( IDENTITY );
      MatrixType b;
      Usul::Math::translate ( a, v, b );
      Details::compareMatrices ( b, e );
    }
    {
      const MatrixType a ( IDENTITY );
      const MatrixType b = Usul::Math::translate ( a, v );
      Details::compareMatrices ( b, e );
    }
  }

  SECTION ( "Can get the determinant" )
  {
    REQUIRE (   0 == Usul::Math::determinant ( MATRIX_A ) );
    REQUIRE ( 156 == Usul::Math::determinant ( MATRIX_B ) );
  }

  SECTION ( "Can get the inverse" )
  {
    {
      MatrixType ib;
      REQUIRE ( true == Usul::Math::inverse ( MATRIX_B, ib ) );
      const std::string actual ( Usul::Strings::formatMatrix44 ( ib ) );
      const std::string expect ( Usul::Strings::formatMatrix44 ( MATRIX_B_INVERSE ) );
      REQUIRE ( expect == actual );
    }
    {
      MatrixType ic;
      REQUIRE ( true == Usul::Math::inverse ( MATRIX_C, ic ) );
      const std::string actual ( Usul::Strings::formatMatrix44 ( ic ) );
      const std::string expect ( Usul::Strings::formatMatrix44 ( MATRIX_C_INVERSE ) );
      REQUIRE ( expect == actual );
    }
  }

  SECTION ( "Can handle not inverse" )
  {
    MatrixType ia;
    REQUIRE ( false == Usul::Math::inverse ( MATRIX_A, ia ) );
  }

  SECTION ( "Can multiply two matrices" )
  {
    const MatrixType i ( IDENTITY );
    const MatrixType a ( MATRIX_A );
    const MatrixType b ( MATRIX_B );
    const MatrixType axb ( MATRIX_A_X_B );
    const MatrixType bxa ( MATRIX_B_X_A );
    {
      MatrixType c;
      Usul::Math::multiply ( i, i, c );
      Details::compareMatrices ( i, c );
      Details::compareMatrices ( i, Usul::Math::multiply ( i, i ) );
      Details::compareMatrices ( i, i * i );
    }
    {
      MatrixType c;
      Usul::Math::multiply ( a, b, c );
      Details::compareMatrices ( axb, c );
      Details::compareMatrices ( axb, Usul::Math::multiply ( a, b ) );
      Details::compareMatrices ( axb, a * b );
    }
    {
      MatrixType c;
      Usul::Math::multiply ( b, a, c );
      Details::compareMatrices ( bxa, c );
      Details::compareMatrices ( bxa, Usul::Math::multiply ( b, a ) );
      Details::compareMatrices ( bxa, b * a );
    }
  }

  SECTION ( "Can multiply matrix times 3D vector" )
  {
    const MatrixType ma ( MATRIX_A );
    const MatrixType mb ( MATRIX_B );
    const MatrixType mc ( MATRIX_C );
    const Vector3Type va ( 2, 3, 4 );
    {
      Vector3Type vb;
      Usul::Math::multiply ( ma, va, vb );

      const std::string actual ( Usul::Strings::formatVector3 ( vb ) );
      const std::string expect ( Usul::Strings::formatVector3 ( Vector3Type (
        T ( 0.6511627906976745 ),
        T ( 0.7674418604651163 ),
        T ( 0.8837209302325582 ) ) )
      );
      REQUIRE ( expect == actual );

      REQUIRE ( Usul::Math::equal ( vb, Usul::Math::multiply ( ma, va ) ) );
      REQUIRE ( Usul::Math::equal ( vb, ma * va ) );
    }
    {
      Vector3Type vb;
      Usul::Math::multiply ( mb, va, vb );

      const std::string actual ( Usul::Strings::formatVector3 ( vb ) );
      const std::string expect ( Usul::Strings::formatVector3 ( Vector3Type (
        T ( 1 ),
        T ( 0.5666666666666667 ),
        T ( 0.9333333333333333 ) ) )
      );
      REQUIRE ( expect == actual );

      REQUIRE ( Usul::Math::equal ( vb, Usul::Math::multiply ( mb, va ) ) );
      REQUIRE ( Usul::Math::equal ( vb, mb * va ) );
    }
    {
      Vector3Type vb;
      Usul::Math::multiply ( mc, va, vb );

      REQUIRE ( 9 == vb[0] );
      REQUIRE ( 9 == vb[1] );
      REQUIRE ( 9 == vb[2] );

      REQUIRE ( Usul::Math::equal ( vb, Usul::Math::multiply ( mc, va ) ) );
      REQUIRE ( Usul::Math::equal ( vb, mc * va ) );
    }
  }

  SECTION ( "Can multiply matrix times 4D vector" )
  {
    const MatrixType ma ( MATRIX_A );
    const MatrixType mb ( MATRIX_B );
    const MatrixType mc ( MATRIX_C );
    const Vector4Type va ( 2, 3, 4, 1 );
    {
      Vector4Type vb;
      Usul::Math::multiply ( ma, va, vb );

      REQUIRE ( 56 == vb[0] );
      REQUIRE ( 66 == vb[1] );
      REQUIRE ( 76 == vb[2] );
      REQUIRE ( 86 == vb[3] );

      REQUIRE ( Usul::Math::equal ( vb, Usul::Math::multiply ( ma, va ) ) );
      REQUIRE ( Usul::Math::equal ( vb, ma * va ) );
    }
    {
      Vector4Type vb;
      Usul::Math::multiply ( mb, va, vb );

      REQUIRE ( 60 == vb[0] );
      REQUIRE ( 34 == vb[1] );
      REQUIRE ( 56 == vb[2] );
      REQUIRE ( 60 == vb[3] );

      REQUIRE ( Usul::Math::equal ( vb, Usul::Math::multiply ( mb, va ) ) );
      REQUIRE ( Usul::Math::equal ( vb, mb * va ) );
    }
    {
      Vector4Type vb;
      Usul::Math::multiply ( mc, va, vb );

      REQUIRE ( 9 == vb[0] );
      REQUIRE ( 9 == vb[1] );
      REQUIRE ( 9 == vb[2] );
      REQUIRE ( 1 == vb[3] );

      REQUIRE ( Usul::Math::equal ( vb, Usul::Math::multiply ( mc, va ) ) );
      REQUIRE ( Usul::Math::equal ( vb, mc * va ) );
    }
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the math functions.
//
////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE ( "Matrix44 functions for float and double", "", float, double )
{
  typedef TestType T;
  typedef std::numeric_limits < T > Limits;
  typedef typename Usul::Math::Matrix44 < T > MatrixType;
  typedef typename Usul::Math::Vector3  < T > Vector3Type;

  static_assert ( ( false == Limits::is_integer ), "Template type is an integer" );
  constexpr TestType tol = Limits::epsilon();

  SECTION ( "Can rotate a matrix" )
  {
    const MatrixType m = Usul::Math::rotate ( MatrixType(), Vector3Type ( 1, 0, 0 ), static_cast < TestType > ( Usul::Math::PI_OVER_2 ) );
    const Vector3Type v = Usul::Math::multiply ( m, Vector3Type ( 0, 1, 0 ) );

    REQUIRE ( std::abs ( v[0] - 0 ) < tol );
    REQUIRE ( std::abs ( v[1] - 0 ) < tol );
    REQUIRE ( std::abs ( v[2] - 1 ) < tol );
  }
}
