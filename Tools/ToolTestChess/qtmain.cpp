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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QApplication>
#include "chessbitboard.h"
#include "chessboard.h"
#include "chessmove.h"
#include "chesspiece.h"
#include "chessscore.h"
#include "chesssquare.h"
#include "qtchessresources.h"
#include "qttestchessmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  START_TRACE();

  TRACE("Creating QtResources");
  ribi::Chess::QtResources();

  TRACE("Testing Score");
  ribi::Chess::Score::Test();

  TRACE("Testing Square");
  ribi::Chess::Square::Test();

  TRACE("Testing BitBoard");
  ribi::Chess::BitBoard::Test();

  TRACE("Testing Move");
  ribi::Chess::Move::Test();

  TRACE("Testing Piece");
  ribi::Chess::Piece::Test();


  ribi::QtTestChessMenuDialog w;
  w.show();
  return a.exec();
}
