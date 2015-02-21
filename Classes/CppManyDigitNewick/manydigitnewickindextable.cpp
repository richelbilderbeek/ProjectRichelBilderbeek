//---------------------------------------------------------------------------
/*
ManyDigitNewick, Newick class
Copyright (C) 2011-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppManyDigitNewick.htm
//---------------------------------------------------------------------------


#include "manydigitnewickindextable.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <sstream>


#include <boost/numeric/conversion/cast.hpp>

///CanGetData returns is GetData can be called with success
bool ribi::ManyDigitIndexTable::CanGetIndex(const Coordinat& coordinat) const
{
  return m_v.CanRetrieve(coordinat.ToVector());
}

const ribi::ManyDigitNewickCoordinat ribi::ManyDigitIndexTable::Find(
  const int value) const
{
  //Check indices
  {
    const auto begin = m_v.PeekIndices().begin();
    const auto end   = m_v.PeekIndices().end();
    const auto x = std::find(begin,end,value);
    if (x!=end)
    {
      const int index_found = std::distance(begin,x);
      assert(index_found >= 0);
      assert(index_found < boost::numeric_cast<int>(m_v.PeekIndices().size()));
      return Coordinat( { index_found } );
    }
  }

  //Check MultiVector
  const std::vector<MultiVector<int> >& mvs
    = m_v.PeekMultiVectors();
  const int size = mvs.size();
  for (int i=0; i!=size; ++i)
  {

    const auto result
      = FindInternal(
          std::vector<int>(1,i),
          mvs[i],
          value);
    if (!result.empty())
    {
      return Coordinat(result);
    }
  }

  assert(!"Should not get here");
  std::stringstream s;
  s << "Value " << value << " not found in ribi::ManyDigitIndexTable::Find";
  throw std::logic_error(s.str());
}

const std::vector<int> ribi::ManyDigitIndexTable::FindInternal(
  const std::vector<int>& indices,
  const MultiVector<int>& v,
  const int value)
{
  //Check indices
  {
    const auto begin = v.PeekIndices().begin();
    const auto end   = v.PeekIndices().end();
    const auto x = std::find(begin,end,value);
    if (x!=end)
    {
      const int index_found = std::distance(begin,x);
      assert(index_found >= 0);
      assert(index_found < boost::numeric_cast<int>(v.PeekIndices().size()));
      std::vector<int> result = indices;
      result.push_back(index_found);
      return result;
    }
  }

  //Check MultiVector
  const auto& mvs = v.PeekMultiVectors();
  const int size = mvs.size();
  for (int i=0; i!=size; ++i)
  {
    std::vector<int> indices_deeper = indices;
    indices_deeper.push_back(i);
    const auto result
      = FindInternal(
        indices_deeper,mvs[i],value);
    if (!result.empty()) return result;
  }
  return std::vector<int>();
}

///GetIndex returns m_index_table[x][y]
int ribi::ManyDigitIndexTable::GetIndex(const ManyDigitNewickCoordinat& indices) const
{
  assert(CanGetIndex(indices));
  return m_v.Retrieve(indices.ToVector());
}

///GetNumAllocated calculates the number of indices allocated
//int ribi::ManyDigitIndexTable::GetNumAllocated() const
//{
//  int n_allocated = 0;
//  for(const MultiVector<int>& v: m_v.PeekMultiVectors())
//  {
//    n_allocated+=boost::numeric_cast<int>(v.size());
//  }
//  return n_allocated;
//}

///GetNumUsed calculates the number of indices used
//int ribi::ManyDigitIndexTable::GetNumUsed() const
//{
//  int n_non_zero = 0;
//  for(const MultiVector<int>& v: m_v.PeekMultiVectors())
//  {
//    n_non_zero +=
//      std::count_if(
//        v.PeekIndices().begin(),
//        v.PeekIndices().end(),
//        std::bind2nd(std::greater<int>(),0));
//  }
//  return n_non_zero;
//}

///SetIndex sets m_index_table[x][y] == z
///and resized the m_index_table is necessary
void ribi::ManyDigitIndexTable::SetIndex(
  const ManyDigitNewickCoordinat& indices,
  const int value)
{
  assert(value > 0);
  assert(
    !m_v.CanRetrieve(indices.ToVector())
    || m_v.Retrieve(indices.ToVector()) == 0);
  m_v.Store(indices.ToVector(),value);
  assert(m_v.Retrieve(indices.ToVector()) == value);
}

