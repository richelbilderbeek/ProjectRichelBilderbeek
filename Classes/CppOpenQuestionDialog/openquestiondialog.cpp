//---------------------------------------------------------------------------
/*
OpenQuestionDialog, dialog for OpenQuestion
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppOpenQuestionDialog.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "openquestiondialog.h"

#include <cassert>
#include <sstream>

#include "openquestion.h"
#include "openquestiondialogfactory.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::OpenQuestionDialog::OpenQuestionDialog()
  : m_signal_open_question_changed{},
    m_answer_in_progress{},
    m_open_question{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

/*
ribi::OpenQuestionDialog::OpenQuestionDialog(const boost::shared_ptr<const OpenQuestion>& question)
  : m_open_question(question)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(question);
  assert(!HasSubmitted());
  assert(GetQuestion());
}
*/

boost::shared_ptr<const ribi::Question> ribi::OpenQuestionDialog::GetQuestion() const noexcept
{
  return m_open_question;
}

std::string ribi::OpenQuestionDialog::GetVersion() noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::OpenQuestionDialog::GetVersionHistory() noexcept
{
  return {
    "2011-06-29: version 1.0: initial version",
    "2013-10-24: version 1.1: added testing",
    "2014-06-05: version 1.2: moved some code to OpenQuestionDialogFactory",
    "2014-06-12: version 1.3: added support for displaying an answer-in-progress"
  };
}

void ribi::OpenQuestionDialog::SetAnswerInProgress(const std::string& answer_in_progress) noexcept
{
  if (m_answer_in_progress != answer_in_progress)
  {
    m_answer_in_progress = answer_in_progress;
    m_signal_open_question_changed(this);
  }
}

void ribi::OpenQuestionDialog::SetOpenQuestion(const boost::shared_ptr<OpenQuestion>& open_question) noexcept
{
  if (m_open_question != open_question)
  {
    m_open_question = open_question;
    m_signal_open_question_changed(this);
  }
}


void ribi::OpenQuestionDialog::Submit(const std::string& s)
{
  if (HasSubmitted())
  {
    throw std::logic_error("Cannot submit a second answer");
  }
  assert(!HasSubmitted());

  this->SetIsCorrect(GetQuestion()->IsCorrect(s));
  //this->m_signal_submitted(this);
}

#ifndef NDEBUG
void ribi::OpenQuestionDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    OpenQuestionDialogFactory();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Test setting the open questions
  for(const auto dialog: OpenQuestionDialogFactory().GetTestOpenQuestionDialogs())
  {
    assert(!dialog->HasSubmitted());
  }
}
#endif

std::string ribi::OpenQuestionDialog::ToStr() const noexcept
{
  std::stringstream s;
  s << m_open_question->ToStr();
  return s.str();
}
