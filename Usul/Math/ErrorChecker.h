
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Error-checking class that throws.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_ERROR_CHECKER_H_
#define _USUL_MATH_ERROR_CHECKER_H_

#include <stdexcept>


#ifndef USUL_CHECK_INDEX_RANGE
#define USUL_CHECK_INDEX_RANGE(size,index)\
{\
  if ( ( index < 0 ) || ( index >= size ) )\
  {\
    throw std::out_of_range ( "Index out of range" );\
  }\
}
#endif // USUL_CHECK_INDEX_RANGE


#endif // _USUL_MATH_ERROR_CHECKER_H_
