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
#ifndef TWODIGITNEWICKINDEXER_H
#define TWODIGITNEWICKINDEXER_H

#include <cassert>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "twodigitnewickindextable.h"
#include "twodigitnewicks.h"
#include "twodigitnewick.h"
#include "binarynewickvector.h"
#pragma GCC diagnostic pop

namespace ribi {

///NewickIndex converts any newick to (X,Y)
struct TwoDigitNewickIndexer
{
  //TwoDigitNewickIndexer constructor does all the work
  TwoDigitNewickIndexer(const BinaryNewickVector& n, const double theta);

  ///ConstructNewick constructs a full BinaryNewickVector from
  ///the TwoDigitNewick at index i.
  ///ConstructNewick is for debugging purposes only,
  ///as it's the idea to work with non-full determined
  ///(that is: two-digit) Newicks
  const BinaryNewickVector ConstructNewick(const int i) const;

  int GetCalculatedToIndex() const { return m_calculated_to_index; }
  ///GetData allows a peek at the x-y ordered data
  const TwoDigitNewickIndexTable& GetIndexTable() const
  {
    return m_index_table;
  }
  const TwoDigitNewick& GetNewick(const int i) const
  {
    return m_newicks.GetNewick(i);
  }
  const TwoDigitNewick& GetNewick(const int x, const int y) const
  {
    assert(m_index_table.CanGetIndex(x,y));
    const int i = m_index_table.GetIndex(x,y);
    return GetNewick(i);
  }
  const TwoDigitNewicks& GetNewicks() const
  {
    return m_newicks;
  }
  ///GetProbability returns the probability of the BinaryNewickVector
  ///given at the constructor
  double GetProbability() const;

  int GetReserved() const { return m_reserved; }


  ///After a leaf has been cut, then
  void TryToCalculateNewNewicks();
  void UpdateCalculatedFromIndex();


  private:

  int m_calculated_to_index;
  int m_current_index;
  TwoDigitNewickIndexTable m_index_table;
  TwoDigitNewicks m_newicks;

  ///m_probability is the probability of the given Newick.
  ///m_probability is calculated in the constructor of TwoDigitNewickIndexer
  ///and can be obtained by GetProbability.
  double m_probability;

  const int m_reserved;
  const double m_theta;

  ///Calculate the Newick probability of Newick (a,b).
  ///Both a and b are simple, that is: no index
  ///for a complex Newick
  //double CalculateEwensProbability(
  //  const int a,const int b) const;

  ///CalculateReserved calculates the index
  ///that must be reserver
  int CalculateReserved(const BinaryNewickVector& n) const;

  const TwoDigitNewick CreateTwoDigitNewickDerivatives(const int x, const int y,
    const int sum_above_zero,
    const int sum_above_one);

  const TwoDigitNewick CreateTwoDigitNewickDerivativesSimpleSimple(
    const int x,
    const int y);

  const TwoDigitNewick CreateTwoDigitNewickDerivativesSimpleComplex(
    const int x,
    const int y,
    const int sum_above_zero,
    const int sum_above_one);

  const TwoDigitNewick CreateTwoDigitNewickDerivativesComplexComplex(
    const int x,
    const int y,
    const int sum_above_zero,
    const int sum_above_one);

  ///GetDeltaSumAboveZero calculates the delta in the
  ///TwoDigitNewick::m_sum_above_zero of a new Newick
  ///when an old_value is changed.
  int GetDeltaSumAboveZero(const int old_value) const;

  ///GetDeltaSumAboveOne calculates the delta in the
  ///TwoDigitNewick::m_sum_above_one of a new Newick
  ///when an old_value is changed.
  int GetDeltaSumAboveOne(const TwoDigitNewickDerivative& d) const;
  //int GetDeltaSumAboveOne(const int old_value) const;


  ///IsSimple determines if a Newick at index i is simple.
  ///A Newick is simple if F=(X,Y) where X and Y are
  ///less than the reserved index
  bool IsSimple(const int i) const;

  ///Feed the (x,y) indices of a Newick and obtain the
  ///summarized index.
  ///Feed also obtains the derived Newicks.
  ///Note that Feed must be fed simple Newicks first
  ///int Feed(const int x, const int y)
  int SummarizeNewick(
    const int x, const int y,
    const int sum_above_zero,
    const int sum_above_one);

  ///TryToCalculateNewNewick tries to calculate the probability
  ///of Newick with index i
  void TryToCalculateNewNewick(const int i);

};

///IsSimple determines if a binary Newick is simple,
//that is in the form '(X,Y)', where both X and Y are values
//bool IsSimple(const BinaryNewickVector& n);

} //namespace ribi

#endif // TWODIGITNEWICKINDEXER_H
