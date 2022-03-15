
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

#include "Usul/Time/Now.h"

#include <chrono>
#include <ctime>


namespace Usul {
namespace Time {
namespace Now {


///////////////////////////////////////////////////////////////////////////////
//
//  Return the time since the epoch in milliseconds.
//
///////////////////////////////////////////////////////////////////////////////

std::uint64_t Implementation::milliseconds()
{
  const auto now ( std::chrono::steady_clock::now().time_since_epoch() );
  const auto duration ( std::chrono::duration_cast < std::chrono::milliseconds > ( now ) );
  const auto count ( duration.count() );
  return ( ( count > 0 ) ? static_cast < std::uint64_t > ( count ) : 0 );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return a formatted string. See std::strftime for arguments.
//
///////////////////////////////////////////////////////////////////////////////

std::string Implementation::format ( const std::string &arg )
{
  // The buffer we fill.
  constexpr std::size_t BUFFER_SIZE = 256;
  char buffer[BUFFER_SIZE];

  // Get the current time.
  const std::time_t now = std::time ( nullptr );

  // Get the given format string or a default one.
  constexpr char DEFAULT_FORMAT_STRING[] = "%Y-%m-%d %H:%M:%S";
  const std::string fs = (
    ( false == arg.empty() ) ?
    arg :
    std::string ( DEFAULT_FORMAT_STRING )
  );

  // Write the formatted string to the buffer.
  const std::size_t numBytes = std::strftime (
    buffer,
    BUFFER_SIZE,
    fs.c_str(),
    std::localtime ( &now )
  );

  // Return the buffer if the write was successful, otherwise an empty string.
  return ( ( numBytes > 0 ) ? std::string ( buffer ) : std::string() );
}


} // namespace Now
} // namespace Time
} // namespace Usul
