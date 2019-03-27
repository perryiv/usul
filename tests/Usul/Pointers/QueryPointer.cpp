
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the query-pointers.
//
////////////////////////////////////////////////////////////////////////////////

#include "Helpers/Classes.h"
#include "Helpers/Instances.h"
#include "Helpers/ITest1.h"
#include "Helpers/ITest2.h"

#include "Usul/Pointers/Pointers.h"

#include "catch2/catch.hpp"


////////////////////////////////////////////////////////////////////////////////
//
//  Classes used below.
//
////////////////////////////////////////////////////////////////////////////////

struct Component1 : public Helpers::ClassA,
  public Helpers::ITest1
{
  typedef Helpers::ClassA BaseClass;
  USUL_REFERENCED_CLASS ( Component1 );
  USUL_DECLARE_IUNKNOWN_MEMBERS;
  Component1() : BaseClass() {}
  virtual bool doTest1() { return true; }
protected:
  ~Component1() {}
};
USUL_IMPLEMENT_IUNKNOWN_MEMBERS ( Component1, Component1::BaseClass )
Usul::Interfaces::IUnknown *Component1::queryInterface ( unsigned long iid )
{
  switch ( iid )
  {
    case Usul::Interfaces::IUnknown::IID:
    case Helpers::ITest1::IID:
      return static_cast < Helpers::ITest1 * > ( this );
    default:
      return nullptr;
  }
}

struct Component2 : public Helpers::ClassA,
  public Helpers::ITest2
{
  typedef Helpers::ClassA BaseClass;
  USUL_REFERENCED_CLASS ( Component2 );
  USUL_DECLARE_IUNKNOWN_MEMBERS;
  Component2() : BaseClass() {}
  virtual bool doTest2() { return true; }
protected:
  ~Component2() {}
};
USUL_IMPLEMENT_IUNKNOWN_MEMBERS ( Component2, Component2::BaseClass )
Usul::Interfaces::IUnknown *Component2::queryInterface ( unsigned long iid )
{
  switch ( iid )
  {
    case Usul::Interfaces::IUnknown::IID:
    case Helpers::ITest2::IID:
      return static_cast < Helpers::ITest2 * > ( this );
    default:
      return nullptr;
  }
}

