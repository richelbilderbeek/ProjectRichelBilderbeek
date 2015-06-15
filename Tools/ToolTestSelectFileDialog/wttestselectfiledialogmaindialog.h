//---------------------------------------------------------------------------
/*
TestSelectFileDialog, tool to test the SelectFileDialog class
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
//From http://www.richelbilderbeek.nl/ToolTestSelectFileDialog.htm
//---------------------------------------------------------------------------
#ifndef WTTESTSELECTFILEDIALOGMAINDIALOG_H
#define WTTESTSELECTFILEDIALOGMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <vector>
#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace Wt { struct WAnchor; }

namespace ribi {

struct WtSelectFileDialog;
//---------------------------------------------------------------------------
struct WtTestSelectFileDialogMainDialog : public Wt::WContainerWidget
{
  WtTestSelectFileDialogMainDialog();

  private:

  ///OnSelect is called when a user selects a file
  void OnSelect();

  ///Show is called at startup
  void Show();

  ///The user interface of this class
  struct Ui
  {
    Ui() : m_anchor(0), m_dialog(0) {}
    Wt::WAnchor * m_anchor;
    WtSelectFileDialog * m_dialog;
  } ui;
};

} //~namespace ribi

#endif // WTTESTSELECTFILEDIALOGMAINDIALOG_H
