
################################################################################
#
#  Copyright (c) 2021, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  CMake functions.
#
################################################################################


################################################################################
#
#  Function to print the package property.
#
################################################################################

function(print_property)
  if ( NOT "${${ARGV0}_${ARGV1}}" STREQUAL "" )
    message ( "   <> ${ARGV0}_${ARGV1} = ${${ARGV0}_${ARGV1}}" )
  endif()
endfunction()


################################################################################
#
#  Function to print the package information.
#
################################################################################

function(print_package)
  print_property ( ${ARGV0} "FOUND" )
  print_property ( ${ARGV0} "VERSION" )
  print_property ( ${ARGV0} "INCLUDE_DIRS" )
  print_property ( ${ARGV0} "INCLUDES" )
  print_property ( ${ARGV0} "DEFINITIONS" )
  print_property ( ${ARGV0} "LIBRARIES" )
  print_property ( ${ARGV0} "BUILD_MODULES" )
  print_property ( ${ARGV0} "SYSTEM_LIBS" )
endfunction()
