
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Property-map adaptors for 4x4 matrices.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_PROPERTIES_4_BY_4_MATRIX_H_
#define _USUL_PROPERTIES_4_BY_4_MATRIX_H_

#include "Usul/Math/Matrix44.h"
#include "Usul/Properties/Map.h"


namespace Usul {
namespace Properties {
namespace Details {


///////////////////////////////////////////////////////////////////////////////
//
//  Macro used below.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_PROPERTIES_MAP_CONVERT_MATRIX_44(from_type,to_type) \
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
      static_cast < to_value_type > ( value[ 0] ), \
      static_cast < to_value_type > ( value[ 1] ), \
      static_cast < to_value_type > ( value[ 2] ), \
      static_cast < to_value_type > ( value[ 3] ), \
      static_cast < to_value_type > ( value[ 4] ), \
      static_cast < to_value_type > ( value[ 5] ), \
      static_cast < to_value_type > ( value[ 6] ), \
      static_cast < to_value_type > ( value[ 7] ), \
      static_cast < to_value_type > ( value[ 8] ), \
      static_cast < to_value_type > ( value[ 9] ), \
      static_cast < to_value_type > ( value[10] ), \
      static_cast < to_value_type > ( value[11] ), \
      static_cast < to_value_type > ( value[12] ), \
      static_cast < to_value_type > ( value[13] ), \
      static_cast < to_value_type > ( value[14] ), \
      static_cast < to_value_type > ( value[15] ) \
    ); \
  } \
}


///////////////////////////////////////////////////////////////////////////////
//
//  Template helper class with specializations. Add more as needed.
//
///////////////////////////////////////////////////////////////////////////////

template <> struct Getter < false, Usul::Math::Matrix44d >
{
  static Usul::Math::Matrix44d get ( const Map &m, const std::string &name, const Usul::Math::Matrix44d &defaultValue )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      return defaultValue;
    }

    USUL_PROPERTIES_MAP_CONVERT_MATRIX_44 ( Usul::Math::Matrix44d, Usul::Math::Matrix44d );
    USUL_PROPERTIES_MAP_CONVERT_MATRIX_44 ( Usul::Math::Matrix44f, Usul::Math::Matrix44d );

    return defaultValue;
  }
};
template <> struct Getter < false, Usul::Math::Matrix44f >
{
  static Usul::Math::Matrix44f get ( const Map &m, const std::string &name, const Usul::Math::Matrix44f &defaultValue )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      return defaultValue;
    }

    USUL_PROPERTIES_MAP_CONVERT_MATRIX_44 ( Usul::Math::Matrix44f, Usul::Math::Matrix44f );
    USUL_PROPERTIES_MAP_CONVERT_MATRIX_44 ( Usul::Math::Matrix44d, Usul::Math::Matrix44f );

    return defaultValue;
  }
};


///////////////////////////////////////////////////////////////////////////////
//
//  Template helper class with specializations. Add more as needed.
//
///////////////////////////////////////////////////////////////////////////////

template <> struct Require < false, Usul::Math::Matrix44d >
{
  static Usul::Math::Matrix44d get ( const Map &m, const std::string &name )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not in the map" ) );
    }

    USUL_PROPERTIES_MAP_CONVERT_MATRIX_44 ( Usul::Math::Matrix44d, Usul::Math::Matrix44d );
    USUL_PROPERTIES_MAP_CONVERT_MATRIX_44 ( Usul::Math::Matrix44f, Usul::Math::Matrix44d );

    throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not the required type" ) );
  }
};
template <> struct Require < false, Usul::Math::Matrix44f >
{
  static Usul::Math::Matrix44f get ( const Map &m, const std::string &name )
  {
    const Object *obj = m.object ( name );
    if ( nullptr == obj )
    {
      throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not in the map" ) );
    }

    USUL_PROPERTIES_MAP_CONVERT_MATRIX_44 ( Usul::Math::Matrix44f, Usul::Math::Matrix44f );
    USUL_PROPERTIES_MAP_CONVERT_MATRIX_44 ( Usul::Math::Matrix44d, Usul::Math::Matrix44f );

    throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not the required type" ) );
  }
};


} // namespace Details
} // namespace Properties
} // namespace Usul


#endif // _USUL_PROPERTIES_4_BY_4_MATRIX_H_
