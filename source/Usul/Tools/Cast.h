
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
      // Temporarily disable the warning we get when compiling with the
      // pedantic flag. This happens with some versions of gcc.
      #ifdef __GNUC__
      # pragma GCC diagnostic push
      # pragma GCC diagnostic ignored "-Wpedantic"
      #endif

      // Do the cast.
      return ( ( ToType ) from );

      // Put things back where we found them.
      #ifdef __GNUC__
      # pragma GCC diagnostic pop
      #endif
    }
  }
}


#define USUL_UNSAFE_CAST(to_type,from_object)\
  Usul::Tools::unsafeCast < to_type > ( from_object )


#endif // _USUL_TOOLS_UNSAFE_CAST_H_
