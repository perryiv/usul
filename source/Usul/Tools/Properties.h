
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

#include <any>
#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>


namespace Usul {
namespace Tools {
namespace Properties {


///////////////////////////////////////////////////////////////////////////////
//
//  The container of properties.
//
///////////////////////////////////////////////////////////////////////////////

typedef std::map < std::string, std::any > MapType;


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

  try
  {
    // Visual C++ does not like the unused value returned by the cast.
    #ifdef _WIN32
    # pragma warning ( push )
    # pragma warning ( disable : 4834 )
    #endif

    std::any_cast < ValueType > ( i->second );

    #ifdef _WIN32
    # pragma warning ( pop )
    #endif

    return true;
  }

  catch ( const std::bad_any_cast & )
  {
    return false;
  }
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

  try
  {
    return std::any_cast < ValueType > ( i->second );
  }

  catch ( const std::bad_any_cast & )
  {
    return defaultValue;
  }
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

  try
  {
    return std::any_cast < ValueType > ( i->second );
  }

  catch ( const std::bad_any_cast & )
  {
    throw std::runtime_error ( "Property '" + name + "' is the wrong type" );
  }
}


} // namespace Properties
} // namespace Tools
} // namespace Usul


#endif // _USUL_TOOLS_PROPERTIES_H_
