//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011-2015 Richel Bilderbeek

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
#ifndef TESTQUESTIONMAINDIALOG_H
#define TESTQUESTIONMAINDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct MultipleChoiceQuestion;
struct MultipleChoiceQuestionDialog;
struct OpenQuestion;
struct OpenQuestionDialog;
struct QuestionDialog;

///The GUI independent TestQuestion main dialog
struct TestQuestionMainDialog
{
  TestQuestionMainDialog();

  std::vector<boost::shared_ptr<QuestionDialog>>& GetQuestions() { return m_questions; }

  private:
  std::vector<boost::shared_ptr<QuestionDialog>> m_questions;

  void OnQuestionAnswered();

  static std::vector<boost::shared_ptr<QuestionDialog>> CreateQuestions();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi


#endif // TESTQUESTIONMAINDIALOG_H
