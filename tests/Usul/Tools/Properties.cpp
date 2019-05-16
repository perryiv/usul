
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
#include "Usul/Math/Vector2.h"
#include "Usul/Math/Vector3.h"
#include "Usul/Math/Vector4.h"
#include "Usul/Tools/Properties.h"

#include "catch2/catch.hpp"

namespace Math = Usul::Math;
namespace Properties = Usul::Tools::Properties;


////////////////////////////////////////////////////////////////////////////////
//
//  Test the property function(s).
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Properties" )
{
  typedef Properties::MapType Map;

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

  const Map properties = {
    { "center", v3d1 },
    { "color", v4f1 },
    { "radius", 1.0 },
    { "matrix", md1 }
  };

  SECTION ( "Can see if there are properties" )
  {
    REQUIRE (  true == Properties::has ( properties, "center" ) );
    REQUIRE (  true == Properties::has ( properties, "color" ) );
    REQUIRE (  true == Properties::has ( properties, "radius" ) );
    REQUIRE (  true == Properties::has ( properties, "matrix" ) );

    REQUIRE ( false == Properties::has ( properties, "corner" ) );
  }

  SECTION ( "Can see if there are properties of a specific type" )
  {
    REQUIRE (  true == Properties::has < Math::Vec3d > ( properties, "center" ) );
    REQUIRE ( false == Properties::has < Math::Vec3f > ( properties, "center" ) );
    REQUIRE ( false == Properties::has < double      > ( properties, "center" ) );

    REQUIRE (  true == Properties::has < Math::Vec4f > ( properties, "color" ) );
    REQUIRE ( false == Properties::has < Math::Vec4d > ( properties, "color" ) );
    REQUIRE ( false == Properties::has < float       > ( properties, "color" ) );

    REQUIRE (  true == Properties::has < double > ( properties, "radius" ) );
    REQUIRE ( false == Properties::has < float  > ( properties, "radius" ) );
    REQUIRE ( false == Properties::has < int    > ( properties, "radius" ) );

    REQUIRE (  true == Properties::has < Math::Matrix44d > ( properties, "matrix" ) );
    REQUIRE ( false == Properties::has < Math::Matrix44f > ( properties, "matrix" ) );
    REQUIRE ( false == Properties::has < double          > ( properties, "matrix" ) );

    REQUIRE ( false == Properties::has < Math::Vec3d     > ( properties, "corner" ) );
    REQUIRE ( false == Properties::has < Math::Vec4d     > ( properties, "corner" ) );
    REQUIRE ( false == Properties::has < Math::Vec3f     > ( properties, "corner" ) );
    REQUIRE ( false == Properties::has < Math::Vec4f     > ( properties, "corner" ) );
    REQUIRE ( false == Properties::has < Math::Matrix44d > ( properties, "corner" ) );
    REQUIRE ( false == Properties::has < Math::Matrix44f > ( properties, "corner" ) );
    REQUIRE ( false == Properties::has < double          > ( properties, "corner" ) );
    REQUIRE ( false == Properties::has < float           > ( properties, "corner" ) );
    REQUIRE ( false == Properties::has < int             > ( properties, "corner" ) );
  }

  SECTION ( "Should return default" )
  {
    REQUIRE ( Math::equal ( v3f2, Properties::get ( properties, "center", v3f2 ) ) );
    REQUIRE ( Math::equal ( v4f2, Properties::get ( properties, "center", v4f2 ) ) );
    REQUIRE ( Math::equal ( v4d2, Properties::get ( properties, "center", v4d2 ) ) );
    REQUIRE ( Math::equal (  md2, Properties::get ( properties, "center",  md2 ) ) );
    REQUIRE ( Math::equal (  md2, Properties::get ( Map(),      "center",  md2 ) ) );

    REQUIRE ( Math::equal ( v3f2, Properties::get ( properties, "color", v3f2 ) ) );
    REQUIRE ( Math::equal ( v3d2, Properties::get ( properties, "color", v3d2 ) ) );
    REQUIRE ( Math::equal ( v4d2, Properties::get ( properties, "color", v4d2 ) ) );
    REQUIRE ( Math::equal (  md2, Properties::get ( properties, "color",  md2 ) ) );
    REQUIRE ( Math::equal (  md2, Properties::get ( Map(),      "color",  md2 ) ) );

    REQUIRE ( 1.0f == Properties::get ( properties, "radius", 1.0f ) );
    REQUIRE ( 1L   == Properties::get ( properties, "radius", 1L   ) );

    REQUIRE ( Math::equal (  mf2, Properties::get ( properties, "matrix",  mf2 ) ) );
    REQUIRE ( Math::equal ( v3f2, Properties::get ( properties, "matrix", v3f2 ) ) );
    REQUIRE ( Math::equal ( v3f2, Properties::get ( Map(),      "matrix", v3f2 ) ) );
  }

  SECTION ( "Should not return default" )
  {
    REQUIRE ( Math::equal ( v3d1, Properties::get ( properties, "center", v3d2 ) ) );
    REQUIRE ( Math::equal ( v4f1, Properties::get ( properties, "color",  v4f2 ) ) );
    REQUIRE ( Math::equal (  md1, Properties::get ( properties, "matrix",  md2 ) ) );
    REQUIRE ( 1.0 == Properties::get ( properties, "radius",  2.0 ) );
  }

  SECTION ( "Should throw" )
  {
    try
    {
      Properties::require < Math::Vec3f > ( Map(), "center" );
      REQUIRE ( false ); // Should not get to this line.
    }
    catch ( const std::exception &e )
    {
      // We should be here because of the exception.
      REQUIRE ( std::string ( e.what() ) == std::string ( "Property 'center' not found in container" ) );
    }

    try
    {
      Properties::require < Math::Vec3f > ( properties, "center" );
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
      REQUIRE ( Math::equal ( v3d1, Properties::require < Math::Vec3d > ( properties, "center" ) ) );
      REQUIRE ( true ); // We should be here.
    }
    catch ( ... )
    {
      REQUIRE ( false ); // Should not get to this line.
    }
  }
}
