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
#ifndef MANYDIGITNEWICKCOORDINAT_H
#define MANYDIGITNEWICKCOORDINAT_H

#include <vector>

namespace ribi {

///ManyDigitNewickCoordinat is an any-dimensional
///coordinat with its indices sorted.
struct ManyDigitNewickCoordinat
{
  ManyDigitNewickCoordinat(const std::vector<int>& v);
  const std::vector<int>& ToVector() const { return m_v; }
  bool AllSimple(const int threshold_index) const;

  bool IsSorted() const;
  bool IsValid() const;

  private:
  const std::vector<int> m_v;

  static const std::vector<int> Sort(std::vector<int> v);

};

} //~namespace ribi

#endif // MANYDIGITNEWICKCOORDINAT_H
