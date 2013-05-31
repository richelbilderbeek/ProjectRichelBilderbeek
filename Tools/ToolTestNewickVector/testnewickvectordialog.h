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
#ifndef TESTNEWICKVECTORDIALOG_H
#define TESTNEWICKVECTORDIALOG_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "about.h"

struct NewickVector;

struct TestNewickVectorDialog
{
  TestNewickVectorDialog();
  void AutoCalculate();
  void Calculate();
  void SetAnalyseCalculation(const bool b);
  void SetCompareToTwoDigitNewick(const bool b);
  void SetMaxComplexity(const std::string& s);
  void SetNewick(const std::string& s);
  void SetTheta(const std::string& s);
  const std::vector<std::string>& GetText() const { return m_text; }

  private:
  //Input
  bool m_analyse_calculation;
  bool m_compare;
  std::string m_max_complexity_str;
  std::string m_newick_str;
  std::string m_theta_str;
  //Internal
  boost::scoped_ptr<NewickVector> m_newick;
  double m_theta;
  //Output
  std::string m_complexity;
  double m_denominator;
  std::string m_n_combinations;
  std::string m_n_symmetries;

  std::vector<std::string> m_text;

  void Analyse();
  void AnalyseArity();
  void AnalyseCalculation();
  void AnalyseRootBranches();
  void AnalyseSimplerNewicks();
  bool CheckMaxComplexity();
  bool CheckNewick();
  bool CheckTheta();

  public:

  static const About GetAbout();
  static const std::string GetVersion();
  static const std::vector<std::string> GetVersionHistory();

};

#endif // TESTNEWICKVECTORDIALOG_H
