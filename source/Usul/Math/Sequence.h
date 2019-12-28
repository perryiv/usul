
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2019, Perry L Miller IV
//  All rights reserved.
//  MIT License: https://opensource.org/licenses/mit-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Math functions for sequences scalars and vectors.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _USUL_MATH_SEQUENCE_FUNCTIONS_H_
#define _USUL_MATH_SEQUENCE_FUNCTIONS_H_

#include "Usul/Math/Matrix44.h"
#include "Usul/Math/Vector3.h"

#include <vector>


namespace Usul {
namespace Math {


/////////////////////////////////////////////////////////////////////////////
//
//  Transform the sequence of vec3 elements.
//  Note: a and b can be the same vector.
//
/////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void transform ( const Matrix44 < T, I > &m, const std::vector < Vector3 < T, I > > &a, std::vector < Vector3 < T, I > > &b )
{
  // Shortcuts.
  typedef std::vector < Vector3 < T, I > > Sequence;
  typedef typename Sequence::size_type Size;

  // Needed below.
  const Size num = a.size();

  // Resize if we have to.
  // This also handles the case when a and b are the same vector.
  if ( b.size() != num )
  {
    b.resize ( num );
  }

  // Loop through the sequence.
  for ( Size i = 0; i < num; ++i )
  {
    Usul::Math::multiply ( m, a[i], b[i] );
  }
}
template < class T, class I >
inline void transform ( const Matrix44 < T, I > &m, std::vector < Vector3 < T, I > > &a )
{
  transform ( m, a, a );
}


/////////////////////////////////////////////////////////////////////////////
//
//  Normalize the sequence of vec3 elements.
//  Note: a and b can be the same vector.
//
/////////////////////////////////////////////////////////////////////////////

template < class T, class I >
inline void normalize ( const std::vector < Vector3 < T, I > > &a, std::vector < Vector3 < T, I > > &b )
{
  // Shortcuts.
  typedef std::vector < Vector3 < T, I > > Sequence;
  typedef typename Sequence::size_type Size;

  // Needed below.
  const Size num = a.size();

  // Resize if we have to.
  // This also handles the case when a and b are the same vector.
  if ( b.size() != num )
  {
    b.resize ( num );
  }

  // Loop through the sequence.
  for ( Size i = 0; i < num; ++i )
  {
    Usul::Math::normalize ( a[i], b[i] );
  }
}
template < class T, class I >
inline void normalize ( std::vector < Vector3 < T, I > > &a )
{
  normalize ( a, a );
}


} // namespace Math
} // namespace Usul


#endif // _USUL_MATH_SEQUENCE_FUNCTIONS_H_
