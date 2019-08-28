
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  For working with bits.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_BITS_H_
#define _USUL_BITS_H_


namespace Usul {
namespace Bits {


//////////////////////////////////////////////////////////////////////////
//
//  See if the "bits" are in "number".
//
//////////////////////////////////////////////////////////////////////////

template < class N, class B > inline bool has ( N number, B bits )
{
  return ( ( number & bits ) == ( static_cast < N > ( bits ) ) );
}


//////////////////////////////////////////////////////////////////////////
//
//  Add the "bits" to "number".
//
//////////////////////////////////////////////////////////////////////////

template < class N, class B > inline N add ( N number, B bits )
{
  return ( number | bits );
}


//////////////////////////////////////////////////////////////////////////
//
//  Remove the "bits" from "number".
//
//////////////////////////////////////////////////////////////////////////

template < class N, class B > inline N remove ( N number, B bits )
{
  return ( ( number & bits ) ? ( number ^ bits ) : number );
}


//////////////////////////////////////////////////////////////////////////
//
//  Toggle the "bits" in "number".
//
//////////////////////////////////////////////////////////////////////////

template < class N, class B > inline N toggle ( N number, B bits )
{
  return ( number ^ bits );
}


//////////////////////////////////////////////////////////////////////////
//
//  Set the "bits" in "number".
//
//////////////////////////////////////////////////////////////////////////

template < class N, class B > inline N set ( N number, B bits, bool state )
{
  return ( ( state ) ? Usul::Bits::add ( number, bits ) : Usul::Bits::remove ( number, bits ) );
}


} // namespace Bits
} // namespace Usul


#endif // _USUL_BITS_H_
