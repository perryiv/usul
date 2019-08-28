
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the functions for bits.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Bits/Bits.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the reference-counted base class.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Functions for bits" )
{
  SECTION ( "Can see if a number has bits" )
  {
    REQUIRE (  true == Usul::Bits::has ( 0x00000003u, 0x00000001u ) );
    REQUIRE ( false == Usul::Bits::has ( 0x00000002u, 0x00000001u ) );
  }

  SECTION ( "Can add bits to a number" )
  {
    unsigned int num = 0x00000001u;
    num = Usul::Bits::add ( num, 0x00000002u );
    REQUIRE ( 0x00000003u == num );
    REQUIRE (  true == Usul::Bits::has ( num, 0x00000001u ) );
    REQUIRE (  true == Usul::Bits::has ( num, 0x00000002u ) );
    REQUIRE (  true == Usul::Bits::has ( num, 0x00000003u ) );
    REQUIRE ( false == Usul::Bits::has ( num, 0x00000004u ) );
  }

  SECTION ( "Can remove bits from a number" )
  {
    unsigned int num = 0x00001111u;
    num = Usul::Bits::remove ( num, 0x00000001u );
    REQUIRE ( 0x00001110u == num );
    REQUIRE (  true == Usul::Bits::has ( num, 0x00000010u ) );
    REQUIRE ( false == Usul::Bits::has ( num, 0x00000001u ) );
  }

  SECTION ( "Can toggle bits in a number" )
  {
    unsigned int num = 0x00001111u;
    num = Usul::Bits::toggle ( num, 0x00000001u );
    REQUIRE ( 0x00001110u == num );
    num = Usul::Bits::toggle ( num, 0x00000010u );
    REQUIRE ( 0x00001100u == num );
    num = Usul::Bits::toggle ( num, 0x00000001u );
    REQUIRE ( 0x00001101u == num );
  }

  SECTION ( "Can set bits in a number" )
  {
    unsigned int num = 0x00001111u;
    num = Usul::Bits::set ( num, 0x00000101u, false );
    REQUIRE ( 0x00001010u == num );
    num = Usul::Bits::set ( num, 0x00000101u, true );
    REQUIRE ( 0x00001111u == num );
  }
}
