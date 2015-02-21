//---------------------------------------------------------------------------
/*
Question, class for a question
Copyright (C) 2011-2015 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppQuestion
//---------------------------------------------------------------------------
#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>
#include <boost/checked_delete.hpp>

namespace ribi {

///Class for a question.
///A question only knows its question and correct answers and optionally
///an image. Derived classes need to maintain incorrect answers.
struct Question
{
  explicit Question(
    const std::string& filename,
    const std::string& question,
    const std::vector<std::string>& correct_answers
  );

  ///Create a copy of the Question, depending on the derived class its type
  virtual Question * Clone() const noexcept = 0;

  ///Obtain the correct answer(s)
  const std::vector<std::string>& GetCorrectAnswers() const noexcept { return m_correct_answers; }

  ///Obtain the possible media filename, which will be empty
  ///if none is used
  const std::string& GetFilename() const noexcept { return m_filename; }

  ///Obtain the question
  const std::string& GetQuestion() const noexcept { return m_question; }

  ///Obtain the version
  static std::string GetVersion() noexcept;

  ///Obtain the version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Would a submitted std::string be the correct answer?
  bool IsCorrect(const std::string& s) const noexcept;

  ///How to display the question as multiple lines
  virtual std::vector<std::string> ToLines() const noexcept = 0;

  ///Convert to std::string line, as read from file
  virtual std::string ToStr() const noexcept = 0;

  protected:
  virtual ~Question() noexcept {}

  private:
  friend void boost::checked_delete<>(Question *);
  friend void boost::checked_delete<>(const Question *);

  ///Every Question might have a media filename
  const std::string m_filename;

  ///The question
  const std::string m_question;

  ///The list of possible answers
  const std::vector<std::string> m_correct_answers;
};

std::ostream& operator<<(std::ostream& os,const Question& question);

} //~namespace ribi

#endif // QUESTION_H
