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
#ifndef WTTESTQUESTIONMENUDIALOG_H
#define WTTESTQUESTIONMENUDIALOG_H
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct TestQuestionMenuDialog;
//---------------------------------------------------------------------------
struct WtTestQuestionMenuDialog : public Wt::WContainerWidget
{
  WtTestQuestionMenuDialog();
  private:
  Wt::WWidget * CreateNewAboutDialog() const;
  Wt::WWidget * CreateNewMainDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;

  boost::scoped_ptr<TestQuestionMenuDialog> m_dialog;
};

} //~namespace ribi

#endif // WTTESTQUESTIONMENUDIALOG_H
