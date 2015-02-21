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
#ifndef TWODIGITNEWICKINDEXERTABLE_H
#define TWODIGITNEWICKINDEXERTABLE_H

#include <vector>

namespace ribi {

///TwoDigitNewickIndexTable manages (X,Y) -> index
struct TwoDigitNewickIndexTable
{
  ///CanGetIndex returns if GetIndex can be called with success
  bool CanGetIndex(const int x, const int y) const;
  ///Find returns the x-y-coordinats of the Newick with index i
  const std::pair<int,int> Find(const int i) const;
  ///Get returns the internals of TwoDigitNewickIndexTable
  const std::vector<std::vector<int> >& Get() const { return m_v; }
  ///GetIndex returns m_index_table[x][y]
  int GetIndex(const int x, const int y) const;
  ///GetNumAllocated calculates the number of indices allocated
  int GetNumAllocated() const;
  ///GetNumUsed calculates the number of indices used
  int GetNumUsed() const;
  ///Set (x,y) to index z
  void SetIndex(const int x, const int y, const int z);
  private:
  ///m_index_table is the index table that maps (x,y) to a value,
  ///so that m_index_table[x][y] equals that value
  std::vector<std::vector<int> > m_v;
};

} //~namespace ribi

#endif // TWODIGITNEWICKINDEXERTABLE_H
