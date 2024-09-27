
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
//  This singleton class will only have useful information if both _DEBUG
//  and USUL_REFERENCED_CLASS_DEBUG_KEEP_TRACK are defined at compile time.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Usul/Export.h"
#include "Usul/Config.h"

#include <cstdint>
#include <iosfwd>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace Usul { namespace Base { class Referenced; } }


namespace Usul {
namespace Base {


class USUL_EXPORT ObjectMap
{
public:

  typedef std::mutex Mutex;
  typedef std::lock_guard < Mutex > Guard;
  typedef unsigned int ReferenceCount;
  typedef std::uint64_t ConstructionOrder;
  typedef std::string TypeName;
  typedef std::unordered_map < Referenced*, ConstructionOrder > Map;
  typedef Map::const_iterator Itr;
  typedef Map::value_type Value;
  typedef Map::size_type SizeType;
  typedef std::tuple < const Referenced*, ReferenceCount, ConstructionOrder, TypeName > Data;
  typedef std::vector < Data > DataVec;

  ObjectMap();
  ~ObjectMap();

  enum DataIndex
  {
    REFERENCED_OBJECT = 0,
    REFERENCE_COUNT = 1,
    CONSTRUCTION_ORDER = 2,
    TYPE_NAME = 3
  };

  bool empty() const;

  DataVec get() const;
  void    get ( DataVec& ) const;

  static ObjectMap& getSingleton();

  static void format ( const Data&, std::ostream& out );
  void        format ( std::ostream& out ) const;

  SizeType size() const;

protected:

  friend class Referenced;

  void add ( Referenced* );
  void remove ( Referenced* );

private:

  void _destroyObjectMap();

  mutable Mutex _mutex;
  std::uint64_t _count;
  Map _map;
};


} // namespace Base
} // namespace Usul
