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

  ///Returns chi_squared_value and critical_value
  ///if (chi_squared_value < critical_value)
  ///{
  ///  std::cout
  ///    << "Cannot reject null hypothesis that the measured values "
  ///        "do follow the expected frequencies" << std::endl;
  ///}
  ///else
  ///{
  ///  std::cout
  ///    << "Reject null hypothesis that the measured values "
  ///       "do follow the expected frequencies" << std::endl;
  ///}
  std::pair<double,double> CalculateChiSquared(
    const std::map<char,double>& frequency_measured,
    const std::map<char,double>& frequency_expected
  ) const noexcept;

  ///Score the characters frequencies in text
  std::map<char,double> GetCharFrequency(const std::string& text) const noexcept;

  ///Tally the characters in text
  std::map<char,int> GetCharTally(const std::string& text) const noexcept;

  ///Score the characters frequencies in text
  std::vector<std::map<char,double>> GetCharFrequency(const std::string& text, const int period) const noexcept;

  ///Tally the characters in text for a certain period
  std::vector<std::map<char,int>> GetCharTally(const std::string& text, const int period) const noexcept;


  std::string GetExampleDutch() const noexcept
  {
    return
      "In de kansrekening speelt het begrip kansverdeling, waarschijnlijkheidsverdeling "
      "of -distributie (niet te verwarren met het gelijknamige begrip distributie in de "
      "analyse) een centrale rol. Bij een experiment waarin het toeval een rol speelt, "
      "geeft de kansverdeling aan hoe de kansen verdeeld zijn. In de theorie wordt hier "
      "een zeer specifieke betekenis aan gegeven, maar meer algemeen duidt men met "
      "kansverdeling wel het geheel van mogelijke uitkomsten en bijbehorende kansen aan."
      "Zo wordt bij een worp met een zuivere dobbelsteen de kansverdeling van het geworpen "
      "ogenaantal wel beschreven als gelijk aan 1/6 voor elke uitkomst. Strikt genomen is "
      "dit echter de kansfunctie, waarmee overigens de kansverdeling wel vastgelegd wordt. "
      "Het formele begrip kansverdeling is voornamelijk van theoretisch belang en zelfs daar "
      "zal vaker met de verdelingsfunctie, die geheel bepalend is voor de kansverdeling, "
      "gewerkt worden. Bij discrete kansverdelingen wordt de verdelingsfunctie op zijn "
      "beurt weer geheel bepaald door een kansfunctie en bij continue veranderlijken "
      "(absoluut continue verdelingsfunctie) door een kansdichtheid."
    ;
  }

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
  static std::map<char,double> GetLetterFrequencyEnglish() noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  int GuessCaesarCipherKey(
    const std::string& secret_text,
    const std::map<char,double>& expected_char_frequency = GetLetterFrequencyEnglish()
    ) const noexcept;

  int GuessVigenereCipherKeyLength(const std::string& secret_text) const noexcept;

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
