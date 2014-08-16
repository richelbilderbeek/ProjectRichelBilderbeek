//---------------------------------------------------------------------------
/*
Hometrainer, exercise and survey suite
Copyright (C) 2009-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolHometrainer.htm
//---------------------------------------------------------------------------
#ifndef WTHOMETRAINERMENUDIALOG_H
#define WTHOMETRAINERMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct WtHometrainerLoadExerciseDialog;
struct WtHometrainerStartExerciseDialog;


struct WtHometrainerMenuDialog : public Wt::WContainerWidget
{
  WtHometrainerMenuDialog();

private:

  struct Ui
  {
    Ui();
    WtHometrainerLoadExerciseDialog * const m_load_exercise;
    WtHometrainerStartExerciseDialog * const m_start_exercise;
  } ui;

  Wt::WWidget * CreateNewAboutDialog() const;
  Wt::WWidget * CreateNewWelcomeDialog() const;

  ///Respond to the user that has selected an exercise file in the 'Load Exercise' dialog
  void OnSelectedFile(const std::string filename);
};

} //namespace ribi

#endif // WTHOMETRAINERMENUDIALOG_H
