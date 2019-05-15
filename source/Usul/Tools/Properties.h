
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Functions for working with a map of any type.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_TOOLS_PROPERTIES_H_
#define _USUL_TOOLS_PROPERTIES_H_

#include "Usul/Tools/NoCopying.h"

#include <string>
#include <type_traits>
#include <variant>


namespace Usul {
namespace Tools {
namespace Properties {


///////////////////////////////////////////////////////////////////////////////
//
//  See if the map has the given property.
//
///////////////////////////////////////////////////////////////////////////////

template < class MapType >
inline bool has ( const MapType &properties, const std::string &name )
{
  typedef typename MapType::const_iterator Itr;
  Itr i ( properties.find ( name ) );
  return ( ( properties.end() == i ) ? false : true );
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if the map has a property of the given type.
//
///////////////////////////////////////////////////////////////////////////////

template < class ValueType, class MapType >
inline bool has ( const MapType &properties, const std::string &name )
{
  static_assert ( std::is_copy_constructible < ValueType >::value, "Not copy constructible" );

  typedef typename MapType::const_iterator Itr;
  Itr i ( properties.find ( name ) );

  if ( properties.end() == i )
  {
    return false;
  }

  return std::holds_alternative < ValueType > ( i->second );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the value if we find it, otherwise return the given default.
//
///////////////////////////////////////////////////////////////////////////////

template < class ValueType, class MapType >
inline ValueType get ( const MapType &properties, const std::string &name, ValueType defaultValue )
{
  static_assert ( std::is_copy_constructible < ValueType >::value, "Not copy constructible" );

  typedef typename MapType::const_iterator Itr;
  Itr i ( properties.find ( name ) );

  if ( properties.end() == i )
  {
    return defaultValue;
  }

  if ( std::holds_alternative < ValueType > ( i->second ) )
  {
    return std::get < ValueType > ( i->second );
  }

  return defaultValue;
}


} // namespace Properties
} // namespace Tools
} // namespace Usul


#endif // _USUL_TOOLS_PROPERTIES_H_
