//---------------------------------------------------------------------------
/*
TestLed, tool to test the Led class
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestLed.htm
//---------------------------------------------------------------------------
#ifndef WTTESTLEDMAINDIALOG_H
#define WTTESTLEDMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#pragma GCC diagnostic pop

namespace ribi {

struct WtDialWidget;
struct WtLedWidget;

struct WtTestLedMainDialog : public Wt::WContainerWidget
{
  WtTestLedMainDialog();

  private:
  struct Ui
  {
    Ui()
      : m_dial_color{}, m_dial_intensity{}, m_dial_size{},
      m_label_color{}, m_label_intensity{}, m_label_size{},
      m_led{}
    {

    }
    WtDialWidget * m_dial_color;
    WtDialWidget * m_dial_intensity;
    WtDialWidget * m_dial_size;
    Wt::WLabel * m_label_color;
    Wt::WLabel * m_label_intensity;
    Wt::WLabel * m_label_size;
    WtLedWidget * m_led;
  } ui;
  void OnDialColorChange();
  void OnDialIntensityChange();
  void OnDialSizeChange();
  void ShowMain();
};

} //~namespace ribi

#endif // WTTESTLEDMAINDIALOG_H
