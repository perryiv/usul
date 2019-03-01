
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Intrusive-pointer functions. Keep these in global namespace. These names
//  are compatable with boost::intrusive_ptr.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_POINTERS_INTRUSIVE_POINTER_FUNCTIONS_H_
#define _USUL_POINTERS_INTRUSIVE_POINTER_FUNCTIONS_H_


template < class T > inline void intrusive_ptr_add_ref ( T *ptr )
{
  if ( ptr )
  {
    ptr->ref();
  }
}
template < class T > inline void intrusive_ptr_release ( T *ptr )
{
  if ( ptr )
  {
    ptr->unref();
  }
}
template < class T > inline void ptr_release_no_delete ( T *ptr )
{
  if ( ptr )
  {
    ptr->unref ( false );
  }
}


#endif // _USUL_POINTERS_INTRUSIVE_POINTER_FUNCTIONS_H_
