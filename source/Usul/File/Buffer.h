
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2006, 2020, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  File buffer class with progress notification.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_FILE_BUFFER_CLASS_
#define _USUL_FILE_BUFFER_CLASS_

#include <cstdint>
#include <ctime>
#include <string>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <type_traits>


namespace Usul {
namespace File {


///////////////////////////////////////////////////////////////////////////////
//
//  Default callback throttle policy.
//
///////////////////////////////////////////////////////////////////////////////

struct ClockThrottlePolicy
{
  ClockThrottlePolicy() :
    _start ( static_cast < double > ( std::clock() ) ),
    _delay ( 100.0 )
  {
  }

  bool shouldReportProgress ( std::uint64_t, std::uint64_t )
  {
    const double now = static_cast < double > ( std::clock() );
    const double milliseconds = 1000.0 * ( now - _start ) / CLOCKS_PER_SEC;

    if ( milliseconds > _delay )
    {
      _start = now;
      return true;
    }

    return false;
  }

  // Get/set the delay in milliseconds.
  double getDelay() const { return _delay; }
  void   setDelay ( double delay ) { _delay = delay; }

private:

  double _start;
  double _delay;
};


///////////////////////////////////////////////////////////////////////////////
//
//  File buffer class.
//
///////////////////////////////////////////////////////////////////////////////

template < class CharType, class ThrottlePolicyType = ClockThrottlePolicy >
class Buffer: public std::basic_filebuf < CharType, std::char_traits < CharType > >
{
public:

  typedef std::basic_filebuf < CharType, std::char_traits < CharType > > BaseClass;
  typedef std::function < void ( std::uint64_t, std::uint64_t ) > ProgressFunction;
  typedef ThrottlePolicyType ThrottlePolicy;
  typedef typename BaseClass::char_type char_type;
  typedef typename BaseClass::int_type int_type;
  typedef typename BaseClass::pos_type pos_type;

  //
  // Constructor.
  //
  explicit Buffer ( const std::string &file ) : BaseClass(),
    _size ( 0 ),
    _count ( 0 ),
    _throttle(),
    _progress()
  {
    // Should be true.
    static_assert ( ( std::is_same < CharType, char_type > ::value ),          "Inconsistent character types" );
    static_assert ( ( sizeof ( std::uint64_t ) >= sizeof ( std::uintptr_t ) ), "A 64-bit integer cannot safely hold a pointer" );

    // Try to open the file.
    if ( nullptr == this->open ( file.c_str(), std::ios_base::in | std::ios_base::binary ) )
    {
      throw std::runtime_error ( std::string ( "Error 2836857267: Could not open file: " ) + file );
    }

    // Determine the size of the file by seeking to the end.
    const pos_type size = this->pubseekoff ( 0, std::ios_base::end, std::ios_base::in );

    // Handle negative position.
    // On Mac static asserts for pos_type being unsigned and integral failed.
    if ( size < 0 )
    {
      throw std::runtime_error ( std::string ( "Error 1590612853: Negative file size for: " ) + file );
    }

    // This cast should always be valid because we already checked sizes above.
    _size = static_cast < std::uint64_t > ( size );

    // Put the cursor back at the beginning.
    this->pubseekoff ( 0, std::ios_base::beg, std::ios_base::in );
  }

  //
  // Get/set the progress function.
  //
  const ProgressFunction getProgressFunction() const { return _progress; }
  void                   setProgressFunction ( ProgressFunction fun ) { _progress = fun; }

  //
  // Get/set the throttle.
  //
  const ThrottlePolicy &getThrottlePolicy() const { return _throttle; }
  ThrottlePolicy &      getThrottlePolicy()       { return _throttle; }
  void                  setThrottlePolicy ( ThrottlePolicy policy ) { _throttle = policy; }

  //
  // Get the file size.
  //
  std::uint64_t getFileSize() const { return _size; }

protected:

  //
  // Call the progress functor if there is one.
  //
  template < class T >
  void _notifyProgressFunction ( T count )
  {
    // This should be a valid cast because we already checked sizes above.
    _count += static_cast < std::uint64_t > ( count );

    // Throttle the calls to the progress function.
    if ( _throttle.shouldReportProgress ( _count, _size ) )
    {
      // If there is a progress callback ...
      if ( _progress )
      {
        // Call the progress function.
        _progress ( _count, _size );
      }
    }
  }

  // #ifdef __APPLE__

  //
  // Overloaded to monitor progress.
  //
  virtual std::streamsize xsgetn ( char_type *s, std::streamsize count )
  {
    const std::streamsize answer = BaseClass::xsgetn ( s, count ); // Call this first.
    this->_notifyProgressFunction ( answer );
    return answer;
  }

  // #elif _WIN32
  //
  // //
  // // Overloaded to monitor progress.
  // //
  // virtual int_type uflow()
  // {
  //   const int_type answer = BaseClass::uflow(); // Call this first.
  //   this->_notifyProgressFunction ( this->egptr() - this->gptr() ); // End minus the current.
  //   return answer;
  // }
  //
  // #else // Linux
  //
  // //
  // // Overloaded to monitor progress.
  // //
  // virtual int_type underflow()
  // {
  //   const int_type answer = BaseClass::underflow(); // Call this first.
  //   this->_notifyProgressFunction ( this->egptr() - this->gptr() ); // End minus the current.
  //   return answer;
  // }
  //
  // #endif

private:

  std::uint64_t _size;
  std::uint64_t _count;
  ThrottlePolicy _throttle;
  ProgressFunction _progress;
};


} // namespace File
} // namespace Usul


#endif // _USUL_FILE_BUFFER_CLASS_
