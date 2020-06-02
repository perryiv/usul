
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Test the job manager.
//
////////////////////////////////////////////////////////////////////////////////

#include "Usul/Jobs/Manager.h"
#include "Usul/Strings/Format.h"
#include "Usul/Tools/ScopedCall.h"

#include "catch2/catch.hpp"

#include <iostream>
#include <type_traits>


////////////////////////////////////////////////////////////////////////////////
//
//  Test the job manager.
//
////////////////////////////////////////////////////////////////////////////////

TEST_CASE ( "Job manager" )
{
  typedef Usul::Jobs::Manager Manager;
  typedef Usul::Jobs::Job Job;
  typedef Job::Ptr JobPtr;

  static_assert ( std::is_same < JobPtr, Manager::JobPtr > ::value,
    "Inconsistent job pointer types" );

  // Make the singleton.
  Manager &manager = Manager::instance();

  // Destroy the singleton.
  USUL_SCOPED_CALL ( [] ()
  {
    Manager::destroy();
  } );

  SECTION ( "Number of jobs" )
  {
    std::cout << Usul::Strings::format (
      "Job manager is using ", manager.getMaxNumThreadsAllowed(), " threads\n"
    ) << std::flush;

    REQUIRE ( 0 == manager.getNumJobsQueued() );
    REQUIRE ( 0 == manager.getNumJobsRunning() );
    REQUIRE ( 0 == manager.getNumJobs() );
  }

  SECTION ( "Add many fast jobs" )
  {
    // How many jobs to add.
    const unsigned int numJobs = 100;

    // Add jobs to the manager.
    for ( unsigned int i = 0; i < numJobs; ++i )
    {
      manager.addJob ( JobPtr ( new Job ( [] ()
      {
        // Sleep some to simulate a lengthy task.
        std::this_thread::sleep_for ( std::chrono::milliseconds ( 5 ) );
      } ) ) );
    }

    // Make sure we have jobs. Note: Some of the jobs may have finished already.
    REQUIRE ( manager.getNumJobs() > 0 );

    // Wait for all the jobs to finish.
    manager.waitAll();

    // Make sure we have the right number of jobs.
    REQUIRE ( 0 == manager.getNumJobs() );
  }

  SECTION ( "Add fewer long jobs" )
  {
    // How many jobs to add.
    const unsigned int numJobs = 5;

    // Add jobs to the manager.
    for ( unsigned int i = 0; i < numJobs; ++i )
    {
      manager.addJob ( JobPtr ( new Job ( [] ()
      {
        // Sleep some to simulate a lengthy task.
        std::this_thread::sleep_for ( std::chrono::milliseconds ( 100 ) );
      } ) ) );
    }

    // Make sure we have the right number of jobs. Note: It's unlikely that any
    // of them are already done and removed from the job manager.
    REQUIRE ( numJobs == manager.getNumJobs() );

    // Wait for all the jobs to finish.
    manager.waitAll();

    // Make sure we have the right number of jobs.
    REQUIRE ( 0 == manager.getNumJobs() );
  }

  SECTION ( "Add many fast jobs and do not wait for them" )
  {
    // How many jobs to add.
    const unsigned int numJobs = 100;

    // Add jobs to the manager.
    for ( unsigned int i = 0; i < numJobs; ++i )
    {
      manager.addJob ( JobPtr ( new Job ( [] ()
      {
        // Sleep some to simulate a lengthy task.
        std::this_thread::sleep_for ( std::chrono::milliseconds ( 5 ) );
      } ) ) );
    }

    // Make sure we have jobs. Note: Some of the jobs may have finished already.
    REQUIRE ( manager.getNumJobs() > 0 );

    // This will wait for all the jobs to finish.
    Manager::destroy();
  }
}
