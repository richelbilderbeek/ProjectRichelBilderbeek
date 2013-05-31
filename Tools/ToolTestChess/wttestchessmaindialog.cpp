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
//#include <algorithm>
#include <cassert>
//#include <string>
//#include <vector>
//---------------------------------------------------------------------------
//#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WSelectionBox>
#include <Wt/WTextArea>
//---------------------------------------------------------------------------
//#include "about.h"
#include "chesssquare.h"
#include "chesssquareselector.h"
#include "trace.h"
//#include "wtaboutdialog.h"
#include "wtchessboardwidget.h"
#include "wtchessresources.h"
#include "wttestchessmaindialog.h"
//---------------------------------------------------------------------------
WtTestChessMainDialog::Ui::Ui()
 : m_chessboard(new WtChessBoardWidget(400,400)),
   m_select(new Wt::WSelectionBox),
   m_text(new Wt::WTextArea)
{
}
//---------------------------------------------------------------------------
WtTestChessMainDialog::Ui::~Ui()
{
 delete m_chessboard;
}
//---------------------------------------------------------------------------
WtTestChessMainDialog::WtTestChessMainDialog()
{
  setContentAlignment(Wt::AlignCenter);
  addWidget(ui.m_chessboard);
  addWidget(new Wt::WBreak);
  addWidget(ui.m_select);
  addWidget(new Wt::WBreak);
  addWidget(ui.m_text);

  ui.m_select->setMinimumSize(400,Wt::WLength::Auto);
  ui.m_select->addItem("A");
  ui.m_select->addItem("B");
  ui.m_select->addItem("C");

  ui.m_text->setMinimumSize(400,Wt::WLength::Auto);
  ui.m_text->setText("This is text");
}
//---------------------------------------------------------------------------
