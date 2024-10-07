
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Functions for casting.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <limits>
#include <stdexcept>
#include <type_traits>


namespace Usul
{
  namespace Tools
  {
    //
    //  So that c-style casts are easy to find.
    //
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

    //
    //	Helper classes.
    //
    template < class ToType, class FromType > struct CanCast;
    template <> struct CanCast < unsigned int, std::size_t >
    {
      typedef std::size_t FromType;
      typedef unsigned int ToType;

      typedef std::numeric_limits < ToType > ToTypeLimits;
      typedef std::numeric_limits < FromType > FromTypeLimits;

      static bool canCastTo ( FromType from )
      {
        static_assert ( std::is_integral_v < FromType > );
        static_assert ( std::is_integral_v < ToType > );
        static_assert ( std::is_unsigned_v < FromType > );
        static_assert ( std::is_unsigned_v < ToType > );

        // We're trying to go from a large unsigned type to a smaller one.
        static_assert ( sizeof ( FromType ) >= sizeof ( ToType ) );

        return ( from <= ( static_cast < FromType > ( ToTypeLimits::max() ) ) );
      }
    };
    template <> struct CanCast < double, std::uint64_t >
    {
      typedef std::uint64_t FromType;
      typedef double ToType;

      typedef std::numeric_limits < ToType > ToTypeLimits;
      typedef std::numeric_limits < FromType > FromTypeLimits;

      static bool canCastTo ( FromType from )
      {
        static_assert ( std::is_integral_v < FromType > );
        static_assert ( std::is_floating_point_v < ToType > );
        static_assert ( std::is_unsigned_v < FromType > );
        static_assert ( std::is_floating_point_v < ToType > );

        static_assert ( sizeof ( FromType ) == sizeof ( ToType ) );

        return ( from <= ( static_cast < FromType > ( ToTypeLimits::max() ) ) );
      }
    };

    //
    //	Make sure we can safely cast.
    //
    template < class ToType, class FromType >
    inline bool canCastTo ( FromType from )
    {
      typedef CanCast < ToType, FromType > LocalType;
      return LocalType::canCastTo ( from );
    }

    //
    //	Safely cast. Throws an exception if there will be an overflow.
    //
    template < class ToType, class FromType >
    inline bool safeCastTo ( FromType from )
    {
      if ( false == canCastTo < ToType > ( from ) )
      {
        throw std::invalid_argument ( "Invalid cast" );
      }
      return ( static_cast < ToType > ( from ) );
    }
  }
}


//
//  So that c-style casts are easy to find.
//
#define USUL_UNSAFE_CAST(to_type,from_object)\
  Usul::Tools::unsafeCast < to_type > ( from_object )
