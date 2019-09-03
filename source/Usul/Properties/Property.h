
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Template class for defining property types.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_PROPERTIES_PROPERTY_H_
#define _USUL_PROPERTIES_PROPERTY_H_

#include "Usul/Properties/Object.h"
#include "Usul/Tools/NoThrow.h"

#include <type_traits>


namespace Usul {
namespace Properties {


template < class T >
class Property : public Usul::Properties::Object
{
public:

  // Useful typedefs.
  typedef Usul::Properties::Object BaseClass;
  typedef T ValueType;
  typedef Property < ValueType > ThisType;

  // Smart-pointer definitions.
  USUL_DEFINE_REF_POINTERS ( Property );

  // Constructor.
  Property ( const ValueType &value ) :
    BaseClass(),
    _value ( value )
  {
    static_assert ( std::is_copy_constructible < ValueType >::value, "Value type is not copy-constructible" );
  }

  // Get the value.
  const ValueType &getValue() const { return _value; }

protected:

  // Use reference counting.
  virtual ~Property()
  {
  }

private:

  const ValueType _value;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Make a property object.
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
static Usul::Properties::Object *make ( const T &value )
{
  return new Property < T > ( value );
}


} // namespace Properties
} // namespace Usul


#endif // _USUL_PROPERTIES_PROPERTY_H_