
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the smart-pointers.
//
////////////////////////////////////////////////////////////////////////////////

#include "Helpers/Classes.h"
#include "Helpers/Instances.h"

#include "Usul/Pointers/Pointers.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Classes used below.
//
////////////////////////////////////////////////////////////////////////////////

struct RefCountedClass1 : public Helpers::ClassA
{
  typedef Helpers::ClassA BaseClass;
  USUL_DEFINE_REF_POINTERS ( RefCountedClass1 );
  RefCountedClass1() : BaseClass() {}
protected:
  ~RefCountedClass1() {}
};

struct RefCountedClass2 : public RefCountedClass1
{
  typedef RefCountedClass1 BaseClass;
  USUL_DEFINE_REF_POINTERS ( RefCountedClass2 );
  RefCountedClass2() : BaseClass() {}
protected:
  ~RefCountedClass2() {}
};


////////////////////////////////////////////////////////////////////////////////
//
//  Test the smart-pointers.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "All smart pointers" )
{
  SECTION ( "Can use the reference pointers" )
  {
    {
      RefCountedClass2::RefPtr a1 = new RefCountedClass2();
      RefCountedClass2::RefPtr a2 ( new RefCountedClass2() );
      RefCountedClass1::RefPtr a3 = new RefCountedClass2();
      RefCountedClass1::RefPtr a4 ( new RefCountedClass2() );
      RefCountedClass1::RefPtr a5 ( nullptr );

      REQUIRE ( 4 == Helpers::Instances::get().size() );

      REQUIRE ( 1 == a1->getReferenceCount() );
      REQUIRE ( 1 == a2->getReferenceCount() );
      REQUIRE ( 1 == a3->getReferenceCount() );
      REQUIRE ( 1 == a4->getReferenceCount() );
    }

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }

  SECTION ( "Can use the valid reference pointers" )
  {
    {
      RefCountedClass2::ValidRefPtr a1 = new RefCountedClass2();
      RefCountedClass2::ValidRefPtr a2 ( new RefCountedClass2() );
      RefCountedClass1::ValidRefPtr a3 = new RefCountedClass2();
      RefCountedClass1::ValidRefPtr a4 ( new RefCountedClass2() );

      REQUIRE ( 4 == Helpers::Instances::get().size() );

      REQUIRE ( 1 == a1->getReferenceCount() );
      REQUIRE ( 1 == a2->getReferenceCount() );
      REQUIRE ( 1 == a3->getReferenceCount() );
      REQUIRE ( 1 == a4->getReferenceCount() );
    }

    {
      try
      {
        // This should throw a standard exception.
        RefCountedClass2::ValidRefPtr a5 ( nullptr );

        // Need to use the variable. Should not get to here.
        REQUIRE ( a5.valid() );
        REQUIRE ( false );
      }
      catch ( const std::exception &e )
      {
        const std::string expected ( "Error accessing null pointer" );
        const std::string actual ( e.what(), e.what() + 28 );
        REQUIRE ( actual == expected );
      }
      catch ( ... )
      {
        // Should not get to here.
        REQUIRE ( false );
      }
    }

    {
      try
      {
        // This should not throw an exception.
        RefCountedClass2::ValidAccessRefPtr a5 ( nullptr );

        // Should be true.
        REQUIRE ( false == a5.valid() );

        // This should throw a standard exception.
        a5->getReferenceCount();

        // Should not get to here.
        REQUIRE ( false );
      }
      catch ( const std::exception &e )
      {
        const std::string expected ( "Error accessing null pointer" );
        const std::string actual ( e.what(), e.what() + 28 );
        REQUIRE ( actual == expected );
      }
      catch ( ... )
      {
        // Should not get to here.
        REQUIRE ( false );
      }
    }

    {
      RefCountedClass2 *pa1 = nullptr;
      RefCountedClass2 *pa2 = nullptr;

      {
        RefCountedClass2::NoDeleteRefPtr a1 = new RefCountedClass2();
        RefCountedClass2::NoDeleteRefPtr a2 ( new RefCountedClass2() );

        REQUIRE ( 2 == Helpers::Instances::get().size() );
        REQUIRE ( 1 == a1->getReferenceCount() );
        REQUIRE ( 1 == a2->getReferenceCount() );

        pa1 = a1.get();
        pa2 = a2.get();
      }

      REQUIRE ( 2 == Helpers::Instances::get().size() );
      REQUIRE ( 0 == pa1->getReferenceCount() );
      REQUIRE ( 0 == pa2->getReferenceCount() );

      {
        RefCountedClass2::RefPtr a1 = pa1;
        RefCountedClass2::RefPtr a2 ( pa2 );

        REQUIRE ( 2 == Helpers::Instances::get().size() );
        REQUIRE ( 1 == a1->getReferenceCount() );
        REQUIRE ( 1 == a2->getReferenceCount() );
      }

      REQUIRE ( 0 == Helpers::Instances::get().size() );
    }
  }
}
