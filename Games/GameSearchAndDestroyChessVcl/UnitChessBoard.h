//---------------------------------------------------------------------------
/*
  SearchAndDestroyChess 2, Kriegspiel/Dark Chess game
  Copyright (C) 2008  Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitChessBoardH
#define UnitChessBoardH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <vector>
#include "UnitEnumChessPieceColor.h"
#include "UnitChessMove.h"
struct ChessPiece;
//---------------------------------------------------------------------------
//ChessBoard manages the position of the pieces
//It does not know whose turn it is (ChessGame does)
struct ChessBoard
{
  typedef std::vector<std::vector<ChessPiece> > Board;

  ChessBoard();

  const Board& GetPieces() const { return mPieces; }

  const bool CanDoMove(const ChessMove& move) const;
  void DoMove(const ChessMove& move);
  const ChessPiece GetPiece(const int x, const int y) const;

  const std::vector<std::vector<bool> > GetInSight(const EnumChessPieceColor color) const;

  const std::vector<ChessMove> GetAllValidMoves(const int x, const int y) const;
  const std::vector<ChessMove> GetAllPossibleMoves(const EnumChessPieceColor whoseTurn) const;

  void CoutPieces(const EnumChessPieceColor color) const;
  void CoutSight(const EnumChessPieceColor color) const;

  const bool IsGameOver() const;
  const EnumChessPieceColor GetWinner() const;

  private:

  Board mPieces;
  void SetPiece(const ChessPiece& piece, const int x, const int y);

  std::vector<ChessMove> mMoves;

  const std::vector<std::vector<ChessPiece> > GetInitialSetup();

  const bool IsValidMove(const ChessMove& move) const;

  const std::vector<ChessMove> GetAllValidMovesPawn(const int x, const int y) const;
  const std::vector<ChessMove> GetAllValidMovesKnight(const int x, const int y) const;
  const std::vector<ChessMove> GetAllValidMovesBishop(const int x, const int y) const;
  const std::vector<ChessMove> GetAllValidMovesRook(const int x, const int y) const;
  const std::vector<ChessMove> GetAllValidMovesQueen(const int x, const int y) const;
  const std::vector<ChessMove> GetAllValidMovesKing(const int x, const int y) const;

  const bool CanDoCastlingShort(const EnumChessPieceColor color) const;
  const bool CanDoCastlingLong(const EnumChessPieceColor color) const;
};
//---------------------------------------------------------------------------
#endif
