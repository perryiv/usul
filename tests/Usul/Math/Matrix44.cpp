
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
  typedef typename Usul::Math::Vector4  < TestType > Vector4Type;
  typedef typename Usul::Math::Vector3  < TestType > Vector3Type;

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

  SECTION ( "Can multiply matrix times vector" )
  {
    {
      const MatrixType a ( &MATRIX_A[0] );
      const Vector3Type b ( 2, 3, 4 );
      Vector3Type c;
      Usul::Math::multiply ( a, b, c );

      REQUIRE (  3 == c[0] );
      REQUIRE (  6 == c[1] );
      REQUIRE ( 15 == c[2] );
    }
    {
      const MatrixType a ( &MATRIX_A[0] );
      const Vector4Type b ( 2, 3, 4, 1 );
      Vector4Type c;
      Usul::Math::multiply ( a, b, c );

      REQUIRE (  3 == c[0] );
      REQUIRE (  6 == c[1] );
      REQUIRE ( 15 == c[2] );
      REQUIRE (  4 == c[3] );
    }
  }
}
