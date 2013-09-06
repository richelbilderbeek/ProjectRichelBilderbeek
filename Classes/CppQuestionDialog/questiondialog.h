//---------------------------------------------------------------------------
/*
QuestionDialog, dialog for Question
Copyright (C) 2011-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQuestionDialog.htm
//---------------------------------------------------------------------------
#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>

namespace ribi {

struct Question;

///Dialog for an Question
struct QuestionDialog
{
  explicit QuestionDialog(const boost::shared_ptr<Question>& question);

  ///Check if an answer can be submitted
  bool CanSubmit() const { return !m_has_submitted; }

  ///Get all possible correct answers
  const std::vector<std::string> GetCorrectAnswers() const;

  ///Obtain the question
  boost::shared_ptr<Question> GetQuestion() const { return m_question; }

  ///Obtain the version
  static const std::string GetVersion();

  ///Obtain the version history
  static const std::vector<std::string> GetVersionHistory();

  ///Check if an answer has been submitted
  bool HasSubmitted() const { return m_has_submitted; }

  ///See if the submitted answer is correct
  bool IsAnswerCorrect() const;

  ///(Re)set the Question
  //void SetQuestion(const Question * const question);
  void SetQuestion(const boost::shared_ptr<Question>& question);

  ///Submit an answer
  void Submit(const std::string& s);

  protected:
  virtual ~QuestionDialog() {}
  friend void boost::checked_delete<>(QuestionDialog*);

  private:
  ///The question
  boost::shared_ptr<Question> m_question;

  ///Has the user already submitted an answer?
  bool m_has_submitted;

  ///Was the submitted answer correct?
  bool m_is_correct;
};

} //~namespace ribi

#endif // OPENQUESTIONDIALOG_H
