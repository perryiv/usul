
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
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
      USUL_TOOLS_NO_THROW ( throwStandardException );
      USUL_TOOLS_NO_THROW ( throwCustomException );
      USUL_TOOLS_NO_THROW ( throwNumber );
      USUL_TOOLS_NO_THROW ( []()
      {
        throw std::string ( "This is a string" );
      } );

      // If we get here it worked.
      REQUIRE ( true );
    }
    catch ( ... )
    {
      // Should not be here.
      REQUIRE ( false );
    }
  }
}
