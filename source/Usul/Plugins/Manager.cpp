
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Adam Kubach and Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Manager of plugins.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/Plugins/Manager.h"
#include "Usul/Config.h"
#include "Usul/Tools/NoThrow.h"
#include "Usul/Interfaces/IPlugin.h"
#include "Usul/Strings/Format.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>

typedef Usul::Interfaces::IPlugin IPlugin;

namespace Usul {
namespace Plugins {


///////////////////////////////////////////////////////////////////////////////
//
//  Get the instance. Not thread safe. Call early from one thread.
//
///////////////////////////////////////////////////////////////////////////////

Manager& Manager::instance()
{
  static Manager instance; // Thread-safe construction as of C++11
  return instance;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor
//
///////////////////////////////////////////////////////////////////////////////

Manager::Manager() :
  _mutex(),
  _plugins(),
  _libraries()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor
//
///////////////////////////////////////////////////////////////////////////////

Manager::~Manager()
{
  USUL_TOOLS_NO_THROW ( 1568933601, std::bind ( &Manager::_destroy, this ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destroy this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_destroy()
{
  this->reset();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Reset this instance.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::reset()
{
  this->removeAll ( &std::clog );
  this->unloadAll ( &std::clog );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Finalize the plugin.
//
///////////////////////////////////////////////////////////////////////////////

namespace { namespace Details
{
  inline void finalizePlugin ( Usul::Interfaces::IUnknown::RefPtr unknown, std::ostream *out )
  {
    if ( true == unknown.valid() )
    {
      Usul::Interfaces::IPlugin::QueryPtr plugin ( unknown );
      if ( true == plugin.valid() )
      {
        // Feedback if the caller wants it.
        if ( nullptr != out )
        {
          *out << Usul::Strings::format ( "Releasing plugin: ", plugin->getPluginName(), '\n' ) << std::flush;
        }

        // Tell the plugin it's about to be released.
        plugin->finalizePlugin();
      }
    }
  }
} }


///////////////////////////////////////////////////////////////////////////////
//
//  Finalize the library.
//
///////////////////////////////////////////////////////////////////////////////

namespace { namespace Details
{
  inline void finalizeLibrary ( Library::RefPtr library, std::ostream *out )
  {
    if ( true == library.valid() )
    {
      // Feedback if the caller wants it.
      if ( nullptr != out )
      {
        *out << Usul::Strings::format ( "Releasing library: ", library->getFileName(), '\n' ) << std::flush;
      }
    }
  }
} }


///////////////////////////////////////////////////////////////////////////////
//
//  Add the plugin.
//
//  Note: It's currently possible to add the same plugin more than once.
//  It's not clear how to catch this without sacrificing performance and/or
//  relying on the plugin implementing the IPlugin interface. Also, it's not
//  clear if it will cause a problem if the same plugin is added more than once.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::add ( IUnknown::RefPtr unknown )
{
  if ( true == unknown.valid() )
  {
    Guard guard ( _mutex );
    _plugins.push_back ( unknown );
  }

  IPlugin::QueryPtr plugin ( unknown );
  if ( true == plugin.valid() )
  {
    plugin->initializePlugin();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Remove all the plugins
//
///////////////////////////////////////////////////////////////////////////////

void Manager::removeAll ( std::ostream *out )
{
  // Copy the container and clear our member.
  Plugins plugins;
  this->_copyAndClear ( plugins );

  // Loop through the copy.
  for ( Plugins::iterator i = plugins.begin(); i != plugins.end(); ++i )
  {
    // Reference the plugin.
    IUnknown::RefPtr plugin ( *i );

    // Finalize it. Don't let this throw because we need to keep looping.
    USUL_TOOLS_NO_THROW ( 1568933602, std::bind ( &Details::finalizePlugin, plugin, out ) );
  }

  // Do this now rather than wait for the destructor.
  // It's a little easier to debug.
  plugins.clear();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Load the library.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::load ( const std::string &file )
{
  Library::RefPtr library ( new Library ( file ) );
  Guard guard ( _mutex );
  _libraries.push_back ( library );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Unload all the libraries.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::unloadAll ( std::ostream *out )
{
  // Copy the container and clear our member.
  Libraries libraries;
  this->_copyAndClear ( libraries );

  // Loop through the copy.
  for ( Libraries::iterator i = libraries.begin(); i != libraries.end(); ++i )
  {
    // Reference the library.
    Library::RefPtr library ( *i );

    // Finalize it. Don't let this throw because we need to keep looping.
    USUL_TOOLS_NO_THROW ( 1568933603, std::bind ( &Details::finalizeLibrary, library, out ) );
  }

  // Do this now rather than wait for the destructor.
  // It's a little easier to debug.
  libraries.clear();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Predicate used for finding plugins.
//
///////////////////////////////////////////////////////////////////////////////

namespace { namespace Details
{
  inline bool implementsInterface ( Usul::Interfaces::IUnknown::RefPtr unknown, unsigned long iid )
  {
    if ( true == unknown.valid() )
    {
      return ( nullptr != unknown->queryInterface ( iid ) );
    }
    return false;
  }
} }


///////////////////////////////////////////////////////////////////////////////
//
//  Find the first plugin that matches the interface.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Interfaces::IUnknown::RefPtr Manager::findFirst ( unsigned long iid ) const
{
  return this->findFirstIf ( std::bind ( &Details::implementsInterface, std::placeholders::_1, iid ) );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Find all the plugins that match the predicate.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::findAll ( unsigned long iid, Plugins &answer ) const
{
  this->findAllIf ( std::bind ( &Details::implementsInterface, std::placeholders::_1, iid ), answer );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return list of plugin names.
//
///////////////////////////////////////////////////////////////////////////////

Manager::Strings Manager::getNames ( bool sort ) const
{
  Manager::Strings names;

  Plugins unknowns;
  this->_copy ( unknowns );

  for ( Plugins::iterator i = unknowns.begin(); i != unknowns.end(); ++i )
  {
    IPlugin::QueryPtr plugin ( *i );
    if ( true == plugin.valid() )
    {
      names.push_back ( plugin->getPluginName() );
    }
  }

  if ( true == sort )
  {
    std::sort ( names.begin(), names.end() );
  }

  return names;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Print message about loaded plugins.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::print ( std::ostream &out ) const
{
  std::ostringstream stream;

  const Manager::Strings names ( this->getNames() );
  stream << names.size() << ( ( 1 == names.size() ) ? ( " plugin" ) : ( " plugins" ) );
  if ( false == names.empty() )
  {
    stream << ": ";
    std::copy ( names.begin(), names.end(), std::ostream_iterator<std::string> ( stream, "; " ) );
  }
  stream << '\n';
  out << stream.str() << std::flush;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Copy the container of plugins in a thread-safe way.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_copy ( Plugins &plugins ) const
{
  Guard guard ( _mutex );
  plugins = _plugins;
}
void Manager::_copyAndClear ( Plugins &plugins )
{
  Guard guard ( _mutex );
  plugins = _plugins;
  _plugins.clear();
}


///////////////////////////////////////////////////////////////////////////////
//
//  Copy the container of libraries in a thread-safe way.
//
///////////////////////////////////////////////////////////////////////////////

void Manager::_copyAndClear ( Libraries &libraries )
{
  Guard guard ( _mutex );
  libraries = _libraries;
  _libraries.clear();
}


} // namespace Plugins
} // namespace Usul
