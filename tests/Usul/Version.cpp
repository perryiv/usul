
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the version.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Version.h"

#include "catch2/catch.hpp"

#include <string>


////////////////////////////////////////////////////////////////////////////////
//
//  Test the version.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Version should be correct" )
{
  REQUIRE ( Usul::Version::MAJOR == 3 );
  REQUIRE ( Usul::Version::MINOR == 5 );
  REQUIRE ( Usul::Version::PATCH == 4 );
  REQUIRE ( std::string ( Usul::Version::STRING ) == std::string ( "3.5.4" ) );
}
