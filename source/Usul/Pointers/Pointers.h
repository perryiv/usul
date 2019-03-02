
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Some handy smart-pointer definitions and macros.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_POINTERS_DEFINITIONS_H_
#define _USUL_POINTERS_DEFINITIONS_H_

#include "Usul/Strings/Format.h"
#include "Usul/Pointers/QueryPointer.h"

#include <stdexcept>
#include <typeinfo>


namespace Usul {
namespace Pointers {
namespace Configs {


///////////////////////////////////////////////////////////////////////////////
//
//  Class that does nothing.
//
///////////////////////////////////////////////////////////////////////////////

struct DoNothing
{
  template < class T > static void check ( const T * )
  {
  }
};


///////////////////////////////////////////////////////////////////////////////
//
//  Class that throws if given a null pointer.
//
///////////////////////////////////////////////////////////////////////////////

struct NullThrows
{
  template < class T > static void check ( const T *t )
  {
    if ( nullptr == t )
    {
      const std::type_info &info ( typeid ( T ) );
      const std::string name ( ( nullptr == info.name() ) ?
        "Could not determine type name" : info.name() );
      throw std::runtime_error ( Usul::Strings::format
        ( "Error accessing null pointer of type '", name, "'" ) );
    }
  }
};


///////////////////////////////////////////////////////////////////////////////
//
//  Policy class with reference counting.
//
///////////////////////////////////////////////////////////////////////////////

struct RefCountingPolicy
{
  template < class T > static void ref ( T *ptr )
  {
    if ( ptr )
    {
      ptr->ref();
    }
  }
  template < class T > static void unref ( T *ptr, bool allowDelete = true )
  {
    if ( ptr )
    {
      ptr->unref ( allowDelete );
    }
  }
};


///////////////////////////////////////////////////////////////////////////////
//
//  Policy class that always unreferences without deleting.
//
///////////////////////////////////////////////////////////////////////////////

struct NoDeleteRefCountingPolicy : public RefCountingPolicy
{
  typedef RefCountingPolicy BaseClass;

  // Need second argument to compile.
  template < class T > static void unref ( T *ptr, bool allowDelete = false )
  {
    // Always set this to false. This way we use the variable and keep the
    // compiler happy when compiling with strict warnings.
    allowDelete = false;

    // Pass false rather than given value.
    BaseClass::unref ( ptr, allowDelete );
  }
};


///////////////////////////////////////////////////////////////////////////////
//
//  Smart-pointer configuration:
//  - Reference counting.
//  - Null is ok.
//
///////////////////////////////////////////////////////////////////////////////

struct RefCountingNullOk
{
  typedef Usul::Pointers::Configs::RefCountingPolicy ReferencePolicy;
  typedef Usul::Pointers::Configs::DoNothing AccessPolicy;
  typedef Usul::Pointers::Configs::DoNothing AssignmentPolicy;
  typedef Usul::Pointers::Configs::DoNothing ConstructorPolicy;
  typedef Usul::Pointers::Configs::DoNothing DestructorPolicy;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Smart-pointer configuration:
//  - Reference counting.
//  - Null is ok.
//  - No deleting when unreferencing.
//
///////////////////////////////////////////////////////////////////////////////

struct NoDeleteRefCountingNullOk : public RefCountingNullOk
{
  typedef Usul::Pointers::Configs::NoDeleteRefCountingPolicy ReferencePolicy;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Smart-pointer configuration:
//  - Reference counting.
//  - Null throws an exception.
//
///////////////////////////////////////////////////////////////////////////////

struct RefCountingNullThrows
{
  typedef Usul::Pointers::Configs::RefCountingPolicy ReferencePolicy;
  typedef Usul::Pointers::Configs::NullThrows AccessPolicy;
  typedef Usul::Pointers::Configs::NullThrows AssignmentPolicy;
  typedef Usul::Pointers::Configs::NullThrows ConstructorPolicy;
  typedef Usul::Pointers::Configs::DoNothing DestructorPolicy;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Smart-pointer configuration:
//  - Reference counting.
//  - Null access throws an exception.
//
///////////////////////////////////////////////////////////////////////////////

struct RefCountingNullAccessThrows
{
  typedef Usul::Pointers::Configs::RefCountingPolicy ReferencePolicy;
  typedef Usul::Pointers::Configs::NullThrows AccessPolicy;
  typedef Usul::Pointers::Configs::DoNothing AssignmentPolicy;
  typedef Usul::Pointers::Configs::DoNothing ConstructorPolicy;
  typedef Usul::Pointers::Configs::DoNothing DestructorPolicy;
};


} // namespace Configs
} // namespace Pointers
} // namespace Usul


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for declaring ref-counting smart-pointer members.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_DEFINE_REF_POINTERS(class_name) \
  [[maybe_unused]] typedef Usul::Pointers::SmartPointer < class_name, Usul::Pointers::Configs::RefCountingNullOk > RefPtr; \
  [[maybe_unused]] typedef Usul::Pointers::SmartPointer < class_name, Usul::Pointers::Configs::RefCountingNullThrows > ValidRefPtr; \
  [[maybe_unused]] typedef Usul::Pointers::SmartPointer < class_name, Usul::Pointers::Configs::RefCountingNullAccessThrows > ValidAccessRefPtr; \
  [[maybe_unused]] typedef Usul::Pointers::SmartPointer < class_name, Usul::Pointers::Configs::NoDeleteRefCountingNullOk > NoDeleteRefPtr

#define USUL_DEFINE_QUERY_POINTERS(class_name) \
  USUL_DEFINE_REF_POINTERS ( class_name ); \
  [[maybe_unused]] typedef Usul::Pointers::QueryPointer < class_name, Usul::Pointers::Configs::RefCountingNullOk > QueryPtr; \
  [[maybe_unused]] typedef Usul::Pointers::QueryPointer < class_name, Usul::Pointers::Configs::RefCountingNullThrows > ValidQueryPtr; \
  [[maybe_unused]] typedef Usul::Pointers::QueryPointer < class_name, Usul::Pointers::Configs::RefCountingNullAccessThrows > ValidAccessQueryPtr; \
  [[maybe_unused]] typedef Usul::Pointers::QueryPointer < class_name, Usul::Pointers::Configs::NoDeleteRefCountingNullOk > NoDeleteQueryPtr


#endif // _USUL_POINTERS_DEFINITIONS_H_
