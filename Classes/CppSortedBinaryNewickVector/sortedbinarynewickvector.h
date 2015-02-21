//---------------------------------------------------------------------------
/*
  The Rampal Etienne Project, calculates the probability of a phylogeny
  (C) 2009-2015 Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef SORTEDBINARYNEWICKVECTOR_H
#define SORTEDBINARYNEWICKVECTOR_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "binarynewickvector.h"
#include "newick.h"
#pragma GCC diagnostic pop

namespace ribi {

//A SortedBinaryNewickVector is a ShortNewick with its internal storage hided
//All functions that needed a ShortNewick's internals
//  are members of SortedBinaryNewickVector
struct SortedBinaryNewickVector
{
  SortedBinaryNewickVector(const SortedBinaryNewickVector& rhs);
  SortedBinaryNewickVector(const BinaryNewickVector& rhs);
  SortedBinaryNewickVector(const std::vector<int>& any_v);

  bool Empty() const { return m_v.empty(); }
  double CalcDenominator(const double theta) const;
  double CalcProbabilitySimpleNewick(const double theta) const;
  bool IsSimple() const;
  int Size() const { return m_v.size(); }

  const SortedBinaryNewickVector TermIsNotOne(const int i) const;
  const SortedBinaryNewickVector TermIsOne(const int i) const;
  const SortedBinaryNewickVector LoseBrackets(const int x,const int i) const;

  const std::vector<int>& Peek() const { return m_v;}
  std::string ToStr() const;

  private:
  std::vector<int> m_v;
   bool IsCloseBracketRight(const int pos) const;
   bool IsOpenBracketLeft(const int pos) const;

  friend  bool operator<(const SortedBinaryNewickVector& lhs, const SortedBinaryNewickVector& rhs);
  void Sort();
  const std::vector<int> Sort(
    const std::vector<int>::const_iterator b,
    const std::vector<int>::const_iterator e) const;

  static int FindPosBefore(const std::vector<int>& v,const int x, const int index);
  static int FindPosAfter(const std::vector<int>& v,const int x, const int index);

  public:

  static double CalculateProbability(
    const std::string& newick_str,
    const double theta);

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  static bool NewickCompare(
    const std::vector<int>& lhs,
    const std::vector<int>& rhs);

};

bool operator<(const SortedBinaryNewickVector& lhs, const SortedBinaryNewickVector& rhs);

//const std::string ToString(const SortedBinaryNewickVector& n,
//  const bool add_brackets = true);

} //~namespace ribi

#endif //SORTEDBINARYNEWICKVECTOR_H
