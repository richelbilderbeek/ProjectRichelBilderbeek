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
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "multiplechoicequestiondialog.h"

#include <cassert>

#include "multiplechoicequestion.h"
#include "question.h"

MultipleChoiceQuestionDialog::MultipleChoiceQuestionDialog(
  const boost::shared_ptr<MultipleChoiceQuestion>& question)
  //const MultipleChoiceQuestion * const question)
  : QuestionDialog(question)
{
  assert(CanSubmit());
  assert(!HasSubmitted());
  assert(GetQuestion());
}

MultipleChoiceQuestionDialog::MultipleChoiceQuestionDialog(const std::string& question)
  : QuestionDialog(
    boost::shared_ptr<MultipleChoiceQuestion>(new
      MultipleChoiceQuestion(question)))
{
  assert(CanSubmit());
  assert(!HasSubmitted());
  assert(GetQuestion());
}

///Create a default Question
/*
MultipleChoiceQuestion * MultipleChoiceQuestionDialog::CreateDefaultQuestion()
{
  return new MultipleChoiceQuestion(
      "*",
      "1+2=",
      "3",
      {"1","2","4","5"} );
}
*/

///Create a default Question
boost::shared_ptr<MultipleChoiceQuestion> MultipleChoiceQuestionDialog::CreateDefaultQuestion()
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

const std::string MultipleChoiceQuestionDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> MultipleChoiceQuestionDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-29: version 1.0: initial version");
  return v;
}

