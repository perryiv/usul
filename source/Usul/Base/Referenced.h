
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

#include "Usul/Base/Typed.h"

#ifdef USUL_USE_ATOMIC_REFERENCE_COUNTER
# ifdef _WIN32
#  pragma warning ( disable : 4251 ) // Disable warning about exporting atomic.
#  include <atomic>
# else
#  include <memory>
# endif
#endif


namespace Usul { namespace Interfaces { struct IUnknown; } }


namespace Usul {
namespace Base {


class USUL_EXPORT Referenced : public Typed
{
public:

  typedef Typed BaseClass;
  typedef unsigned int CounterType;

	// Get this referenced object as an IUnknown pointer, which may return null.
	virtual Usul::Interfaces::IUnknown *asUnknown();

  // Reference this instance.
  void ref();

  // Dereference this instance.
  void unref ( bool allowDeletion = true );

  // Get the reference count.
  CounterType getReferenceCount() const;

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


#endif // _USUL_REFERENCED_BASE_CLASS_H_
