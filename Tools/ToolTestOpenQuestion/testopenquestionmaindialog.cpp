//---------------------------------------------------------------------------
/*
TestOpenQuestion, tool to test the OpenQuestion and OpenQuestionDialog classes
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestOpenQuestion.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testopenquestionmaindialog.h"

#include "openquestion.h"
#include "openquestiondialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TestOpenQuestionMainDialog::TestOpenQuestionMainDialog()
  : m_questions(CreateQuestions())
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<boost::shared_ptr<ribi::QuestionDialog> > ribi::TestOpenQuestionMainDialog::CreateQuestions()
{
  std::vector<boost::shared_ptr<QuestionDialog> > v;

  v.push_back(
    boost::shared_ptr<QuestionDialog>(
      new OpenQuestionDialog(
        boost::shared_ptr<OpenQuestion>(
          new OpenQuestion(
            "*",
            "1+1=",
            { "2", "two" }
          )
        )
      )
    )
  );
  v.push_back(
    boost::shared_ptr<QuestionDialog>(
      new OpenQuestionDialog(
        boost::shared_ptr<OpenQuestion>(
          new OpenQuestion(
            "question.png",
            "The solution of this equation is...",
            { "2", "two" }
          )
        )
      )
    )
  );
  std::random_shuffle(v.begin(),v.end());

  return v;
}

#ifndef NDEBUG
void ribi::TestOpenQuestionMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestOpenQuestionMainDialog::Test");
  TRACE("Finished ribi::TestOpenQuestionMainDialog::Test successfully");
}
#endif
