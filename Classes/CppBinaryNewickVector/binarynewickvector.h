//---------------------------------------------------------------------------
/*
BinaryNewickVector, class to store a Newick as a std::vector<int>
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
  BinaryNewickVector(const std::string& s) noexcept;
  BinaryNewickVector(const std::vector<int>& v) noexcept;

  double CalcDenominator(const double theta) const noexcept;
  const BigInteger CalcNumOfCombinations() const noexcept;
  const BigInteger CalcNumOfSymmetries() const noexcept;
  double CalcProbabilitySimpleNewick(const double theta) const noexcept;
  bool Empty() const noexcept { return m_v.empty(); }

  ///Peek at the implementation
  const std::vector<int>& Peek() const noexcept { return m_v; }
  std::vector<BinaryNewickVector> GetSimplerNewicks() const noexcept;
  std::pair<BinaryNewickVector,BinaryNewickVector> GetRootBranches() const noexcept;
  bool IsSimple() const noexcept;
  std::string ToStr() const noexcept;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;
  int Size() const noexcept;


  private:
  std::vector<int> m_v;

  static double CalculateProbabilityInternal(
    const BinaryNewickVector& n,
    const double theta,
    NewickStorage<BinaryNewickVector>& storage
  ) noexcept;

  bool IsCloseBracketRight(const int pos) const noexcept;
  bool IsOpenBracketLeft(const int pos) const noexcept;
  BinaryNewickVector LoseBrackets(const int x, const int i) const noexcept;
  BinaryNewickVector TermIsNotOne(const int i) const noexcept;
  BinaryNewickVector TermIsOne(const int i) const noexcept;

  public:
  static double CalculateProbability(
    const std::string& newick_str,
    const double theta
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  static bool NewickCompare(
    const std::vector<int>& lhs,
    const std::vector<int>& rhs
  ) noexcept;

};

bool operator<(
  const BinaryNewickVector& lhs,
  const BinaryNewickVector& rhs) noexcept;

} //~namespace ribi

#endif // RIBI_BINARYNEWICKVECTOR_H
