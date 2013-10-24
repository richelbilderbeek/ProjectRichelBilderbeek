//---------------------------------------------------------------------------
/*
OpenQuestionDialog, dialog for OpenQuestion
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
//From http://www.richelbilderbeek.nl/CppOpenQuestionDialog.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "openquestiondialog.h"

#include "openquestion.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::OpenQuestionDialog::OpenQuestionDialog(const std::string& question)
  : m_question(new OpenQuestion(question))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(!HasSubmitted());
  assert(GetQuestion());
}

ribi::OpenQuestionDialog::OpenQuestionDialog(const boost::shared_ptr<const OpenQuestion>& question)
  : m_question(question)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(question);
  assert(!HasSubmitted());
  assert(GetQuestion());
}

const boost::shared_ptr<const ribi::Question> ribi::OpenQuestionDialog::GetQuestion() const
{
  return m_question;
}

const std::string ribi::OpenQuestionDialog::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::OpenQuestionDialog::GetVersionHistory() noexcept
{
  return {
    "2011-06-29: version 1.0: initial version",
    "2013-10-24: version 1.1: added testing"
  };
}

void ribi::OpenQuestionDialog::Submit(const std::string& s)
{
  if (HasSubmitted())
  {
    throw std::logic_error("Cannot submit a second answer");
  }
  assert(!HasSubmitted());

  this->SetIsCorrect(GetQuestion()->IsCorrect(s));
}

#ifndef NDEBUG
void ribi::OpenQuestionDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::OpenQuestionDialog::Test");
  //Test setting the open questions
  for(const std::string& s: OpenQuestion::GetValidOpenQuestions())
  {
    const boost::shared_ptr<OpenQuestion> q {
      new OpenQuestion(s)
    };
    assert(q);
    const OpenQuestionDialog d(q);
    assert(!d.HasSubmitted() );
  }
  TRACE("Finished ribi::OpenQuestionDialog::Test successfully");
}
#endif
