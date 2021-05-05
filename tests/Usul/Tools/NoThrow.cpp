
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the no-throw function(s).
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Tools/NoThrow.h"
#include "Usul/IO/Redirect/String.h"

#include "catch2/catch.hpp"

#include <stdexcept>
#include <sstream>
#include <string>


////////////////////////////////////////////////////////////////////////////////
//
//  Helper functions that throw an exception.
//
////////////////////////////////////////////////////////////////////////////////

inline void throwStandardException()
{
  throw std::runtime_error ( "This is a standard exception" );
}
inline void throwCustomException()
{
  struct MyException{};
  throw MyException();
}
inline void throwNumber()
{
  throw 123;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the cast function.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "No-throw wrapper function" )
{
  std::ostringstream expected;
  expected << "Standard exception caught, ID: 1568933700, This is a standard exception\n";
  expected << "Unknown exception caught, ID: 1568933701\n";
  expected << "Unknown exception caught, ID: 1568933702\n";
  expected << "Unknown exception caught, ID: 1568933703\n";
  expected << "Unknown exception caught, ID: 1568933705\n";
  expected << "Unknown exception caught, ID: 1568933706\n";
  expected << "Unknown exception caught, ID: 1568933707\n";
  expected << "This function does not throw\n";

  SECTION ( "Can throw an exception and it gets caught" )
  {
    // Send all standard output to a string while we are within this scope.
    Usul::IO::Redirect::String redirect;

    // test when the function throws.
    USUL_TOOLS_NO_THROW ( 1568933700, throwStandardException );
    USUL_TOOLS_NO_THROW ( 1568933701, throwCustomException );
    USUL_TOOLS_NO_THROW ( 1568933702, throwNumber );
    USUL_TOOLS_NO_THROW ( 1568933703, [] ()
    {
      throw std::string ( "This is a string" );
    } );

    // Have to do this to test other streams, as well as no stream.
    std::ostringstream out;
    Usul::Tools::noThrow ( 1568933704, throwNumber, &out );
    Usul::Tools::noThrow ( 1568933705, throwNumber, &std::cout );
    Usul::Tools::noThrow ( 1568933706, throwNumber, &std::cerr );
    Usul::Tools::noThrow ( 1568933707, throwNumber, &std::clog );
    Usul::Tools::noThrow ( 1568933708, throwNumber );

    // Test when the function does not throw.
    USUL_TOOLS_NO_THROW ( 1568933709, [] ()
    {
      std::cout << "This function does not throw" << std::endl;
    } );

    // Make sure the redirect object contains what it should.
    REQUIRE ( redirect.getContents() == expected.str() );
  }
}
