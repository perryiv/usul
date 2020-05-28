
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the file buffer with progress.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/File/Buffer.h"

#include "catch2/catch.hpp"

#include <fstream>
#include <vector>

extern std::string programName;


////////////////////////////////////////////////////////////////////////////////
//
//  Test the file buffer.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "File buffer" )
{
  typedef Usul::File::Buffer < char > FileBuffer;
  typedef std::vector < FileBuffer::char_type > Contents;

  SECTION ( "Should report progress" )
  {
    // Open the one file we know is present, this program.
    FileBuffer buffer ( programName );

    // Used to capture the progress information in the callback.
    double fraction = 0;

    // Set the callback.
    buffer.setProgressFunction ( [ &buffer, &fraction ] ( std::uint64_t count, std::uint64_t size )
    {
      REQUIRE ( size == buffer.getFileSize() );
      fraction = ( static_cast < double > ( count ) / static_cast < double > ( size ) );
    } );

    // Set the throttle to the same value to make sure it compiles.
    buffer.getThrottlePolicy().setDelay ( buffer.getThrottlePolicy().getDelay() );

    // Make the input stream.
    std::istream in ( &buffer );

    // Read one character at a time so that we can get progress for small files.
    char temp;
    in.rdbuf()->pubsetbuf ( &temp, 1 );

    // Needed below.
    Contents contents ( 1024 );

    // Read the stream until the end.
    while ( in.good() )
    {
      in.read ( &contents[0], static_cast < std::streamsize > ( contents.size() ) );
    }

    // Make sure we got some progress. Note: It's very likely that the last
    // call to the progress function will not be at 100% completion.
    REQUIRE ( fraction > 0 );
    REQUIRE ( fraction <= 1 );
  }
}
