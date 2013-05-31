//---------------------------------------------------------------------------
/*
ManyDigitNewick, Newick class
Copyright (C) 2011 Richel Bilderbeek

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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "manydigitnewick.h"

#include <cassert>
#include <cmath>

//Terrible #define, but my crosscompiler cannot find the definition of M_PI in cmath.h :-(
#ifndef M_PI
# define M_PI		3.14159265358979323846	/* pi */
#endif

#include <iostream>
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include "newickvector.h"
#include "newick.h"
#include "manydigitnewickindexer.h"
//---------------------------------------------------------------------------
double ManyDigitNewick::sm_theta = -1.0;
//---------------------------------------------------------------------------
///Create an empty MyDigitNewick, to have a
///default contructor
ManyDigitNewick::ManyDigitNewick()
  : m_probability(-1.0),
    m_denominator(-1.0),
    m_sum_terms_above_zero(-1),
    m_sum_terms_above_one(-1)
{
  assert(this->Empty());
}
//---------------------------------------------------------------------------
ManyDigitNewick::ManyDigitNewick(
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
//---------------------------------------------------------------------------
double ManyDigitNewick::CalculateDenominator(
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
//---------------------------------------------------------------------------
///Calculates the probability for a certain Newick
///with a certain theta. This is the main (helper)
///function.
double ManyDigitNewick::CalculateProbability(
  const std::string& newick_str,
  const double theta)
{
  TRACE_FUNC();
  ManyDigitNewick::SetTheta(theta);
  const NewickVector n(newick_str);
  const ManyDigitNewickIndexer i(n,theta);
  return i.GetProbability();
}
//---------------------------------------------------------------------------
bool ManyDigitNewick::Empty() const
{
  return m_derivatives.empty();
}
//---------------------------------------------------------------------------
double ManyDigitNewick::GetDenominator() const
{
  assert(IsComplete());
  return m_denominator;
}
//---------------------------------------------------------------------------
const std::vector<ManyDigitNewickDerivative>& ManyDigitNewick::GetDerivatives() const
{
  return m_derivatives;
}
//---------------------------------------------------------------------------
double ManyDigitNewick::GetProbability() const
{
  assert(IsProbabilityKnown());
  return m_probability;
}
//---------------------------------------------------------------------------
int ManyDigitNewick::GetSumTermsAboveOne() const
{
  assert(m_sum_terms_above_one >= 0);
  return m_sum_terms_above_one;
}
//---------------------------------------------------------------------------
int ManyDigitNewick::GetSumTermsAboveZero() const
{
  if (!(m_sum_terms_above_zero >= 0))
  {
    std::clog << "BREAKPOINT";
  }
  assert(m_sum_terms_above_zero >= 0);
  return m_sum_terms_above_zero;
}
//---------------------------------------------------------------------------
const std::string ManyDigitNewick::GetVersion()
{
  return "1.1";
}
//---------------------------------------------------------------------------
const std::vector<std::string> ManyDigitNewick::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-08-22: version 1.0: initial version");
  v.push_back("2011-02-20: version 1.1: added version history");
  return v;
}
//---------------------------------------------------------------------------
///A complete ManyDigitNewick has (hopefully) all its
///derivatives present, as well as its sums of terms
///above zero and one.
bool ManyDigitNewick::IsComplete() const
{
  return (!m_derivatives.empty()
    && m_sum_terms_above_zero >= 0
    && m_sum_terms_above_one  >= 0);
}
//---------------------------------------------------------------------------
bool ManyDigitNewick::IsProbabilityKnown() const
{
  return m_probability >= 0.0;
}
//---------------------------------------------------------------------------
void ManyDigitNewick::SetProbability(const double p)
{
  assert(p >= 0.0);
  assert(p <= 1.0000001);
  m_probability = p;
}
//---------------------------------------------------------------------------
void ManyDigitNewick::SetTheta(const double theta)
{
  assert(theta >= 0.0);
  sm_theta = theta;
}
//---------------------------------------------------------------------------
void ManyDigitNewick::Test()
{
  const double theta = 10.0;
  ManyDigitNewick::SetTheta(theta);
  const std::vector<std::string> v = Newick::CreateValidNewicks();
  BOOST_FOREACH(const std::string& s,v)
  {
    if ( Newick::CalcComplexity(Newick::StringToNewick(s))
      >  BigInteger(10000) )
    {
      continue;
    }
    ManyDigitNewick::CalculateProbability(s,theta);
  }
}
//---------------------------------------------------------------------------
