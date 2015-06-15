//---------------------------------------------------------------------------
/*
TestGroupWidget, tool to test the GroupWidget class
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
//From http://www.richelbilderbeek.nl/ToolTestGroupWidget.htm
//---------------------------------------------------------------------------
#ifndef WTTESTGROUPWIDGETDIALOG_H
#define WTTESTGROUPWIDGETDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct WtGroupWidget;
//---------------------------------------------------------------------------
struct WtTestGroupWidgetMainDialog : public Wt::WContainerWidget
{
  WtTestGroupWidgetMainDialog();

  private:
  struct Ui
  {
    Ui();
    Wt::WLineEdit * const m_edit;
    WtGroupWidget * const m_widget;
  } ui;

  ///Respond to a change in m_edit
  void OnChanged();

  ///Respond to a click on the button
  void OnClicked();

  //From http://www.richelbilderbeek.nl/CppSeperateString.htm
  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator);

};

} //~namespace ribi

#endif // WTTESTGROUPWIDGETDIALOG_H
