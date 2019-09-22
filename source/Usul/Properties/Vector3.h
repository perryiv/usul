
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Property-map adaptors for vectors of length 3.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_PROPERTIES_VECTOR_3_H_
#define _USUL_PROPERTIES_VECTOR_3_H_

#include "Usul/Math/Vector3.h"
#include "Usul/Properties/Map.h"


namespace Usul {
namespace Properties {
namespace Details {


///////////////////////////////////////////////////////////////////////////////
//
//  Macro used below.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_PROPERTIES_MAP_CONVERT_VECTOR_3(from_type,to_type) \
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
      static_cast < to_value_type > ( value[2] ) \
    ); \
  } \
}


///////////////////////////////////////////////////////////////////////////////
//
//  Template helper class with specializations. Add more as needed.
//
///////////////////////////////////////////////////////////////////////////////

template <> struct Getter < false, Usul::Math::Vec3d >
{
  static Usul::Math::Vec3d get ( const Map &m, const std::string &name, const Usul::Math::Vec3d &defaultValue )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      return defaultValue;
    }

    USUL_PROPERTIES_MAP_CONVERT_VECTOR_3 ( Usul::Math::Vec3d, Usul::Math::Vec3d );
    USUL_PROPERTIES_MAP_CONVERT_VECTOR_3 ( Usul::Math::Vec3f, Usul::Math::Vec3d );

    return defaultValue;
  }
};
template <> struct Getter < false, Usul::Math::Vec3f >
{
  static Usul::Math::Vec3f get ( const Map &m, const std::string &name, const Usul::Math::Vec3f &defaultValue )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      return defaultValue;
    }

    USUL_PROPERTIES_MAP_CONVERT_VECTOR_3 ( Usul::Math::Vec3f, Usul::Math::Vec3f );
    USUL_PROPERTIES_MAP_CONVERT_VECTOR_3 ( Usul::Math::Vec3d, Usul::Math::Vec3f );

    return defaultValue;
  }
};


///////////////////////////////////////////////////////////////////////////////
//
//  Template helper class with specializations. Add more as needed.
//
///////////////////////////////////////////////////////////////////////////////

template <> struct Require < false, Usul::Math::Vec3d >
{
  static Usul::Math::Vec3d get ( const Map &m, const std::string &name )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not in the map" ) );
    }

    USUL_PROPERTIES_MAP_CONVERT_VECTOR_3 ( Usul::Math::Vec3d, Usul::Math::Vec3d );
    USUL_PROPERTIES_MAP_CONVERT_VECTOR_3 ( Usul::Math::Vec3f, Usul::Math::Vec3d );

    throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not the required type" ) );
  }
};
template <> struct Require < false, Usul::Math::Vec3f >
{
  static Usul::Math::Vec3f get ( const Map &m, const std::string &name )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not in the map" ) );
    }

    USUL_PROPERTIES_MAP_CONVERT_VECTOR_3 ( Usul::Math::Vec3f, Usul::Math::Vec3f );
    USUL_PROPERTIES_MAP_CONVERT_VECTOR_3 ( Usul::Math::Vec3d, Usul::Math::Vec3f );

    throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not the required type" ) );
  }
};


} // namespace Details
} // namespace Properties
} // namespace Usul


#endif // _USUL_PROPERTIES_VECTOR_3_H_
