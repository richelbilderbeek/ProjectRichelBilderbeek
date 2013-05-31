//---------------------------------------------------------------------------
/*
TestChess, program to test my chess classes
Copyright (C) 2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestChess.htm
//---------------------------------------------------------------------------
#ifndef WTTESTCHESSMAINDIALOG_H
#define WTTESTCHESSMAINDIALOG_H
//---------------------------------------------------------------------------
//#include <boost/scoped_ptr.hpp>
//#include <boost/signals2.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
struct WtChessBoardWidget;
namespace Wt { struct WSelectionBox; }
namespace Wt { struct WTextArea; }
//---------------------------------------------------------------------------
///WtTestChessMainDialog displays a
///WtChessBoardWidget
struct WtTestChessMainDialog : public Wt::WContainerWidget
{
  WtTestChessMainDialog();

  private:

  ///The user interface
  struct Ui
  {
    Ui();
    ~Ui();
    WtChessBoardWidget * const m_chessboard;
    Wt::WSelectionBox * const m_select;
    Wt::WTextArea * const m_text;
  } ui;
};
//---------------------------------------------------------------------------
#endif // WTTESTCHESSMAINDIALOG_H
