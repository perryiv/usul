
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Interface for testing.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_TESTS_INTERFACES_TEST_1_H_
#define _USUL_TESTS_INTERFACES_TEST_1_H_

#include "Usul/Interfaces/IUnknown.h"


namespace Helpers {


struct ITest1 : public Usul::Interfaces::IUnknown
{
  // Smart-pointer definitions.
  USUL_DEFINE_QUERY_POINTERS ( ITest1 );

  // Id for this interface.
  enum { IID = 1551497265u };

  virtual bool doTest1() = 0;
};


} // Helpers


#endif // _USUL_TESTS_INTERFACES_TEST_1_H_
