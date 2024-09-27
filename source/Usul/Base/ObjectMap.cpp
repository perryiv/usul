
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2024, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Class for keeping track of instances of the referenced class.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Base/ObjectMap.h"
#include "Usul/Base/Referenced.h"
#include "Usul/Tools/NoThrow.h"

#include <functional>
#include <stdexcept>


namespace Usul {
namespace Base {


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

ObjectMap::ObjectMap() : _mutex(), _count ( 0 ), _map()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

ObjectMap::~ObjectMap()
{
  USUL_TOOLS_NO_THROW ( 1727457545, std::bind ( &ObjectMap::_destroyObjectMap, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy.
//
///////////////////////////////////////////////////////////////////////////////

void ObjectMap::_destroyObjectMap()
{
  this->format ( std::cerr );
  std::cerr << std::flush;
}


///////////////////////////////////////////////////////////////////////////////
//
//  For debugging. This singleton class will only have useful information
//  if both _DEBUG and USUL_REFERENCED_CLASS_DEBUG_KEEP_TRACK are defined
//  at compile time.
//
///////////////////////////////////////////////////////////////////////////////

ObjectMap& ObjectMap::getSingleton()
{
  static ObjectMap om;
  return om;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Add the object.
//
///////////////////////////////////////////////////////////////////////////////

void ObjectMap::add ( Referenced* obj )
{
  Guard guard ( _mutex );

  // This should not happen.
  if ( nullptr == obj )
  {
    throw std::runtime_error ( "Can not add null referenced object to map" );
  }

  // This should not happen.
  if ( true == _map.contains ( obj ) )
  {
    throw std::runtime_error ( "Object map already contains this address" );
  }

  _map.insert ( Value ( obj, _count++ ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Remove the object.
//
///////////////////////////////////////////////////////////////////////////////

void ObjectMap::remove ( Referenced* obj )
{
  Guard guard ( _mutex );
  _map.erase ( obj );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the number of objects.
//
///////////////////////////////////////////////////////////////////////////////

ObjectMap::SizeType ObjectMap::size() const
{
  Guard guard ( _mutex );
  return _map.size();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Is the map empty?
//
///////////////////////////////////////////////////////////////////////////////

bool ObjectMap::empty() const
{
  Guard guard ( _mutex );
  return _map.empty();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the data.
//
///////////////////////////////////////////////////////////////////////////////

void ObjectMap::get ( DataVec& dv ) const
{
  Guard guard ( _mutex );
  for ( Itr i = _map.begin(); i != _map.end(); ++i )
  {
    const Referenced* obj = i->first;

    // Should not happen but make sure.
    if ( nullptr == obj )
    {
      continue;
    }

    dv.push_back ( Data (
      obj,
      obj->getReferenceCount(),
      i->second,
      Referenced::getTypeName ( obj )
    ) );
  }
}
ObjectMap::DataVec ObjectMap::get() const
{
  // Note: Don't lock the mutex here because it's not recursive.
  DataVec dv;
  this->get ( dv );
  return dv;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Format the data.
//
///////////////////////////////////////////////////////////////////////////////

void ObjectMap::format ( const Data& data, std::ostream& out )
{
  out <<   "Address: "            << std::get < DataIndex::REFERENCED_OBJECT >  ( data );
  out << ", Reference Count: "    << std::get < DataIndex::REFERENCE_COUNT >    ( data );
  out << ", Construction Order: " << std::get < DataIndex::CONSTRUCTION_ORDER > ( data );
  out << ", Type Name: "          << std::get < DataIndex::TYPE_NAME >          ( data );
  out << '\n';
}
void ObjectMap::format ( std::ostream& out ) const
{
  for ( const Data& data : this->get() )
  {
    ObjectMap::format ( data, out );
  }
}


} // namespace Base
} // namespace Usul
