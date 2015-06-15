//---------------------------------------------------------------------------
/*
TestExercise, tool to test the Exercise class
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestExercise.htm
//---------------------------------------------------------------------------
#ifndef WTTESTEXERCISEMAINDIALOG_H
#define WTTESTEXERCISEMAINDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct WtExercise;

struct WtTestExerciseMainDialog : public Wt::WContainerWidget
{
  WtTestExerciseMainDialog();

  private:
  struct Ui
  {
    Ui();
    Wt::WTextArea * const m_area_input;
    Wt::WPushButton * const m_button_submit;
    Wt::WLineEdit * const m_edit_wait_correct;
    Wt::WLineEdit * const m_edit_wait_incorrect;
    Wt::WLabel * const m_label_status;
    WtExercise * const m_exercise_dialog;
  } ui;

  void OnSubmit();
};

} //~namespace ribi

#endif // WTTESTEXERCISEMAINDIALOG_H
