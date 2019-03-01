
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Convenient (and safe) reference and dereference.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_POINTERS_SAFE_REFERENCE_FUNCTIONS_H_
#define _USUL_POINTERS_SAFE_REFERENCE_FUNCTIONS_H_


namespace Usul
{
  namespace Pointers
  {
    template < class T > inline void reference ( T *ptr )
    {
      if ( ptr )
      {
        ptr->ref();
      }
    }
    template < class T > inline void unreference ( T *ptr )
    {
      if ( ptr )
      {
        ptr->unref();
      }
    }
  }
}


#endif // _USUL_POINTERS_SAFE_REFERENCE_FUNCTIONS_H_
