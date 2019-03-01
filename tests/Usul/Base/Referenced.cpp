
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

    a1->ref();
    ab->ref();
    b1->ref();

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    a1->unref();
    ab->unref();
    b1->unref();

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }
}
