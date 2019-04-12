
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

#include <chrono>
#include <cstdint>


namespace Usul {
namespace Time {
namespace Now {


///////////////////////////////////////////////////////////////////////////////
//
//  Return the time since the epoch in milliseconds.
//
///////////////////////////////////////////////////////////////////////////////

inline std::uint64_t milliseconds()
{
  const auto now ( std::chrono::steady_clock::now().time_since_epoch() );
  const auto duration ( std::chrono::duration_cast < std::chrono::milliseconds > ( now ) );
  const auto count ( duration.count() );
  return ( ( count > 0 ) ? static_cast < std::uint64_t > ( count ) : 0 );
}


} // namespace Now
} // namespace Time
} // namespace Usul


#endif // _USUL_TIME_NOW_FUNCTIONS_H_
