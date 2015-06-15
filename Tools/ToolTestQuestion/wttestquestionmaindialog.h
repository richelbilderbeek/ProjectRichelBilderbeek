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
#ifndef WTTESTQUESTIONMAINDIALOG_H
#define WTTESTQUESTIONMAINDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace Wt { struct WLabel; }

namespace ribi {

struct TestQuestionMainDialog;
struct WtQuestionDialog;

struct WtTestQuestionMainDialog : public Wt::WContainerWidget
{
  WtTestQuestionMainDialog();

  private:
  struct Ui
  {
    Ui();
    Wt::WGroupBox * const m_box;
    Wt::WLineEdit * const m_edit;
    //WtQuestionDialog * m_question;
    Wt::WLabel * const m_label;
  } ui;

  void OnEditChanged();

  void OnSubmit();
};

} //~namespace ribi

#endif // WTTESTQUESTIONMAINDIALOG_H
