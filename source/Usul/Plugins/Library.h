
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

#ifndef _USUL_PLUGINS_LIBRARY_CLASS_H_
#define _USUL_PLUGINS_LIBRARY_CLASS_H_

#include "Usul/Base/Referenced.h"
#include "Usul/Pointers/Pointers.h"
#include "Usul/Tools/NoCopying.h"

#include <string>


namespace Usul {
namespace Plugins {


class USUL_EXPORT Library :
  public Usul::Base::Referenced,
  public Usul::Tools::NoCopying
{
public:

  // Typedefs.
  typedef Usul::Base::Referenced BaseClass;
  typedef void * Function;
  typedef void * ModuleHandle;

  // Smart pointers.
  USUL_REFERENCED_CLASS ( Library );

  // Construction.
  Library ( const std::string &path );

  // Get the library's file name.
  const std::string &   getFileName() const { return _file; }

  // Get a pointer to the function.
  Function              getFunction ( const std::string &name ) const;

protected:

  // Only construct on the heap. Use reference counting.
  virtual ~Library();

private:

  void                  _free();

  ModuleHandle _module;
  const std::string _file;
};


} // namespace Plugins
} // namespace Usul


#endif // _USUL_PLUGINS_LIBRARY_CLASS_H_
