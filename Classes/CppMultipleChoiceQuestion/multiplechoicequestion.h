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
#ifndef MULTIPLECHOICEQUESTION_H
#define MULTIPLECHOICEQUESTION_H

#include <string>
#include <vector>

#include "question.h"

namespace ribi {

///Class for a multiple choice question
struct MultipleChoiceQuestion : public Question
{
  ///Throws nothing or std::out_of_range or std::runtime_error
  explicit MultipleChoiceQuestion(const std::string& question);

  explicit MultipleChoiceQuestion(
    const std::string& filename,
    const std::string& question,
    const std::string& answer,
    const std::vector<std::string>& wrong_answers);

  ///Create a copy of the Question, depending on the derived class its type
  Question * Clone() const noexcept;

  ///Obtain the only correct answer
  const std::string& GetAnswer() const noexcept;

  ///Obtain the possible options to be chosen in a random order
  const std::vector<std::string>& GetOptions() const noexcept;

  ///Obtain the version
  static const std::string GetVersion() noexcept;

  ///Obtain the version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the wrong answers
  const std::vector<std::string>& GetWrongAnswers() const noexcept { return m_wrong_answers; }

  private:
  friend void boost::checked_delete<>(MultipleChoiceQuestion *);
  ~MultipleChoiceQuestion() noexcept {}

  ///All the wrong answers
  const std::vector<std::string> m_wrong_answers;

  ///All the options the user can choose from, which equals
  ///all wrong answers and the correct answer, shuffled randomly
  const std::vector<std::string> m_options;

  ///Create the possible options to be chosen in a random order
  static const std::vector<std::string> CreateOptions(
    const std::vector<std::string>& wrong_answers,
    const std::string& answer) noexcept;

  ///The options (correct + wrong answers) are at indices 2 to SeperateString(input,',').size()
  static const std::vector<std::string> ExtractOptions(
    const std::string& input);

  ///The wrong answers are at indices 3 to SeperateString(input,',').size()
  static const std::vector<std::string> ExtractWrongAnswers(
    const std::string& input);

  //Split a string
  //From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator) noexcept;

};

} //~namespace ribi

#endif // MULTIPLECHOICEQUESTION_H
