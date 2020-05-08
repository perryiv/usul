
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Base class for redirecting stdout and stderr.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_STREAM_H_
#define _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_STREAM_H_

#include <iostream>


namespace Usul {
namespace IO {
namespace Redirect {


struct Base
{
  Base() :
    _cout ( std::cout.rdbuf() ),
    _cerr ( std::cerr.rdbuf() ),
    _clog ( std::clog.rdbuf() )
  {
  }

  ~Base()
  {
    try
    {
      std::cout.rdbuf ( _cout );
      std::cerr.rdbuf ( _cerr );
      std::clog.rdbuf ( _clog );
    }
    catch ( ... )
    {
    }
  }

protected:

  void _setOutputStream ( std::ostream &out )
  {
    std::cout.rdbuf ( out.rdbuf() );
    std::cerr.rdbuf ( out.rdbuf() );
    std::clog.rdbuf ( out.rdbuf() );
  }

private:

  std::streambuf *_cout;
  std::streambuf *_cerr;
  std::streambuf *_clog;
};


} // namespace Redirect
} // namespace IO
} // namespace Usul


#endif // _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_STREAM_H_
