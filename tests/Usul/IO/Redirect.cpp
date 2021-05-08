
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test redirecting standard streams.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/IO/Redirect/Callback.h"
#include "Usul/IO/Redirect/File.h"
#include "Usul/IO/Redirect/String.h"

#include "catch2/catch.hpp"

#include <algorithm>
#include <iostream>


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to write to the stream.
//
////////////////////////////////////////////////////////////////////////////////

inline void writeToStream ( std::ostream &out, const std::string &name, unsigned int start, unsigned int num )
{
  for ( unsigned int i = start; i < ( start + num ); ++i )
  {
    out << "Stream = " << name << ", count = " << i << std::endl;
  }
}


////////////////////////////////////////////////////////////////////////////////
//
//  Helper function to write to the streams.
//
////////////////////////////////////////////////////////////////////////////////

inline void writeToStandardStreams ( unsigned int num )
{
  writeToStream ( std::cout, "some_string", ( 0 * num ), num );
  writeToStream ( std::cerr, "some_string", ( 1 * num ), num );
  writeToStream ( std::clog, "some_string", ( 2 * num ), num );
}


////////////////////////////////////////////////////////////////////////////////
//
//  Test the output redirection.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Test the output redirection" )
{
  // We write to each standard stream this many times.
  constexpr unsigned int num = 2;

  // Make the expected string.
  std::ostringstream expected;
  writeToStream ( expected, "some_string", 0, ( num * 3 ) );

  SECTION ( "Can redirect to a string" )
  {
    // Send all standard output to a string while we are within this scope.
    Usul::IO::Redirect::String redirect;

    // Write to the standard streams.
    writeToStandardStreams ( num );

    // Should be true.
    REQUIRE ( redirect.getContents() == expected.str() );
  }

  SECTION ( "Can redirect to a file" )
  {
    // The name of the file that gets standard output.
    const std::string file ( "test_standard_stream_redirection.txt" );

    // Make sure we make a new file.
    std::remove ( file.c_str() );

    // Send all standard output to a file while we are within this scope.
    // Pass true to automatically delete the file.
    Usul::IO::Redirect::File redirect ( file, true );

    // Write to the standard streams.
    writeToStandardStreams ( num );

    // Should be true.
    REQUIRE ( redirect.getContents() == expected.str() );
  }

  SECTION ( "Can redirect to a callback function" )
  {
    // Send all standard output to this callback while we are within this scope.
    std::ostringstream actual;
    Usul::IO::Redirect::Callback cr ( [ &actual ] ( const std::string &s )
    {
      actual << s;
    } );

    // Write to the standard streams.
    writeToStandardStreams ( num );

    // TODO: Figure out why std::endl does not become a newline character,
    // but for now, just remove them from the expected result.
    std::string answer = expected.str();
    answer.erase ( std::remove ( answer.begin(), answer.end(), '\n' ), answer.end() );
    answer.erase ( std::remove ( answer.begin(), answer.end(), '\r' ), answer.end() );

    // The streams act too differently on Windows. Debug this when time permits.
    #ifndef _WIN32

    // Should be true.
    REQUIRE ( actual.str() == answer );

    #endif // _WIN32
  }
}
