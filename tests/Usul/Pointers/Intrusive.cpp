
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the intrusive pointer functions.
//
////////////////////////////////////////////////////////////////////////////////

#include "Helpers/Classes.h"
#include "Helpers/Instances.h"

#include "Usul/Pointers/Intrusive.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Test the intrusive pointer functions.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Intrusive pointer referenced-counting functions" )
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

    intrusive_ptr_add_ref ( a1 );
    intrusive_ptr_add_ref ( ab );
    intrusive_ptr_add_ref ( b1 );
    intrusive_ptr_add_ref ( b2 );

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == a1->getReferenceCount() );
    REQUIRE ( 1 == ab->getReferenceCount() );
    REQUIRE ( 1 == b1->getReferenceCount() );

    intrusive_ptr_add_ref ( a1 );
    intrusive_ptr_add_ref ( ab );
    intrusive_ptr_add_ref ( b1 );
    intrusive_ptr_add_ref ( b2 );

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 2 == a1->getReferenceCount() );
    REQUIRE ( 2 == ab->getReferenceCount() );
    REQUIRE ( 2 == b1->getReferenceCount() );

    intrusive_ptr_release ( a1 );
    intrusive_ptr_release ( ab );
    intrusive_ptr_release ( b1 );
    intrusive_ptr_release ( b2 );

    REQUIRE ( 3 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == a1->getReferenceCount() );
    REQUIRE ( 1 == ab->getReferenceCount() );
    REQUIRE ( 1 == b1->getReferenceCount() );

    intrusive_ptr_release ( a1 );
    intrusive_ptr_release ( ab );
    intrusive_ptr_release ( b1 );
    intrusive_ptr_release ( b2 );

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }

  SECTION ( "Can safely reference and dereference null" )
  {
    Helpers::ClassA *a1 = nullptr;
    Helpers::ClassB *b1 = nullptr;

    REQUIRE ( 0 == Helpers::Instances::get().size() );

    intrusive_ptr_release ( a1 );
    intrusive_ptr_release ( b1 );

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }

  SECTION ( "Can dereference without deleting" )
  {
    Helpers::ClassA *a1 = new Helpers::ClassA;
    Helpers::ClassB *b1 = new Helpers::ClassB;

    REQUIRE ( 2 == Helpers::Instances::get().size() );

    REQUIRE ( 0 == a1->getReferenceCount() );
    REQUIRE ( 0 == b1->getReferenceCount() );

    intrusive_ptr_add_ref ( a1 );
    intrusive_ptr_add_ref ( b1 );

    REQUIRE ( 2 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == a1->getReferenceCount() );
    REQUIRE ( 1 == b1->getReferenceCount() );

    intrusive_ptr_add_ref ( a1 );
    intrusive_ptr_add_ref ( b1 );

    REQUIRE ( 2 == Helpers::Instances::get().size() );

    REQUIRE ( 2 == a1->getReferenceCount() );
    REQUIRE ( 2 == b1->getReferenceCount() );

    ptr_release_no_delete ( a1 );
    ptr_release_no_delete ( b1 );

    REQUIRE ( 2 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == a1->getReferenceCount() );
    REQUIRE ( 1 == b1->getReferenceCount() );

    ptr_release_no_delete ( a1 );
    ptr_release_no_delete ( b1 );

    REQUIRE ( 2 == Helpers::Instances::get().size() );

    REQUIRE ( 0 == a1->getReferenceCount() );
    REQUIRE ( 0 == b1->getReferenceCount() );

    intrusive_ptr_add_ref ( a1 );
    intrusive_ptr_add_ref ( b1 );

    REQUIRE ( 2 == Helpers::Instances::get().size() );

    REQUIRE ( 1 == a1->getReferenceCount() );
    REQUIRE ( 1 == b1->getReferenceCount() );

    intrusive_ptr_release ( a1 );
    intrusive_ptr_release ( b1 );

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }
}
