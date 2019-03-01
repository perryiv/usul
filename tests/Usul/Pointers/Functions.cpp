
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

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the reference-counted base class.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Safe referenced-counting functions" )
{
  SECTION ( "Can safely reference and dereference instances" )
  {
    Helpers::ClassA *a1 = new Helpers::ClassA;
    Helpers::ClassA *ab = new Helpers::ClassB;
    Helpers::ClassB *b1 = new Helpers::ClassB;
    Helpers::ClassB *b2 = nullptr;

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 0 == a1->getReferenceCount() );
    REQUIRE ( 0 == ab->getReferenceCount() );
    REQUIRE ( 0 == b1->getReferenceCount() );

    Usul::Pointers::reference ( a1 );
    Usul::Pointers::reference ( ab );
    Usul::Pointers::reference ( b1 );
    Usul::Pointers::reference ( b2 );

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == a1->getReferenceCount() );
    REQUIRE ( 1 == ab->getReferenceCount() );
    REQUIRE ( 1 == b1->getReferenceCount() );

    Usul::Pointers::reference ( a1 );
    Usul::Pointers::reference ( ab );
    Usul::Pointers::reference ( b1 );
    Usul::Pointers::reference ( b2 );

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 2 == a1->getReferenceCount() );
    REQUIRE ( 2 == ab->getReferenceCount() );
    REQUIRE ( 2 == b1->getReferenceCount() );

    Usul::Pointers::unreference ( a1 );
    Usul::Pointers::unreference ( ab );
    Usul::Pointers::unreference ( b1 );
    Usul::Pointers::unreference ( b2 );

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == a1->getReferenceCount() );
    REQUIRE ( 1 == ab->getReferenceCount() );
    REQUIRE ( 1 == b1->getReferenceCount() );

    Usul::Pointers::unreference ( a1 );
    Usul::Pointers::unreference ( ab );
    Usul::Pointers::unreference ( b1 );
    Usul::Pointers::unreference ( b2 );

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }

  SECTION ( "Can safely reference and dereference null" )
  {
    Helpers::ClassA *a1 = nullptr;
    Helpers::ClassB *b1 = nullptr;

    Usul::Pointers::unreference ( a1 );
    Usul::Pointers::unreference ( b1 );

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }

  SECTION ( "Can reference and dereference nested classes" )
  {
    Helpers::ClassC *c1 = new Helpers::ClassC;
    Helpers::ClassC *c2 = new Helpers::ClassC;

    // Each class contains one reference-counted class.
    REQUIRE ( 4 == Helpers::Instances::get().size() );

    REQUIRE ( 0 == c1->getReferenceCount() );
    REQUIRE ( 0 == c2->getReferenceCount() );

    Usul::Pointers::reference ( c1 );
    Usul::Pointers::reference ( c2 );

    REQUIRE ( 4 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == c1->getReferenceCount() );
    REQUIRE ( 1 == c2->getReferenceCount() );

    Usul::Pointers::reference ( c1 );
    Usul::Pointers::reference ( c2 );

    REQUIRE ( 4 == Helpers::Instances::get().size() );

    REQUIRE ( 2 == c1->getReferenceCount() );
    REQUIRE ( 2 == c2->getReferenceCount() );

    Usul::Pointers::unreference ( c1 );
    Usul::Pointers::unreference ( c2 );

    REQUIRE ( 4 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == c1->getReferenceCount() );
    REQUIRE ( 1 == c2->getReferenceCount() );

    Usul::Pointers::unreference ( c1 );
    Usul::Pointers::unreference ( c2 );

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }
}
