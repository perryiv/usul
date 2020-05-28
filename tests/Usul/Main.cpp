
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Main file for test program.
//
////////////////////////////////////////////////////////////////////////////////

#include "Helpers/Instances.h"

#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"

#include <iostream>
#include <stdexcept>

std::string programName;


////////////////////////////////////////////////////////////////////////////////
//
//  Main function.
//
////////////////////////////////////////////////////////////////////////////////

int main ( int argc, char **argv )
{
  int result ( 1 );

  try
  {
    programName = argv[0];
    result = Catch::Session().run ( argc, argv );

    if ( false == Helpers::Instances::get().empty() )
    {
      throw std::runtime_error ( "Instances remain in memory" );
    }

    Helpers::Instances::destroy();
  }

  catch ( const std::exception &e )
  {
    std::cout << "Standard exception caught: " << e.what() << std::endl;
  }

  catch ( ... )
  {
    std::cout << "Unknown exception caught" << std::endl;
  }

  return result;
}
