
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Redirect stdout and stderr to a string.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_STRING_H_
#define _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_STRING_H_

#include "Usul/IO/Redirect/Base.h"

#include <sstream>


namespace Usul {
namespace IO {
namespace Redirect {


struct String : public Base
{
  String() : Base(),
    _out()
  {
    this->_setOutputStream ( _out );
  }

  ~String()
  {
  }

  std::string getContents() const
  {
    return _out.str();
  }

private:

  std::ostringstream _out;
};


} // namespace Redirect
} // namespace IO
} // namespace Usul


#endif // _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_STRING_H_
