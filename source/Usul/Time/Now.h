
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Get the current time.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_TIME_NOW_FUNCTIONS_H_
#define _USUL_TIME_NOW_FUNCTIONS_H_

#include "Usul/Export.h"

#include <cstdint>
#include <string>


namespace Usul {
namespace Time {
namespace Now {


///////////////////////////////////////////////////////////////////////////////
//
//  Hiding the implementations in a class because importing and exporting
//  symbols on Windows works better this way.
//
///////////////////////////////////////////////////////////////////////////////

struct USUL_EXPORT Implementation
{
  static std::uint64_t milliseconds();
  static std::string format ( const std::string & );
};


///////////////////////////////////////////////////////////////////////////////
//
//  These functions are the public ones.
//
///////////////////////////////////////////////////////////////////////////////

// Return the time since the epoch in milliseconds.
inline std::uint64_t milliseconds()
{
  return Implementation::milliseconds();
}

// Return a formatted string. See std::strftime for arguments.
inline std::string format ( const std::string &fs = std::string() )
{
  return Implementation::format ( fs );
}


} // namespace Now
} // namespace Time
} // namespace Usul


#endif // _USUL_TIME_NOW_FUNCTIONS_H_
