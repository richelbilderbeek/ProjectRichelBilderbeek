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
#ifndef MANYDIGITINDEXTABLE_H
#define MANYDIGITINDEXTABLE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Weffc++"
#include <vector>
#include "multivector.h"
#include "manydigitnewickcoordinat.h"
#pragma GCC diagnostic push

namespace ribi {

///ManyDigitIndexTable manages (X,Y) -> index
struct ManyDigitIndexTable
{
  typedef ManyDigitNewickCoordinat Coordinat;

  ///CanGetIndex returns if GetIndex can be called with success
  bool CanGetIndex(const Coordinat& indices) const;

  ///Find returns the x-y-coordinats of the Newick with index i
  ///This is a linear (in this case, relatively time-intensive) method.
  const Coordinat Find(const int i) const;

  ///Get returns the internals of ManyDigitIndexTable
  const MultiVector<int>& Get() const { return m_v; }

  ///GetIndex returns m_index_table[x][y]
  int GetIndex(const Coordinat& indices) const;

  ///GetNumAllocated calculates the number of indices allocated
  //int GetNumAllocated() const;
  ///GetNumUsed calculates the number of indices used
  //int GetNumUsed() const;
  ///Set (x,y) to index z
  void SetIndex(const Coordinat& coordinat, const int value);
  private:
  ///m_index_table is the index table that maps (x,y) to a value,
  ///so that m_index_table[x][y] equals that value
  MultiVector<int> m_v;


  static const std::vector<int> FindInternal(
    const std::vector<int>& indices,
    const MultiVector<int>& v,
    const int value);
};

} //~namespace ribi

#endif // MANYDIGITINDEXTABLE_H
