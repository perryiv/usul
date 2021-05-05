
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2021, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Redirect stdout and stderr to a callback function.
//
//  https://stackoverflow.com/questions/30970385/capturing-and-raising-events-on-stdcout-flush-events
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_CALLBACK_FUNCTION_H_
#define _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_CALLBACK_FUNCTION_H_

#include "Usul/IO/Redirect/Base.h"

#include <functional>
#include <sstream>
#include <string>


namespace Usul {
namespace IO {
namespace Redirect {


namespace Details
{
  struct FunctionBuffer : public std::stringbuf
  {
    typedef std::stringbuf BaseClass;
    typedef BaseClass::int_type IntType;
    typedef BaseClass::char_type CharType;
    typedef BaseClass::traits_type TraitsType;
    typedef std::function < void ( const std::string & ) > Fun;

    FunctionBuffer ( Fun fun ) : BaseClass(), _fun ( fun )
    {
      // this->pubsetbuf ( nullptr, 0 );
    }

    virtual ~FunctionBuffer()
    {
    }

  protected:

    virtual std::streamsize xsputn ( const CharType *s, std::streamsize count ) override
    {
      if ( ( nullptr != s ) && ( count > 0 ) && ( _fun ) )
      {
        const std::string temp ( s, s + count );
        _fun ( temp );
      }
      return count;
    }

    // virtual IntType overflow ( IntType c ) override
    // {
    //   if ( _fun )
    //   {
    //     const std::string s ( &c, &c + 1 );
    //     _fun ( s );
    //   }
    //   return BaseClass::overflow ( c );
    //   // if ( !TraitsType::eq_int_type ( c, TraitsType::eof() ) )
    //   // {
    //   //   CharType *ptr = this->pptr();
    //   //   if ( nullptr != ptr )
    //   //   {
    //   //     CharType &current = *ptr;
    //   //     current = TraitsType::to_char_type ( c );
    //   //     this->pbump ( 1 );
    //   //   }
    //   // }
    //   //
    //   // return ( ( this->sync() ) ? TraitsType::not_eof ( c ) : TraitsType::eof() );
    // }

    // virtual int_type sync() override
    // {
    //   if ( this->pbase() != this->pptr() )
    //   {
    //     if ( _fun )
    //     {
    //       const std::string s ( this->pbase(), this->pptr() );
    //       _fun ( s );
    //     }
    //     this->setp ( this->pbase(), this->epptr() );
    //   }
    //   return 0;
    // }

  private:

    Fun _fun;
  };
}


struct Callback : public Base
{
  typedef Details::FunctionBuffer FunctionBuffer;
  typedef FunctionBuffer::Fun Function;

  Callback ( Function fun ) : Base(), _buffer ( fun )
  {
    this->_setOutputBuffer ( &_buffer );
  }

  ~Callback()
  {
    // Do this before our buffer gets deleted.
    this->_restore();
  }

private:

  Details::FunctionBuffer _buffer;
};


} // namespace Redirect
} // namespace IO
} // namespace Usul


#endif // _USUL_IO_REDIRECT_STANDARD_OUTPUT_TO_CALLBACK_FUNCTION_H_
