//---------------------------------------------------------------------------
/*
Question, class for a question
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
// From http://www.richelbilderbeek.nl/CppQuestion
//---------------------------------------------------------------------------
#ifndef QUESTION_H
#define QUESTION_H
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <vector>
#include <string>
#include <boost/checked_delete.hpp>
//---------------------------------------------------------------------------
///Class for a question
struct Question
{
  ///Create a copy of the Question, depending on the derived class its type
  virtual Question * Clone() const = 0;

  ///Is the submitted std::string a correct answer?
  bool IsCorrect(const std::string& s) const;

  ///Obtain the possible media filename, which will be empty
  ///if none is used
  const std::string& GetFilename() const { return m_filename; }

  ///Obtain the question
  const std::string& GetQuestion() const { return m_question; }

  ///Obtain the version
  static const std::string GetVersion();

  ///Obtain the version history
  static const std::vector<std::string> GetVersionHistory();

  protected:
  //Made constructor private, because one cannot make a Question, only
  //derived classes of Question
  explicit Question(
    const std::string& filename,
    const std::string& question,
    const std::vector<std::string>& answers);

  virtual ~Question() {}
  friend void boost::checked_delete<>(Question *);

  ///Obtain the answer(s)
  const std::vector<std::string>& GetAnswers() const { return m_answers; }

  ///Every Question might have a media filename
  const std::string m_filename;

  ///The question
  const std::string m_question;

  ///The list of possible answers
  const std::vector<std::string> m_answers;
};
//---------------------------------------------------------------------------
#endif // QUESTION_H
