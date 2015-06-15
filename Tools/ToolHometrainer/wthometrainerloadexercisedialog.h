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
#ifndef WTHOMETRAINERLOADEXERCISEDIALOG_H
#define WTHOMETRAINERLOADEXERCISEDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/signals2.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct WtSelectHometrainerFileDialog;

struct WtHometrainerLoadExerciseDialog : public Wt::WContainerWidget
{
  WtHometrainerLoadExerciseDialog();

  ///Check the folder for files again
  void DoRefresh();

  ///When a file is selected, m_signal_selected_file is emitted
  boost::signals2::signal<void (const std::string)> m_signal_selected_file;

  private:
  struct Ui
  {
    Ui();
    Wt::WLabel * const m_label_status;
    WtSelectHometrainerFileDialog * const m_select_file;
  } ui;

  ///OnSelectedFile is called when a file is selected in m_select_file
  ///and emits m_signal_selected_file with the filename
  void OnSelectedFile() const;
};

} //~namespace ribi

#endif // WTHOMETRAINERLOADEXERCISEDIALOG_H
