//---------------------------------------------------------------------------
/*
Hometrainer, exercise and survey suite
Copyright (C) 2009-2015 Richel Bilderbeek

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
#ifndef WTHOMETRAINERSTARTEXERCISEDIALOG_H
#define WTHOMETRAINERSTARTEXERCISEDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct WtExercise;

struct WtHometrainerStartExerciseDialog : public Wt::WContainerWidget
{
  WtHometrainerStartExerciseDialog();

  void LoadExercise(const std::string& filename);

  private:
  struct Ui
  {
    Ui();
    Wt::WGroupBox * const m_box_exercise;
  } ui;
};

} //~namespace ribi

#endif // WTHOMETRAINERSTARTEXERCISEDIALOG_H
