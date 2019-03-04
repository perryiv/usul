
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Functions for files.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_FILE_FUNCTIONS_H_
#define _USUL_FILE_FUNCTIONS_H_

#include <fstream>

namespace Usul {
namespace File {


///////////////////////////////////////////////////////////////////////////////
//
//  See if the file can be read.
//  https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
//
///////////////////////////////////////////////////////////////////////////////

inline bool isReadable ( const std::string &name )
{
  if ( !name.empty() )
  {
    std::ifstream file ( name.c_str() );
    return file.good();
  }

  return false;
}


} // namespace File
} // namespace Usul


#endif // _USUL_FILE_FUNCTIONS_H_