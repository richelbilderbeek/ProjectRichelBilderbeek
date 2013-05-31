//---------------------------------------------------------------------------
/*
  The Rampal Etienne Project, calculates the probability of a phylogeny
  (C) 2009 Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <fstream>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/numeric/conversion/cast.hpp>
#include <boost/timer.hpp>
//---------------------------------------------------------------------------
#include "binarynewickvector.h"
#include "manydigitnewick.h"
#include "newick.h"
#include "newickravindran.h"
#include "newickvector.h"
#include "sortedbinarynewickvector.h"
#include "twodigitnewick.h"
#include "testnewick.h"
#include "trace.h"
//---------------------------------------------------------------------------
const int TestNewick::m_flag_all = 63;
const int TestNewick::m_flag_binary_newick_vector = 1;
const int TestNewick::m_flag_many_digit_newick = 2;
const int TestNewick::m_flag_newick_vector = 4;
const int TestNewick::m_flag_ravindran = 8;
const int TestNewick::m_flag_sorted_binary_newick_vector = 16;
const int TestNewick::m_flag_two_digit_newick = 32;
//---------------------------------------------------------------------------
TestNewick::TestNewick()
  : m_time(0.0),
    m_probability(0.0)
{
  //Do nothing
}
//---------------------------------------------------------------------------
///CreateAllTests creates all tests
const std::vector<boost::shared_ptr<TestNewick> > TestNewick::CreateTests(const int flags)
{
  std::vector<boost::shared_ptr<TestNewick> > v;
  if (flags & m_flag_binary_newick_vector)
    v.push_back(boost::shared_ptr<TestNewick>(new TestBinaryNewickVector));
  if (flags & m_flag_many_digit_newick)
    v.push_back(boost::shared_ptr<TestNewick>(new TestManyDigitNewick));
  if (flags & m_flag_newick_vector)
    v.push_back(boost::shared_ptr<TestNewick>(new TestNewickVector));
  if (flags & m_flag_ravindran)
    v.push_back(boost::shared_ptr<TestNewick>(new TestRavindran));
  if (flags & m_flag_sorted_binary_newick_vector)
    v.push_back(boost::shared_ptr<TestNewick>(new TestSortedBinaryNewickVector));
  if (flags & m_flag_two_digit_newick)
    v.push_back(boost::shared_ptr<TestNewick>(new TestTwoDigitNewick));
  return v;
}
//---------------------------------------------------------------------------
void TestNewick::SetProbability(const double probability)
{
  m_probability = probability;
}
//---------------------------------------------------------------------------
void TestNewick::SetTime(const double time)
{
  m_time = time;
}
//---------------------------------------------------------------------------
//Ewensprobability = probability * num_of_combinations
/*
const std::string Test::GetEwensProbability() const
{
  const BigInteger n_combinations
    = Newick::CalcNumOfCombinations(
        BinaryNewickVector(GetNewick()).Get());
  try
  {
    const int i = n_combinations.toInt();
    const double d = boost::numeric_cast<double>(i);
    const double ewens_probability = d * GetProbability();
    return boost::lexical_cast<std::string>(ewens_probability);
  }
  catch (...)
  {
    const std::string s
      = bigIntegerToString(n_combinations)
      + std::string(" * ")
      + boost::lexical_cast<std::string>(GetProbability());
    return s;
  }
}
*/
//---------------------------------------------------------------------------
bool TestBinaryNewickVector::CanCalculate(const std::string& newick_str, const double theta)
{
  if (theta <= 0.0) return false;
  if (!Newick::IsNewick(newick_str))
    return false;
  const std::vector<int> newick = Newick::StringToNewick(newick_str);
  if (!Newick::IsUnaryNewick(newick) && !Newick::IsBinaryNewick(newick))
    return false;
  return true;
}
//---------------------------------------------------------------------------
void TestBinaryNewickVector::Calculate(const std::string& newick_str, const double theta)
{
  assert(CanCalculate(newick_str,theta));
  boost::timer t;
  const double p
    = BinaryNewickVector::CalculateProbability(
      newick_str,theta);
  SetTime(t.elapsed());
  SetProbability(p);
}
//---------------------------------------------------------------------------
bool TestManyDigitNewick::CanCalculate(const std::string& newick_str, const double theta)
{
  TRACE("TODO");
  return false;

  if (theta <= 0.0) return false;
  if (!Newick::IsNewick(newick_str)) return false;
  return true;
}
//---------------------------------------------------------------------------
void TestManyDigitNewick::Calculate(const std::string& newick_str, const double theta)
{
  assert(CanCalculate(newick_str,theta));
  boost::timer t;
  const double p
    = ManyDigitNewick::CalculateProbability(
      newick_str,theta);
  SetTime(t.elapsed());
  SetProbability(p);
}
//---------------------------------------------------------------------------
bool TestNewickVector::CanCalculate(const std::string& newick_str, const double theta)
{
  if (theta <= 0.0) return false;
  if (!Newick::IsNewick(newick_str)) return false;
  return true;
}
//---------------------------------------------------------------------------
void TestNewickVector::Calculate(const std::string& newick_str, const double theta)
{
  assert(CanCalculate(newick_str,theta));
  boost::timer t;
  const double p
    = NewickVector::CalculateProbability(
      newick_str,theta);
  SetTime(t.elapsed());
  SetProbability(p);
}
//---------------------------------------------------------------------------
bool TestRavindran::CanCalculate(const std::string& newick_str, const double theta)
{
  if (theta <= 0.0) return false;
  if (!Newick::IsNewick(newick_str))
    return false;
  const std::vector<int> newick = Newick::StringToNewick(newick_str);
  if (Newick::CalcComplexity(newick) > 1000000)
    return false;
  if (!Newick::IsUnaryNewick(newick) && !Newick::IsBinaryNewick(newick))
    return false;
  return true;
}
//---------------------------------------------------------------------------
void TestRavindran::Calculate(const std::string& newick_str, const double theta)
{
  assert(CanCalculate(newick_str,theta));
  boost::timer t;
  const double p
    = NewickRavindran::CalculateProbability(
      newick_str,
      theta);
  SetTime(t.elapsed());
  SetProbability(p);
}
//---------------------------------------------------------------------------
bool TestSortedBinaryNewickVector::CanCalculate(const std::string& newick_str, const double theta)
{
  if (theta <= 0.0) return false;
  if (!Newick::IsNewick(newick_str))
    return false;
  const std::vector<int> newick = Newick::StringToNewick(newick_str);
  if (!Newick::IsUnaryNewick(newick) && !Newick::IsBinaryNewick(newick))
    return false;
  return true;
}
//---------------------------------------------------------------------------
void TestSortedBinaryNewickVector::Calculate(const std::string& newick_str, const double theta)
{
  assert(CanCalculate(newick_str,theta));
  boost::timer t;
  const double p
    = SortedBinaryNewickVector::CalculateProbability(
      newick_str,
      theta);
  SetTime(t.elapsed());
  SetProbability(p);
}
//---------------------------------------------------------------------------
bool TestTwoDigitNewick::CanCalculate(const std::string& newick_str, const double theta)
{
  if (theta <= 0.0) return false;
  if (!Newick::IsNewick(newick_str))
    return false;
  const std::vector<int> newick = Newick::StringToNewick(newick_str);
  if (!Newick::IsUnaryNewick(newick) && !Newick::IsBinaryNewick(newick))
    return false;
  return true;
}
//---------------------------------------------------------------------------
void TestTwoDigitNewick::Calculate(const std::string& newick_str, const double theta)
{
  assert(CanCalculate(newick_str,theta));
  boost::timer t;
  const double p
    = TwoDigitNewick::CalculateProbability(
      newick_str,
      theta);
  SetTime(t.elapsed());
  SetProbability(p);
}
//---------------------------------------------------------------------------
