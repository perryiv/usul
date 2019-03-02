
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

#ifndef _USUL_TESTS_INTERFACES_TEST_2_H_
#define _USUL_TESTS_INTERFACES_TEST_2_H_

#include "Usul/Interfaces/IUnknown.h"


namespace Helpers {


struct ITest2 : public Usul::Interfaces::IUnknown
{
  // Smart-pointer definitions.
  USUL_DEFINE_QUERY_POINTERS ( ITest2 );

  // Id for this interface.
  enum { IID = 1551499920u };

  virtual bool doTest2() = 0;
};


} // namespace Helpers


#endif // _USUL_TESTS_INTERFACES_TEST_2_H_
