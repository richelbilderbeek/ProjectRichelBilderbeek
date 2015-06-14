//---------------------------------------------------------------------------
/*
TestNewick, test the Newick classes and functions
Copyright (C) 2009-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestNewick.htm
//---------------------------------------------------------------------------
#include <fstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/numeric/conversion/cast.hpp>
#include <boost/timer.hpp>

#include "binarynewickvector.h"
#include "manydigitnewick.h"
#include "newick.h"
#include "newickvector.h"
#include "sortedbinarynewickvector.h"
#include "twodigitnewick.h"
#include "testnewick.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::TestNewick::TestNewick()
  : m_time(0.0),
    m_probability(0.0)
{
  //Do nothing
}

///CreateAllTests creates all tests
const std::vector<boost::shared_ptr<ribi::TestNewick>> ribi::TestNewick::CreateTests(const int flags)
{
  std::vector<boost::shared_ptr<TestNewick> > v;
  if (flags & m_flag_binary_newick_vector)
    v.push_back(boost::shared_ptr<TestNewick>(new TestBinaryNewickVector));
  if (flags & m_flag_many_digit_newick)
    v.push_back(boost::shared_ptr<TestNewick>(new TestManyDigitNewick));
  if (flags & m_flag_newick_vector)
    v.push_back(boost::shared_ptr<TestNewick>(new TestNewickVector));
  if (flags & m_flag_sorted_binary_newick_vector)
    v.push_back(boost::shared_ptr<TestNewick>(new TestSortedBinaryNewickVector));
  if (flags & m_flag_two_digit_newick)
    v.push_back(boost::shared_ptr<TestNewick>(new TestTwoDigitNewick));
  return v;
}

void ribi::TestNewick::SetProbability(const double probability)
{
  m_probability = probability;
}

void ribi::TestNewick::SetTime(const double time)
{
  m_time = time;
}

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

bool ribi::TestBinaryNewickVector::CanCalculate(const std::string& newick_str, const double theta)
{
  if (theta <= 0.0) return false;
  if (!Newick().IsNewick(newick_str))
    return false;
  const std::vector<int> newick = Newick().StringToNewick(newick_str);
  if (!Newick().IsUnaryNewick(newick) && !Newick().IsBinaryNewick(newick))
    return false;
  return true;
}

void ribi::TestBinaryNewickVector::Calculate(const std::string& newick_str, const double theta)
{
  assert(CanCalculate(newick_str,theta));
  boost::timer t;
  const double p
    = BinaryNewickVector::CalculateProbability(
      newick_str,theta);
  SetTime(t.elapsed());
  SetProbability(p);
}

bool ribi::TestManyDigitNewick::CanCalculate(const std::string& newick_str, const double theta)
{
  //TestManyDigitNewick gives incorrect results!
  return false;

  if (theta <= 0.0) return false;
  if (!Newick().IsNewick(newick_str)) return false;
  return true;
}

void ribi::TestManyDigitNewick::Calculate(const std::string& newick_str, const double theta)
{
  assert(CanCalculate(newick_str,theta));
  boost::timer t;
  const double p
    = ManyDigitNewick::CalculateProbability(
      newick_str,theta);
  SetTime(t.elapsed());
  SetProbability(p);
}

bool ribi::TestNewickVector::CanCalculate(const std::string& newick_str, const double theta)
{
  if (theta <= 0.0) return false;
  if (!Newick().IsNewick(newick_str)) return false;
  return true;
}

void ribi::TestNewickVector::Calculate(const std::string& newick_str, const double theta)
{
  assert(CanCalculate(newick_str,theta));
  boost::timer t;
  const double p
    = NewickVector::CalculateProbability(
      newick_str,theta);
  SetTime(t.elapsed());
  SetProbability(p);
}

bool ribi::TestSortedBinaryNewickVector::CanCalculate(const std::string& newick_str, const double theta)
{
  if (theta <= 0.0) return false;
  if (!Newick().IsNewick(newick_str))
    return false;
  const std::vector<int> newick = Newick().StringToNewick(newick_str);
  if (!Newick().IsUnaryNewick(newick) && !Newick().IsBinaryNewick(newick))
    return false;
  return true;
}

void ribi::TestSortedBinaryNewickVector::Calculate(const std::string& newick_str, const double theta)
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

bool ribi::TestTwoDigitNewick::CanCalculate(const std::string& newick_str, const double theta)
{
  if (theta <= 0.0) return false;
  if (!Newick().IsNewick(newick_str))
    return false;
  const std::vector<int> newick = Newick().StringToNewick(newick_str);
  if (!Newick().IsUnaryNewick(newick) && !Newick().IsBinaryNewick(newick))
    return false;
  return true;
}

void ribi::TestTwoDigitNewick::Calculate(const std::string& newick_str, const double theta)
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

