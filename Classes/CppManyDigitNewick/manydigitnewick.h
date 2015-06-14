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
#ifndef MANYDIGITNEWICK_H
#define MANYDIGITNEWICK_H

#include <string>
#include <vector>

#include "manydigitnewickderivative.h"

namespace ribi {

///ManyDigitNewick contains all
///ManyDigitDerivative that can be
///constructed from a phylogeny. For example,
///if from a certain phylogeny three derived
///phylogenies can be constructed, ManyDigitDerivativesData
///will hold three elements.
///The algorithm is described at
///http://www.richelbilderbeek.nl/CppTwoDigitNewickAlgorithm.htm
///
///The meat of the code is in ManyDigitNewick::CalculateProbability
struct ManyDigitNewick
{
  typedef ManyDigitNewickDerivative Derivative;

  //An empty ManyDigitNewick
  ManyDigitNewick();

  ///A ManyDigitNewick cannot be created without
  ///its derivatives: a ManyDigitNewick IS its
  ///derivatives in a way.
  ///sum_above_zero and sum_above_one are needed to
  ///calculate its denominator
  explicit ManyDigitNewick(
    const std::vector<Derivative>& derivatives,
    const int sum_above_zero,
    const int sum_above_one);

  ///Empty returns !IsComplete
  bool Empty() const noexcept;

  const std::vector<Derivative>& GetDerivatives() const noexcept;
  ///IsComplete determines if the ManyDigitNewick is
  ///initialized completely
  bool IsComplete() const;
  bool IsProbabilityKnown() const noexcept;
  double GetDenominator() const;
  double GetProbability() const;
  int GetSumTermsAboveOne() const;
  int GetSumTermsAboveZero() const;
  void SetProbability(const double p);
  static void SetTheta(const double theta);

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  ///m_derivatives contains all the information
  ///needed to get to this Newick's derivatives
  std::vector<Derivative> m_derivatives;

  ///m_probability denotes the probability
  ///a Newick exists.
  ///A negative value of m_probability denotes
  ///that it is not yet calculated.
  double m_probability;

  ///m_denominator constant for a Newick.
  double m_denominator;

  int m_sum_terms_above_zero;
  int m_sum_terms_above_one;

  static double sm_theta;

  double CalculateDenominator(
    const int sum_above_zero,
    const int sum_above_one) const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  public:

  static double CalculateProbability(
    const std::string& newick,
    const double theta);


};

} //~namespace ribi

#endif // TWODIGITNEWICK_H

