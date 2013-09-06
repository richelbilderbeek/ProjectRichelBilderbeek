//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestDial.htm
//---------------------------------------------------------------------------
#ifndef WTTESTDIALMAINDIALOG_H
#define WTTESTDIALMAINDIALOG_H
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
namespace Wt { struct WLabel; }

namespace ribi {

struct WtDialWidget;

struct WtTestDialMainDialog : public Wt::WContainerWidget
{
  WtTestDialMainDialog();

  private:

  struct Ui
  {
    Ui() : m_dial(0), m_label_color(0), m_label_position(0), m_dial_color(0) {}
    WtDialWidget * m_dial;
    Wt::WLabel * m_label_color;
    Wt::WLabel * m_label_position;
    WtDialWidget * m_dial_color;
  } ui;

  void OnDialColorChange();
  void OnDialPositionChange();
  void Show();
};

} //~namespace ribi

#endif // WTTESTDIALMAINDIALOG_H
