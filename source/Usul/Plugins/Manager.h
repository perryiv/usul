
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

#ifndef _USUL_PLUGINS_MANAGER_CLASS_H_
#define _USUL_PLUGINS_MANAGER_CLASS_H_

#include "Usul/Export.h"
#include "Usul/Interfaces/IUnknown.h"
#include "Usul/Plugins/Library.h"
#include "Usul/Pointers/Pointers.h"
#include "Usul/Tools/NoCopying.h"

#include <iosfwd>
#include <mutex>
#include <vector>


namespace Usul {
namespace Plugins {


class USUL_EXPORT Manager : public Usul::Tools::NoCopying
{
public:

  // Useful typedefs.
  typedef Usul::Interfaces::IUnknown IUnknown;
  typedef std::vector < IUnknown::RefPtr > Plugins;
  typedef std::vector < Library::RefPtr > Libraries;
  typedef std::vector < std::string > Strings;
  typedef std::lock_guard < std::mutex > Guard;

  // Get the singleton interface.
  static Manager &instance();

  // Add a plugin.
  void add ( IUnknown::RefPtr );

  // Remove all the plugins.
  void removeAll ( std::ostream *out = nullptr );

  // Find the first plugin that implements the interface or matches the predicate.
  IUnknown::RefPtr                      findFirst ( unsigned long iid ) const;
  template < class P > IUnknown::RefPtr findFirstIf ( P pred ) const;

  // Find all the plugins that implement the interface.
  void                      findAll ( unsigned long iid, Plugins & ) const;
  template < class P > void findAllIf ( P pred, Plugins & ) const;

  // Return list of plugin names.
  Strings getNames ( bool sort = true ) const;

  // Load the library.
  void load ( const std::string &file );

  // Print message about loaded plugins.
  void print ( std::ostream & ) const;

  // Reset the manager to the initial state.
  void reset();

  // Unload all the libraries.
  void unloadAll ( std::ostream *out = nullptr );

private:

  Manager();
  ~Manager();

  void _copy ( Plugins & ) const;
  void _copyAndClear ( Plugins & );
  void _copyAndClear ( Libraries & );

  void _destroy();

  mutable std::mutex _mutex;
  Plugins _plugins;
  Libraries _libraries;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Find the first plugin that matches the predicate.
//
///////////////////////////////////////////////////////////////////////////////

template < class P > inline Usul::Interfaces::IUnknown::RefPtr Manager::findFirstIf ( P pred ) const
{
  Plugins plugins;
  this->_copy ( plugins );

  for ( Plugins::iterator i = plugins.begin(); i != plugins.end(); ++i )
  {
    IUnknown::RefPtr plugin ( *i );
    if ( true == pred ( plugin ) )
    {
      return plugin;
    }
  }
  return IUnknown::RefPtr ( nullptr );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Find all the plugins that match the predicate.
//
///////////////////////////////////////////////////////////////////////////////

template < class P > inline void Manager::findAllIf ( P pred, Plugins &answer ) const
{
  Plugins plugins;
  this->_copy ( plugins );

  answer.clear();
  answer.reserve ( plugins.size() );

  for ( Plugins::iterator i = plugins.begin(); i != plugins.end(); ++i )
  {
    IUnknown::RefPtr plugin ( *i );
    if ( true == pred ( plugin ) )
    {
      answer.push_back ( plugin );
    }
  }
}


} // namespace Plugins
} // namespace Usul


#endif // _USUL_PLUGINS_MANAGER_CLASS_H_
