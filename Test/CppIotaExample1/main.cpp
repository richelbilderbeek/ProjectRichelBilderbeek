#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// Numeric functions implementation -*- C++ -*-

// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
// Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/**
 *  @brief  Create a range of sequentially increasing values.
 *
 *  For each element in the range @p [first,last) assigns @p value and
 *  increments @p value as if by @p ++value.
 *
 *  @param  first  Start of range.
 *  @param  last  End of range.
 *  @param  value  Starting value.
 *  @return  Nothing.
 */
template<typename _ForwardIterator, typename _Tp>
  void iota(_ForwardIterator __first, _ForwardIterator __last, _Tp __value)
{
  // concept requirements
  __glibcxx_function_requires(_Mutable_ForwardIteratorConcept<
    _ForwardIterator>)
  __glibcxx_function_requires(_ConvertibleConcept<_Tp,
    typename iterator_traits<_ForwardIterator>::value_type>)
     __glibcxx_requires_valid_range(__first, __last);
  for (; __first != __last; ++__first)
  {
  *__first = __value;
  ++__value;
  }
}

int main()
{
  std::vector<int> v(10,0);

  iota(v.begin(),v.end(),0);

  std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
}

/* Screen output:
 
0 1 2 3 4 5 6 7 8 9 

*/