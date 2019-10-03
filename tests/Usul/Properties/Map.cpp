
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

#include "Usul/Math/Functions.h"
#include "Usul/Math/Matrix44.h"
#include "Usul/Properties/Map.h"
#include "Usul/Properties/Matrix44.h"
#include "Usul/Properties/Vector2.h"
#include "Usul/Properties/Vector3.h"
#include "Usul/Properties/Vector4.h"

#include "catch2/catch.hpp"

USUL_DEFINE_MAKE_PROPERTY_FUNCTION_SHORTCUT; // mp

namespace Math = Usul::Math;
namespace Properties = Usul::Properties;
typedef unsigned int uint;

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

    REQUIRE ( 1.0  == a.get < double > ( "1d", 2.0  ) );
    REQUIRE ( 1.0f == a.get < float  > ( "1f", 2.0f ) );
    REQUIRE ( 1    == a.get < int    > ( "1i", 2    ) );
    REQUIRE ( 1u   == a.get < uint   > ( "1u", 2u   ) );

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

  SECTION ( "Getting properties can convert them to similar type" )
  {
    Map a;

    a.insert ( "p1", 1.0 );
    REQUIRE ( 1.0  == Properties::get < double > ( a, "p1", 2.0  ) );
    REQUIRE ( 1.0f == Properties::get < float  > ( a, "p1", 2.0f ) );
    REQUIRE ( 1    == Properties::get < int    > ( a, "p1", 2    ) );
    REQUIRE ( 1u   == Properties::get < uint   > ( a, "p1", 2u   ) );

    a.insert ( "p2", 1.1f );
    REQUIRE ( 1.1  == Math::round ( Properties::get < double > ( a, "p2", 2.0  ), 1 ) );
    REQUIRE ( 1.1f == Math::round ( Properties::get < float  > ( a, "p2", 2.0f ), 1 ) );
    REQUIRE ( 1    == Properties::get < int  > ( a, "p2", 2  ) ); // Truncated by static_cast
    REQUIRE ( 1u   == Properties::get < uint > ( a, "p2", 2u ) ); // Truncated by static_cast

    a.insert ( "p3", 1u );
    REQUIRE ( 1.0  == Properties::get < double > ( a, "p3", 2.0  ) );
    REQUIRE ( 1.0f == Properties::get < float  > ( a, "p3", 2.0f ) );
    REQUIRE ( 1    == Properties::get < int    > ( a, "p3", 2  ) );
    REQUIRE ( 1u   == Properties::get < uint   > ( a, "p3", 2u ) );

    a.insert ( "p4", "hi" );
    REQUIRE ( "hi" == Properties::get < std::string > ( a, "p4", "low" ) );

    a.insert ( "p5", Math::Vec3d ( 1, 2, 3 ) );
    REQUIRE ( true == Math::equal ( Math::Vec3d ( 1, 2, 3 ), Properties::get < Math::Vec3d > ( a, "p5", Math::Vec3d ( 10, 20, 30 ) ) ) );
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

    REQUIRE ( 1.0  == a.require < double > ( "1d" ) );
    REQUIRE ( 1.0f == a.require < float  > ( "1f" ) );
    REQUIRE ( 1    == a.require < int    > ( "1i" ) );
    REQUIRE ( 1u   == a.require < uint   > ( "1u" ) );
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

    REQUIRE (  1.0  == a.get < double > ( "1d", 2.0  ) );
    REQUIRE (  2.0f == a.get < float  > ( "1d", 2.0f ) );
    REQUIRE (  2    == a.get < int    > ( "1d", 2    ) );
    REQUIRE (  2u   == a.get < uint   > ( "1d", 2u   ) );
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

  SECTION ( "Can pass properties to constructor" )
  {
    const Map a ( {
      { "1", mp ( 1 ) },
      { "2", mp ( 2.0 ) },
      { "3", mp ( 3.0f ) },
      { "4", mp ( 4u ) },
      { "5", mp ( std::string ( "five" ) ) }, // Not sure why we have to wrap with a string.
      { "6", mp ( Math::Vec3d ( 1, 2, 3 ) ) }
    } );

    REQUIRE ( 1      == a.require < int          > ( "1" ) );
    REQUIRE ( 2.0    == a.require < double       > ( "2" ) );
    REQUIRE ( 3.0f   == a.require < float        > ( "3" ) );
    REQUIRE ( 4u     == a.require < unsigned int > ( "4" ) );
    REQUIRE ( "five" == a.require < std::string  > ( "5" ) );
    REQUIRE ( true == Math::equal ( Math::Vec3d ( 1, 2, 3 ), a.require < Math::Vec3d > ( "6" ) ) );
  }

  SECTION ( "Can get property names" )
  {
    const Map a ( {
      { "1", mp ( 1 ) },
      { "2", mp ( 2 ) },
      { "3", mp ( 3 ) },
      { "4", mp ( 4 ) }
    } );

    REQUIRE ( Map::Strings ( { "1", "2", "3", "4" } ) == a.names() );
  }

  SECTION ( "Can merge property maps" )
  {
    const Map a ( {
      { "1", mp ( 1 ) },
      { "2", mp ( 2 ) },
      { "3", mp ( 3 ) }
    } );

    const Map b ( {
      { "3", mp ( std::string ( "three" ) ) },
      { "4", mp ( 4 ) },
      { "5", mp ( 5 ) }
    } );

    const Map c = Usul::Properties::merge ( a, b );

    REQUIRE ( Map::Strings ( { "1", "2", "3", "4", "5" } ) == c.names() );

    REQUIRE ( 1       == c.require < int         > ( "1" ) );
    REQUIRE ( 2       == c.require < int         > ( "2" ) );
    REQUIRE ( "three" == c.require < std::string > ( "3" ) );
    REQUIRE ( 4       == c.require < int         > ( "4" ) );
    REQUIRE ( 5       == c.require < int         > ( "5" ) );
  }

  SECTION ( "Can merge properties directly" )
  {
    const Map a ( {
      { "1", mp ( 1 ) },
      { "2", mp ( 2 ) },
      { "3", mp ( 3 ) }
    } );

    const Map b = Usul::Properties::merge ( a, {
      { "3", mp ( std::string ( "three" ) ) },
      { "4", mp ( 4 ) },
      { "5", mp ( 5 ) }
    } );

    REQUIRE ( Map::Strings ( { "1", "2", "3", "4", "5" } ) == b.names() );

    REQUIRE ( 1       == b.require < int         > ( "1" ) );
    REQUIRE ( 2       == b.require < int         > ( "2" ) );
    REQUIRE ( "three" == b.require < std::string > ( "3" ) );
    REQUIRE ( 4       == b.require < int         > ( "4" ) );
    REQUIRE ( 5       == b.require < int         > ( "5" ) );
  }
}
