//---------------------------------------------------------------------------
/*
TestOpenQuestion, tool to test the OpenQuestion and OpenQuestionDialog classes
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
//From http://www.richelbilderbeek.nl/ToolTestOpenQuestion.htm
//---------------------------------------------------------------------------
#ifndef TESTOPENQUESTIONMAINDIALOG_H
#define TESTOPENQUESTIONMAINDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct MultipleChoiceQuestion;
struct MultipleChoiceQuestionDialog;
struct OpenQuestion;
struct OpenQuestionDialog;
struct QuestionDialog;

///The GUI independent TestOpenQuestion main dialog
struct TestOpenQuestionMainDialog
{
  TestOpenQuestionMainDialog();

  std::vector<boost::shared_ptr<QuestionDialog> >& GetQuestions() { return m_questions; }

  private:
  std::vector<boost::shared_ptr<QuestionDialog> > m_questions;

  void OnQuestionAnswered();

  static std::vector<boost::shared_ptr<QuestionDialog> > CreateQuestions();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TESTOPENQUESTIONMAINDIALOG_H
