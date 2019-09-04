
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the property function(s).
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Math/Vector4.h"
#include "Usul/Properties/Map.h"

#include "catch2/catch.hpp"

namespace Math = Usul::Math;
namespace Properties = Usul::Properties;

#define COMMON_CONSTRUCTOR_ARGUMENTS { \
  { "center", Properties::make ( v3d1 ) }, \
  { "color",  Properties::make ( v4f1 ) }, \
  { "radius", Properties::make ( 1.0 ) }, \
  { "matrix", Properties::make ( md1 ) } \
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the property function(s).
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Property Functions" )
{
  typedef Properties::Map Map;

  const Math::Matrix44d md1 (
    0.0, 1.0, 2.0, 3.0,
    1.0, 2.0, 3.0, 4.0,
    2.0, 3.0, 4.0, 5.0,
    3.0, 4.0, 5.0, 6.0
  );
  const Math::Matrix44d md2;

  const Math::Matrix44f mf1 (
    0.0f, 1.0f, 2.0f, 3.0f,
    1.0f, 2.0f, 3.0f, 4.0f,
    2.0f, 3.0f, 4.0f, 5.0f,
    3.0f, 4.0f, 5.0f, 6.0f
  );
  const Math::Matrix44f mf2;

  const Math::Vec3d v3d1 ( 0.1, 0.2, 0.3 );
  const Math::Vec3d v3d2 ( 1.0, 2.0, 3.0 );

  const Math::Vec3f v3f1 ( 0.1f, 0.2f, 0.3f );
  const Math::Vec3f v3f2 ( 1.0f, 2.0f, 3.0f );

  const Math::Vec4d v4d1 ( 0.5, 0.5, 0.5, 1.0 );
  const Math::Vec4d v4d2 ( 1.0, 2.0, 3.0, 1.0 );

  const Math::Vec4f v4f1 ( 0.5f, 0.5f, 0.5f, 1.0f );
  const Math::Vec4f v4f2 ( 1.0f, 2.0f, 3.0f, 1.0f );

  SECTION ( "Use all the constructors" )
  {
    const Map a;
    const Map b ( a );
    const Map c ( a.values() );
    const Map d ( COMMON_CONSTRUCTOR_ARGUMENTS );
  }

  SECTION ( "Use all the assignment operators" )
  {
    const Map a;
    const Map b = a;
    const Map c = a.values();
    const Map d = { COMMON_CONSTRUCTOR_ARGUMENTS };
  }

  SECTION ( "Size of the map" )
  {
    const Map a;
    REQUIRE ( 0 == a.size() );

    const Map b ( COMMON_CONSTRUCTOR_ARGUMENTS );
    REQUIRE ( 4 == b.size() );
  }

  SECTION ( "Empty map" )
  {
    const Map a;
    REQUIRE ( true == a.empty() );

    const Map b ( COMMON_CONSTRUCTOR_ARGUMENTS );
    REQUIRE ( false == b.empty() );
  }

  SECTION ( "Equal maps" )
  {
    const Map a;
    const Map b ( a );
    REQUIRE ( a == b );
    REQUIRE ( Usul::Properties::equal ( a, b ) );

    const Map c ( COMMON_CONSTRUCTOR_ARGUMENTS );
    const Map d ( c );
    REQUIRE ( c == d );
    REQUIRE ( Usul::Properties::equal ( c, d ) );
  }

  SECTION ( "Can insert and get properties" )
  {
    Map a;

    a.insert ( "1d", 1.0 );
    a.insert ( "1f", 1.0f );
    a.insert ( "1i", 1 );
    a.insert ( "1u", 1u );

    REQUIRE ( 1.0  == a.get < double       > ( "1d", 2.0  ) );
    REQUIRE ( 1.0f == a.get < float        > ( "1f", 2.0f ) );
    REQUIRE ( 1    == a.get < int          > ( "1i", 2    ) );
    REQUIRE ( 1u   == a.get < unsigned int > ( "1u", 2u   ) );

    a.insert ( "md1", md1 );
    a.insert ( "v3d1", v3d1 );
    a.insert ( "v3f1", v3f1 );
    a.insert ( "v4d1", v4d1 );
    a.insert ( "v4f1", v4f1 );

    REQUIRE ( Math::equal ( md1,  a.get < Math::Matrix44d > ( "md1",  md2  ) ) );
    REQUIRE ( Math::equal ( v3d1, a.get < Math::Vec3d     > ( "v3d1", v3d2 ) ) );
    REQUIRE ( Math::equal ( v3f1, a.get < Math::Vec3f     > ( "v3f1", v3f2 ) ) );
    REQUIRE ( Math::equal ( v4d1, a.get < Math::Vec4d     > ( "v4d1", v4d2 ) ) );
    REQUIRE ( Math::equal ( v4f1, a.get < Math::Vec4f     > ( "v4f1", v4f2 ) ) );

    a.insert ( "empty string", "" );
    REQUIRE ( true == a.has ( "empty string" ) );
    REQUIRE ( "" == a.get < std::string > ( "empty string", "not empty" ) );

    a.insert ( "nullptr", nullptr );
    REQUIRE ( true == a.has ( "nullptr" ) );
    REQUIRE ( nullptr == a.require < std::nullptr_t > ( "nullptr" ) );
  }

  SECTION ( "Second insertion should fail" )
  {
    Map a;

    a.insert ( "p1", 10 );
    REQUIRE ( 10 == a.get < int > ( "p1", 100 ) );

    a.insert ( "p1", 20 );
    REQUIRE ( 10 == a.get < int > ( "p1", 100 ) );
  }

  SECTION ( "Can update properties" )
  {
    Map a;

    a.update ( "p1", 10 );
    REQUIRE ( 10 == a.get < int > ( "p1", 100 ) );

    a.update ( "p1", 20 );
    REQUIRE ( 20 == a.get < int > ( "p1", 100 ) );

    a.update ( "p1", "p1" );
    REQUIRE ( "p1" == a.get < std::string > ( "p1", "p1" ) );
  }

  SECTION ( "Can clear the map" )
  {
    Map a;

    REQUIRE ( 0 == a.size() );

    a.insert ( "p1", "hi" );
    a.insert ( "p2", 100  );

    REQUIRE ( 2 == a.size() );

    a.clear();

    REQUIRE ( 0 == a.size() );
  }

  SECTION ( "Can erase properties" )
  {
    Map a;

    a.insert ( "p1", "hi" );
    a.insert ( "p2", 100  );
    a.insert ( "p3", 1.0  );
    a.insert ( "p4", 42   );
    REQUIRE ( 4 == a.size() );

    REQUIRE (  true == a.has ( "p1" ) );
    REQUIRE (  true == a.has ( "p2" ) );
    REQUIRE (  true == a.has ( "p3" ) );
    REQUIRE (  true == a.has ( "p4" ) );
    REQUIRE ( false == a.has ( "p5" ) );

    a.erase ( "p1" );
    REQUIRE ( 3 == a.size() );
    REQUIRE ( false == a.has ( "p1" ) );

    a.erase ( "wrong name" );
    REQUIRE ( 3 == a.size() );
    REQUIRE ( false == a.has ( "wrong name" ) );

    a.erase ( "p2" );
    REQUIRE ( 2 == a.size() );
    REQUIRE ( false == a.has ( "p2" ) );

    a.erase ( "p3" );
    REQUIRE ( 1 == a.size() );
    REQUIRE ( false == a.has ( "p3" ) );

    a.erase ( "p4" );
    REQUIRE ( 0 == a.size() );
    REQUIRE ( false == a.has ( "p4" ) );
  }

  SECTION ( "Can insert and require properties" )
  {
    Map a;

    a.insert ( "1d", 1.0 );
    a.insert ( "1f", 1.0f );
    a.insert ( "1i", 1 );
    a.insert ( "1u", 1u );
    a.insert ( "p1", "p1" );

    REQUIRE ( 1.0  == a.require < double       > ( "1d" ) );
    REQUIRE ( 1.0f == a.require < float        > ( "1f" ) );
    REQUIRE ( 1    == a.require < int          > ( "1i" ) );
    REQUIRE ( 1u   == a.require < unsigned int > ( "1u" ) );
    REQUIRE ( "p1" == a.require < std::string  > ( "p1" ) );

    a.insert ( "md1", md1 );
    a.insert ( "v3d1", v3d1 );
    a.insert ( "v3f1", v3f1 );
    a.insert ( "v4d1", v4d1 );
    a.insert ( "v4f1", v4f1 );

    REQUIRE ( Math::equal ( md1,  a.require < Math::Matrix44d > ( "md1"  ) ) );
    REQUIRE ( Math::equal ( v3d1, a.require < Math::Vec3d     > ( "v3d1" ) ) );
    REQUIRE ( Math::equal ( v3f1, a.require < Math::Vec3f     > ( "v3f1" ) ) );
    REQUIRE ( Math::equal ( v4d1, a.require < Math::Vec4d     > ( "v4d1" ) ) );
    REQUIRE ( Math::equal ( v4f1, a.require < Math::Vec4f     > ( "v4f1" ) ) );
  }

  SECTION ( "Get default value when appropriate" )
  {
    Map a;

    REQUIRE ( 12.34 == a.get < double > ( "p1", 12.34 ) );

    a.insert ( "1d", 1.0 );
    a.insert ( "1f", 1.0f );
    a.insert ( "1i", 1 );
    a.insert ( "1u", 1u );

    REQUIRE ( 12.34 == a.get < double > ( "p1", 12.34 ) );

    REQUIRE (  1.0  == a.get < double       > ( "1d", 2.0  ) );
    REQUIRE (  2.0f == a.get < float        > ( "1d", 2.0f ) );
    REQUIRE (  2    == a.get < int          > ( "1d", 2    ) );
    REQUIRE (  2u   == a.get < unsigned int > ( "1d", 2u   ) );
  }

  SECTION ( "Should throw" )
  {
    try
    {
      Map a;
      a.insert ( "p1", 123.456 );

      a.require < double > ( "p1" );
      REQUIRE ( true ); // Should get to this line.

      a.require < float > ( "p1" );
      REQUIRE ( false ); // Should not get to this line.
    }
    catch ( const std::exception &e )
    {
      // We should be here because of the exception.
      REQUIRE ( std::string ( e.what() ) == std::string ( "Property 'p1' is not the required type" ) );
    }

    try
    {
      Map a;
      a.insert ( "p1", 123.456 );

      a.require < double > ( "p2" );
      REQUIRE ( false ); // Should not get to this line.
    }
    catch ( const std::exception &e )
    {
      // We should be here because of the exception.
      REQUIRE ( std::string ( e.what() ) == std::string ( "Property 'p2' is not in the map" ) );
    }
  }
}
