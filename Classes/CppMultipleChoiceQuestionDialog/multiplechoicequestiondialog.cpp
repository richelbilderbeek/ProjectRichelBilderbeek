//---------------------------------------------------------------------------
/*
MultipleChoiceQuestionDialog, dialog for MultipleChoiceQuestion
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
//From http://www.richelbilderbeek.nl/CppMultipleChoiceQuestionDialog.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "multiplechoicequestiondialog.h"

#include <cassert>
#include <boost/scoped_ptr.hpp>

#include "multiplechoicequestion.h"
#include "question.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::MultipleChoiceQuestionDialog::MultipleChoiceQuestionDialog(
  const boost::shared_ptr<const MultipleChoiceQuestion>& question)
  //const MultipleChoiceQuestion * const question)
  : QuestionDialog(question)
{
  assert(!HasSubmitted());
  assert(GetQuestion());
}

ribi::MultipleChoiceQuestionDialog::MultipleChoiceQuestionDialog(const std::string& question)
  : QuestionDialog(
    boost::shared_ptr<MultipleChoiceQuestion>(new
      MultipleChoiceQuestion(question)))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(!HasSubmitted());
  assert(GetQuestion());
}

boost::shared_ptr<ribi::MultipleChoiceQuestion>
  ribi::MultipleChoiceQuestionDialog::CreateDefaultQuestion() noexcept
{
  return boost::shared_ptr<MultipleChoiceQuestion>(
    new MultipleChoiceQuestion(
      "*",
      "1+2=",
      "3",
      {"1","2","4","5"}
    )
  );
}

const std::string ribi::MultipleChoiceQuestionDialog::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::MultipleChoiceQuestionDialog::GetVersionHistory() noexcept
{
  return {
    "2011-06-29: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::MultipleChoiceQuestionDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::MultipleChoiceQuestionDialog::Test");

  //Test submitting correct and incorrect answers to this dialog
  {
    const std::vector<std::string> valid {
      MultipleChoiceQuestion::GetValidMultipleChoiceQuestions()
    };
    for (const std::string& s: valid)
    {
      const boost::shared_ptr<const MultipleChoiceQuestion> question {
        new MultipleChoiceQuestion(s)
      };

      //Submit correct answer to this dialog
      {
        boost::scoped_ptr<MultipleChoiceQuestionDialog> dialog {
          new MultipleChoiceQuestionDialog(
            question
          )
        };
        assert(!dialog->HasSubmitted());

        const std::string answer = question->GetAnswer();
        assert(!question->GetWrongAnswers().empty());

        dialog->Submit(answer);

        assert(dialog->HasSubmitted());
        assert(dialog->IsAnswerCorrect());
      }
      //Submit incorrect answer to this dialog
      {
        boost::scoped_ptr<MultipleChoiceQuestionDialog> dialog {
          new MultipleChoiceQuestionDialog(
            question
          )
        };
        assert(!dialog->HasSubmitted());

        assert(!question->GetWrongAnswers().empty());
        const std::string wrong_answer = question->GetWrongAnswers().at(0);
        dialog->Submit(wrong_answer);

        assert(dialog->HasSubmitted());
        assert(!dialog->IsAnswerCorrect());
      }
    }
  }


  TRACE("Finished ribi::MultipleChoiceQuestionDialog::Test successfully");
}
#endif
