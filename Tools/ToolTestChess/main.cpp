//---------------------------------------------------------------------------
/*
TestChess, program to test my chess classes
Copyright (C) 2012-2015 Richel Bilderbeek

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
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "chessbitboard.h"
#include "chessboard.h"
#include "chesscolor.h"
#include "chessmove.h"
#include "chesspiece.h"
#include "chessscore.h"
#include "chesssquare.h"
#include "testchessmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

///TODO
///- Add variant 'Juggernaut Chess': every turn a player receives 5 movement points.
///  Moving a piece costs as muchg movement points at that piece its value:
///  Pawn = 1, Knight = 3, Bishop = 3, Rook = 5, Queen = 10, King = 20, Castling = 20 + 5 = 25
///- Add variant 'Half Chess': every turn, only the pieces on one square color are allowed to be moved
///- Add variant 'Traitor's Chess': every turn a player may move any piece, including those of the opponent
///- Add variant 'Cannibal Chess': a player may also capture his/her own pieces
int main()
{
  START_TRACE();
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


  TRACE("ALL TESTS SUCCEEDED");
  ribi::TestChessMenuDialog d;
}
