
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, 2019, Perry L Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Predicate classes to test if two floating-point numbers are "close".
//  See Bruce Dawson's paper [1] for details.
//
//  In most cases, this approach is much better than specifying a tolerance
//  because, as Chris Lomont asserts in [2], "...the tolerance required
//  depends on the size of the values being tested."
//
//  Lomont's paper describes a solution that executes faster than Dawson's,
//  but is the method platform independent?
//
//  Dawson's code [3] had a default value of 10 for numAdjacentValues.
//
//  [1] http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
//  [2] http://www.lomont.org/Math/Papers/2005/CompareFloat.pdf
//  [3] ftp://ftp.cygnus-software.com/pub/comparecode.zip
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_CLOSE_FLOAT_H_
#define _USUL_MATH_CLOSE_FLOAT_H_

#include "Usul/Math/Base.h"

#include <cstdint>
#include <cmath>
#include <iostream>


namespace Usul {
namespace Math {


///////////////////////////////////////////////////////////////////////////////
//
//  Helper functions for close-float functor below.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  inline std::int32_t handleTwosCompliment ( std::int32_t v )
  {
    return ( ( v < 0 ) ? ( 0x80000000 - v ) : v );
  }
  inline std::int64_t handleTwosCompliment ( std::int64_t v )
  {
    return ( ( v < 0 ) ? ( 0x8000000000000000ull - v ) : v );
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Type-traits for close-float functor below.
//
///////////////////////////////////////////////////////////////////////////////

namespace Detail
{
  template < class FloatType > struct IntegerSelector;
  template <> struct IntegerSelector < float >
  {
    typedef std::int32_t SignedInteger;
    typedef std::uint32_t UnsignedInteger;
  };
  template <> struct IntegerSelector < double >
  {
    typedef std::int64_t SignedInteger;
    typedef std::uint64_t UnsignedInteger;
  };
  template <> struct IntegerSelector < long double >
  {
    // Without this it may select for double, and we do not support that.
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  Returns true if given floating-point values are "close".
//
//  Single precision floating point numbers are an interpretation of a
//  sequence of 32 "bit", typically rendered with ones and zeros.
//
//  At any given floating point number we can increment or decrement by the
//  smallest bit, which gives us our next "closest" floating point number.
//
///////////////////////////////////////////////////////////////////////////////

template < class FloatType_ > struct CloseFloat
{
  // Useful typedefs.
  typedef FloatType_ FloatType;
  typedef Detail::IntegerSelector < FloatType > IntegerSelector;
  typedef typename IntegerSelector::SignedInteger SignedInteger;
  typedef typename IntegerSelector::UnsignedInteger UnsignedInteger;
  typedef CloseFloat < FloatType > ThisType;

  // Make this predicate adaptable.
	typedef FloatType first_argument_type;
	typedef FloatType second_argument_type;
	typedef bool result_type;

  // Let the compiler make copy constructor and assignment operator.
  // Note: previous default of 10 was causing std::map::find to return false
  // but then std::map::insert would return an existing value, when this class
  // was used with LessVector as the map's comparison predicate. Not exactly
  // sure why but tightening up the specified difference made the problem go away.
  explicit CloseFloat ( unsigned int numAdjacentValues ) : _numAdjacentValues ( numAdjacentValues )
  {
  }

  // Compare the two numbers.
  // This is an implementation of LomontCompare1 from [2] (see references above).
  // The variable numAdjacentValues is known as "unites in last place" or ULP
  // in the literature.
  static bool compare ( FloatType a, FloatType b, UnsignedInteger numAdjacentValues )
  {
    // They are close if they are exact.
    if ( a == b )
    {
      // std::cout << "They are exact" << std::endl;
      return true;
    }

    // If either are NAN, then they cannot be equal, even if they are identical.
    if ( std::isnan ( a ) || std::isnan ( b ) )
    {
      std::cout << "One or both is nan" << std::endl;
      return false; // TODO: Make this a policy using a template argument.
    }

    // If either are infinity, then they are "close" iff they are exact.
    if ( ( false == std::isfinite ( a ) ) || ( false == std::isfinite ( b ) ) )
    {
      std::cout << "One or both is not finite" << std::endl;
      return a == b; // TODO: Make this a policy using a template argument.
    }

    // Interpret the memory as a signed integer.
    SignedInteger ia ( *( reinterpret_cast < SignedInteger * > ( &a ) ) );
    SignedInteger ib ( *( reinterpret_cast < SignedInteger * > ( &b ) ) );

    std::cout << "ia = " << ia << "\nib = " << ib << std::endl;

    // Make them lexicographically ordered as a twos-complement int.
    ia = Detail::handleTwosCompliment ( ia );
    ib = Detail::handleTwosCompliment ( ib );

    // See how far apart a and b are.
    const UnsignedInteger diff ( static_cast < UnsignedInteger > ( Usul::Math::absolute ( ia - ib ) ) );

#ifdef _DEBUG

    if ( diff <= numAdjacentValues )
    {
      if ( a != b )
      {
        return true; // "Close" but not equal.
      }
    }

#endif

    // They are "close" if the difference is within the specified amount.
    return ( diff <= numAdjacentValues );
  }

  bool operator () ( FloatType a, FloatType b ) const
  {
    return ThisType::compare ( a, b, _numAdjacentValues );
  }

protected:

  UnsignedInteger _numAdjacentValues;
};


///////////////////////////////////////////////////////////////////////////////
//
//  Helper function.
//
///////////////////////////////////////////////////////////////////////////////

template < class FloatType, class UnsignedIntegerType  >
bool isCloseFloat ( FloatType a, FloatType b, UnsignedIntegerType numAdjacentValues )
{
  typedef CloseFloat < FloatType > CloseFloatType;
  return CloseFloatType::compare ( a, b, numAdjacentValues );
}


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_CLOSE_FLOAT_H_
