//---------------------------------------------------------------------------
/*
TestToggleButton, tool to test the ToggleButton class
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
//From http://www.richelbilderbeek.nl/ToolTestToggleButton.htm
//---------------------------------------------------------------------------
#ifndef WTTESTTOGGLEBUTTONDIALOG_H
#define WTTESTTOGGLEBUTTONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/scoped_ptr.hpp>
#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace Wt { struct WLabel; }

namespace ribi {
struct TestToggleButtonMenuDialog;
struct WtDialWidget;
struct WtToggleButtonWidget;

struct WtTestToggleButtonMainDialog : public Wt::WContainerWidget
{
  WtTestToggleButtonMainDialog();

  private:
  boost::scoped_ptr<TestToggleButtonMenuDialog> m_dialog;

  struct Ui
  {
    Ui() : m_dial(0), m_label_color(0), m_label_toggle(0), m_toggle_button(0) {}
    WtDialWidget * m_dial;
    Wt::WLabel * m_label_color;
    Wt::WLabel * m_label_toggle;
    WtToggleButtonWidget * m_toggle_button;
  } ui;

  void OnAboutClick();
  void OnDialChanged();
  void OnToggleButtonColorChanged();
  void OnToggleButtonToggled();
  void ShowAbout();
  void ShowMain();
};

} //~namespace ribi

#endif // WTTESTTOGGLEBUTTONDIALOG_H
