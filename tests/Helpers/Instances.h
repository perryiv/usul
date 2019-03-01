
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  Helper singleton class for keeping track of all referenced instances.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_TEST_HELPER_SINGLETON_INSTANCES_H_
#define _USUL_TEST_HELPER_SINGLETON_INSTANCES_H_

#include <set>

namespace Helpers {


////////////////////////////////////////////////////////////////////////////////
//
//  Singleton class that constains the set of all referenced instances.
//
////////////////////////////////////////////////////////////////////////////////

class Instances
{
public:

  typedef std::set < void * > Set;

  static Instances &get();

  ~Instances();

  void add ( void *ptr ) { _set.insert ( ptr ); }

  void remove ( void *ptr ) { _set.erase ( _set.find ( ptr ) ); }

  Set::size_type size() const { return _set.size(); }

  bool empty() const { return _set.empty(); }

protected:

  Instances();

private:

  Set _set;
};


} // namespace Helpers


#endif // _USUL_TEST_HELPER_SINGLETON_INSTANCES_H_
