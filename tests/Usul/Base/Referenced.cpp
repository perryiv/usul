
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the reference-counted base class.
//
////////////////////////////////////////////////////////////////////////////////

#include "Helpers/Classes.h"
#include "Helpers/Instances.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the reference-counted base class.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Referenced base class" )
{
  SECTION ( "Can make referenced instances and have them delete themselves" )
  {
    Helpers::ClassA *a1 = new Helpers::ClassA;
    Helpers::ClassA *ab = new Helpers::ClassB;
    Helpers::ClassB *b1 = new Helpers::ClassB;

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 0 == a1->getReferenceCount() );
    REQUIRE ( 0 == ab->getReferenceCount() );
    REQUIRE ( 0 == b1->getReferenceCount() );

    a1->ref();
    ab->ref();
    b1->ref();

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == a1->getReferenceCount() );
    REQUIRE ( 1 == ab->getReferenceCount() );
    REQUIRE ( 1 == b1->getReferenceCount() );

    a1->ref();
    ab->ref();
    b1->ref();

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 2 == a1->getReferenceCount() );
    REQUIRE ( 2 == ab->getReferenceCount() );
    REQUIRE ( 2 == b1->getReferenceCount() );

    a1->unref();
    ab->unref();
    b1->unref();

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == a1->getReferenceCount() );
    REQUIRE ( 1 == ab->getReferenceCount() );
    REQUIRE ( 1 == b1->getReferenceCount() );

    a1->unref();
    ab->unref();
    b1->unref();

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

    c1->ref();
    c2->ref();

    REQUIRE ( 4 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == c1->getReferenceCount() );
    REQUIRE ( 1 == c2->getReferenceCount() );

    c1->ref();
    c2->ref();

    REQUIRE ( 4 == Helpers::Instances::get().size() );

    REQUIRE ( 2 == c1->getReferenceCount() );
    REQUIRE ( 2 == c2->getReferenceCount() );

    c1->unref();
    c2->unref();

    REQUIRE ( 4 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == c1->getReferenceCount() );
    REQUIRE ( 1 == c2->getReferenceCount() );

    c1->unref();
    c2->unref();

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }
}
