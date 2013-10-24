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
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "questiondialog.h"

#include <cassert>
#include <stdexcept>

#include "openquestion.h"
#include "multiplechoicequestion.h"
#include "question.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QuestionDialog::QuestionDialog()
  : m_signal_request_quit{},
    m_signal_submitted{},
    m_is_correct{}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_is_correct.empty() && "Answer is indeterminate at construction");
  assert(!HasSubmitted());
}

const std::string ribi::QuestionDialog::AskUserForInput() const noexcept
{
  std::string t;
  std::getline(std::cin,t);
  return t;
}

//const std::vector<std::string> ribi::QuestionDialog::GetCorrectAnswers() const noexcept
//{
// return this->GetQuestion()->GetAnswers();
//}

void ribi::QuestionDialog::Execute()
{
  assert(this->GetQuestion());
  std::cout
    << (*this->GetQuestion()) << '\n';

  std::cout << "Please enter your answer: " << std::endl;

  const std::string s = AskUserForInput();
  if (s.empty())
  {
    m_signal_request_quit();
    return;
  }

  assert(!this->HasSubmitted());
  this->Submit(s);
  assert(this->HasSubmitted());

  std::cout << std::endl;

  if (this->IsAnswerCorrect())
  {
    std::cout << "Correct\n";
  }
  else
  {
    const std::vector<std::string> correct_answers { this->GetQuestion()->GetCorrectAnswers() };
    std::cout
      << "Incorrect, "
      << (correct_answers.size() == 1 ? "the correct answer is: " : "the correct answers are: ")
      << '\n';
    for (const std::string& s: correct_answers)
    {
      std::cout << "  " << s << '\n';
    }
  }
  std::cout << std::endl;
}

const std::string ribi::QuestionDialog::GetVersion() noexcept
{
  return "1.3";
}

const std::vector<std::string> ribi::QuestionDialog::GetVersionHistory() noexcept
{
  return {
    "2011-06-29: version 1.0: initial version",
    "2013-09-26: version 1.1: improved const-correctness, added noexcept",
    "2013-10-24: version 1.2: added Execute for console application",
    "2013-10-25: version 1.3: added testing to derived classes"
  };
}

bool ribi::QuestionDialog::IsAnswerCorrect() const
{
  if (!HasSubmitted())
  {
    throw std::logic_error("Cannot only check if answer is correct, after submitting an answer");
  }
  assert(HasSubmitted());
  assert(!m_is_correct.empty());
  assert(m_is_correct.size() == 1);
  assert(m_is_correct[0] == 0 || m_is_correct[0] == 1);
  return m_is_correct[0] == 1;
}

void ribi::QuestionDialog::SetIsCorrect(const bool is_correct)
{
  assert(m_is_correct.empty()
    && "Can only answer exactly once");
  m_is_correct.push_back(is_correct ? 1 : 0);
  assert(!m_is_correct.empty()
    && "Must have stored that the question is answered");

  //m_has_submitted = true;
  assert(HasSubmitted());

  m_signal_submitted(IsAnswerCorrect());
}

/*
void ribi::QuestionDialog::SetQuestion(const boost::shared_ptr<const Question> question)
{
  if (!question)
  {
    throw std::logic_error("Cannot set a nullptr as a question in QuestionDialog::SetQuestion");
  }

  assert(question);
  if (question && question.get() != GetQuestion().get())
  {
    m_question = question;
    m_is_correct.clear();
    assert(!HasSubmitted());
  }
}
*/

#ifndef NDEBUG
void ribi::QuestionDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QuestionDialog::Test");
  TRACE("Finished ribi::QuestionDialog::Test successfully");
}
#endif

