//---------------------------------------------------------------------------
/*
TestNewickVector, GUI tool to test NewickVector
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
//From http://www.richelbilderbeek.nl/ToolTestNewickVector.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testnewickvectordialog.h"

#include <cassert>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/lexical_cast.hpp>

#include "fileio.h"
#include "binarynewickvector.h"
#include "testtimer.h"
#include "fuzzy_equal_to.h"
#include "newick.h"
#include "newickvector.h"
#include "twodigitnewick.h"

#pragma GCC diagnostic pop

ribi::TestNewickVectorDialog::TestNewickVectorDialog() noexcept
  : m_analyse_calculation{false},
    m_compare{false},
    m_max_complexity_str{},
    m_newick_str{},
    m_theta_str{},
    m_newick{},
    m_theta{},
    m_complexity{},
    m_denominator{},
    m_n_combinations{},
    m_n_symmetries{},
    m_text{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

void ribi::TestNewickVectorDialog::Analyse() noexcept
{
  //Store the data
  m_newick.reset(new NewickVector(m_newick_str));
  m_theta = boost::lexical_cast<double>(m_theta_str);
  m_complexity = bigIntegerToString(m_newick->CalcComplexity());
  m_denominator = m_newick->CalcDenominator(m_theta);

  m_text.push_back("Newick complexity: "
      + m_complexity);

  AnalyseArity();
  AnalyseSimplerNewicks();
  AnalyseCalculation();

  AnalyseRootBranches();

  if (Newick().IsBinaryNewick(m_newick->Peek()))
  {
    m_n_combinations = bigIntegerToString(m_newick->CalcNumOfCombinations());
    m_n_symmetries = bigIntegerToString(m_newick->CalcNumOfSymmetries());
  }
  else
  {
    m_n_combinations = "N/A (not a binary Newick)";
    m_n_symmetries = "N/A (not a binary Newick)";
  }
  m_text.push_back("Number of combinations: " + m_n_combinations);
  m_text.push_back("Number of symmetries: " + m_n_symmetries);
  m_text.push_back("Denominator: " + boost::lexical_cast<std::string>(m_denominator));
}

void ribi::TestNewickVectorDialog::AnalyseArity() noexcept
{
  //Check if simple Newick
  if (Newick().IsSimple(m_newick->Peek()))
  {
    m_text.push_back("Simple Newick: Yes");
    m_text.push_back("Ewens probability: "
      + boost::lexical_cast<std::string>(
        m_newick->CalcProbabilitySimpleNewick(m_theta)));
  }
  else
  {
    m_text.push_back("Simple Newick: No");
  }
  //Check if binary Newick
  if (Newick().IsBinaryNewick(m_newick->Peek()))
  {
    m_text.push_back("Binary Newick: Yes");
  }
  else
  {
    m_text.push_back("Binary Newick: No");
  }
  if (Newick().IsTrinaryNewick(m_newick->Peek()))
  {
    m_text.push_back("Trinary Newick: Yes");
  }
  else
  {
    m_text.push_back("Trinary Newick: No");
  }
}

void ribi::TestNewickVectorDialog::AnalyseCalculation() noexcept
{
  if (!m_analyse_calculation) return;

  typedef std::pair<std::vector<int>,int> NewickFrequencyPair;
  const std::vector<NewickFrequencyPair> simpler
    = Newick().GetSimplerNewicksFrequencyPairs(m_newick->Peek());
  //Collect cooeficients
  std::vector<double> coefficients;
  for(const NewickFrequencyPair& p: simpler)
  {
    const int f = p.second;
    coefficients.push_back(f == 1
      ? m_theta / m_denominator
      : boost::numeric_cast<double>(f*(f-1)) / m_denominator);
  }
  assert(coefficients.size() == simpler.size());
  //Collect probabilities
  std::vector<double> probabilities;
  for(const NewickFrequencyPair& p: simpler)
  {
    const NewickVector n(p.first);
    probabilities.push_back(n.CalculateProbability(n.ToStr(),m_theta));
  }
  assert(probabilities.size() == simpler.size());

  //Display general info
  m_text.push_back(std::string(80,'-'));
  m_text.push_back("Calculation");
  m_text.push_back(std::string(80,'-'));
  m_text.push_back("N = the phylogeny = " + m_newick_str);
  m_text.push_back("t = theta = " + m_theta_str);
  m_text.push_back("p(N,t) = probability = SUM(c_i * p_i)");
  m_text.push_back("c(N,t) = coefficient");
  m_text.push_back("D(N,t) = denominator = "
    + boost::lexical_cast<std::string>(m_denominator));

  //Display derived Newicks
  const int n_simpler = boost::numeric_cast<int>(simpler.size());
  for (int i=0; i!=n_simpler; ++i)
  {
    m_text.push_back(
      "N'"
      + boost::lexical_cast<std::string>(i+1)
      + " = "
      + Newick().NewickToString(simpler[i].first));
  }
  m_text.push_back(" ");
  m_text.push_back("For t = "
    + boost::lexical_cast<std::string>(m_theta)
    + ":");
  m_text.push_back(" ");
  //Display probabilities
  for (int i=0; i!=n_simpler; ++i)
  {
    m_text.push_back(
      "p'"
      + boost::lexical_cast<std::string>(i+1)
      + " = "
      + boost::lexical_cast<std::string>(probabilities[i])
      + " (calculated at once with NewickVector)"
    );
  }
  //Display coefficients
  for (int i=0; i!=n_simpler; ++i)
  {
    const int f = simpler[i].second;
    m_text.push_back(
      "c'"
      + boost::lexical_cast<std::string>(i+1)
      + " = "
      + std::string(f == 1 ? "t / d" : "(f*(f-1)) / d")
      + " = "
      + boost::lexical_cast<std::string>(f == 1
        ? m_theta
        : boost::lexical_cast<double>(f*(f-1)))
      + " / "
      + boost::lexical_cast<std::string>(m_denominator)
      + " = "
      + boost::lexical_cast<std::string>(coefficients[i])
      + " (as f equals "
      + boost::lexical_cast<std::string>(f)
      + ")"
    );
  }
  m_text.push_back("p(N,t) = SUM(c_i * p_i)");
  {

    for (int i=0; i!=n_simpler; ++i)
    {
      std::string s = (i==0
        ? "       =  "
        : "         +");
      s += " ( "
        + boost::lexical_cast<std::string>(coefficients[i])
        + " * "
        + boost::lexical_cast<std::string>(probabilities[i])
        + " )";
      m_text.push_back(s);
    }
    //Hand-calculate probability
    double p_by_hand = 0.0;
    for (int i=0; i!=n_simpler; ++i)
    {
      p_by_hand += (coefficients[i] * probabilities[i]);
    }
    //p_by_hand/=m_denominator;
    m_text.push_back(
      "       = "
      + boost::lexical_cast<std::string>(p_by_hand)
      + " (hand-calculated)"
    );
    const double p_at_once = m_newick->CalculateProbability(m_newick->ToStr(),m_theta);
    m_text.push_back(
      std::string(ribi::fuzzy_equal_to()(p_by_hand,p_at_once)
        ? "       = "
        : "       != ")
      + boost::lexical_cast<std::string>(p_at_once)
      + " (calculated at once by NewickVector)"
    );
    if (m_compare
      && (  Newick().IsUnaryNewick(m_newick->Peek())
         || Newick().IsBinaryNewick(m_newick->Peek()) ) )
    {
      const double p_two_digit_newick = TwoDigitNewick::CalculateProbability(m_newick->ToStr(),m_theta);
      m_text.push_back(
        std::string(ribi::fuzzy_equal_to()(p_two_digit_newick,p_at_once)
          ? "       = "
          : "       != ")
        + boost::lexical_cast<std::string>(p_two_digit_newick)
        + " (calculated at once by TwoDigitNewick)"
      );
    }
  }
  m_text.push_back(std::string(80,'-'));
}

void ribi::TestNewickVectorDialog::AnalyseRootBranches() noexcept
{
  if(!Newick().IsUnaryNewick(m_newick->Peek()))
  {
    std::string text = "(X,Y) =\n";
    const std::vector<std::vector<int> > b
      = Newick().GetRootBranches(m_newick->Peek());
    try
    {
      for(const std::vector<int>& c: b)
      {
        Newick().CheckNewick(c);
        text+="  " + Newick().NewickToString(c);
      }
    }
    catch (std::exception& e)
    {
      text+=std::string(e.what());
    }
    text+="\n";
    m_text.push_back(text);
  }
}

void ribi::TestNewickVectorDialog::AnalyseSimplerNewicks() noexcept
{
  typedef std::pair<std::vector<int>,int> NewickFrequencyPair;
  const std::vector<NewickFrequencyPair> simpler
    = Newick().GetSimplerNewicksFrequencyPairs(m_newick->Peek());
  std::string text = "Simpler Newicks:\n";
  for(const NewickFrequencyPair& simple_pair: simpler)
  {
    const std::vector<int>& simple = simple_pair.first;
    const int f = simple_pair.second;
    try
    {
      Newick().CheckNewick(simple);
      text+="  ";
      text+=Newick().NewickToString(simple);
      text+=" (from f = ";
      text+=boost::lexical_cast<std::string>(f);
      text+=")\n";
    }
    catch (std::exception& e)
    {

      //Should not get here
      text += std::string(e.what()) + "\n";
    }
  }
  if (simpler.empty()) text+=" [none]\n";
  //Pop the trailing '\n'
  text.resize(text.size() - 1);
  m_text.push_back(text.c_str());
}

void ribi::TestNewickVectorDialog::AutoCalculate() noexcept
{
  m_text.resize(0);

  if (!CheckNewick()) return;
  if (!CheckTheta()) return;
  if (!CheckMaxComplexity()) return;

  const BigInteger max_complexity
    = stringToBigInteger(m_max_complexity_str);
  if (Newick().CalcComplexity(Newick().StringToNewick(m_newick_str))
    > max_complexity)
  {
    m_text.push_back("Newick too complex to auto-calculate. Press 'Calculate' or increase the value for auto-calculate");
    return;
  }
  Analyse();
}

void ribi::TestNewickVectorDialog::Calculate() noexcept
{
  m_text.resize(0);
  if (!CheckNewick()) return;
  if (!CheckTheta()) return;
  Analyse();

}

bool ribi::TestNewickVectorDialog::CheckMaxComplexity() noexcept
{
  try
  {
    boost::lexical_cast<int>(m_max_complexity_str);
  }
  catch (boost::bad_lexical_cast&)
  {
    m_text.push_back("Valid maximum autocalc complexity: No");
    return false;
  }
  m_text.push_back("Valid maximum autocalc complexity: Yes");
  return true;
}

bool ribi::TestNewickVectorDialog::CheckNewick() noexcept
{
  if (!Newick().IsNewick(m_newick_str))
  {
    m_text.push_back("Valid Newick: No");
    //No Newick, why not?
    try
    {
      Newick().CheckNewick(m_newick_str);
    }
    catch (std::exception& e)
    {
      //Must get here
      m_text.push_back(std::string("Exception: ") + e.what());
    }
    return false;
  }
  m_text.push_back("Valid Newick: Yes");
  return true;
}

bool ribi::TestNewickVectorDialog::CheckTheta() noexcept
{
  try
  {
    boost::lexical_cast<double>(m_theta_str);
  }
  catch (boost::bad_lexical_cast&)
  {
    m_text.push_back("Valid theta: No");
    return false;
  }
  m_text.push_back("Valid theta: Yes");
  return true;
}


void ribi::TestNewickVectorDialog::SetAnalyseCalculation(const bool b) noexcept
{
  m_analyse_calculation = b;
}

void ribi::TestNewickVectorDialog::SetCompareToTwoDigitNewick(const bool b) noexcept
{
  m_compare = b;
}

void ribi::TestNewickVectorDialog::SetMaxComplexity(const std::string& s)
{
  m_max_complexity_str = s;
}

void ribi::TestNewickVectorDialog::SetNewick(const std::string& s)
{
  m_newick_str = s;
}

void ribi::TestNewickVectorDialog::SetTheta(const std::string& s)
{
  m_theta_str = s;
}

#ifndef NDEBUG
void ribi::TestNewickVectorDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
    Newick().Test();
    BinaryNewickVector::Test();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
