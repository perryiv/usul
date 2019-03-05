
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
  SECTION ( "Can throw an exception and it gets caught" )
  {
    try
    {
      // test when the function throws.
      USUL_TOOLS_NO_THROW ( throwStandardException );
      USUL_TOOLS_NO_THROW ( throwCustomException );
      USUL_TOOLS_NO_THROW ( throwNumber );
      USUL_TOOLS_NO_THROW ( []()
      {
        throw std::string ( "This is a string" );
      } );

      // Have to do this to test other streams, as well as no stream.
      std::ostringstream out;
      Usul::Tools::noThrow ( throwNumber, __FILE__, __LINE__, &out );
      Usul::Tools::noThrow ( throwNumber, __FILE__, __LINE__, &std::cout );
      Usul::Tools::noThrow ( throwNumber, __FILE__, __LINE__, &std::cerr );
      Usul::Tools::noThrow ( throwNumber, __FILE__, __LINE__, &std::clog );
      Usul::Tools::noThrow ( throwNumber, __FILE__, __LINE__ );

      // Test when the function does not throw.
      USUL_TOOLS_NO_THROW ( []()
      {
        std::cout << "This function does not throw" << std::endl;
      } );

      // If we get here then it worked.
      REQUIRE ( true );
    }
    catch ( ... )
    {
      // Should not be here.
      REQUIRE ( false );
    }
  }
}
