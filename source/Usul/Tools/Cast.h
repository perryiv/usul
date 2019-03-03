
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  So that c-style casts are easy to find.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_TOOLS_UNSAFE_CAST_H_
#define _USUL_TOOLS_UNSAFE_CAST_H_


namespace Usul
{
  namespace Tools
  {
    template < class ToType, class FromType >
    inline ToType unsafeCast ( FromType from )
    {
      return ( ( ToType ) from );
    }
  }
}


#define USUL_UNSAFE_CAST(to_type,from_object)\
  Usul::Tools::unsafeCast < to_type > ( from_object )


#endif // _USUL_TOOLS_UNSAFE_CAST_H_
