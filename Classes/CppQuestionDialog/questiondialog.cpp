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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "questiondialog.h"

#include <cassert>
#include <stdexcept>
#include "question.h"
#pragma GCC diagnostic pop

ribi::QuestionDialog::QuestionDialog(const boost::shared_ptr<const Question> question)
  : m_has_submitted(false),
    m_is_correct(false),
    m_question{question}
{
  assert(m_question);
  assert(!HasSubmitted());
  assert(GetQuestion());
}

//const std::vector<std::string> ribi::QuestionDialog::GetCorrectAnswers() const noexcept
//{
//  return this->GetQuestion()->GetAnswers();
//}

const std::string ribi::QuestionDialog::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::QuestionDialog::GetVersionHistory() noexcept
{
  return {
    "2011-06-29: version 1.0: initial version",
    "2013-09-26: version 1.1: improved const-correctness, added noexcept"
  };
}

bool ribi::QuestionDialog::IsAnswerCorrect() const
{
  if (!HasSubmitted())
  {
    throw std::logic_error("Cannot only check if answer is correct, after submitting an answer");
  }
  assert(HasSubmitted());
  return m_is_correct;
}

void ribi::QuestionDialog::SetQuestion(const boost::shared_ptr<const Question> question)
{
  if (!question)
  {
    throw std::logic_error("Cannot set a nullptr as a question in QuestionDialog::SetQuestion");
  }

  assert(question);
  if (question && question.get() != m_question.get())
  {
    m_question = question;
    m_has_submitted = false;
  }
}

void ribi::QuestionDialog::Submit(const std::string& s)
{
  if (HasSubmitted())
  {
    throw std::logic_error("Cannot submit a second answer");
  }
  assert(!HasSubmitted());

  m_is_correct = m_question->IsCorrect(s);

  m_has_submitted = true;
  assert(HasSubmitted());
}

