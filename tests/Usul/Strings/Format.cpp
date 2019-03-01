
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the function(s) for strings.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Strings/Format.h"

#include "catch2/catch.hpp"

#include <string>


const std::string expected = "\
Quote 1: My name is Inigo Montoya. You killed my father. Prepare to die.\n\
Quote 2: There’s something I ought to tell you. I’m not left-handed either.\n\
Quote 3: No more rhymes now, I mean it.\n\
Quote 4: Anybody want a peanut?";


////////////////////////////////////////////////////////////////////////////////
//
//  Test the cast function.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "String formatting" )
{
  SECTION ( "Can format a string" )
  {
    const std::string answer = Usul::Strings::format (
      "Quote ", 1, ": ", "My name is Inigo Montoya. You killed my father. Prepare to die.", '\n',
      "Quote ", 2, ": ", "There’s something I ought to tell you. I’m not left-handed either.", '\n',
      "Quote ", 3, ": ", "No more rhymes now, I mean it.", '\n',
      "Quote ", 4, ": ", "Anybody want a peanut?"
    );

    REQUIRE ( answer == expected );
  }
}
