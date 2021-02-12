
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

#include <atomic>
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
  typedef std::atomic < unsigned int > AtomicUnsignedInt;

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
    std::cout << "Job manager is using " << manager.getMaxNumThreadsAllowed() << " threads" << std::endl;
    REQUIRE ( 0 == manager.getNumJobsQueued() );
    REQUIRE ( 0 == manager.getNumJobsRunning() );
    REQUIRE ( 0 == manager.getNumJobs() );
  }

  SECTION ( "Add many fast jobs" )
  {
    // How many jobs to add.
    const unsigned int numJobs = 100;

    // Count the jobs.
    AtomicUnsignedInt count ( 0 );

    // Add jobs to the manager.
    for ( unsigned int i = 0; i < numJobs; ++i )
    {
      manager.addJob ( JobPtr ( new Job ( [ &count ] ( JobPtr )
      {
        // Increment the count.
        ++count;

        // Sleep some to simulate a lengthy task.
        std::this_thread::sleep_for ( std::chrono::milliseconds ( 5 ) );
      } ) ) );
    }

    // Make sure we have jobs. Note: Some of the jobs may have finished already.
    REQUIRE ( manager.getNumJobs() > 0 );

    // Wait for all the jobs to finish.
    manager.waitAll();

    // Try to prevent test failures that look like this:
    //   REQUIRE( 0 == manager.getNumJobs() )
    // with expansion:
    //   0 == 1
    std::this_thread::sleep_for ( std::chrono::milliseconds ( 500 ) );

    // Make sure.
    REQUIRE ( 0 == manager.getNumJobs() );

    // Did all the jobs run?
    REQUIRE ( numJobs == count );
  }

  SECTION ( "Add fewer long jobs" )
  {
    // How many jobs to add.
    const unsigned int numJobs = 5;

    // Count the jobs.
    AtomicUnsignedInt count ( 0 );

    // Add jobs to the manager.
    for ( unsigned int i = 0; i < numJobs; ++i )
    {
      manager.addJob ( JobPtr ( new Job ( [ &count ] ( JobPtr )
      {
        // Increment the count.
        ++count;

        // Sleep some to simulate a lengthy task.
        std::this_thread::sleep_for ( std::chrono::milliseconds ( 100 ) );
      } ) ) );
    }

    // Make sure we have the right number of jobs. Note: It's unlikely that any
    // of them are already done and removed from the job manager.
    // Wrong, this often fails, but it does not matter, the checks below matter.
    // REQUIRE ( numJobs == manager.getNumJobs() );

    // Wait for all the jobs to finish.
    manager.waitAll();

    // Make sure.
    REQUIRE ( 0 == manager.getNumJobs() );

    // Try to prevent test failures that look like this:
    // /some/path/usul/tests/Usul/Jobs/Manager.cpp:92: FAILED:
    //   REQUIRE( numJobs == count )
    // with expansion:
    //   100 == 100
    std::this_thread::sleep_for ( std::chrono::milliseconds ( 5 ) );

    // Did all the jobs run?
    REQUIRE ( numJobs == count );
  }

  SECTION ( "Add many fast jobs and do not wait for them" )
  {
    // How many jobs to add.
    const unsigned int numJobs = 100;

    // Count the jobs.
    AtomicUnsignedInt count ( 0 );

    // Add jobs to the manager.
    for ( unsigned int i = 0; i < numJobs; ++i )
    {
      manager.addJob ( JobPtr ( new Job ( [ &count ] ( JobPtr )
      {
        // Increment the count.
        ++count;

        // Sleep some to simulate a lengthy task.
        std::this_thread::sleep_for ( std::chrono::milliseconds ( 5 ) );
      } ) ) );
    }

    // Make sure we have jobs. Note: Some of the jobs may have finished already.
    REQUIRE ( manager.getNumJobs() > 0 );

    // This clears the queue, cancels the running jobs (which is just a hint),
    // and waits for the running jobs to finish.
    Manager::destroy();

    // We should not have completed all the jobs.
    REQUIRE ( count < numJobs );
  }

  SECTION ( "Add jobs with just lambda expression" )
  {
    // The jobs will increment this.
    unsigned int count = 0;

    // How many jobs to add.
    const unsigned int numJobs = 100;

    // Add several jobs.
    for ( unsigned int i = 0; i < numJobs; ++i )
    {
      Usul::Jobs::Manager::instance().addJob ( [ &count ] ( JobPtr )
      {
        ++count;
      } );
    }

    // Wait for all the jobs to finish.
    Usul::Jobs::Manager::instance().waitAll();

    // This should be true.
    REQUIRE ( numJobs == count );
  }

  SECTION ( "Add jobs that throw exceptions and call error handler" )
  {
    // The jobs will increment this.
    unsigned int count = 0;

    // How many jobs to add.
    const unsigned int numJobs = 100;

    // Save the original error handler (which is probably null) and always restore it.
    Manager::ErrorHandler original = manager.getErrorHandler();
    USUL_SCOPED_CALL ( ( [ &manager, original ] () { manager.setErrorHandler ( original ); } ) );

    // The exception message.
    const std::string message ( "Throwing exception from inside job" );

    // Set the error handler.
    manager.setErrorHandler ( [ &count, &message ] ( Manager::JobPtr, const std::exception &e )
    {
      ++count;
      REQUIRE ( message == e.what() );
    } );

    // Add several jobs.
    for ( unsigned int i = 0; i < numJobs; ++i )
    {
      manager.addJob ( [ &count, &message ] ( JobPtr )
      {
        // Every other one we throw an exception.
        if ( 0 == ( count % 2 ) )
        {
          throw std::runtime_error ( message );
        }

        // If we get this far then increment the count.
        ++count;
      } );
    }

    // Wait for all the jobs to finish.
    manager.waitAll();

    // This should be true.
    REQUIRE ( numJobs == count );
  }

  SECTION ( "Remove all jobs from inside error handler" )
  {
    // Save the original error handler (which is probably null) and always restore it.
    Manager::ErrorHandler original = manager.getErrorHandler();
    USUL_SCOPED_CALL ( ( [ &manager, original ] () { manager.setErrorHandler ( original ); } ) );

    // The exception message.
    const std::string message ( "Throwing exception from inside job" );

    // Set the error handler.
    manager.setErrorHandler ( [ &manager ] ( Manager::JobPtr job, const std::exception & )
    {
      std::cout << "Job " << job->getID() << " deliberately had an error, cancelling all jobs" << std::endl;

      // Clears the queue of jobs that are still waiting to execute.
      manager.clearQueuedJobs();

      // Cancel any other running jobs (which is just a hint).
      manager.cancelRunningJobs();

      // Note: Do not call manager.destroy() in here because it causes a dead-lock.
    } );

    // Add several jobs that spin until they are cancelled.
    for ( unsigned int i = 0; i < ( manager.getMaxNumThreadsAllowed() - 1 ); ++i )
    {
      manager.addJob ( [] ( JobPtr job )
      {
        while ( false == job->isCancelled() )
        {
          // Sleep some to simulate a lengthy task.
          std::this_thread::sleep_for ( std::chrono::milliseconds ( 50 ) );

          std::cout << "Job " << job->getID() << " is doing work" << std::endl;
        }

        std::cout << "Job " << job->getID() << " has been cancelled" << std::endl;
      } );
    }

    // Let the above jobs get started.
    std::this_thread::sleep_for ( std::chrono::milliseconds ( 100 ) );

    // Add one more job that will throw an exception.
    manager.addJob ( [] ( JobPtr job )
    {
      throw std::runtime_error ( Usul::Strings::format ( "Job ", job->getID(), " is throwing an exception" ) );
    } );

    // Wait for all the jobs to finish.
    manager.waitAll();
  }
}
