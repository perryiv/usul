
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Redirect stdout and stderr to a file.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_FILE_H_
#define _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_FILE_H_

#include "Usul/IO/Redirect/Base.h"

#include <fstream>
#include <sstream>
#include <stdexcept>


namespace Usul {
namespace IO {
namespace Redirect {


struct File : public Base
{
  File ( const std::string &name, bool deleteFile = true ) : Base(),
    _name ( name ),
    _out ( name.c_str(), std::ofstream::out | std::ofstream::app ),
    _deleteFile ( deleteFile )
  {
    if ( false == _out.is_open() )
    {
      std::ostringstream message;
      message << "Failed to open file '" << name << "' for appending when redirecting standard streams";
      throw std::runtime_error ( message.str() );
    }

    this->_setOutputStream ( _out );
  }

  ~File()
  {
    if ( true == _deleteFile )
    {
      _out.close();
      std::remove ( _name.c_str() );
    }
  }

  std::string getContents() const
  {
    typedef std::istreambuf_iterator < char > Itr;
    std::ifstream in ( _name.c_str() );
    return std::string ( ( Itr ( in ) ), Itr() );
  }

private:

  const std::string _name;
  std::ofstream _out;
  const bool _deleteFile;
};


} // namespace Redirect
} // namespace IO
} // namespace Usul


#endif // _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_FILE_H_
