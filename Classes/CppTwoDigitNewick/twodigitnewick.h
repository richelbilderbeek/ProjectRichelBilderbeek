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
#ifndef TWODIGITNEWICK_H
#define TWODIGITNEWICK_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "twodigitnewickderivative.h"
#pragma GCC diagnostic pop

namespace ribi {

///TwoDigitNewick contains all
///TwoDigitNewickDerivative that can be
///constructed from a phylogeny. For example,
///if from a certain phylogeny three derived
///phylogenies can be constructed, TwoDigitNewickDerivativesData
///will hold three elements
struct TwoDigitNewick
{
  //An empty TwoDigitNewick
  TwoDigitNewick();

  ///A TwoDogitNewick cannot be created without
  ///its derivatives: a TwoDigitNewick IS its
  ///derivatives in a way.
  ///sum_above_zero and sum_above_one are needed to
  ///calculate its denominator
  TwoDigitNewick(
    const std::vector<TwoDigitNewickDerivative>& derivatives,
    const int sum_above_zero,
    const int sum_above_one);

  ///Empty returns !IsComplete
  bool Empty() const;

  const std::vector<TwoDigitNewickDerivative>& GetDerivatives() const;
  ///IsComplete determines if the TwoDigitNewick is
  ///initialized completely
  bool IsComplete() const;
  bool IsProbabilityKnown() const;
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
  std::vector<TwoDigitNewickDerivative> m_derivatives;

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

  public:

  static double CalculateProbability(
    const std::string& newick,
    const double theta);

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // TWODIGITNEWICK_H

