
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

#include <stdexcept>
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
inline bool has ( const MapType &container, const std::string &name )
{
  typedef typename MapType::const_iterator Itr;
  Itr i ( container.find ( name ) );
  return ( ( container.end() == i ) ? false : true );
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if the map has a property of the given type.
//
///////////////////////////////////////////////////////////////////////////////

template < class ValueType, class MapType >
inline bool has ( const MapType &container, const std::string &name )
{
  static_assert ( std::is_copy_constructible < ValueType >::value, "Not copy constructible" );

  typedef typename MapType::const_iterator Itr;
  Itr i ( container.find ( name ) );

  if ( container.end() == i )
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
inline ValueType get ( const MapType &container, const std::string &name, ValueType defaultValue )
{
  static_assert ( std::is_copy_constructible < ValueType >::value, "Not copy constructible" );

  typedef typename MapType::const_iterator Itr;
  Itr i ( container.find ( name ) );

  if ( container.end() == i )
  {
    return defaultValue;
  }

  if ( std::holds_alternative < ValueType > ( i->second ) )
  {
    return std::get < ValueType > ( i->second );
  }

  return defaultValue;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return the value if we find it, otherwise throw an exception.
//
///////////////////////////////////////////////////////////////////////////////

template < class ValueType, class MapType >
inline ValueType require ( const MapType &container, const std::string &name )
{
  static_assert ( std::is_copy_constructible < ValueType >::value, "Not copy constructible" );

  typedef typename MapType::const_iterator Itr;
  Itr i ( container.find ( name ) );

  if ( container.end() == i )
  {
    throw std::runtime_error ( "Property '" + name + "' not found in container" );
  }

  if ( std::holds_alternative < ValueType > ( i->second ) )
  {
    return std::get < ValueType > ( i->second );
  }

  throw std::runtime_error ( "Property '" + name + "' is the wrong type" );
}


} // namespace Properties
} // namespace Tools
} // namespace Usul


#endif // _USUL_TOOLS_PROPERTIES_H_
