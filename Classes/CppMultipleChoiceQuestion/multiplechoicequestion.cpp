//---------------------------------------------------------------------------
/*
MultipleChoiceQuestion, class for a multiple choice question
Copyright (C) 2011  Richl Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppMultipleChoiceQuestion
//---------------------------------------------------------------------------
#include "multiplechoicequestion.h"

#include <algorithm>
#include <cassert>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string/split.hpp>
#pragma GCC diagnostic pop


ribi::MultipleChoiceQuestion::MultipleChoiceQuestion(const std::string& question)
  : Question(
      SeperateString(question,',').at(0),
      SeperateString(question,',').at(1),
      { SeperateString(question,',').at(2) }),
    m_wrong_answers(ExtractWrongAnswers(question)),
    m_options(ExtractOptions(question))
{

}

ribi::MultipleChoiceQuestion::MultipleChoiceQuestion(
  const std::string& filename,
  const std::string& question,
  const std::string& answer,
  const std::vector<std::string>& wrong_answers)
: Question(filename,question, {answer} ),
  m_wrong_answers(wrong_answers),
  m_options(CreateOptions(wrong_answers,answer))
{
  //assert(!filename.empty() && "Filename must not be empty");
  //assert(FileExists(filename) == true && "File must exists");
  //assert(!question.empty() && "MultipleChoiceQuestion must not be empty");
  //assert(!correct_answer.empty() && "Correct answer must not be empty");
  assert(!wrong_answers.empty() && "Wrong answers must not be empty");
  assert(wrong_answers.size() <= 5 && "There is a maximum of five wrong answers");
}

ribi::Question * ribi::MultipleChoiceQuestion::Clone() const
{
  return new MultipleChoiceQuestion(
    this->GetFilename(),
    this->GetQuestion(),
    this->GetAnswer(),
    this->GetWrongAnswers());
}

const std::string& ribi::MultipleChoiceQuestion::GetAnswer() const
{
  assert(!m_answers.empty());
  return m_answers[0];
}

const std::vector<std::string> ribi::MultipleChoiceQuestion::CreateOptions(
  const std::vector<std::string>& wrong_answers,
  const std::string& answer)
{
  std::vector<std::string> v = wrong_answers;
  v.push_back(answer);
  std::random_shuffle(v.begin(),v.end());
  return v;
}

const std::vector<std::string> ribi::MultipleChoiceQuestion::ExtractOptions(const std::string& input)
{
  const std::vector<std::string> v = SeperateString(input,',');
  std::vector<std::string> w;
  std::copy(v.begin() + 2,v.end(),std::back_inserter(w));
  std::random_shuffle(w.begin(),w.end());
  return w;
}

const std::vector<std::string> ribi::MultipleChoiceQuestion::ExtractWrongAnswers(const std::string& input)
{
  const std::vector<std::string> v = SeperateString(input,',');
  std::vector<std::string> w;
  std::copy(v.begin() + 3,v.end(),std::back_inserter(w));
  return w;
}

const std::vector<std::string>& ribi::MultipleChoiceQuestion::GetOptions() const
{
  return m_options;
}

const std::string ribi::MultipleChoiceQuestion::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::MultipleChoiceQuestion::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-27: version 1.0: initial version");
  v.push_back("2011-09-16: version 1.1: allow parsing from std::string");
  return v;
}

const std::vector<std::string> ribi::MultipleChoiceQuestion::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

