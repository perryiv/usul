
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
  REQUIRE ( Usul::Version::MAJOR == 4 );
  REQUIRE ( Usul::Version::MINOR == 1 );
  REQUIRE ( Usul::Version::PATCH == 0 );
  REQUIRE ( std::string ( Usul::Version::STRING ) == std::string ( "4.1.0" ) );
}
