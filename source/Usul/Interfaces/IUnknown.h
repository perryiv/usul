
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all other interfaces.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_INTERFACES_UNKNOWN_H_
#define _USUL_INTERFACES_UNKNOWN_H_

#include "Usul/Pointers/Pointers.h"

#ifdef _WIN32
# pragma warning ( disable : 4275 ) // Disable warning about dll interfaces.
#endif

namespace Usul {
namespace Interfaces {


struct IUnknown
{
  // Smart-pointer definitions.
  USUL_DEFINE_QUERY_POINTERS ( IUnknown );

  // Id for this interface.
  enum { IID = 1551585483 };

  // See if the interface is supported.
  virtual IUnknown *      queryInterface ( unsigned long iid ) = 0;

  // Reference and unreference the interface.
  virtual void            ref() = 0;
  virtual void            unref ( bool allowDeletion = true ) = 0;

protected:

  // Make gcc happy.
  virtual ~IUnknown(){}
};


} // namespace Interfaces
} // namespace Usul


///////////////////////////////////////////////////////////////////////////////
//
//  Macro to declare IUnknown member functions.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_DECLARE_IUNKNOWN_MEMBERS \
  virtual Usul::Interfaces::IUnknown *  queryInterface ( unsigned long iid ); \
  virtual void                          ref(); \
  virtual void                          unref ( bool allowDeletion = true )


///////////////////////////////////////////////////////////////////////////////
//
//  Macro to implement IUnknown member functions (except queryInterface).
//  Typically the base class will be Usul::Base::Referenced.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_IMPLEMENT_IUNKNOWN_MEMBERS(class_name,base_class) \
  void class_name::ref()                        { base_class::ref(); } \
  void class_name::unref ( bool allowDeletion ) { base_class::unref ( allowDeletion ); }


#endif // _USUL_INTERFACES_UNKNOWN_H_
