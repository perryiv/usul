
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
    result = Catch::Session().run ( argc, argv );

    if ( false == Helpers::Instances::get().empty() )
    {
      throw std::runtime_error ( "Instances remain in memory" );
    }
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
