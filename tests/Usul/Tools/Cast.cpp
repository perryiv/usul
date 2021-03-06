
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the cast function(s).
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Tools/Cast.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the cast function.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Unsafe casting" )
{
  struct A
  {
    A() : a ( 10 ){}
    int a;
  };

  SECTION ( "Can unsafely cast between types" )
  {
    A *a1 = new A();
    void *temp = USUL_UNSAFE_CAST ( A*, a1 );
    A *a2  = USUL_UNSAFE_CAST ( A*, temp );
    REQUIRE ( a1 == a2 );
  }

  SECTION ( "Can reinterpret cast between types" )
  {
    A *a1 = new A();
    void *temp = reinterpret_cast < void * > ( a1 );
    A *a2  = reinterpret_cast < A * > ( temp );
    REQUIRE ( a1 == a2 );
  }
}
