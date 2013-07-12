//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQuestion.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testquestionmaindialog.h"

#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"

TestQuestionMainDialog::TestQuestionMainDialog()
  : m_questions(CreateQuestions())
{

}

std::vector<boost::shared_ptr<QuestionDialog> > TestQuestionMainDialog::CreateQuestions()
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
            "question.png",
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





