//---------------------------------------------------------------------------
/*
TestMultipleChoiceQuestion, tests multiple choice question classes
Copyright (C) 2013-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestMultipleChoiceQuestion.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testmultiplechoicequestionmaindialog.h"

#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TestMultipleChoiceQuestionMainDialog::TestMultipleChoiceQuestionMainDialog()
  : m_questions(CreateQuestions())
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<boost::shared_ptr<ribi::QuestionDialog> > ribi::TestMultipleChoiceQuestionMainDialog::CreateQuestions()
{
  std::vector<boost::shared_ptr<QuestionDialog> > v;

  v.push_back(
    boost::shared_ptr<QuestionDialog>(
      new MultipleChoiceQuestionDialog(
        boost::shared_ptr<MultipleChoiceQuestion>(
          new MultipleChoiceQuestion(
            "*",
            "1+1=",
            "2",
            { "1", "3", "4", "5", "6" }
          )
        )
      )
    )
  );
  v.push_back(
    boost::shared_ptr<QuestionDialog>(
      new MultipleChoiceQuestionDialog(
        boost::shared_ptr<MultipleChoiceQuestion>(
          new MultipleChoiceQuestion(
            "Question.png",
            "The solution of this equation is...",
            "2",
            { "1", "3", "4", "5", "6" }
          )
        )
      )
    )
  );

  std::random_shuffle(v.begin(),v.end());

  return v;
}

#ifndef NDEBUG
void ribi::TestMultipleChoiceQuestionMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
