
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Functions for environment variables.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/System/Environment.h"

#include <cstdlib>
#include <sstream>


namespace Usul {
namespace System {


///////////////////////////////////////////////////////////////////////////////
//
//  Get the environment variable.
//
///////////////////////////////////////////////////////////////////////////////

namespace Details
{
  inline bool get ( const std::string &name, std::string &value )
  {
    if ( true == name.empty() )
    {
      return false;
    }

    const char *temp = nullptr;

    #ifdef _WIN32

    temp = std::getenv ( name.c_str() );

    #else

    temp = std::getenv ( name.c_str() );

    #endif

    if ( nullptr == temp )
    {
      return false;
    }

    value = temp;

    return true;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the environment variable.
//
///////////////////////////////////////////////////////////////////////////////

std::string Environment::get ( const std::string &name )
{
  std::string value;
  Details::get ( name, value );
  return value;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Require the environment variable.
//
///////////////////////////////////////////////////////////////////////////////

std::string Environment::require ( const std::string &name )
{
  std::string value;

  if ( true == name.empty() )
  {
    throw std::runtime_error ( "Empty environment variable name" );
  }

  if ( false == Details::get ( name, value ) )
  {
    std::ostringstream out;
    out << "Failed to get environment variable: " << name;
    throw std::runtime_error ( out.str() );
  }

  return value;
}


} // namespace System
} // namespace Usul
