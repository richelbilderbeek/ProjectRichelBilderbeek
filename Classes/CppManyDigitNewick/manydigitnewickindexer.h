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
#ifndef MANYDIGITNEWICKINDEXER_H
#define MANYDIGITNEWICKINDEXER_H

#include <cassert>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "manydigitnewick.h"
//#include "manydigitnewickcoordinat.h"
#include "manydigitnewickderivative.h"
#include "manydigitnewickindextable.h"
#include "manydigitnewicks.h"
#include "multivector.h"
#include "newickvector.h"
#pragma GCC diagnostic pop

namespace ribi {

///ManyDigitNewickIndexer converts any newick to (X,Y,...)
struct ManyDigitNewickIndexer
{
  typedef ManyDigitNewickDerivative Derivative;

  //ManyDigitNewickIndexer constructor does all the work
  ManyDigitNewickIndexer(const NewickVector& n, const double theta);

  ///ConstructNewick constructs a full NewickVector from
  ///the ManyDigitNewick at index i.
  ///ConstructNewick is for debugging purposes only,
  ///as it's the idea to work with non-full determined
  ///(that is: two-digit) Newicks
  const NewickVector ConstructNewick(const int i) const;

  int GetCalculatedToIndex() const { return m_calculated_to_index; }
  ///GetData allows a peek at the data
  const ManyDigitIndexTable& GetIndexTable() const
  {
    return m_index_table;
  }
  const ManyDigitNewick& GetNewick(const int i) const
  {
    return m_newicks.GetNewick(i);
  }
  const ManyDigitNewick& GetNewick(const std::vector<int>& indices) const;
  const ManyDigitNewicks& GetNewicks() const
  {
    return m_newicks;
  }
  ///GetProbability returns the probability of the NewickVector
  ///given at the constructor
  double GetProbability() const;

  int GetReserved() const { return m_reserved; }


  ///After a leaf has been cut, then
  void TryToCalculateNewNewicks();
  void UpdateCalculatedFromIndex();


  private:
  ManyDigitIndexTable m_index_table;
  ManyDigitNewicks m_newicks;
  const double m_theta;
  const int m_reserved;
  int m_current_index;
  int m_calculated_to_index;

  ///m_probability is the probability of the given Newick.
  ///m_probability is calculated in the constructor of ManyDigitNewickIndexer
  ///and can be obtained by GetProbability.
  double m_probability;

  ///Calculate the Newick probability of Newick (a,b).
  ///Both a and b are simple, that is: no index
  ///for a complex Newick
  //double CalculateEwensProbability(
  //  const int a,const int b) const;

  ///CalculateReserved calculates the index
  ///that must be reserver
  int CalculateReserved(const NewickVector& n) const;

  const ManyDigitNewick CreateManyDigitDerivatives(
    const ManyDigitNewickCoordinat& coordinat,
    const int sum_above_zero,
    const int sum_above_one);

  ///GetDeltaSumAboveZero calculates the delta in the
  ///ManyDigitNewick::m_sum_above_zero of a new Newick
  ///when an old_value is changed.
  int GetDeltaSumAboveZero(const int old_value) const;

  ///GetDeltaSumAboveOne calculates the delta in the
  ///ManyDigitNewick::m_sum_above_one of a new Newick
  ///when an old_value is changed.
  int GetDeltaSumAboveOne(const Derivative& d) const;
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
    const ManyDigitNewickCoordinat& coordinat,
    const int sum_above_zero,
    const int sum_above_one);

  ///TryToCalculateNewNewick tries to calculate the probability
  ///of Newick with index i
  void TryToCalculateNewNewick(const int i);

  //static bool IsSorted(const std::vector<int>& v);
};

} //~namespace ribi

#endif //MANYDIGITNEWICKINDEXER_H
