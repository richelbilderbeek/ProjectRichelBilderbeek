//---------------------------------------------------------------------------
/*
TestShinyButton, tool to test the ShinyButton class
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
//From http://www.richelbilderbeek.nl/ToolTestShinyButton.htm
//---------------------------------------------------------------------------
#ifndef WTTESTSHINYBUTTONDIALOG_H
#define WTTESTSHINYBUTTONDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace Wt { struct WLabel; }

namespace ribi {

struct TestShinyButtonMenuDialog;
struct WtDialWidget;
struct WtShinyButtonWidget;

struct WtTestShinyButtonMainDialog : public Wt::WContainerWidget
{
  WtTestShinyButtonMainDialog();

  private:
  boost::scoped_ptr<TestShinyButtonMenuDialog> m_dialog;

  struct Ui
  {
    Ui();
    WtDialWidget * const m_dial_color;
    WtDialWidget * const m_dial_gradient;
    Wt::WLineEdit * const m_edit;
    Wt::WLabel * const m_label_color;
    WtShinyButtonWidget * const m_shiny_button;
  } ui;

  void OnDialChanged();
  void OnEditChanged();
  void OnShinyButtonColorChanged();
};

} //~namespace ribi

#endif // WTTESTSHINYBUTTONDIALOG_H