struct Component3 : public Helpers::ClassA,
  public Helpers::ITest1,
  public Helpers::ITest2
{
  typedef Helpers::ClassA BaseClass;
  USUL_REFERENCED_CLASS ( Component3 );
  USUL_DECLARE_IUNKNOWN_MEMBERS;
  Component3() : BaseClass() {}
  virtual bool doTest1() { return true; }
  virtual bool doTest2() { return true; }
protected:
  ~Component3() {}
};
USUL_IMPLEMENT_IUNKNOWN_MEMBERS ( Component3, Component3::BaseClass )
Usul::Interfaces::IUnknown *Component3::queryInterface ( unsigned long iid )
{
  switch ( iid )
  {
    case Usul::Interfaces::IUnknown::IID:
    case Helpers::ITest1::IID:
      return static_cast < Helpers::ITest1 * > ( this );
    case Helpers::ITest2::IID:
      return static_cast < Helpers::ITest2 * > ( this );
    default:
      return nullptr;
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the query-pointers.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "All query pointers" )
{
  SECTION ( "Can use the query pointers" )
  {
    {
      Component1::RefPtr a1 = new Component1();
      Component2::RefPtr a2 ( new Component2() );
      Component3::RefPtr a3 = new Component3();
      Component3::RefPtr a4 = nullptr;

      REQUIRE ( 3 == Helpers::Instances::get().size() );

      REQUIRE ( 1 == a1->getReferenceCount() );
      REQUIRE ( 1 == a2->getReferenceCount() );
      REQUIRE ( 1 == a3->getReferenceCount() );

      Helpers::ITest1::QueryPtr q1 = a1;
      Helpers::ITest1::QueryPtr q2 = a2;
      Helpers::ITest1::QueryPtr q3 = a3;
      Helpers::ITest1::QueryPtr q4 = a4;

      REQUIRE (  true == q1.valid() );
      REQUIRE ( false == q2.valid() ); // Is not a Test1.
      REQUIRE (  true == q3.valid() );
      REQUIRE ( false == q4.valid() );

      REQUIRE ( 2 == a1->getReferenceCount() );
      REQUIRE ( 1 == a2->getReferenceCount() );
      REQUIRE ( 2 == a3->getReferenceCount() );

      REQUIRE ( true == q1->doTest1() );
      REQUIRE ( true == q3->doTest1() );

      Helpers::ITest2::QueryPtr r1 = a1;
      Helpers::ITest2::QueryPtr r2 = a2;
      Helpers::ITest2::QueryPtr r3 = a3;
      Helpers::ITest2::QueryPtr r4 = a4;

      REQUIRE ( false == r1.valid() ); // Is not a Test2.
      REQUIRE (  true == r2.valid() );
      REQUIRE (  true == r3.valid() );
      REQUIRE ( false == r4.valid() );

      REQUIRE ( 2 == a1->getReferenceCount() );
      REQUIRE ( 2 == a2->getReferenceCount() );
      REQUIRE ( 3 == a3->getReferenceCount() );

      REQUIRE ( true == r2->doTest2() );
      REQUIRE ( true == r3->doTest2() );

      REQUIRE ( 3 == Helpers::Instances::get().size() );
    }

    REQUIRE ( 0 == Helpers::Instances::get().size() );
  }

  SECTION ( "Can use the valid query pointers" )
  {
    {
      Component1::RefPtr a1 = new Component1();
      Component2::RefPtr a2 ( new Component2() );
      Component3::RefPtr a3 = new Component3();

      REQUIRE ( 3 == Helpers::Instances::get().size() );

      REQUIRE ( 1 == a1->getReferenceCount() );
      REQUIRE ( 1 == a2->getReferenceCount() );
      REQUIRE ( 1 == a3->getReferenceCount() );

      Helpers::ITest1::ValidQueryPtr q1 = a1;
      Helpers::ITest2::ValidQueryPtr q2 = a2;
      Helpers::ITest1::ValidQueryPtr q3 = a3;
      Helpers::ITest2::ValidQueryPtr q4 = a3;

      REQUIRE ( true == q1.valid() );
      REQUIRE ( true == q2.valid() );
      REQUIRE ( true == q3.valid() );
      REQUIRE ( true == q4.valid() );

      REQUIRE ( 2 == a1->getReferenceCount() );
      REQUIRE ( 2 == a2->getReferenceCount() );
      REQUIRE ( 3 == a3->getReferenceCount() );

      REQUIRE ( true == q1->doTest1() );
      REQUIRE ( true == q2->doTest2() );
      REQUIRE ( true == q3->doTest1() );
      REQUIRE ( true == q4->doTest2() );
    }

    {
      try
      {
        // Make the component.
        Component1::RefPtr a1 = new Component1();

        // Should be true.
        REQUIRE ( 1 == Helpers::Instances::get().size() );
        REQUIRE ( 1 == a1->getReferenceCount() );

        // Should work because it implements ITest1.
        Helpers::ITest1::ValidQueryPtr q1 = a1;
        REQUIRE ( 2 == a1->getReferenceCount() );

        // Should throw a standard exception because it does not implement ITest2.
        Helpers::ITest2::ValidQueryPtr q2 = a1;

        // Need to use the variable. Should not get to here.
        REQUIRE ( a1.valid() );
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

      REQUIRE ( 0 == Helpers::Instances::get().size() );
    }

    {
      try
      {
        // Make the component.
        Component1::RefPtr a1 = new Component1();

        // Should be true.
        REQUIRE ( 1 == Helpers::Instances::get().size() );
        REQUIRE ( 1 == a1->getReferenceCount() );

        // Should work because it implements ITest1.
        Helpers::ITest1::ValidAccessQueryPtr q1 = a1;
        REQUIRE ( 2 == a1->getReferenceCount() );

        // Should not throw an exception because of the pointer type.
        Helpers::ITest2::ValidAccessQueryPtr q2 = a1;
        REQUIRE ( false == q2.valid() );
        REQUIRE ( 2 == a1->getReferenceCount() );

        // Should throw a standard exception because the query failed.
        q2->doTest2();

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

      REQUIRE ( 0 == Helpers::Instances::get().size() );
    }

    {
      Component3 *pa1 = nullptr;
      Component3 *pa2 = nullptr;

      {
        Component3::NoDeleteRefPtr a1 = new Component3();
        Component3::NoDeleteRefPtr a2 ( new Component3() );

        REQUIRE ( 2 == Helpers::Instances::get().size() );
        REQUIRE ( 1 == a1->getReferenceCount() );
        REQUIRE ( 1 == a2->getReferenceCount() );

        pa1 = a1.get();
        pa2 = a2.get();

        Helpers::ITest1::NoDeleteQueryPtr n1 = a1;
        Helpers::ITest1::NoDeleteQueryPtr n2 ( a2 );

        REQUIRE ( 2 == Helpers::Instances::get().size() );
        REQUIRE ( 2 == a1->getReferenceCount() );
        REQUIRE ( 2 == a2->getReferenceCount() );
      }

      REQUIRE ( 2 == Helpers::Instances::get().size() );
      REQUIRE ( 0 == pa1->getReferenceCount() );
      REQUIRE ( 0 == pa2->getReferenceCount() );

      {
        Helpers::ITest1::QueryPtr q1 = pa1;
        Helpers::ITest1::QueryPtr q2 ( pa2 );

        REQUIRE ( 2 == Helpers::Instances::get().size() );
        REQUIRE ( 1 == pa1->getReferenceCount() );
        REQUIRE ( 1 == pa2->getReferenceCount() );
      }

      REQUIRE ( 0 == Helpers::Instances::get().size() );
    }
  }
}
