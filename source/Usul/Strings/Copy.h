
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Functions for copying raw strings.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_STRINGS_COPY_H_
#define _USUL_STRINGS_COPY_H_

#include "Usul/Export.h"


namespace Usul {
namespace Strings {


struct USUL_EXPORT Copy
{
  static char *copy ( const char * );
};


inline char *copy ( const char *s ) { return Copy::copy ( s ); }


} // namespace Strings
} // namespace Usul


#endif // _USUL_STRINGS_COPY_H_
