
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Class that represents a dynamically loaded library.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Plugins/Library.h"
#include "Usul/File/Functions.h"
#include "Usul/Tools/Cast.h"
#include "Usul/Tools/NoThrow.h"
#include "Usul/Strings/Format.h"
#include "Usul/System/LastError.h"

#ifdef _WIN32
# define NOMINMAX
# define VC_EXTRALEAN
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#else
# include <dlfcn.h>
#endif

#include <functional>

typedef Usul::System::LastError LastError;

namespace Usul {
namespace Plugins {


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Library::Library ( const std::string &file ) : BaseClass(),
  _module ( nullptr ),
  _file ( file )
{
  // Initialize the last error.
  LastError::init();

  // Must have valid file name.
  if ( true == _file.empty() )
  {
    throw std::invalid_argument ( "Empty file name given when loading library" );
  }

  // File must be readable.
  if ( false == Usul::File::isReadable ( _file ) )
  {
    throw std::invalid_argument ( Usul::Strings::format
      ( "Library file '", _file, ", does not exist" ) );
  }

#ifdef _MSC_VER
  _module = reinterpret_cast < ModuleHandle > ( ::LoadLibrary ( _file.c_str() ) );
#else
  _module = reinterpret_cast < ModuleHandle > ( ::dlopen ( _file.c_str(), RTLD_LAZY | RTLD_GLOBAL ) );
#endif

  // See if it worked.
  if ( nullptr == _module )
  {
    throw std::runtime_error ( Usul::Strings::format (
      "Failed to load library: ", _file,
      ", System error number: ", LastError::number(),
      ", System error message: ", LastError::message() ) );
  }

  // Get the debug function. Note: some versions of g++ do not allow a
  // reinterpret_cast when compiling with pedantic flag.
  typedef bool ( *DebugFunction )();
  DebugFunction isDebugBuild ( Usul::Tools::unsafeCast < DebugFunction > ( this->getFunction ( "usul_is_debug_build" ) ) );

  // If we found it then use it.
  if ( nullptr != isDebugBuild )
  {
  #ifdef _DEBUG
    if ( false == isDebugBuild() )
  #else
    if ( true == isDebugBuild() )
  #endif
    {
      throw std::runtime_error ( Usul::Strings::format
        ( "Mismatched build mode in library: ", _file ) );
    }
  }

  // Look for the function used to initialize a plugin.
  typedef void ( *Initialize )();
  Initialize initialize ( Usul::Tools::unsafeCast < Initialize > ( this->getFunction ( "usul_plugin_initialize" ) ) );

  // If we found it then call it.
  if ( nullptr != initialize )
  {
    initialize();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Library::~Library()
{
  USUL_TOOLS_NO_THROW ( 1568933600, std::bind ( &Library::_free, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Free the library.
//  This is only called from the destructor so no need for a mutex.
//
///////////////////////////////////////////////////////////////////////////////

void Library::_free()
{
  // Handle null modules.
  if ( nullptr == _module )
  {
    return;
  }

  typedef void ( *Finalize )();

  // Look for the function to finalize a plugin before we delete _module.
  Finalize finalize ( Usul::Tools::unsafeCast < Finalize > ( this->getFunction ( "usul_plugin_finalize" ) ) );

  // If we found the finalize function then call it.
  if ( nullptr != finalize )
  {
    finalize();
  }

  // Initialize the last error.
  LastError::init();

#ifdef _MSC_VER
  bool result ( 0 != ::FreeLibrary ( reinterpret_cast < HMODULE > ( _module ) ) );
#else
  bool result ( 0 == ::dlclose ( reinterpret_cast < void * > ( _module ) ) );
#endif

  // Make sure it worked.
  if ( false == result )
  {
    throw std::runtime_error ( Usul::Strings::format (
      "Failed to free library '", _file,
      ", System error number: ", LastError::number(),
      ", System error message: ", LastError::message() ) );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the address of the function.
//  This is read-only so no need for a mutex.
//
///////////////////////////////////////////////////////////////////////////////

Library::Function Library::getFunction ( const std::string &name ) const
{
  // Handle bad input.
  if ( name.empty() )
  {
    return nullptr;
  }

  // Handle bad module.
  if ( nullptr == _module )
  {
    return nullptr;
  }

#ifdef _WIN32
  return reinterpret_cast < Function > ( ::GetProcAddress ( reinterpret_cast < HMODULE > ( _module ), name.c_str() ) );
#else
  return reinterpret_cast < Function > ( ::dlsym ( reinterpret_cast < void * > ( _module ), name.c_str() ) );
#endif
}


} // namespace Plugins
} // namespace Usul
