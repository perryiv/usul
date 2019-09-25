
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
  USUL_REFERENCED_CLASS ( Property );

  // Constructor.
  Property ( const ValueType &value ) :
    BaseClass(),
    _value ( value )
  {
    static_assert ( std::is_copy_constructible < ValueType >::value, "Value type is not copy-constructible" );
  }

  // Return the type info of the value.
  virtual const std::type_info &getTypeInfo() const override { return typeid ( ValueType ); }

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


///////////////////////////////////////////////////////////////////////////////
//
//  Wrapper function for brevity.
//  It's a macro because there may be name clashing if "mp" already exists.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_DEFINE_MAKE_PROPERTY_FUNCTION_SHORTCUT \
  template < class T > inline Usul::Properties::Object *mp ( const T &value ) \
  { \
    return Usul::Properties::make ( value ); \
  }


#endif // _USUL_PROPERTIES_PROPERTY_H_
