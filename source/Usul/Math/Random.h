
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Random number generation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_RANDOM_FUNCTIONS_H_
#define _USUL_MATH_RANDOM_FUNCTIONS_H_

#include <cstdlib>
#include <type_traits>


namespace Usul {
namespace Math {


///////////////////////////////////////////////////////////////////////////////
//
//  Generate a random floating-point number between the given range.
//
///////////////////////////////////////////////////////////////////////////////

namespace { namespace Details
{
  template < class T > struct Random
  {
    static void get ( const T &mn, const T &mx, T &answer )
    {
      // Make sure we're working with a floating point number type.
      typedef T Number;
      static_assert ( std::is_floating_point < Number >::value, "Not a floating-point number type" );

      // Shortcut.
      const Number randMax = static_cast < Number > ( RAND_MAX );

      // A random number between 0 and 1.
      const Number value = static_cast < Number > ( std::rand() ) / randMax;

      // Assign the adjusted value.
      answer = ( mn + ( value * ( mx - mn ) ) );
    }
  };
} }


///////////////////////////////////////////////////////////////////////////////
//
//  Generate a random float between the given range.
//
///////////////////////////////////////////////////////////////////////////////

inline void random ( float &answer, const float &mn = 0.0f, const float &mx = 1.0f )
{
  typedef Details::Random < float > Random;
  return Random::get ( mn, mx, answer );
}
inline float random ( const float &mn = 0.0f, const float &mx = 1.0f )
{
  float answer ( 0.0f );
  random ( answer, mn, mx );
  return answer;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Generate a random double between the given range.
//
///////////////////////////////////////////////////////////////////////////////

inline void random ( double &answer, const double &mn = 0.0, const double &mx = 1.0 )
{
  typedef Details::Random < double > Random;
  return Random::get ( mn, mx, answer );
}
inline double random ( const double &mn = 0.0, const double &mx = 1.0 )
{
  double answer ( 0.0 );
  random ( answer, mn, mx );
  return answer;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Generate a random long double between the given range.
//
///////////////////////////////////////////////////////////////////////////////

inline void random ( long double &answer, const long double &mn = 0.0, const long double &mx = 1.0 )
{
  typedef Details::Random < long double > Random;
  return Random::get ( mn, mx, answer );
}
inline long double random ( const long double &mn = 0.0, const long double &mx = 1.0 )
{
  long double answer ( 0.0 );
  random ( answer, mn, mx );
  return answer;
}


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_RANDOM_FUNCTIONS_H_
