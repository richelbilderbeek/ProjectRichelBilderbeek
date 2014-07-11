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
#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>
#include "UnitChessBoard.h"
#include "UnitChessPiece.h"
#pragma hdrstop

#include "UnitChessGame.h"
//---------------------------------------------------------------------------
ChessGame::ChessGame()
  : mWhoseTurn(white)
{

}
//---------------------------------------------------------------------------
const bool ChessGame::CanDoMove(const ChessMove& move) const
{
  //Regular move
  const ChessPiece piece = mBoard.GetPiece(move.x1,move.y1);
  //Is it of the right color?
  if (piece.GetColor()!=mWhoseTurn) return false;
  //Is the captured piece of the other color?
  //->checked by ChessBoard
  //ChessBoard checks the rest
  return mBoard.CanDoMove(move);
}
//---------------------------------------------------------------------------
void ChessGame::DoMove(const ChessMove& move)
{
  assert(this->CanDoMove(move)==true);
  mBoard.DoMove(move);
  mWhoseTurn = (mWhoseTurn == white ? black : white);
}
//---------------------------------------------------------------------------
void ChessGame::CoutGame() const
{
  mBoard.CoutSight(mWhoseTurn);
  std::cout
    << std::endl
    << (mWhoseTurn == white ? "White" : "Black")
    << " player's turn"
    << std::endl;
}
//---------------------------------------------------------------------------
void ChessGame::CoutBoard() const
{
  mBoard.CoutPieces(mWhoseTurn);
  std::cout
    << std::endl
    << (mWhoseTurn == white ? "White" : "Black")
    << " player's turn"
    << std::endl;
}
//---------------------------------------------------------------------------
const bool ChessGame::IsGameOver() const
{
  return mBoard.IsGameOver();
}
//---------------------------------------------------------------------------
const EnumChessPieceColor ChessGame::GetWinner() const
{
  assert(this->IsGameOver()==true);
  return mBoard.GetWinner();
}
//---------------------------------------------------------------------------
const std::vector<std::vector<bool> > ChessGame::GetInSight() const
{
  return mBoard.GetInSight(mWhoseTurn);
}
//---------------------------------------------------------------------------
const ChessMove ChessGame::SuggestMove() const
{
  //Get all possible moves
  std::vector<ChessMove> moves = mBoard.GetAllPossibleMoves(mWhoseTurn);
  std::random_shuffle(moves.begin(), moves.end() );

  const int nMoves = moves.size();
  assert(nMoves>0);

  const std::vector<double> moveValues = AttributeValues(moves);

  const std::vector<double>::const_iterator pMove
    = std::max_element( moveValues.begin(),moveValues.end() );
  const int index = pMove - moveValues.begin();
  assert(index >= 0);
  assert(index < static_cast<int>(moves.size()));
  return moves[ index ];

}
//---------------------------------------------------------------------------
const std::vector<double> ChessGame::AttributeValues(
  const std::vector<ChessMove>& moves) const
{
  const int nMoves = moves.size();
  std::vector<double> v(nMoves,0.0);
  for (int i=0; i!=nMoves; ++i)
  {
    v[i] = AttributeValue(moves[i]);
  }
  return v;
}
//---------------------------------------------------------------------------
const double ChessGame::AttributeValue(
  const ChessMove& move) const
{
  double value = 0.0;
  const int y1 = move.y1;
  const int x1 = move.x1;
  const int y2 = move.y2;
  const int x2 = move.x2;
  const ChessPiece piece = mBoard.GetPiece(x1,y1);
  assert(piece.IsNull()==false);
  //const EnumChessPieceColor color = piece.GetColor();

  if (mBoard.GetPiece(x2,y2).IsNull()==false)
  {
    //An expensive piece should not take a cheaper piece
    //The more expensive the piece to move,
    //  the less motivated it will be to take a piece
    if (piece.GetType()==king  ) { value-=100.0; }
    if (piece.GetType()==queen ) { value-= 9.0; }
    if (piece.GetType()==rook  ) { value-= 4.0; }
    if (piece.GetType()==bishop) { value-= 2.0; }
    if (piece.GetType()==knight) { value-= 2.0; }
    if (piece.GetType()==pawn  ) { value-= 0.0; }
    //The more expensive the piece to take,
    //  the more motivated it will be to take it
    const ChessPiece victim = mBoard.GetPiece(x2,y2);
    if (victim.GetType()==king  ) { value+=100000.0; }
    if (victim.GetType()==queen ) { value+=10.0; }
    if (victim.GetType()==rook  ) { value+= 5.0; }
    if (victim.GetType()==bishop) { value+= 3.0; }
    if (victim.GetType()==knight) { value+= 3.0; }
    if (victim.GetType()==pawn  ) { value+= 1.0; }
  }
  return value;
}
//---------------------------------------------------------------------------
//Parse in the format:
//a2 a4
//a2xb3
//Na1 a8
//Pc1xd5
const bool ChessGame::ParseMove(
  const std::string& s,
  ChessMove& move) const
{
  if (s.empty()==true) return false;
  //Obtain chesstypes from the only upper case character at the first index
  //If there is no upper case, it is a pawn
  if (s=="o-o" || s=="O-O" || s == "0-0")
  {
    const int y = (this->GetWhoseTurn() == white ? 0 : 7);
    move = ChessMove(king,4,y,false,6,y);
    return true;
  }
  if (s=="o-o-o" || s=="O-O-O" || s == "0-0-0")
  {
    const int y = (this->GetWhoseTurn() == white ? 0 : 7);
    move = ChessMove(king,4,y,false,2,y);
    return true;
  }

  switch(s[0])
  {
    case 'N': move.type = knight; break;
    case 'B': move.type = bishop; break;
    case 'R': move.type = rook  ; break;
    case 'Q': move.type = queen ; break;
    case 'K': move.type = king  ; break;
    default: move.type = pawn;
  }

  const int minSize = (move.type == pawn ? 5 : 6);
  if (static_cast<int>(s.size()) < minSize) return false;

  if (move.type == pawn)
  {
     if (s[2]==' ') move.capture = false;
     else if (s[2]=='x') move.capture = true;
     else return false;
  }
  else
  {
     if (s[3]==' ') move.capture = false;
     else if (s[3]=='x') move.capture = true;
     else return false;
  }

  const std::string from = (move.type == pawn ? s.substr(0,2) : s.substr(1,2) );
  const std::string to   = (move.type == pawn ? s.substr(3,2) : s.substr(4,2) );

  switch(from[0])
  {
    case 'a': move.x1 = 0; break;
    case 'b': move.x1 = 1; break;
    case 'c': move.x1 = 2; break;
    case 'd': move.x1 = 3; break;
    case 'e': move.x1 = 4; break;
    case 'f': move.x1 = 5; break;
    case 'g': move.x1 = 6; break;
    case 'h': move.x1 = 7; break;
    default: return false;
  }

  switch(from[1])
  {
    case '1': move.y1 = 0; break;
    case '2': move.y1 = 1; break;
    case '3': move.y1 = 2; break;
    case '4': move.y1 = 3; break;
    case '5': move.y1 = 4; break;
    case '6': move.y1 = 5; break;
    case '7': move.y1 = 6; break;
    case '8': move.y1 = 7; break;
    default: return false;
  }

  switch(to[0])
  {
    case 'a': move.x2 = 0; break;
    case 'b': move.x2 = 1; break;
    case 'c': move.x2 = 2; break;
    case 'd': move.x2 = 3; break;
    case 'e': move.x2 = 4; break;
    case 'f': move.x2 = 5; break;
    case 'g': move.x2 = 6; break;
    case 'h': move.x2 = 7; break;
    default: return false;
  }

  switch(to[1])
  {
    case '1': move.y2 = 0; break;
    case '2': move.y2 = 1; break;
    case '3': move.y2 = 2; break;
    case '4': move.y2 = 3; break;
    case '5': move.y2 = 4; break;
    case '6': move.y2 = 5; break;
    case '7': move.y2 = 6; break;
    case '8': move.y2 = 7; break;
    default: return false;
  }

  //if it contains exactly one 'x' it is a capture
  return true;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
