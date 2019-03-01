
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class with virtual type-id member.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_TYPED_BASE_CLASS_H_
#define _USUL_TYPED_BASE_CLASS_H_

#include "Usul/Config.h"
#include "Usul/Export.h"

#include <typeinfo>


namespace Usul {
namespace Base {


struct USUL_EXPORT Typed
{
  virtual const std::type_info &typeId() const;

protected:

  virtual ~Typed();
};


} // namespace Base
} // namespace Usul


#endif // _USUL_TYPED_BASE_CLASS_H_
