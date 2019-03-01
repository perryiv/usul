
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Helper singleton class for keeping track of all referenced instances.
//
////////////////////////////////////////////////////////////////////////////////

#include "Helpers/Instances.h"

#include "catch2/catch.hpp"

#include <mutex>

namespace Helpers {


////////////////////////////////////////////////////////////////////////////////
//
//  Singleton instance.
//
////////////////////////////////////////////////////////////////////////////////

namespace Details
{
  std::mutex _mutex;
  Instances *_singleton = nullptr;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
////////////////////////////////////////////////////////////////////////////////

Instances::Instances() : _set()
{
}


////////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
////////////////////////////////////////////////////////////////////////////////

Instances::~Instances()
{
  REQUIRE ( _set.empty() );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Singleton access.
//
////////////////////////////////////////////////////////////////////////////////

Instances &Instances::get()
{
  std::lock_guard < std::mutex > lock ( Details::_mutex );

  if ( !Details::_singleton )
  {
    Details::_singleton = new Instances();
  }

  return *Details::_singleton;
}


} // namespace Helpers
