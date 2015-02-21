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
#ifndef MANYDIGITNEWICKS_H
#define MANYDIGITNEWICKS_H

#include <vector>

#include "manydigitnewick.h"

namespace ribi {

///ManyDigitNewicks manages ManyDigitManyDigitNewicks.
///ManyDigitManyDigitNewicks manage F'(index) -> { indices }
struct ManyDigitNewicks
{
  typedef ManyDigitNewickDerivative Derivative;

  ManyDigitNewicks(const int n_reserved, const double theta);
  ///Empty returns if m_v is empty
  ///Set a Newick at index i
  ///\warning: do not use push_back, because of recursive calls
  void SetNewick(const int i, const ManyDigitNewick& v);
  bool Empty() const { return m_v.empty(); }
  ///Empty returns if an index is empty
  bool Empty(const int i) const;
  ///Get returns the internals of ManyDigitNewicks
  const std::vector<ManyDigitNewick>& Get() const { return m_v; }
  ///GetNewick returns the Newick at index i.
  ///i is checked for its range.
  const ManyDigitNewick& GetNewick(const int i) const;
  ///Sets the derivatives of F(i) to { v }
  //void SetDerivatives(const int i,const ManyDigitNewick& v);
  ///Obtain the number of Derivatives

  ///SetNewickProbability sets the probability of the Newick
  ///at index i to p
  void SetNewickProbability(const int i,const double p);

  int Size() const;
private:
  ///m_derivatives contains for every indexed Newick
  ///its derived indexed ManyDigitNewicks
  std::vector<ManyDigitNewick> m_v;
};

} //~namespace ribi

#endif // MANYDIGITNEWICKS_H
