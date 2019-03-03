
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Inherit from this class to forbid copying and assignment.
//  Similar to boost::noncopyable.
//  https://stackoverflow.com/questions/31940886/is-there-a-stdnoncopyable-or-equivalent
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_TOOLS_NO_COPYING_CLASS_H_
#define _USUL_TOOLS_NO_COPYING_CLASS_H_


namespace Usul {
namespace Tools {


///////////////////////////////////////////////////////////////////////////////
//
//  Inherit from this class to forbid copying and assignment.
//
///////////////////////////////////////////////////////////////////////////////

struct NoCopying
{
  NoCopying() = default;
  ~NoCopying() = default;

  // These are public so the compiler warns about using deleted functions
  // rather than private ones.
  NoCopying ( const NoCopying & ) = delete;
  NoCopying &operator = ( const NoCopying & ) = delete;
};


} // namespace Tools
} // namespace Usul


#endif // _USUL_TOOLS_NO_COPYING_CLASS_H_
