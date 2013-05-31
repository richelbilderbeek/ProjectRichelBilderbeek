//---------------------------------------------------------------------------
/*
TestTwoDigitNewick, tool to test the two-digit-Newick architecture
Copyright (C) 2010 Richel Bilderbeek

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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "twodigitnewickindextable.h"

//---------------------------------------------------------------------------
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <sstream>
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
///CanGetData returns is GetData can be called with success
bool TwoDigitNewickIndexTable::CanGetIndex(const int x, const int y) const
{
  return x < boost::numeric_cast<int>(m_v.size())
      && y < boost::numeric_cast<int>(m_v[x].size());
}
//---------------------------------------------------------------------------
///Find returns the x-y-coordinats of the Newick with index i
const std::pair<int,int> TwoDigitNewickIndexTable::Find(const int i) const
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
  std::cerr << "Index " << i << " not found in TwoDigitNewickIndexTable::Find\n";
  assert(!"Should not get here");
  std::stringstream s;
  s << "Index " << i << " not found in TwoDigitNewickIndexTable::Find";
  throw std::logic_error(s.str());
}
//---------------------------------------------------------------------------
///GetIndex returns m_index_table[x][y]
int TwoDigitNewickIndexTable::GetIndex(const int x, const int y) const
{
  assert(CanGetIndex(x,y));
  return m_v[x][y];
}
//---------------------------------------------------------------------------
///GetNumAllocated calculates the number of indices allocated
int TwoDigitNewickIndexTable::GetNumAllocated() const
{
  int n_allocated = 0;
  BOOST_FOREACH(const std::vector<int>& v,m_v)
  {
    n_allocated+=boost::numeric_cast<int>(v.size());
  }
  return n_allocated;
}
//---------------------------------------------------------------------------
///GetNumUsed calculates the number of indices used
int TwoDigitNewickIndexTable::GetNumUsed() const
{
  int n_non_zero = 0;
  BOOST_FOREACH(const std::vector<int>& v,m_v)
  {
    n_non_zero +=std::count_if(v.begin(),v.end(),
      std::bind2nd(std::greater<int>(),0));
  }
  return n_non_zero;
}
//---------------------------------------------------------------------------
///SetIndex sets m_index_table[x][y] == z
///and resized the m_index_table is necessary
void TwoDigitNewickIndexTable::SetIndex(
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
//---------------------------------------------------------------------------
