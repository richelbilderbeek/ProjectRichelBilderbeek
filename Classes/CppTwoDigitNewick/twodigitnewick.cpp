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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "twodigitnewick.h"

#include <cassert>
#include <iostream>


#include <boost/numeric/conversion/cast.hpp>

#include "binarynewickvector.h"
#include "newick.h"
#include "twodigitnewickindexer.h"

#pragma GCC diagnostic pop

double ribi::TwoDigitNewick::sm_theta = -1.0;

ribi::TwoDigitNewick::TwoDigitNewick()
  : m_derivatives{},
    m_probability(-1.0),
    m_denominator(-1.0),
    m_sum_terms_above_zero(-1),
    m_sum_terms_above_one(-1)
{
  assert(this->Empty());
}

ribi::TwoDigitNewick::TwoDigitNewick(
  const std::vector<TwoDigitNewickDerivative>& derivatives,
  const int sum_above_zero,
  const int sum_above_one)
  : m_derivatives(derivatives),
    m_probability(-1.0),
    m_denominator(
      CalculateDenominator(sum_above_zero,sum_above_one)),
    m_sum_terms_above_zero(sum_above_zero),
    m_sum_terms_above_one(sum_above_one)
{

}

double ribi::TwoDigitNewick::CalculateDenominator(
  const int sum_above_zero,
  const int sum_above_one) const
{
  assert(sm_theta >= 0.0);
  assert(sum_above_zero >= 0);
  #ifndef NDEBUG
  if (sum_above_one < 0)
  {
    std::cerr << "Invalid sum_above_one: " << sum_above_one << '\n';
  }
  #endif
  assert(sum_above_one >= 0);
  const double d
    = boost::numeric_cast<double>(
      sum_above_zero * (sum_above_zero - 1))
    + (boost::numeric_cast<double>(sum_above_one)
       * sm_theta);

  return d;
}

double ribi::TwoDigitNewick::CalculateProbability(
  const std::string& newick_str,
  const double theta)
{
  assert(Newick().IsUnaryNewick(Newick().StringToNewick(newick_str))
      || Newick().IsBinaryNewick(Newick().StringToNewick(newick_str)));
  ribi::TwoDigitNewick::SetTheta(theta);
  const BinaryNewickVector n(newick_str);
  const TwoDigitNewickIndexer i(n,theta);

  return i.GetProbability();
}

bool ribi::TwoDigitNewick::Empty() const
{
  return m_derivatives.empty();
}

double ribi::TwoDigitNewick::GetDenominator() const
{
  assert(IsComplete());
  return m_denominator;
}

const std::vector<ribi::TwoDigitNewickDerivative>& ribi::TwoDigitNewick::GetDerivatives() const
{
  return m_derivatives;
}

double ribi::TwoDigitNewick::GetProbability() const
{
  assert(IsProbabilityKnown());
  return m_probability;
}

int ribi::TwoDigitNewick::GetSumTermsAboveOne() const
{
  assert(m_sum_terms_above_one >= 0);
  return m_sum_terms_above_one;
}

int ribi::TwoDigitNewick::GetSumTermsAboveZero() const
{
  assert(m_sum_terms_above_zero >= 0);
  return m_sum_terms_above_zero;
}

std::string ribi::TwoDigitNewick::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::TwoDigitNewick::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2010-08-22: version 1.0: initial version");
  v.push_back("2011-02-20: version 1.1: added version history");
  return v;
}

bool ribi::TwoDigitNewick::IsComplete() const
{
  return (!m_derivatives.empty()
    && m_sum_terms_above_zero >= 0
    && m_sum_terms_above_one  >= 0);
}

bool ribi::TwoDigitNewick::IsProbabilityKnown() const
{
  return m_probability >= 0.0;
}

void ribi::TwoDigitNewick::SetProbability(const double p)
{
  //if (p < 0.0 || p > 1.0)
  //{
  //  TRACE(p);
  //}
  assert(p >= 0.0);
  assert(p <= 1.00001);
  m_probability = p;
}

void ribi::TwoDigitNewick::SetTheta(const double theta)
{
  assert(theta >= 0.0);
  sm_theta = theta;
}

#ifndef NDEBUG
void ribi::TwoDigitNewick::Test() noexcept
{
  ribi::TwoDigitNewick::SetTheta(10.0);
  const std::vector<std::string> v = Newick().CreateValidNewicks();
  for(const std::string& s: v)
  {
    if ( Newick().CalcComplexity(Newick().StringToNewick(s))
      >  BigInteger(1000000) )
    {
      continue;
    }
    if (Newick().IsBinaryNewick(Newick().StringToNewick(s)))
    {
      BinaryNewickVector n(s);
      TwoDigitNewickIndexer(n,10.0);
    }
  }
}
#endif // NDEBUG
