
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
#include "Usul/Tools/Any.h"

#include "catch2/catch.hpp"

namespace Math = Usul::Math;
namespace Any = Usul::Tools::Any;


////////////////////////////////////////////////////////////////////////////////
//
//  Test the property function(s).
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Usul::Tools::Any" )
{
  typedef Any::MapType Map;

  const Math::Matrix44d md1 (
    0.0, 1.0, 2.0, 3.0,
    1.0, 2.0, 3.0, 4.0,
    2.0, 3.0, 4.0, 5.0,
    3.0, 4.0, 5.0, 6.0
  );
  const Math::Matrix44d md2;
  const Math::Matrix44f mf2;

  const Math::Vec3d v3d1 ( 0.1, 0.2, 0.3 );
  const Math::Vec3d v3d2 ( 1.0, 2.0, 3.0 );
  const Math::Vec3f v3f2 ( 1.0f, 2.0f, 3.0f );

  const Math::Vec4f v4f1 ( 0.5f, 0.5f, 0.5f, 1.0f );
  const Math::Vec4f v4f2 ( 1.0f, 2.0f, 3.0f, 1.0f );
  const Math::Vec4d v4d2 ( 1.0, 2.0, 3.0, 1.0 );

  const Map properties = {
    { "center", v3d1 },
    { "color", v4f1 },
    { "radiusd", 1.0 },
    { "radiusf", 1.0f },
    { "radiusi", 1 },
    { "radiusu", 1u },
    { "matrix", md1 }
  };

  SECTION ( "Can see if there are properties" )
  {
    REQUIRE (  true == Any::has ( properties, "center" ) );
    REQUIRE (  true == Any::has ( properties, "color" ) );
    REQUIRE (  true == Any::has ( properties, "radiusd" ) );
    REQUIRE (  true == Any::has ( properties, "radiusf" ) );
    REQUIRE (  true == Any::has ( properties, "radiusi" ) );
    REQUIRE (  true == Any::has ( properties, "radiusu" ) );
    REQUIRE (  true == Any::has ( properties, "matrix" ) );

    REQUIRE ( false == Any::has ( properties, "corner" ) );
  }

  SECTION ( "Can see if there are properties of a specific type" )
  {
    REQUIRE (  true == Any::has < Math::Vec3d > ( properties, "center" ) );
    REQUIRE ( false == Any::has < Math::Vec3f > ( properties, "center" ) );
    REQUIRE ( false == Any::has < double      > ( properties, "center" ) );

    REQUIRE (  true == Any::has < Math::Vec4f > ( properties, "color" ) );
    REQUIRE ( false == Any::has < Math::Vec4d > ( properties, "color" ) );
    REQUIRE ( false == Any::has < float       > ( properties, "color" ) );

    REQUIRE (  true == Any::has < double       > ( properties, "radiusd" ) );
    REQUIRE ( false == Any::has < float        > ( properties, "radiusd" ) );
    REQUIRE ( false == Any::has < int          > ( properties, "radiusd" ) );
    REQUIRE ( false == Any::has < unsigned int > ( properties, "radiusd" ) );

    REQUIRE ( false == Any::has < double       > ( properties, "radiusf" ) );
    REQUIRE (  true == Any::has < float        > ( properties, "radiusf" ) );
    REQUIRE ( false == Any::has < int          > ( properties, "radiusf" ) );
    REQUIRE ( false == Any::has < unsigned int > ( properties, "radiusf" ) );

    REQUIRE ( false == Any::has < double       > ( properties, "radiusi" ) );
    REQUIRE ( false == Any::has < float        > ( properties, "radiusi" ) );
    REQUIRE (  true == Any::has < int          > ( properties, "radiusi" ) );
    REQUIRE ( false == Any::has < unsigned int > ( properties, "radiusi" ) );

    REQUIRE ( false == Any::has < double       > ( properties, "radiusu" ) );
    REQUIRE ( false == Any::has < float        > ( properties, "radiusu" ) );
    REQUIRE ( false == Any::has < int          > ( properties, "radiusu" ) );
    REQUIRE (  true == Any::has < unsigned int > ( properties, "radiusu" ) );

    REQUIRE (  true == Any::has < Math::Matrix44d > ( properties, "matrix" ) );
    REQUIRE ( false == Any::has < Math::Matrix44f > ( properties, "matrix" ) );
    REQUIRE ( false == Any::has < double          > ( properties, "matrix" ) );

    REQUIRE ( false == Any::has < Math::Vec3d     > ( properties, "corner" ) );
    REQUIRE ( false == Any::has < Math::Vec4d     > ( properties, "corner" ) );
    REQUIRE ( false == Any::has < Math::Vec3f     > ( properties, "corner" ) );
    REQUIRE ( false == Any::has < Math::Vec4f     > ( properties, "corner" ) );
    REQUIRE ( false == Any::has < Math::Matrix44d > ( properties, "corner" ) );
    REQUIRE ( false == Any::has < Math::Matrix44f > ( properties, "corner" ) );
    REQUIRE ( false == Any::has < double          > ( properties, "corner" ) );
    REQUIRE ( false == Any::has < float           > ( properties, "corner" ) );
    REQUIRE ( false == Any::has < int             > ( properties, "corner" ) );
  }

  SECTION ( "Should return default" )
  {
    REQUIRE ( Math::equal ( v3f2, Any::get ( properties, "center", v3f2 ) ) );
    REQUIRE ( Math::equal ( v4f2, Any::get ( properties, "center", v4f2 ) ) );
    REQUIRE ( Math::equal ( v4d2, Any::get ( properties, "center", v4d2 ) ) );
    REQUIRE ( Math::equal (  md2, Any::get ( properties, "center",  md2 ) ) );
    REQUIRE ( Math::equal (  md2, Any::get ( Map(),      "center",  md2 ) ) );

    REQUIRE ( Math::equal ( v3f2, Any::get ( properties, "color", v3f2 ) ) );
    REQUIRE ( Math::equal ( v3d2, Any::get ( properties, "color", v3d2 ) ) );
    REQUIRE ( Math::equal ( v4d2, Any::get ( properties, "color", v4d2 ) ) );
    REQUIRE ( Math::equal (  md2, Any::get ( properties, "color",  md2 ) ) );
    REQUIRE ( Math::equal (  md2, Any::get ( Map(),      "color",  md2 ) ) );

    REQUIRE ( 1.0f == Any::get ( properties, "radiusd", 1.0f ) );
    REQUIRE ( 1L   == Any::get ( properties, "radiusd", 1L   ) );

    REQUIRE ( Math::equal (  mf2, Any::get ( properties, "matrix",  mf2 ) ) );
    REQUIRE ( Math::equal ( v3f2, Any::get ( properties, "matrix", v3f2 ) ) );
    REQUIRE ( Math::equal ( v3f2, Any::get ( Map(),      "matrix", v3f2 ) ) );
  }

  SECTION ( "Should not return default" )
  {
    REQUIRE ( Math::equal ( v3d1, Any::get ( properties, "center", v3d2 ) ) );
    REQUIRE ( Math::equal ( v4f1, Any::get ( properties, "color",  v4f2 ) ) );
    REQUIRE ( Math::equal (  md1, Any::get ( properties, "matrix",  md2 ) ) );
    REQUIRE ( 1.0 == Any::get ( properties, "radiusd",  2.0 ) );
  }

  SECTION ( "Should throw" )
  {
    try
    {
      Any::require < Math::Vec3f > ( Map(), "center" );
      REQUIRE ( false ); // Should not get to this line.
    }
    catch ( const std::exception &e )
    {
      // We should be here because of the exception.
      REQUIRE ( std::string ( e.what() ) == std::string ( "Property 'center' not found in container" ) );
    }

    try
    {
      Any::require < Math::Vec3f > ( properties, "center" );
      REQUIRE ( false ); // Should not get to this line.
    }
    catch ( const std::exception &e )
    {
      // We should be here because of the exception.
      REQUIRE ( std::string ( e.what() ) == std::string ( "Property 'center' is the wrong type" ) );
    }
  }

  SECTION ( "Should not throw" )
  {
    try
    {
      REQUIRE ( Math::equal ( v3d1, Any::require < Math::Vec3d > ( properties, "center" ) ) );
      REQUIRE ( true ); // We should be here.
    }
    catch ( ... )
    {
      REQUIRE ( false ); // Should not get to this line.
    }
  }
}
