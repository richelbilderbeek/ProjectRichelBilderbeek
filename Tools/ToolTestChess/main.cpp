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
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "chessbitboard.h"
#include "chessboard.h"
#include "chesscolor.h"
#include "chessmove.h"
#include "chesspiece.h"
#include "chessscore.h"
#include "chesssquare.h"
#include "trace.h"
//---------------------------------------------------------------------------
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
  Chess::Score::Test();

  TRACE("Testing Square");
  Chess::Square::Test();

  TRACE("Testing BitBoard");
  Chess::BitBoard::Test();

  TRACE("Testing Move");
  Chess::Move::Test();

  TRACE("Testing Piece");
  Chess::Piece::Test();

  TRACE("Testing Board");
  Chess::Board::Test();

  TRACE("ALL TESTS SUCCEEDED");
}
//---------------------------------------------------------------------------
