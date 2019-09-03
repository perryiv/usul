
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Map of properties.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_PROPERTIES_MAP_H_
#define _USUL_PROPERTIES_MAP_H_

#include "Usul/Properties/Property.h"
#include "Usul/Strings/Format.h"

#include <map>
#include <stdexcept>
#include <string>


namespace Usul {
namespace Properties {


class USUL_EXPORT Map
{
public:

  // Useful typedefs.
  typedef Usul::Properties::Object Object;
  typedef std::map < std::string, Object::RefPtr > Values;
  typedef Values::size_type size_type;

  // Constructors
  Map();
  Map ( const Map & );
  Map ( const Map::Values & );

  // Assignment
  Map &operator = ( const Map & );
  Map &operator = ( const Map::Values & );

  // Use reference counting.
  virtual ~Map();

  // Is the map empty?
  bool empty() const { return _values.empty(); }

  // Get the value.
  template < class T >
  const T &get ( const std::string &name, const T &defaultValue ) const;

  // Get the internal values.
  const Values &getValues() const { return _values; }

  // Insert the value.
  template < class T >
  void insert ( const std::string &name, const T &value );

  // Get the value or throw an exception.
  template < class T >
  const T &require ( const std::string &name ) const;

  // Return the size of the map.
  size_type size() const { return _values.size(); }

  // Insert or update the value.
  template < class T >
  void update ( const std::string &name, const T &value );

protected:

  // Get the property object.
  const Object *_getObject ( const std::string &name ) const;
  Object *      _getObject ( const std::string &name );

private:

  void _destroyMap();

  Values _values;
};


///////////////////////////////////////////////////////////////////////////////
//
//  See if they are equal.
//
///////////////////////////////////////////////////////////////////////////////

inline bool equal ( const Map &a, const Map &b )
{
  return ( a.getValues() == b.getValues() );
}
inline bool operator == ( const Map &a, const Map &b )
{
  return ( true == Usul::Properties::equal ( a, b ) );
}
inline bool operator != ( const Map &a, const Map &b )
{
  return ( false == Usul::Properties::equal ( a, b ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the value or return the default.
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
const T &Map::get ( const std::string &name, const T &defaultValue ) const
{
  const Object *obj = this->_getObject ( name );
  if ( nullptr == obj )
  {
    return defaultValue;
  }

  typedef Property < T > PropertyType;
  const PropertyType *prop = dynamic_cast < const PropertyType * > ( obj );
  if ( nullptr == prop )
  {
    return defaultValue;
  }

  return prop->getValue();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Insert the value.
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
void Map::insert ( const std::string &name, const T &value )
{
  typedef typename Values::value_type value_type;
  _values.insert ( value_type ( name, Usul::Properties::make ( value ) ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the value or throw an exception.
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
const T &Map::require ( const std::string &name ) const
{
  const Object *obj = this->_getObject ( name );
  if ( nullptr == obj )
  {
    throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not in the map" ) );
  }

  typedef Property < T > PropertyType;
  const PropertyType *prop = dynamic_cast < const PropertyType * > ( obj );
  if ( nullptr == prop )
  {
    throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not the required type" ) );
  }

  return prop->getValue();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Insert or update the value.
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
void Map::update ( const std::string &name, const T &value )
{
  _values[name] = Usul::Properties::make ( value );
}


} // namespace Properties
} // namespace Usul


#endif // _USUL_PROPERTIES_MAP_H_
