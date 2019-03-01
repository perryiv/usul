
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the reference-counting functions.
//
////////////////////////////////////////////////////////////////////////////////

#include "Helpers/Classes.h"
#include "Helpers/Instances.h"

#include "Usul/Pointers/Functions.h"
#include "Usul/Base/Referenced.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the reference-counted base class.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Save referenced-counting functions" )
{
  SECTION ( "Can safely reference and dereference instances" )
  {
    Helpers::ClassA *a1 = new Helpers::ClassA;
    Helpers::ClassA *ab = new Helpers::ClassB;
    Helpers::ClassB *b1 = new Helpers::ClassB;
    Helpers::ClassB *b2 = nullptr;

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    Usul::Pointers::reference ( a1 );
    Usul::Pointers::reference ( ab );
    Usul::Pointers::reference ( b1 );
    Usul::Pointers::reference ( b2 );

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    Usul::Pointers::unreference ( a1 );
    Usul::Pointers::unreference ( ab );
    Usul::Pointers::unreference ( b1 );
    Usul::Pointers::unreference ( b2 );

    REQUIRE ( 0 == Helpers::Instances::get().size() );

    a1 = nullptr;
    ab = nullptr;
    b1 = nullptr;

    Usul::Pointers::unreference ( a1 );
    Usul::Pointers::unreference ( ab );
    Usul::Pointers::unreference ( b1 );

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }
}
