
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

#ifndef _USUL_SYSTEM_ENVIRONMENT_H_
#define _USUL_SYSTEM_ENVIRONMENT_H_

#include "Usul/Export.h"

#include <string>


namespace Usul {
namespace System {


struct USUL_EXPORT Environment
{
  // Return the environment variable or an empty string.
  static std::string get ( const std::string &name );

  // Return the environment variable or throws an exception.
  static std::string require ( const std::string &name );
};


} // namespace System
} // namespace Usul


#endif // _USUL_SYSTEM_ENVIRONMENT_H_
