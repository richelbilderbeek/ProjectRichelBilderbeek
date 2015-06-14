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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "manydigitnewick.h"

#include <cassert>
#include <cmath>

#include <iostream>


#include <boost/numeric/conversion/cast.hpp>

#include "newickvector.h"
#include "newick.h"
#include "manydigitnewickindexer.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

double ribi::ManyDigitNewick::sm_theta = -1.0;

///Create an empty MyDigitNewick, to have a
///default contructor
ribi::ManyDigitNewick::ManyDigitNewick()
  : m_probability(-1.0),
    m_denominator(-1.0),
    m_sum_terms_above_zero(-1),
    m_sum_terms_above_one(-1)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(this->Empty());
}

ribi::ManyDigitNewick::ManyDigitNewick(
  const std::vector<ManyDigitNewickDerivative>& derivatives,
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

double ribi::ManyDigitNewick::CalculateDenominator(
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

///Calculates the probability for a certain Newick
///with a certain theta. This is the main (helper)
///function.
double ribi::ManyDigitNewick::CalculateProbability(
  const std::string& newick_str,
  const double theta)
{
  ribi::ManyDigitNewick::SetTheta(theta);
  const NewickVector n(newick_str);
  const ManyDigitNewickIndexer i(n,theta);
  return i.GetProbability();
}

bool ribi::ManyDigitNewick::Empty() const noexcept
{
  return m_derivatives.empty();
}

double ribi::ManyDigitNewick::GetDenominator() const
{
  assert(IsComplete());
  return m_denominator;
}

const std::vector<ribi::ManyDigitNewickDerivative>&
  ribi::ManyDigitNewick::GetDerivatives() const noexcept
{
  return m_derivatives;
}

double ribi::ManyDigitNewick::GetProbability() const
{
  assert(IsProbabilityKnown());
  return m_probability;
}

int ribi::ManyDigitNewick::GetSumTermsAboveOne() const
{
  assert(m_sum_terms_above_one >= 0);
  return m_sum_terms_above_one;
}

int ribi::ManyDigitNewick::GetSumTermsAboveZero() const
{
  if (!(m_sum_terms_above_zero >= 0))
  {
    std::clog << "BREAKPOINT";
  }
  assert(m_sum_terms_above_zero >= 0);
  return m_sum_terms_above_zero;
}

std::string ribi::ManyDigitNewick::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::ManyDigitNewick::GetVersionHistory() noexcept
{
  return {
    "2010-08-22: version 1.0: initial version",
    "2011-02-20: version 1.1: added version history"
  };
}

///A complete ManyDigitNewick has (hopefully) all its
///derivatives present, as well as its sums of terms
///above zero and one.
bool ribi::ManyDigitNewick::IsComplete() const
{
  return (!m_derivatives.empty()
    && m_sum_terms_above_zero >= 0
    && m_sum_terms_above_one  >= 0);
}

bool ribi::ManyDigitNewick::IsProbabilityKnown() const noexcept
{
  return m_probability >= 0.0;
}

void ribi::ManyDigitNewick::SetProbability(const double p)
{
  assert(p >= 0.0);
  assert(p <= 1.0000001);
  m_probability = p;
}

void ribi::ManyDigitNewick::SetTheta(const double theta)
{
  assert(theta >= 0.0);
  sm_theta = theta;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#ifndef NDEBUG
void ribi::ManyDigitNewick::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::MultiVector<int>();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const double theta = 10.0;
  ribi::ManyDigitNewick::SetTheta(theta);
  const std::vector<std::string> v = Newick().CreateValidNewicks();
  for(const std::string& s: v)
  {
    if ( Newick().CalcComplexity(Newick().StringToNewick(s))
      >  BigInteger(10000) )
    {
      continue;
    }
    ribi::ManyDigitNewick::CalculateProbability(s,theta);
  }
}
#endif // NDEBUG
#pragma GCC diagnostic pop

