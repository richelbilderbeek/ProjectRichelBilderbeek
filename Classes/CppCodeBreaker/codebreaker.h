//---------------------------------------------------------------------------
/*
CodeBreaker, code breaking class
Copyright (C) 2010-2014 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppCodeBreaker.htm
//---------------------------------------------------------------------------
#ifndef CODEBREAKER_H
#define CODEBREAKER_H

#include <map>
#include <string>
#include <vector>

namespace ribi {

///code breaking class
struct CodeBreaker
{
  CodeBreaker();

  double CalculateChiSquared(
    const std::map<char,double>& frequency_measured,
    const std::map<char,double>& frequency_expected
  ) const noexcept;

  ///Score the characters frequencies in text
  std::map<char,double> GetCharFrequency(const std::string& text) const noexcept;

  ///Tally the characters in text
  std::map<char,int> GetCharTally(const std::string& text) const noexcept;

  ///Tally the characters in text for a certain period
  std::vector<std::map<char,int>> GetCharTally(const std::string& text, const int period) const noexcept;

  std::string GetExampleEnglish() const noexcept
  {
    return
      "In probability theory and statistics, the chi-squared distribution "
      "(also chi-square or x2-distribution) with k degrees of freedom is the "
      "distribution of a sum of the squares of k independent standard normal random "
      "variables. A special case of the gamma distribution, it is one of the most "
      "widely used probability distributions in inferential statistics, e.g., in "
      "hypothesis testing or in construction of confidence intervals. When there "
      "is a need to contrast it with the noncentral chi-squared distribution, this "
      "distribution is sometimes called the central chi-squared distribution. The "
      "chi-squared distribution is used in the common chi-squared tests for goodness "
      "of fit of an observed distribution to a theoretical one, the independence of two "
      "criteria of classification of qualitative data, and in confidence interval "
      "estimation for a population standard deviation of a normal distribution from "
      "a sample standard deviation. Many other statistical tests also use this "
      "distribution, like Friedman's analysis of variance by ranks.";
  }

  std::map<char,double> GetLetterFrequencyDutch() const noexcept;
  std::map<char,double> GetLetterFrequencyEnglish() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  std::vector<double> CalculateRelativeError(
    const std::vector<double>& frequency_measured,
    const std::vector<double>& frequency_expected
  ) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // CODEBREAKER_H
