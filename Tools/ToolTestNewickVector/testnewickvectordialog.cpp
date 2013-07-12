//---------------------------------------------------------------------------
/*
TestNewickVector, GUI tool to test NewickVector
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
//From http://www.richelbilderbeek.nl/ToolTestNewickVector.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testnewickvectordialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

#include "binarynewickvector.h"
#include "newick.h"
#include "newickvector.h"
#include "twodigitnewick.h"

TestNewickVectorDialog::TestNewickVectorDialog()
  : m_analyse_calculation(false)
{
  #ifndef NDEBUG
  Newick::Test();
  BinaryNewickVector::Test();
  #endif
}

void TestNewickVectorDialog::Analyse()
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

  if (Newick::IsBinaryNewick(m_newick->Peek()))
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
  m_text.push_back(std::string("Denominator: ") + boost::lexical_cast<std::string>(m_denominator));
}

void TestNewickVectorDialog::AnalyseArity()
{
  //Check if simple Newick
  if (Newick::IsSimple(m_newick->Peek()))
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
  if (Newick::IsBinaryNewick(m_newick->Peek()))
  {
    m_text.push_back("Binary Newick: Yes");
  }
  else
  {
    m_text.push_back("Binary Newick: No");
  }
  if (Newick::IsTrinaryNewick(m_newick->Peek()))
  {
    m_text.push_back("Trinary Newick: Yes");
  }
  else
  {
    m_text.push_back("Trinary Newick: No");
  }
}

void TestNewickVectorDialog::AnalyseCalculation()
{
  if (!m_analyse_calculation) return;

  typedef std::pair<std::vector<int>,int> NewickFrequencyPair;
  const std::vector<NewickFrequencyPair> simpler
    = Newick::GetSimplerNewicksFrequencyPairs(m_newick->Peek());
  //Collect cooeficients
  std::vector<double> coefficients;
  BOOST_FOREACH(const NewickFrequencyPair& p,simpler)
  {
    const int f = p.second;
    coefficients.push_back(f == 1
      ? m_theta / m_denominator
      : boost::numeric_cast<double>(f*(f-1)) / m_denominator);
  }
  assert(coefficients.size() == simpler.size());
  //Collect probabilities
  std::vector<double> probabilities;
  BOOST_FOREACH(const NewickFrequencyPair& p,simpler)
  {
    const NewickVector n(p.first);
    probabilities.push_back(n.CalculateProbability(n.ToStr(),m_theta));
  }
  assert(probabilities.size() == simpler.size());

  //Display general info
  m_text.push_back(std::string(80,'-'));
  m_text.push_back("Calculation");
  m_text.push_back(std::string(80,'-'));
  m_text.push_back(std::string("N = the phylogeny = ") + m_newick_str);
  m_text.push_back(std::string("t = theta = ") + m_theta_str);
  m_text.push_back("p(N,t) = probability = SUM(c_i * p_i)");
  m_text.push_back("c(N,t) = coefficient");
  m_text.push_back(std::string("D(N,t) = denominator = ")
    + boost::lexical_cast<std::string>(m_denominator));

  //Display derived Newicks
  const int n_simpler = boost::numeric_cast<int>(simpler.size());
  for (int i=0; i!=n_simpler; ++i)
  {
    m_text.push_back(
      std::string("N'")
      + boost::lexical_cast<std::string>(i+1)
      + std::string(" = ")
      + Newick::NewickToString(simpler[i].first));
  }
  m_text.push_back(" ");
  m_text.push_back(std::string("For t = ")
    + boost::lexical_cast<std::string>(m_theta)
    + std::string(":"));
  m_text.push_back(" ");
  //Display probabilities
  for (int i=0; i!=n_simpler; ++i)
  {
    m_text.push_back(
      std::string("p'")
      + boost::lexical_cast<std::string>(i+1)
      + std::string(" = ")
      + boost::lexical_cast<std::string>(probabilities[i])
      + std::string(" (calculated at once with NewickVector)"));
  }
  //Display coefficients
  for (int i=0; i!=n_simpler; ++i)
  {
    const int f = simpler[i].second;
    m_text.push_back(
      std::string("c'")
      + boost::lexical_cast<std::string>(i+1)
      + std::string(" = ")
      + std::string(f == 1 ? "t / d" : "(f*(f-1)) / d")
      + std::string(" = ")
      + boost::lexical_cast<std::string>(f == 1
        ? m_theta
        : boost::lexical_cast<double>(f*(f-1)))
      + std::string(" / ")
      + boost::lexical_cast<std::string>(m_denominator)
      + std::string(" = ")
      + boost::lexical_cast<std::string>(coefficients[i])
      + std::string(" (as f equals ")
      + boost::lexical_cast<std::string>(f)
      + std::string(")"));
  }
  m_text.push_back("p(N,t) = SUM(c_i * p_i)");
  {

    for (int i=0; i!=n_simpler; ++i)
    {
      std::string s = (i==0
        ? "       =  "
        : "         +");
      s += std::string(" ( ")
        + boost::lexical_cast<std::string>(coefficients[i])
        + std::string(" * ")
        + boost::lexical_cast<std::string>(probabilities[i])
        + std::string(" )");
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
      std::string("       = ")
      + boost::lexical_cast<std::string>(p_by_hand)
       + std::string(" (hand-calculated)"));
    const double p_at_once = m_newick->CalculateProbability(m_newick->ToStr(),m_theta);
    m_text.push_back(
     std::string(Newick::fuzzy_equal_to()(p_by_hand,p_at_once)
       ? "       = "
       : "       != ")
     + boost::lexical_cast<std::string>(p_at_once)
     + std::string(" (calculated at once by NewickVector)"));
    if (m_compare
      && (  Newick::IsUnaryNewick(m_newick->Peek())
         || Newick::IsBinaryNewick(m_newick->Peek()) ) )
    {
      const double p_two_digit_newick = TwoDigitNewick::CalculateProbability(m_newick->ToStr(),m_theta);
      m_text.push_back(
       std::string(Newick::fuzzy_equal_to()(p_two_digit_newick,p_at_once)
         ? "       = "
         : "       != ")
       + boost::lexical_cast<std::string>(p_two_digit_newick)
       + std::string(" (calculated at once by TwoDigitNewick)"));
    }
  }
  m_text.push_back(std::string(80,'-'));
}

void TestNewickVectorDialog::AnalyseRootBranches()
{
  if(!Newick::IsUnaryNewick(m_newick->Peek()))
  {
    std::string text = "(X,Y) =\n";
    const std::vector<std::vector<int> > b
      = Newick::GetRootBranches(m_newick->Peek());
    try
    {
      BOOST_FOREACH(const std::vector<int>& c,b)
      {
        Newick::CheckNewick(c);
        text+=std::string("  ") + Newick::NewickToString(c);
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

void TestNewickVectorDialog::AnalyseSimplerNewicks()
{
  typedef std::pair<std::vector<int>,int> NewickFrequencyPair;
  const std::vector<NewickFrequencyPair> simpler
    = Newick::GetSimplerNewicksFrequencyPairs(m_newick->Peek());
  std::string text = "Simpler Newicks:\n";
  BOOST_FOREACH(const NewickFrequencyPair& simple_pair,simpler)
  {
    const std::vector<int>& simple = simple_pair.first;
    const int f = simple_pair.second;
    try
    {
      Newick::CheckNewick(simple);
      text+="  ";
      text+=Newick::NewickToString(simple);
      text+=" (from f = ";
      text+=boost::lexical_cast<std::string>(f);
      text+=")\n";
    }
    catch (std::exception& e)
    {

      //Should not get here
      text += std::string(e.what()) + std::string("\n");
    }
  }
  if (simpler.empty()) text+=" [none]\n";
  //Pop the trailing '\n'
  text.resize(text.size() - 1);
  m_text.push_back(text.c_str());
}

void TestNewickVectorDialog::AutoCalculate()
{
  m_text.resize(0);

  if (!CheckNewick()) return;
  if (!CheckTheta()) return;
  if (!CheckMaxComplexity()) return;

  const BigInteger max_complexity
    = stringToBigInteger(m_max_complexity_str);
  if (Newick::CalcComplexity(Newick::StringToNewick(m_newick_str))
    > max_complexity)
  {
    m_text.push_back("Newick too complex to auto-calculate. Press 'Calculate' or increase the value for auto-calculate");
    return;
  }
  Analyse();
}

void TestNewickVectorDialog::Calculate()
{
  m_text.resize(0);
  if (!CheckNewick()) return;
  if (!CheckTheta()) return;
  Analyse();

}

bool TestNewickVectorDialog::CheckMaxComplexity()
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

bool TestNewickVectorDialog::CheckNewick()
{
  if (!Newick::IsNewick(m_newick_str))
  {
    m_text.push_back("Valid Newick: No");
    //No Newick, why not?
    try
    {
      Newick::CheckNewick(m_newick_str);
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

bool TestNewickVectorDialog::CheckTheta()
{
  //Check if theta is valid
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

const About TestNewickVectorDialog::GetAbout()
{
  About about(
    "Richel Bilderbeek",
    "TestNewickVector",
    "tool to test the NewickVector class",
    "at the 25th of April 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolTestNewickVector.htm",
    GetVersion(),
    GetVersionHistory());
  about.AddLibrary("BigInt: version 2010.04.30");
  about.AddLibrary("BinaryNewickVector: " + BinaryNewickVector::GetVersion());
  about.AddLibrary("NewickVector: " + NewickVector::GetVersion());
  return about;
}

const std::string TestNewickVectorDialog::GetVersion()
{
  return "3.2";
}

const std::vector<std::string> TestNewickVectorDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-02-20: Version 1.0: initial version");
  v.push_back("2011-03-09: Version 2.0: calculates Newick probabilities");
  v.push_back("2011-03-26: Version 3.0: seperated GUI from logic, added web version");
  v.push_back("2011-04-25: Version 3.1: removed web version\'s Close button");
  v.push_back("2011-06-07: Version 3.2: added command-line call");
  return v;
}

void TestNewickVectorDialog::SetAnalyseCalculation(const bool b)
{
  m_analyse_calculation = b;
}

void TestNewickVectorDialog::SetCompareToTwoDigitNewick(const bool b)
{
  m_compare = b;
}

void TestNewickVectorDialog::SetMaxComplexity(const std::string& s)
{
  m_max_complexity_str = s;
}

void TestNewickVectorDialog::SetNewick(const std::string& s)
{
  m_newick_str = s;
}

void TestNewickVectorDialog::SetTheta(const std::string& s)
{
  m_theta_str = s;
}

