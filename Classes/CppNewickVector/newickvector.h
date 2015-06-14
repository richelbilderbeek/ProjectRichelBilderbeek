//---------------------------------------------------------------------------
/*
NewickVector, class to store a Newick as a std::vector<int>
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
//From http://www.richelbilderbeek.nl/CppNewickVector.htm
//---------------------------------------------------------------------------
#ifndef NEWICKVECTOR_H
#define NEWICKVECTOR_H

#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include "BigIntegerLibrary.hh"
#include "newickstorage.h"
#pragma GCC diagnostic pop

namespace ribi {

///NewickVector manages a std::vector<int> resembling
///a binary Newick.
struct NewickVector
{
  NewickVector(const std::string& s);
  NewickVector(const std::vector<int>& v);

  const BigInteger CalcComplexity() const;
  double CalcDenominator(const double theta) const;
  const BigInteger CalcNumOfCombinations() const;
  const BigInteger CalcNumOfSymmetries() const;
  double CalcProbabilitySimpleNewick(const double theta) const;
  bool Empty() const noexcept { return m_v.empty(); }
  const std::vector<int>& Peek() const noexcept { return m_v; }
  const std::vector<NewickVector> GetSimplerNewicks() const;
  const std::pair<NewickVector,NewickVector> GetRootBranches() const;
  bool IsSimple() const;
  std::string ToStr() const;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  int Size() const noexcept;
  const NewickVector TermIsNotOne(const int i) const;
  const NewickVector TermIsOne(const int i) const;


  private:
  const std::vector<int> m_v; //2013-09-16: made const, perhaps won't compile due to copying now?

  int FindPosAfter(const std::vector<int>& v,const int x, const int index) const;
  int FindPosBefore(const std::vector<int>& v,const int x, const int index) const;
  bool IsCloseBracketRight(const int pos) const;
  bool IsOpenBracketLeft(const int pos) const;
  const NewickVector LoseBrackets(const int x, const int i) const;

  static double CalculateProbabilityInternal(
    const NewickVector& n,
    const double theta,
    NewickStorage<NewickVector>& storage);


  public:

  static double CalculateProbability(
    const std::string& newick_str,
    const double theta);


  static bool NewickCompare(
    const std::vector<int>& lhs,
    const std::vector<int>& rhs) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

bool operator<(
  const NewickVector& lhs,
  const NewickVector& rhs);

} //~namespace ribi

#endif // NEWICKVECTOR_H
