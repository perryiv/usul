
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the error-checking.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Errors/Check.h"
#include "Usul/Math/Vector4.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Math/Vector2.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test error checking when accessing an index.
//
////////////////////////////////////////////////////////////////////////////////

template < class VectorType >
inline void testAccessIndexRange ( const VectorType &vec )
{
  typedef typename VectorType::value_type ValueType;
  const unsigned int size = VectorType::SIZE;

  // All these should work.
  for ( unsigned int i = 0; i < size; ++i )
  {
    ValueType value = vec[i];
    value += value; // Keep the compiler happy.
  }

  // This should throw a standard exception.
  try
  {
    vec[size];
    REQUIRE ( false );
  }
  catch ( const std::exception &e )
  {
    const std::string expected ( "Index out of range" );
    const std::string actual ( e.what(), e.what() + 18 );
    REQUIRE ( actual == expected );
  }
  catch ( ... )
  {
    REQUIRE ( false );
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the error-checking.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Error checking" )
{
  typedef Usul::Math::Vec4d Vec4;
  typedef Usul::Math::Vec3d Vec3;
  typedef Usul::Math::Vec2d Vec2;

  SECTION ( "Vector should throw an exception when an index is out of range" )
  {
    testAccessIndexRange ( Vec4 ( 1, 2, 3, 4 ) );
    testAccessIndexRange ( Vec3 ( 1, 2, 3 ) );
    testAccessIndexRange ( Vec2 ( 1, 2 ) );
  }
}
