
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
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_REFERENCED_BASE_CLASS_H_
#define _USUL_REFERENCED_BASE_CLASS_H_

#include "Usul/Base/Typed.h"

#ifdef USUL_USE_ATOMIC_REFERENCE_COUNTER
# ifdef _WIN32
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
  void ref()
  {
    ++_refCount;
  }

  // Dereference this instance.
  void unref ( bool allowDeletion = true )
  {
    if ( ( 0 == --_refCount ) && allowDeletion )
    {
      this->_deleteThis();
    }
  }

  // Get the reference count.
  CounterType getReferenceCount() const
  {
    return _refCount;
  }

protected:

  Referenced() : BaseClass(),
    _refCount ( 0 )
  {
  }
  Referenced ( const Referenced &r ) : BaseClass ( r ),
    _refCount ( 0 )
  {
  }
  Referenced &operator = ( const Referenced &r )
  {
    // We define this function to make sure the compiler does not.
    // A compiler-generated operator would probably assign the reference count,
    // which does not make any sense.
    return *this;
  }

  virtual ~Referenced();

  void _deleteThis();

private:

#ifdef USUL_USE_ATOMIC_REFERENCE_COUNTER
  std::atomic < CounterType > _refCount;
#else
  CounterType _refCount;
#endif
};


} // namespace Base
} // namespace Usul


#endif // _USUL_REFERENCED_BASE_CLASS_H_
