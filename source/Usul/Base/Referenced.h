
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Reference-counting base class.
//
//  For discussion about disabling warning C4251 on Windows see:
//  https://stackoverflow.com/questions/16419318/one-way-of-eliminating-c4251-warning-when-using-stl-classes-in-the-dll-interface
//  https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=vs-2017
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_REFERENCED_BASE_CLASS_H_
#define _USUL_REFERENCED_BASE_CLASS_H_

#include "Usul/Config.h"
#include "Usul/Export.h"

#ifdef USUL_USE_ATOMIC_REFERENCE_COUNTER
# include <atomic>
#endif

namespace Usul { namespace Interfaces { struct IUnknown; } }


namespace Usul {
namespace Base {


class USUL_EXPORT Referenced
{
public:

  typedef unsigned int CounterType;

	// Get this referenced object as an IUnknown pointer, which may return null.
	virtual Usul::Interfaces::IUnknown *asUnknown();

  // Returns null. Provided as a convenience for inheriting classes.
  virtual Usul::Interfaces::IUnknown *queryInterface ( unsigned long );

  // Reference this instance.
  void ref();

  // Dereference this instance.
  void unref ( bool allowDeletion = true );

  // Get the reference count.
  CounterType getReferenceCount() const;

  // Return the type name, or null if it fails.
  static const char* getTypeName ( const Referenced* );

protected:

  Referenced();
  Referenced ( const Referenced &r );

  virtual ~Referenced();

  Referenced &operator = ( const Referenced & );

private:

  void _deleteMe();

#ifdef USUL_USE_ATOMIC_REFERENCE_COUNTER
  std::atomic < CounterType > _refCount;
#else
  CounterType _refCount;
#endif
};


} // namespace Base
} // namespace Usul


///////////////////////////////////////////////////////////////////////////////
//
//  Macro for declaring smart-pointers and other info.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_REFERENCED_CLASS(class_name) \
  USUL_DEFINE_REF_POINTERS ( class_name )


#endif // _USUL_REFERENCED_BASE_CLASS_H_
