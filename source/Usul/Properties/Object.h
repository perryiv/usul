
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for all property objects.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_PROPERTIES_BASE_OBJECT_H_
#define _USUL_PROPERTIES_BASE_OBJECT_H_

#include "Usul/Base/Referenced.h"
#include "Usul/Pointers/Pointers.h"
#include "Usul/Tools/NoCopying.h"

#include <typeinfo>


namespace Usul {
namespace Properties {


class USUL_EXPORT Object : public Usul::Base::Referenced,
  public Usul::Tools::NoCopying
{
public:

  // Useful typedefs.
  typedef Usul::Base::Referenced BaseClass;

  // Smart-pointer definitions.
  USUL_REFERENCED_CLASS ( Object );

  // Return the type info of the value.
  virtual const std::type_info &getTypeInfo() const = 0;

protected:

  // Constructor.
  Object();

  // Use reference counting.
  virtual ~Object();
};


} // namespace Properties
} // namespace Usul


#endif // _USUL_PROPERTIES_BASE_OBJECT_H_
