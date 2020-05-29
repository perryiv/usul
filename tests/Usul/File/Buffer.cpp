
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
#include "Usul/IO/Redirect/String.h"
#include "Usul/Tools/ScopedCall.h"

#include "catch2/catch.hpp"

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>


////////////////////////////////////////////////////////////////////////////////
//
//  Test the file buffer.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "File buffer" )
{
  typedef Usul::File::Buffer < char > FileBuffer;
  typedef std::vector < FileBuffer::char_type > Contents;

  // This string has to live longer than the place that uses it.
  const std::string file ( "large_file_for_testing_progress_callback.txt" );

  SECTION ( "Should report progress" )
  {
    // Make sure we make a new file.
    std::remove ( file.c_str() );

    // Make sure we clean it up.
    USUL_SCOPED_CALL ( [ &file ] ()
    {
      std::remove ( file.c_str() );
    } );

    // Make the command.
    std::ostringstream command;
    const unsigned int numMegaBytes = 128;

    #ifdef _WIN32
    // https://www.windows-commandline.com/how-to-create-large-dummy-file/
    command << "fsutil file createnew " << file << ' ' << ( 1024 * 1024 * numMegaBytes );
    #else
    // https://skorks.com/2010/03/how-to-quickly-generate-a-large-file-on-the-command-line-with-linux/
    command << "dd if=/dev/zero of=" << file << " count=1024 bs=" << ( 1024 * numMegaBytes );
    #endif

    // Execute the command.
    std::cout << "Generating file: " << file << std::endl;
    REQUIRE ( 0 == std::system ( command.str().c_str() ) );
    std::cout << "Done generating file: " << file << std::endl;

    // Open the one file we know is present, this program.
    FileBuffer buffer ( file );

    // Should be true.
    REQUIRE ( 0 == ( buffer.getFileSize() % 1024 ) );
    REQUIRE ( 0 == ( buffer.getFileSize() % ( 1024 * 1024 ) ) );
    REQUIRE ( numMegaBytes == ( buffer.getFileSize() / ( 1024 * 1024 ) ) );

    // Used to capture the progress information in the callback.
    double fraction = 0;

    // Set the callback.
    buffer.setProgressFunction ( [ &buffer, &fraction ] ( std::uint64_t count, std::uint64_t size )
    {
      REQUIRE ( size == buffer.getFileSize() );
      REQUIRE ( count <= size );
      fraction = ( static_cast < double > ( count ) / static_cast < double > ( size ) );

      // Uncomment if you want to see progress.
      std::cout << "Progress fraction: " << fraction << std::endl;
    } );

    // Set the throttle to the same value to make sure it compiles.
    buffer.getThrottlePolicy().setDelay ( buffer.getThrottlePolicy().getDelay() );

    // Make the input stream.
    std::istream in ( &buffer );

    // Needed below.
    Contents contents ( 1024 );

    // Read the stream until the end.
    while ( in.good() )
    {
      in.read ( &contents[0], static_cast < std::streamsize > ( contents.size() ) );
    }

    // Make sure we got some progress. Note: It's very likely that the last
    // call to the progress function will not be at 100% completion.
    REQUIRE ( fraction <= 1 );
    REQUIRE ( fraction > 0 );
  }
}
