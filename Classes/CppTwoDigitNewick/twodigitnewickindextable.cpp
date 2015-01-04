//---------------------------------------------------------------------------
/*
TestTwoDigitNewick, tool to test the two-digit-Newick architecture
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "twodigitnewickindextable.h"


#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <sstream>


#include <boost/numeric/conversion/cast.hpp>

#pragma GCC diagnostic pop

///CanGetData returns is GetData can be called with success
bool ribi::TwoDigitNewickIndexTable::CanGetIndex(const int x, const int y) const
{
  return x < boost::numeric_cast<int>(m_v.size())
      && y < boost::numeric_cast<int>(m_v[x].size());
}

///Find returns the x-y-coordinats of the Newick with index i
const std::pair<int,int> ribi::TwoDigitNewickIndexTable::Find(const int i) const
{
  const int maxx = boost::numeric_cast<int>(m_v.size());
  for (int x=0; x!=maxx; ++x)
  {
    const int maxy = boost::numeric_cast<int>(m_v[x].size());
    for (int y=0; y!=maxy; ++y)
    {
      if (m_v[x][y]==i) return std::make_pair(x,y);
    }
  }
  std::cerr << "Index " << i << " not found in ribi::TwoDigitNewickIndexTable::Find\n";
  assert(!"Should not get here");
  std::stringstream s;
  s << "Index " << i << " not found in ribi::TwoDigitNewickIndexTable::Find";
  throw std::logic_error(s.str());
}

///GetIndex returns m_index_table[x][y]
int ribi::TwoDigitNewickIndexTable::GetIndex(const int x, const int y) const
{
  assert(CanGetIndex(x,y));
  return m_v[x][y];
}

///GetNumAllocated calculates the number of indices allocated
int ribi::TwoDigitNewickIndexTable::GetNumAllocated() const
{
  int n_allocated = 0;
  for(const std::vector<int>& v: m_v)
  {
    n_allocated+=boost::numeric_cast<int>(v.size());
  }
  return n_allocated;
}

///GetNumUsed calculates the number of indices used
int ribi::TwoDigitNewickIndexTable::GetNumUsed() const
{
  int n_non_zero = 0;
  for(const std::vector<int>& v: m_v)
  {
    n_non_zero +=std::count_if(v.begin(),v.end(),
      std::bind2nd(std::greater<int>(),0));
  }
  return n_non_zero;
}

///SetIndex sets m_index_table[x][y] == z
///and resized the m_index_table is necessary
void ribi::TwoDigitNewickIndexTable::SetIndex(
  const int x,
  const int y,
  const int z)
{
  //Does x have a proper std::vector?
  if (x >= boost::numeric_cast<int>(m_v.size()))
  {
    m_v.resize(x + 1,std::vector<int>());
  }
  if (y >= boost::numeric_cast<int>(m_v[x].size()))
  {
    m_v[x].resize(y + 1,0);
  }
  assert(m_v[x][y] == 0);
  assert(z > 0);
  m_v[x][y] = z;
  assert(m_v[x][y] > 0);
}

