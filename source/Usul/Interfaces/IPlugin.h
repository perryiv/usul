
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Adam Kubach
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Interface for a plugin.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_INTERFACES_PLUGIN_H_
#define _USUL_INTERFACES_PLUGIN_H_

#include "Usul/Interfaces/IUnknown.h"

#include <string>


namespace Usul {
namespace Interfaces {


struct IPlugin : public Usul::Interfaces::IUnknown
{
  // Smart-pointer definitions.
  USUL_DEFINE_QUERY_POINTERS ( IPlugin );

  // Id for this interface.
  enum { IID = 1551585493 };

  // Get a description string.
  virtual std::string               getPluginDescription() const = 0;

  // Get the name of the plugin.
  virtual std::string               getPluginName() const = 0;

  // Tell the plugin to initialize.
  virtual void                      initializePlugin() = 0;

  // Tell the plugin to get ready to be released.
  virtual void                      finalizePlugin() = 0;
};


} // namespace Interfaces
} // namespace Usul


#endif // _USUL_INTERFACES_PLUGIN_H_
