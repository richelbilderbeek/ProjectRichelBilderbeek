//---------------------------------------------------------------------------
/*
RubiksClock. Rubik's Clock game.
Copyright (C) 2007-2011  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameRubiksClock.htm
//---------------------------------------------------------------------------
#ifndef WTRUBIKSCLOCKDIALOG_H
#define WTRUBIKSCLOCKDIALOG_H
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
struct WtDialWidget;
struct WtRubiksClockWidget;
//---------------------------------------------------------------------------
struct WtRubiksClockMainDialog : public Wt::WContainerWidget
{
  WtRubiksClockMainDialog();

  private:
  struct Ui
  {
    Ui();
    Wt::WPushButton * const m_button_flip;
    WtDialWidget * const m_dial_size;
    Wt::WLabel * const m_label_size;
    WtRubiksClockWidget * const m_widget;
  } ui;

  ///Respond to a click on m_button_flip
  void OnFlip();

  ///Respond to ui.m_dial_size
  void OnSizeChanged();
};
//---------------------------------------------------------------------------
#endif // WTRUBIKSCLOCKDIALOG_H
