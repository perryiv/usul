
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Property-map adaptors for vectors of length 4.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_PROPERTIES_VECTOR_4_H_
#define _USUL_PROPERTIES_VECTOR_4_H_

#include "Usul/Math/Vector4.h"
#include "Usul/Properties/Map.h"


namespace Usul {
namespace Properties {
namespace { namespace Details {


///////////////////////////////////////////////////////////////////////////////
//
//  Macro used below.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_PROPERTIES_MAP_CONVERT_VECTOR_4(from_type,to_type) \
{ \
  typedef from_type ::value_type from_value_type; \
  typedef to_type ::value_type to_value_type; \
  static_assert ( std::is_arithmetic < from_value_type >::value, "From value is not a number type" ); \
  typedef Property < from_type > PropertyType; \
  const PropertyType *prop = dynamic_cast < const PropertyType * > ( obj ); \
  if ( nullptr != prop ) \
  { \
    const from_type &value = prop->getValue(); \
    return to_type ( \
      static_cast < to_value_type > ( value[0] ), \
      static_cast < to_value_type > ( value[1] ), \
      static_cast < to_value_type > ( value[2] ), \
      static_cast < to_value_type > ( value[3] ) \
    ); \
  } \
}


///////////////////////////////////////////////////////////////////////////////
//
//  Template helper class with specializations. Add more as needed.
//
///////////////////////////////////////////////////////////////////////////////

template <> struct Getter < false, Usul::Math::Vec4d >
{
  static Usul::Math::Vec4d get ( const Map &m, const std::string &name, const Usul::Math::Vec4d &defaultValue )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      return defaultValue;
    }

    USUL_PROPERTIES_MAP_CONVERT_VECTOR_4 ( Usul::Math::Vec4d, Usul::Math::Vec4d );
    USUL_PROPERTIES_MAP_CONVERT_VECTOR_4 ( Usul::Math::Vec4f, Usul::Math::Vec4d );

    return defaultValue;
  }
};
template <> struct Getter < false, Usul::Math::Vec4f >
{
  static Usul::Math::Vec4f get ( const Map &m, const std::string &name, const Usul::Math::Vec4f &defaultValue )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      return defaultValue;
    }

    USUL_PROPERTIES_MAP_CONVERT_VECTOR_4 ( Usul::Math::Vec4f, Usul::Math::Vec4f );
    USUL_PROPERTIES_MAP_CONVERT_VECTOR_4 ( Usul::Math::Vec4d, Usul::Math::Vec4f );

    return defaultValue;
  }
};


///////////////////////////////////////////////////////////////////////////////
//
//  Template helper class with specializations. Add more as needed.
//
///////////////////////////////////////////////////////////////////////////////

template <> struct Require < false, Usul::Math::Vec4d >
{
  static Usul::Math::Vec4d get ( const Map &m, const std::string &name )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not in the map" ) );
    }

    USUL_PROPERTIES_MAP_CONVERT_VECTOR_4 ( Usul::Math::Vec4d, Usul::Math::Vec4d );
    USUL_PROPERTIES_MAP_CONVERT_VECTOR_4 ( Usul::Math::Vec4f, Usul::Math::Vec4d );

    throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not the required type" ) );
  }
};
template <> struct Require < false, Usul::Math::Vec4f >
{
  static Usul::Math::Vec4f get ( const Map &m, const std::string &name )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not in the map" ) );
    }

    USUL_PROPERTIES_MAP_CONVERT_VECTOR_4 ( Usul::Math::Vec4f, Usul::Math::Vec4f );
    USUL_PROPERTIES_MAP_CONVERT_VECTOR_4 ( Usul::Math::Vec4d, Usul::Math::Vec4f );

    throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not the required type" ) );
  }
};


} } // namespace Details
}   // namespace Properties
}   // namespace Usul


#endif // _USUL_PROPERTIES_VECTOR_4_H_
