
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

#include <cstddef>
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

  // Clear the map.
  void clear();

  // Is the map empty?
  bool empty() const { return _values.empty(); }

  // Erase the value.
  bool erase ( const std::string &name );

  // Get the value.
  template < class T >
  const T &get ( const std::string &name, const T &defaultValue ) const;

  // Is there a property with this name and (optionally) type?
  template < class T >
  bool has ( const std::string &name ) const;
  bool has ( const std::string &name ) const;

  // Insert the value.
  template < class T >
  void insert ( const std::string &name, const T &value );
  void insert ( const std::string &name, const std::string &value );
  void insert ( const std::string &name, const char *value );
  void insert ( const std::string &name, std::nullptr_t value );

  // Get the property object.
  const Object *object ( const std::string &name ) const;

  // Get the value or throw an exception.
  template < class T >
  const T &require ( const std::string &name ) const;

  // Return the size of the map.
  size_type size() const { return _values.size(); }

  // Get the type of the property.
  std::string type ( const std::string &name ) const;

  // Insert or update the value.
  template < class T >
  void update ( const std::string &name, const T &value );
  void update ( const std::string &name, const std::string &value );
  void update ( const std::string &name, const char *value );
  void update ( const std::string &name, std::nullptr_t value );

  // Get the internal values.
  const Values &values() const { return _values; }

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
  return ( a.values() == b.values() );
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
  const Object *obj = this->object ( name );
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
  const Object *obj = this->object ( name );
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


///////////////////////////////////////////////////////////////////////////////
//
//  Macros used below.
//
///////////////////////////////////////////////////////////////////////////////

#define USUL_PROPERTIES_MAP_CONVERT(from_type,to_type) \
{ \
  typedef Property < from_type > PropertyType; \
  const PropertyType *prop = dynamic_cast < const PropertyType * > ( obj ); \
  if ( nullptr != prop ) \
  { \
    return static_cast < to_type > ( prop->getValue() ); \
  } \
}


///////////////////////////////////////////////////////////////////////////////
//
//  Template helper class with specializations. Add more as needed.
//  https://www.learncpp.com/cpp-tutorial/13-8-partial-template-specialization-for-pointers/
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class T > struct Getter
  {
    static T get ( const Map &m, const std::string &name, const T &defaultValue )
    {
      const Object *obj = m.object ( name );
      if ( nullptr == obj )
      {
        return defaultValue;
      }

      USUL_PROPERTIES_MAP_CONVERT ( double,         T );
      USUL_PROPERTIES_MAP_CONVERT ( float,          T );
      USUL_PROPERTIES_MAP_CONVERT ( short,          T );
      USUL_PROPERTIES_MAP_CONVERT ( int,            T );
      USUL_PROPERTIES_MAP_CONVERT ( long,           T );
      USUL_PROPERTIES_MAP_CONVERT ( unsigned short, T );
      USUL_PROPERTIES_MAP_CONVERT ( unsigned int,   T );
      USUL_PROPERTIES_MAP_CONVERT ( unsigned long,  T );

      return defaultValue;
    }
  };
  template < typename T > struct Getter < T * >
  {
    static T *get ( const Map &m, const std::string &name, T *defaultValue )
    {
      return m.get < T * > ( name, defaultValue );
    }
  };
  template <> struct Getter < std::string >
  {
    static std::string get ( const Map &m, const std::string &name, const std::string &defaultValue )
    {
      return m.get < std::string > ( name, defaultValue );
    }
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  Non-member function for getting a property and converting it to the
//  correct type if needed.
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
inline T get ( const Map &m, const std::string &name, const T &defaultValue )
{
  typedef Details::Getter < T > Getter;
  return Getter::get ( m, name, defaultValue );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Template helper class with specializations. Add more as needed.
//  https://www.learncpp.com/cpp-tutorial/13-8-partial-template-specialization-for-pointers/
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  template < class T > struct Require
  {
    static T get ( const Map &m, const std::string &name )
    {
      const Object *obj = m.object ( name );
      if ( nullptr == obj )
      {
        throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is not in the map" ) );
      }

      USUL_PROPERTIES_MAP_CONVERT ( double,         T );
      USUL_PROPERTIES_MAP_CONVERT ( float,          T );
      USUL_PROPERTIES_MAP_CONVERT ( short,          T );
      USUL_PROPERTIES_MAP_CONVERT ( int,            T );
      USUL_PROPERTIES_MAP_CONVERT ( long,           T );
      USUL_PROPERTIES_MAP_CONVERT ( unsigned short, T );
      USUL_PROPERTIES_MAP_CONVERT ( unsigned int,   T );
      USUL_PROPERTIES_MAP_CONVERT ( unsigned long,  T );

      throw std::runtime_error ( Usul::Strings::format ( "Property '", name, "' is an unknown type" ) );
    }
  };
  template < typename T > struct Require < T * >
  {
    static T *get ( const Map &m, const std::string &name )
    {
      return m.require < T * > ( name );
    }
  };
  template <> struct Require < std::string >
  {
    static std::string get ( const Map &m, const std::string &name )
    {
      return m.require < std::string > ( name );
    }
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  Non-member functions for requiring a property and converting it to the
//  correct type if needed.
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
inline T require ( const Map &m, const std::string &name )
{
  typedef Details::Require < T > Require;
  return Require::get ( m, name );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the property.
//
///////////////////////////////////////////////////////////////////////////////

template < class T >
inline void set ( Map &m, const std::string &name, const T &value )
{
  m.update < T > ( name, value );
}


///////////////////////////////////////////////////////////////////////////////
//
//  See if the property exists.
//
///////////////////////////////////////////////////////////////////////////////

inline bool has ( Map &m, const std::string &name )
{
  return m.has ( name );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the type of the property.
//
///////////////////////////////////////////////////////////////////////////////

inline std::string type ( Map &m, const std::string &name )
{
  return m.type ( name );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Clean up macros.
//
///////////////////////////////////////////////////////////////////////////////

#undef USUL_PROPERTIES_MAP_CONVERT


} // namespace Properties
} // namespace Usul


#endif // _USUL_PROPERTIES_MAP_H_
