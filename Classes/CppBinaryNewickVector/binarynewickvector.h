//---------------------------------------------------------------------------
/*
BinaryNewickVector, class to store a Newick as a std::vector<int>
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppBinaryNewickVector.htm
//---------------------------------------------------------------------------
#ifndef RIBI_BINARYNEWICKVECTOR_H
#define RIBI_BINARYNEWICKVECTOR_H

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

///BinaryNewickVector manages a std::vector<int> resembling
///a binary Newick.
struct BinaryNewickVector
{
  BinaryNewickVector(const std::string& s);
  BinaryNewickVector(const std::vector<int>& v);

  double CalcDenominator(const double theta) const;
  const BigInteger CalcNumOfCombinations() const;
  const BigInteger CalcNumOfSymmetries() const;
  double CalcProbabilitySimpleNewick(const double theta) const;
  bool Empty() const { return m_v.empty(); }

  ///Peek at the implementation
  const std::vector<int>& Peek() const noexcept { return m_v; }
  const std::vector<BinaryNewickVector> GetSimplerNewicks() const;
  const std::pair<BinaryNewickVector,BinaryNewickVector> GetRootBranches() const;
  bool IsSimple() const;
  std::string ToStr() const noexcept;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  int Size() const noexcept;


  private:
  std::vector<int> m_v;

  static double CalculateProbabilityInternal(
    const BinaryNewickVector& n,
    const double theta,
    NewickStorage<BinaryNewickVector>& storage);

  bool IsCloseBracketRight(const int pos) const;
  bool IsOpenBracketLeft(const int pos) const;
  const BinaryNewickVector LoseBrackets(const int x, const int i) const;
  const BinaryNewickVector TermIsNotOne(const int i) const;
  const BinaryNewickVector TermIsOne(const int i) const;

  public:
  static double CalculateProbability(
    const std::string& newick_str,
    const double theta);

  static void Test() noexcept;

  static bool NewickCompare(
    const std::vector<int>& lhs,
    const std::vector<int>& rhs) noexcept;

};

bool operator<(
  const BinaryNewickVector& lhs,
  const BinaryNewickVector& rhs) noexcept;

} //~namespace ribi

#endif // RIBI_BINARYNEWICKVECTOR_H
