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
#include "chessbitboard.h"
#include "chessboard.h"
#include "chessboardwidget.h"
#include "chesscolor.h"
#include "chessfile.h"
#include "chessgame.h"
#include "chessgamewidget.h"
#include "chessmove.h"
#include "chessmoves.h"
#include "chesspiece.h"
#include "chessrank.h"
#include "chessresources.h"
#include "chessscore.h"
#include "chesssquare.h"
#include "chesssquareselector.h"
#include "chesswidget.h"
#include "testchessmenudialog.h"
#include "widget.h"
//---------------------------------------------------------------------------
const About TestChessMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestChess",
    "testing my chess classes",
    "the 25st of January 2012",
    "2012",
    "http://www.richelbilderbeek.nl/ToolTestChess.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Chess::BitBoard version: " + Chess::BitBoard::GetVersion());
  a.AddLibrary("Chess::Board1d version: " + Chess::Board::GetVersion());
  a.AddLibrary("Chess::BoardWidget version: " + Chess::BoardWidget::GetVersion());
  a.AddLibrary("Chess::ChessWidget version: " + Chess::ChessWidget::GetVersion());
  a.AddLibrary("Chess::Color version: " + Chess::ColorVersion::GetVersion());
  a.AddLibrary("Chess::File version: " + Chess::File::GetVersion());
  a.AddLibrary("Chess::Game version: " + Chess::Game::GetVersion());
  a.AddLibrary("Chess::GameWidget version: " + Chess::GameWidget::GetVersion());
  a.AddLibrary("Chess::Move version: " + Chess::Move::GetVersion());
  a.AddLibrary("Chess::Moves version: " + Chess::Moves::GetVersion());
  a.AddLibrary("Chess::Piece version: " + Chess::Piece::GetVersion());
  a.AddLibrary("Chess::Rank version: " + Chess::Rank::GetVersion());
  a.AddLibrary("Chess::Resources version: " + Chess::Resources::GetVersion());
  a.AddLibrary("Chess::Score version: " + Chess::Score::GetVersion());
  a.AddLibrary("Chess::Square version: " + Chess::Square::GetVersion());
  a.AddLibrary("Chess::SquareSelector version: " + Chess::SquareSelector::GetVersion());

  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}
//---------------------------------------------------------------------------
const std::string TestChessMenuDialog::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> TestChessMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-01-25: Version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
