//---------------------------------------------------------------------------
/*
QuestionDialog, dialog for Question
Copyright (C) 2011-2014 Richel Bilderbeek

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

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include "tribool.h"
#pragma GCC diagnostic pop

namespace ribi {

struct Question;

///Dialog for (a derived class of) Question
///For an OpenQuestion use an OpenQuestionDialog
///For a MultipleChoiceQuestion use a MultipleChoiceQuestionDialog
struct QuestionDialog
{
  explicit QuestionDialog();

  ///Run the dialog from the command line
  void Execute();

  Tribool GetIsCorrect() const noexcept { return m_is_correct; }

  ///Obtain the question
  virtual boost::shared_ptr<const Question> GetQuestion() const = 0;

  ///Obtain the version
  static std::string GetVersion() noexcept;

  ///Obtain the version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Check if an answer has been submitted
  bool HasSubmitted() const { return m_is_correct != Tribool::Indeterminate; }

  ///See if the submitted answer is correct
  bool IsAnswerCorrect() const;

  ///Try to submit an answer
  ///For an open question, s will be the anwer
  ///For a multiple choice question, s will be the index of the answer
  ///Submit will throw an exception if s is invalid. For example,
  ///if s is a word, where a multiple choice question needs an index (like '2')
  virtual void Submit(const std::string& s) = 0;

  virtual std::string ToStr() const noexcept = 0;

  ///This signal is emitted when the client requests to quit
  mutable boost::signals2::signal<void ()> m_signal_request_quit;

  ///This signal is emitted when the client submits an answer, where
  ///the boolean indicates if a correct answer was given
  mutable boost::signals2::signal<void (bool)> m_signal_submitted;

  protected:
  virtual ~QuestionDialog() = default;
  friend void boost::checked_delete<>(QuestionDialog*);
  friend void boost::checked_delete<>(const QuestionDialog*);

  ///Set whether the user has answered the client correct
  ///and emit m_signal_submitted
  void SetIsCorrect(const bool is_correct);

  private:

  ///Was the submitted answer correct?
  ///Emulates a bool*:
  ///m_is_correct.empty() -> nullptr -> indeterminate
  ///m_is_correct[0] == 0 -> false
  ///m_is_correct[0] == 1 -> true
  ///Other values and sizes are invalid
  //std::vector<int> m_is_correct;
  Tribool m_is_correct;

  ///The question
  //boost::shared_ptr<const Question> m_question;

  std::string AskUserForInput() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // OPENQUESTIONDIALOG_H
