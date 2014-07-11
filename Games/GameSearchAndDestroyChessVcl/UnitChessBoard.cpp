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
#include <stdexcept>
#include <cassert>
#include <iostream>
#include "UnitChessPiece.h"
#pragma hdrstop

#include "UnitChessBoard.h"
//---------------------------------------------------------------------------
ChessBoard::ChessBoard()
  : mPieces(GetInitialSetup())
{

}
//---------------------------------------------------------------------------
const ChessPiece ChessBoard::GetPiece(const int x, const int y) const
{
  return mPieces[y][x];
}
//---------------------------------------------------------------------------
void ChessBoard::SetPiece(const ChessPiece& piece, const int x, const int y)
{
  mPieces[y][x] = piece;
  assert(this->GetPiece(x,y) == piece);
}
//---------------------------------------------------------------------------
const bool ChessBoard::IsGameOver() const
{
  bool whiteHasKing = false;
  bool blackHasKing = false;

  for (int y=0; y!=8; ++y)
  {
    for (int x=0; x!=8; ++x)
    {
      const ChessPiece piece = mPieces[y][x];
      if (piece.IsNull()==false && piece.GetType()==king)
      {
        if (piece.GetColor() == white)
          whiteHasKing = true;
        else
          blackHasKing = true;
      }
    }
  }
  return (whiteHasKing == false || blackHasKing == false);
}
//---------------------------------------------------------------------------
const EnumChessPieceColor ChessBoard::GetWinner() const
{
  assert(this->IsGameOver()==true);
  for (int y=0; y!=8; ++y)
  {
    for (int x=0; x!=8; ++x)
    {
      const ChessPiece piece = mPieces[y][x];
      if (piece.GetType()==king)
      {
        if (piece.GetColor() == white)
          return white;
        else
          return black;
      }
    }
  }
  assert(!"Should not get here");
  throw std::logic_error("Cannot find winner");
}
//---------------------------------------------------------------------------
const bool ChessBoard::CanDoMove(const ChessMove& move) const
{
  const ChessPiece piece = this->GetPiece(move.x1,move.y1);
  //Is there a chesspiece?
  if (piece.IsNull()==true) return false;
  //Is it of the right type?
  if (piece.GetType()!=move.type) return false;
  //Is it of the right color? ->Checked by ChessGame
  //Is the destination free or is there an enemy?
  const ChessPiece destination = this->GetPiece(move.x2,move.y2);
  if ( destination.IsNull()==true
    && move.capture == true) return false; //Free space && capture
  if ( destination.IsNull()==false)
  {
    //Cannot capture own pieces
    if (destination.GetColor()==piece.GetColor())
      return false;
    if (destination.GetColor()!=piece.GetColor()
      && move.capture == false) return false; //An enemy && no capture
  }
  return this->IsValidMove(move);
}
//---------------------------------------------------------------------------
void ChessBoard::DoMove(const ChessMove& move)
{
  assert(this->CanDoMove(move)==true);
  const ChessPiece piece = this->GetPiece(move.x1,move.y1);

  if (piece.GetType()==king
    && move.x1 == 4
    && (move.x2 == 2 || move.x2 == 6) )
  {
    const EnumChessPieceColor color = piece.GetColor();
    assert( (color == white && move.y1 == 0 && move.y2 == 0)
      ||    (color == black && move.y1 == 7 && move.y2 == 7) );
    const int y = move.y2;
    //Castling
    if (move.x2 == 2)
    {
      //Castling long
      this->SetPiece(ChessPiece(color,king),2,y); //Move King
      this->SetPiece(ChessPiece(color,rook),3,y); //Move rook
      this->SetPiece(ChessPiece(),4,y);           //Erase old king
      this->SetPiece(ChessPiece(),0,y);           //Erase old rook
    }
    else
    {
      //Castling short
      this->SetPiece(ChessPiece(color,king),6,y); //Move King
      this->SetPiece(ChessPiece(color,rook),5,y); //Move rook
      this->SetPiece(ChessPiece(),4,y);           //Erase old king
      this->SetPiece(ChessPiece(),7,y);           //Erase old rook
    }
  }
  else if (piece.GetType()==pawn
    && this->GetPiece(move.x2,move.y2).IsNull()==true
    && move.x1 != move.x2
    && move.y1 != move.y2)
  {
    //En passant
    this->SetPiece(ChessPiece(piece.GetColor(),pawn),move.x2,move.y2); //Move pawn
    this->SetPiece(ChessPiece(),move.x1,move.y1); //Erase old pawn
    this->SetPiece(ChessPiece(),move.x2,move.y1); //Capture pawn
  }
  else if (piece.GetType()==pawn
    && (move.y2 == 0 || move.y2 == 7) )
  {
    //Promotion to queen
    this->SetPiece(ChessPiece(),move.x1,move.y1); //Overwrite old piece by NullType
    this->SetPiece(ChessPiece(piece.GetColor(),queen),move.x2,move.y2);
  }
  else
  {
    //Regular move (i.e. non-castling)
    this->SetPiece(ChessPiece(),move.x1,move.y1); //Overwrite old piece by NullType
    this->SetPiece(piece,move.x2,move.y2);
  }
  mMoves.push_back(move);
}
//---------------------------------------------------------------------------
const bool ChessBoard::CanDoCastlingShort(const EnumChessPieceColor color) const
{
  //Determine the y
  const int y = (color == white ? 0 : 7);
  //King must be in place
  if(this->GetPiece(4,y).GetType() != king) return false;
  //Is the rook in place?
  if(this->GetPiece(7,y).GetType() != rook) return false;
  //Is nothing in between?
  if(this->GetPiece(5,y).IsNull() == false) return false;
  if(this->GetPiece(6,y).IsNull() == false) return false;

  typedef std::vector<ChessMove>::const_iterator Iter;
  const Iter j = mMoves.end();
  for (Iter i = mMoves.begin(); i!=j; ++i)
  {
    //Check if king has moved
    if ( (*i).type == king && (*i).y1 == y) return false;
    //Check if kingside rook has moved
    if ( (*i).type == rook && (*i).y1 == y && (*i).x1 == 7) return false;
  }
  return true;
}
//---------------------------------------------------------------------------
const bool ChessBoard::CanDoCastlingLong(const EnumChessPieceColor color) const
{
  //Determine the y
  const int y = (color == white ? 0 : 7);
  //King must be in place
  if(this->GetPiece(4,y).GetType() != king) return false;
  //Is the rook in place?
  if(this->GetPiece(0,y).GetType() != rook) return false;
  //Is nothing in between?
  if(this->GetPiece(1,y).IsNull() == false) return false;
  if(this->GetPiece(2,y).IsNull() == false) return false;
  if(this->GetPiece(3,y).IsNull() == false) return false;

  typedef std::vector<ChessMove>::const_iterator Iter;
  const Iter j = mMoves.end();
  for (Iter i = mMoves.begin(); i!=j; ++i)
  {
    //Check if king has moved
    if ( (*i).type == king && (*i).y1 == y) return false;
    //Check if kingside rook has moved
    if ( (*i).type == rook && (*i).y1 == y && (*i).x1 == 0) return false;
  }
  return true;
}
//---------------------------------------------------------------------------
const std::vector<std::vector<ChessPiece> > ChessBoard::GetInitialSetup()
{
  std::vector<std::vector<ChessPiece> > v(8,std::vector<ChessPiece>(8));
  //v has [y][x] index
  v[0][0] = ChessPiece(white,rook  );
  v[0][1] = ChessPiece(white,knight);
  v[0][2] = ChessPiece(white,bishop);
  v[0][3] = ChessPiece(white,queen );
  v[0][4] = ChessPiece(white,king  );
  v[0][5] = ChessPiece(white,bishop);
  v[0][6] = ChessPiece(white,knight);
  v[0][7] = ChessPiece(white,rook  );
  v[1][0] = ChessPiece(white,pawn  );
  v[1][1] = ChessPiece(white,pawn  );
  v[1][2] = ChessPiece(white,pawn  );
  v[1][3] = ChessPiece(white,pawn  );
  v[1][4] = ChessPiece(white,pawn  );
  v[1][5] = ChessPiece(white,pawn  );
  v[1][6] = ChessPiece(white,pawn  );
  v[1][7] = ChessPiece(white,pawn  );
  v[7][0] = ChessPiece(black,rook  );
  v[7][1] = ChessPiece(black,knight);
  v[7][2] = ChessPiece(black,bishop);
  v[7][3] = ChessPiece(black,queen );
  v[7][4] = ChessPiece(black,king  );
  v[7][5] = ChessPiece(black,bishop);
  v[7][6] = ChessPiece(black,knight);
  v[7][7] = ChessPiece(black,rook  );
  v[6][0] = ChessPiece(black,pawn  );
  v[6][1] = ChessPiece(black,pawn  );
  v[6][2] = ChessPiece(black,pawn  );
  v[6][3] = ChessPiece(black,pawn  );
  v[6][4] = ChessPiece(black,pawn  );
  v[6][5] = ChessPiece(black,pawn  );
  v[6][6] = ChessPiece(black,pawn  );
  v[6][7] = ChessPiece(black,pawn  );
  return v;
}
//---------------------------------------------------------------------------
//Color denotes the player who's turn it is, i.e. the player looking at the board
void ChessBoard::CoutPieces(
  const EnumChessPieceColor color) const
{
  const int yBegin = (color == black ? 0 : 7);
  const int yEnd   = (color == black ? 8 : -1);
  const int yStep  = (color == black ? 1 : -1);
  const int xBegin = (color == white ? 0 : 7);
  const int xEnd   = (color == white ? 8 : -1);
  const int xStep  = (color == white ? 1 : -1);

  if (color == white)
    std::cout << "   A  B  C  D  E  F  G  H " << std::endl;
  else
    std::cout << "   H  G  F  E  D  C  B  A " << std::endl;

  for (int y=yBegin; y!=yEnd; y+=yStep)
  {
    std::cout << "  -------------------------" << std::endl;
    std::cout << (y+1) << " ";
    for (int x=xBegin; x!=xEnd; x+=xStep)
    {
      std::cout << "|" << mPieces[y][x];
    }
    std::cout << "| " << (y+1) << std::endl;

  }
  std::cout << "  -------------------------" << std::endl;
  if (color == white)
    std::cout << "   A  B  C  D  E  F  G  H " << std::endl;
  else
    std::cout << "   H  G  F  E  D  C  B  A " << std::endl;

}
//---------------------------------------------------------------------------
//Color denotes the player who's turn it is, i.e. the player looking at the board
void ChessBoard::CoutSight(
  const EnumChessPieceColor color) const
{
  //
  const std::vector<std::vector<bool> > inSight = this->GetInSight(color);

  const int yBegin = (color == black ? 0 : 7);
  const int yEnd   = (color == black ? 8 : -1);
  const int yStep  = (color == black ? 1 : -1);
  const int xBegin = (color == white ? 0 : 7);
  const int xEnd   = (color == white ? 8 : -1);
  const int xStep  = (color == white ? 1 : -1);

  if (color == white)
    std::cout << "   A  B  C  D  E  F  G  H " << std::endl;
  else
    std::cout << "   H  G  F  E  D  C  B  A " << std::endl;

  for (int y=yBegin; y!=yEnd; y+=yStep)
  {
    std::cout << "  -------------------------" << std::endl;
    std::cout << (y+1) << " ";
    for (int x=xBegin; x!=xEnd; x+=xStep)
    {
      std::cout << "|" << (inSight[y][x]==true ? mPieces[y][x] : ChessPiece() );
    }
    std::cout << "| " << (y+1) << std::endl;

  }
  std::cout << "  -------------------------" << std::endl;
  if (color == white)
    std::cout << "   A  B  C  D  E  F  G  H " << std::endl;
  else
    std::cout << "   H  G  F  E  D  C  B  A " << std::endl;


}
//---------------------------------------------------------------------------
const std::vector<std::vector<bool> > ChessBoard::GetInSight(const EnumChessPieceColor color) const
{
  std::vector<std::vector<bool> > inSight(8, std::vector<bool>(8,false));

  for (int y=0; y!=8; ++y)
  {
    for (int x=0; x!=8; ++x)
    {
      //Get the piece there
      const ChessPiece piece = this->GetPiece(x,y);
      //Empty or occupied by enemy? Then continue
      if (piece.IsNull()==true || piece.GetColor()!=color) continue;
      //Occupied by this color
      inSight[y][x] = true;
      //Then get all its valid moves
      const std::vector<ChessMove> moves = this->GetAllValidMoves(x,y);
      const std::vector<ChessMove>::const_iterator j = moves.end();
      for (std::vector<ChessMove>::const_iterator i = moves.begin(); i!=j; ++i)
      {
        inSight[(*i).y2][(*i).x2] = true;
      }
      //Special treatment of pawns
      if (piece.GetType() == pawn)
      {
        if (piece.GetColor()==white)
        {
          //Always look a single square forward
          inSight[y+1][x] = true;
          //Look two squares forward, if the first is not occupied
          if (y==1 && GetPiece(x,y+1).IsNull()==true)
          {
            inSight[y+2][x] = true;
          }
          //Look sideways left
          if (x > 0 && GetPiece(x-1,y+1).IsNull()==true)
          {
            inSight[y+1][x-1] = true;
          }
          //Look sideways right
          if (x < 7 && GetPiece(x+1,y+1).IsNull()==true)
          {
            inSight[y+1][x+1] = true;
          }
          //Look sideways if en passant is possible
          if (y == 4                            //4th row
            && this->mMoves.back().type == pawn //Black moved a pawn
            && this->mMoves.back().y1 == 6      //Black moved two places
            && this->mMoves.back().y2 == 4)     //Black moved two places
          {
            if (this->mMoves.back().x1 == x-1)
              inSight[y][x-1] = true;
            else if (this->mMoves.back().x1 == x+1)
              inSight[y][x+1] = true;
          }
        }
        else
        {
          //Always look a single square forward
          inSight[y-1][x] = true;
          //Look two squares forward, if the first is not occupied
          if (y==6 && GetPiece(x,y-1).IsNull()==true)
          {
            inSight[y-2][x] = true;
          }
          //Look sideways left
          if (x > 0 && GetPiece(x-1,y-1).IsNull()==true)
          {
            inSight[y-1][x-1] = true;
          }
          //Look sideways right
          if (x < 7 && GetPiece(x+1,y-1).IsNull()==true)
          {
            inSight[y-1][x+1] = true;
          }
          //Look sideways if en passant is possible
          if (y == 3                            //3rd row
            && this->mMoves.back().type == pawn //White moved a pawn
            && this->mMoves.back().y1 == 1      //White moved two places
            && this->mMoves.back().y2 == 3)     //White moved two places
          {
            if (this->mMoves.back().x1 == x-1)
              inSight[y][x-1] = true;
            else if (this->mMoves.back().x1 == x+1)
              inSight[y][x+1] = true;
          }
        }
      }
    }
  }
  return inSight;
}
//---------------------------------------------------------------------------
const bool ChessBoard::IsValidMove(const ChessMove& move) const
{
  const std::vector<ChessMove> moves = this->GetAllValidMoves(move.x1, move.y1);
  if (std::find(moves.begin(),moves.end(),move)!=moves.end())
    return true;
  else
    return false;

}
//---------------------------------------------------------------------------
const std::vector<ChessMove> ChessBoard::GetAllPossibleMoves(
  const EnumChessPieceColor whoseTurn) const
{
  std::vector<ChessMove> allMoves;
  for (int y=0; y!=8; ++y)
  {
    for (int x=0; x!=8; ++x)
    {
      if (this->GetPiece(x,y).IsNull() == false 
       && this->GetPiece(x,y).GetColor()==whoseTurn)
      {
        //Get all valid moves of this player's piece here
        const std::vector<ChessMove> thisPieceMoves = GetAllValidMoves(x,y);
        //Append it to allMoves
        std::copy(
          thisPieceMoves.begin(),thisPieceMoves.end(),
          std::back_inserter(allMoves));
      }
    }
  }
  return allMoves;
}
//---------------------------------------------------------------------------
const std::vector<ChessMove> ChessBoard::GetAllValidMoves(
  const int x, const int y) const
{
  const ChessPiece piece = GetPiece(x,y);
  assert(piece.IsNull()==false);
  switch (piece.GetType())
  {
    case pawn  : return GetAllValidMovesPawn(x,y);
    case knight: return GetAllValidMovesKnight(x,y);
    case bishop: return GetAllValidMovesBishop(x,y);
    case rook  : return GetAllValidMovesRook(x,y);
    case queen : return GetAllValidMovesQueen(x,y);
    case king  : return GetAllValidMovesKing(x,y);
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown EnumChessPieceType");
}
//---------------------------------------------------------------------------
const std::vector<ChessMove> ChessBoard::GetAllValidMovesPawn(
  const int x, const int y) const
{
  const ChessPiece piece = GetPiece(x,y);
  assert(piece.IsNull()==false);
  assert(piece.GetType() == pawn);

  std::vector<ChessMove> moves;

  if (piece.GetColor()==white)
  {
    //Move single square forward
    if (GetPiece(x,y+1).IsNull()==true)
    {
      moves.push_back(ChessMove(pawn,x,y,false,x,y+1));
    }
    //Move two squares forward
    if (y==1
      && GetPiece(x,y+1).IsNull()==true
      && GetPiece(x,y+2).IsNull()==true)
    {
      moves.push_back(ChessMove(pawn,x,y,false,x,y+2));
    }
    //Capture left
    if (x > 0
      && GetPiece(x-1,y+1).IsNull()==false
      && GetPiece(x-1,y+1).GetColor()==black)
    {
      moves.push_back(ChessMove(pawn,x,y,true,x-1,y+1));
    }
    //Capture right
    if (x < 7
      && GetPiece(x+1,y+1).IsNull()==false
      && GetPiece(x+1,y+1).GetColor()==black)
    {
      moves.push_back(ChessMove(pawn,x,y,true,x+1,y+1));
    }
    //En passant
    if (y == 4
      && mMoves.back().y1 == 6 //Black had moved two squares
      && mMoves.back().y2 == 4)
    {
      if (mMoves.back().x1 == x - 1) //To the left
      {
        //Note: En passant is not regarded as a capture, as the spot moved to is empty
        moves.push_back(ChessMove(pawn,x,y, false /* note */ ,x-1,y+1));
      }
      else if (mMoves.back().x1 == x + 1) //To the right
      {
        //Note: En passant is not regarded as a capture, as the spot moved to is empty
        moves.push_back(ChessMove(pawn,x,y,false /* note */,x+1,y+1));
      }
    }
  }
  else
  {
    //Move single square forward
    if (GetPiece(x,y-1).IsNull()==true)
    {
      moves.push_back(ChessMove(pawn,x,y,false,x,y-1));
    }
    //Move two squares forward
    if (y==6
      && GetPiece(x,y-1).IsNull()==true
      && GetPiece(x,y-2).IsNull()==true)
    {
      moves.push_back(ChessMove(pawn,x,y,false,x,y-2));
    }
    //Capture left
    if (x > 0
      && GetPiece(x-1,y-1).IsNull()==false
      && GetPiece(x-1,y-1).GetColor()==white)
    {
      moves.push_back(ChessMove(pawn,x,y,true,x-1,y-1));
    }
    //Capture right
    if (x < 7
      && GetPiece(x+1,y-1).IsNull()==false
      && GetPiece(x+1,y-1).GetColor()==white)
    {
      moves.push_back(ChessMove(pawn,x,y,true,x+1,y-1));
    }
    //En passant
    if (y == 3
      && mMoves.back().y1 == 1  //White had moved two squares
      && mMoves.back().y2 == 3)
    {
      if (mMoves.back().x1 == x - 1) //To the left
      {
        //Note: En passant is not regarded as a capture, as the spot moved to is empty
        moves.push_back(ChessMove(pawn,x,y, false /* note */ ,x-1,y-1));
      }
      else if (mMoves.back().x1 == x + 1) //To the right
      {
        //Note: En passant is not regarded as a capture, as the spot moved to is empty
        moves.push_back(ChessMove(pawn,x,y,false /* note */,x+1,y-1));
      }
    }
  }
  return moves;
}
//---------------------------------------------------------------------------
const std::vector<ChessMove> ChessBoard::GetAllValidMovesKnight(
  const int x, const int y) const
{
  const ChessPiece piece = GetPiece(x,y);
  assert(piece.IsNull()==false);
  assert(piece.GetType() == knight);

  std::vector<ChessMove> moves;

  //-2 -1
  if (x > 1 && y > 0)
  {
    //Is it a capture?
    if (GetPiece(x-2,y-1).IsNull() == true)
    {
      moves.push_back(ChessMove(knight,x,y,false,x-2,y-1)); //No capture
    }
    else if (GetPiece(x-2,y-1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(knight,x,y,true,x-2,y-1)); //Capture of enemy
    }
  }
  //-1 -2
  if (x > 0 && y > 1)
  {
    //Is it a capture?
    if (GetPiece(x-1,y-2).IsNull() == true)
    {
      moves.push_back(ChessMove(knight,x,y,false,x-1,y-2)); //No capture
    }
    else if (GetPiece(x-1,y-2).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(knight,x,y,true,x-1,y-2)); //Capture of enemy
    }
  }
  //+2 -1
  if (x < 6 && y > 0)
  {
    //Is it a capture?
    if (GetPiece(x+2,y-1).IsNull() == true)
    {
      moves.push_back(ChessMove(knight,x,y,false,x+2,y-1)); //No capture
    }
    else if (GetPiece(x+2,y-1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(knight,x,y,true,x+2,y-1)); //Capture of enemy
    }
  }
  //-1 +2
  if (x > 0 && y < 6)
  {
    //Is it a capture?
    if (GetPiece(x-1,y+2).IsNull() == true)
    {
      moves.push_back(ChessMove(knight,x,y,false,x-1,y+2)); //No capture
    }
    else if (GetPiece(x-1,y+2).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(knight,x,y,true,x-1,y+2)); //Capture of enemy
    }
  }
  //-2 +1
  if (x > 1 && y < 7)
  {
    //Is it a capture?
    if (GetPiece(x-2,y+1).IsNull() == true)
    {
      moves.push_back(ChessMove(knight,x,y,false,x-2,y+1)); //No capture
    }
    else if (GetPiece(x-2,y+1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(knight,x,y,true,x-2,y+1)); //Capture of enemy
    }
  }
  //+1 -2
  if (x < 7 && y > 1)
  {
    //Is it a capture?
    if (GetPiece(x+1,y-2).IsNull() == true)
    {
      moves.push_back(ChessMove(knight,x,y,false,x+1,y-2)); //No capture
    }
    else if (GetPiece(x+1,y-2).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(knight,x,y,true,x+1,y-2)); //Capture of enemy
    }
  }

  //+2 +1
  if (x < 6 && y < 7)
  {
    //Is it a capture?
    if (GetPiece(x+2,y+1).IsNull() == true)
    {
      moves.push_back(ChessMove(knight,x,y,false,x+2,y+1)); //No capture
    }
    else if (GetPiece(x+2,y+1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(knight,x,y,true,x+2,y+1)); //Capture of enemy
    }
  }
  //+1 +2
  if (x < 7 && y < 6)
  {
    //Is it a capture?
    if (GetPiece(x+1,y+2).IsNull() == true)
    {
      moves.push_back(ChessMove(knight,x,y,false,x+1,y+2)); //No capture
    }
    else if (GetPiece(x+1,y+2).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(knight,x,y,true,x+1,y+2)); //Capture of enemy
    }
  }

  return moves;
}
//---------------------------------------------------------------------------
const std::vector<ChessMove> ChessBoard::GetAllValidMovesBishop(
  const int x, const int y) const
{
  const ChessPiece piece = GetPiece(x,y);
  assert(piece.IsNull()==false);
  assert(piece.GetType() == bishop);

  std::vector<ChessMove> moves;

  //+x +x
  for (int i=1; x+i<8 && y+i<8; ++i)
  {
    //Is it a capture
    if (GetPiece(x+i,y+i).IsNull() == true)
    {
      moves.push_back(ChessMove(bishop,x,y,false,x+i,y+i)); //No capture
    }
    else if (GetPiece(x+i,y+i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(bishop,x,y,true,x+i,y+i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //-x +x
  for (int i=1; x-i>-1 && y+i<8; ++i)
  {
    //Is it a capture
    if (GetPiece(x-i,y+i).IsNull() == true)
    {
      moves.push_back(ChessMove(bishop,x,y,false,x-i,y+i)); //No capture
    }
    else if (GetPiece(x-i,y+i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(bishop,x,y,true,x-i,y+i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //+x -x
  for (int i=1; x+i<8 && y-i>-1; ++i)
  {
    //Is it a capture
    if (GetPiece(x+i,y-i).IsNull() == true)
    {
      moves.push_back(ChessMove(bishop,x,y,false,x+i,y-i)); //No capture
    }
    else if (GetPiece(x+i,y-i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(bishop,x,y,true,x+i,y-i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //-x -x
  for (int i=1; x-i>-1 && y-i>-1; ++i)
  {
    //Is it a capture
    if (GetPiece(x-i,y-i).IsNull() == true)
    {
      moves.push_back(ChessMove(bishop,x,y,false,x-i,y-i)); //No capture
    }
    else if (GetPiece(x-i,y-i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(bishop,x,y,true,x-i,y-i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  return moves;
}
//---------------------------------------------------------------------------
const std::vector<ChessMove> ChessBoard::GetAllValidMovesRook(
  const int x, const int y) const
{
  const ChessPiece piece = GetPiece(x,y);
  assert(piece.IsNull()==false);
  assert(piece.GetType() == rook);

  std::vector<ChessMove> moves;

  //+x +0
  for (int i=1; x+i<8; ++i)
  {
    //Is it a capture
    if (GetPiece(x+i,y+0).IsNull() == true)
    {
      moves.push_back(ChessMove(rook,x,y,false,x+i,y+0)); //No capture
    }
    else if (GetPiece(x+i,y+0).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(rook,x,y,true,x+i,y+0)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }
  //-x +0
  for (int i=1; x-i>-1; ++i)
  {
    //Is it a capture
    if (GetPiece(x-i,y+0).IsNull() == true)
    {
      moves.push_back(ChessMove(rook,x,y,false,x-i,y+0)); //No capture
    }
    else if (GetPiece(x-i,y+0).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(rook,x,y,true,x-i,y+0)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //+0 +x
  for (int i=1; y+i<8; ++i)
  {
    //Is it a capture
    if (GetPiece(x+0,y+i).IsNull() == true)
    {
      moves.push_back(ChessMove(rook,x,y,false,x+0,y+i)); //No capture
    }
    else if (GetPiece(x+0,y+i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(rook,x,y,true,x+0,y+i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //+0 -x
  for (int i=1; y-i>-1; ++i)
  {
    //Is it a capture
    if (GetPiece(x-0,y-i).IsNull() == true)
    {
      moves.push_back(ChessMove(rook,x,y,false,x-0,y-i)); //No capture
    }
    else if (GetPiece(x-0,y-i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(rook,x,y,true,x-0,y-i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  return moves;
}
//---------------------------------------------------------------------------
const std::vector<ChessMove> ChessBoard::GetAllValidMovesQueen(
  const int x, const int y) const
{
  const ChessPiece piece = GetPiece(x,y);
  assert(piece.IsNull()==false);
  assert(piece.GetType() == queen);

  std::vector<ChessMove> moves;


  //+x +x
  for (int i=1; x+i<8 && y+i<8; ++i)
  {
    //Is it a capture
    if (GetPiece(x+i,y+i).IsNull() == true)
    {
      moves.push_back(ChessMove(queen,x,y,false,x+i,y+i)); //No capture
    }
    else if (GetPiece(x+i,y+i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(queen,x,y,true,x+i,y+i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //-x +x
  for (int i=1; x-i>-1 && y+i<8; ++i)
  {
    //Is it a capture
    if (GetPiece(x-i,y+i).IsNull() == true)
    {
      moves.push_back(ChessMove(queen,x,y,false,x-i,y+i)); //No capture
    }
    else if (GetPiece(x-i,y+i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(queen,x,y,true,x-i,y+i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //+x -x
  for (int i=1; x+i<8 && y-i>-1; ++i)
  {
    //Is it a capture
    if (GetPiece(x+i,y-i).IsNull() == true)
    {
      moves.push_back(ChessMove(queen,x,y,false,x+i,y-i)); //No capture
    }
    else if (GetPiece(x+i,y-i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(queen,x,y,true,x+i,y-i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //-x -x
  for (int i=1; x-i>-1 && y-i>-1; ++i)
  {
    //Is it a capture
    if (GetPiece(x-i,y-i).IsNull() == true)
    {
      moves.push_back(ChessMove(queen,x,y,false,x-i,y-i)); //No capture
    }
    else if (GetPiece(x-i,y-i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(queen,x,y,true,x-i,y-i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //+x +0
  for (int i=1; x+i<8; ++i)
  {
    //Is it a capture
    if (GetPiece(x+i,y+0).IsNull() == true)
    {
      moves.push_back(ChessMove(queen,x,y,false,x+i,y+0)); //No capture
    }
    else if (GetPiece(x+i,y+0).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(queen,x,y,true,x+i,y+0)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }
  //-x +0
  for (int i=1; x-i>-1; ++i)
  {
    //Is it a capture
    if (GetPiece(x-i,y+0).IsNull() == true)
    {
      moves.push_back(ChessMove(queen,x,y,false,x-i,y+0)); //No capture
    }
    else if (GetPiece(x-i,y+0).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(queen,x,y,true,x-i,y+0)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //+0 +x
  for (int i=1; y+i<8; ++i)
  {
    //Is it a capture
    if (GetPiece(x+0,y+i).IsNull() == true)
    {
      moves.push_back(ChessMove(queen,x,y,false,x+0,y+i)); //No capture
    }
    else if (GetPiece(x+0,y+i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(queen,x,y,true,x+0,y+i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  //+0 -x
  for (int i=1; y-i>-1; ++i)
  {
    //Is it a capture
    if (GetPiece(x-0,y-i).IsNull() == true)
    {
      moves.push_back(ChessMove(queen,x,y,false,x-0,y-i)); //No capture
    }
    else if (GetPiece(x-0,y-i).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(queen,x,y,true,x-0,y-i)); //Capture of enemy
      break;
    }
    else
    {
      break; //Own color
    }
  }

  return moves;
}
//---------------------------------------------------------------------------
const std::vector<ChessMove> ChessBoard::GetAllValidMovesKing(
  const int x, const int y) const
{
  const ChessPiece piece = GetPiece(x,y);
  assert(piece.IsNull()==false);
  assert(piece.GetType() == king);

  std::vector<ChessMove> moves;

  //+0 -1
  if (y > 0)
  {
    //Is it a capture
    if (GetPiece(x+0,y-1).IsNull() == true)
    {
      moves.push_back(ChessMove(king,x,y,false,x+0,y-1)); //No capture
    }
    else if (GetPiece(x+0,y-1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(king,x,y,true,x+0,y-1)); //Capture of enemy
    }
  }
  //-1 -1
  if (y > 0 && x > 0)
  {
    //Is it a capture
    if (GetPiece(x-1,y-1).IsNull() == true)
    {
      moves.push_back(ChessMove(king,x,y,false,x-1,y-1)); //No capture
    }
    else if (GetPiece(x-1,y-1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(king,x,y,true,x-1,y-1)); //Capture of enemy
    }
  }
  //+1 -1
  if (y > 0 && x < 7)
  {
    //Is it a capture
    if (GetPiece(x+1,y-1).IsNull() == true)
    {
      moves.push_back(ChessMove(king,x,y,false,x+1,y-1)); //No capture
    }
    else if (GetPiece(x+1,y-1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(king,x,y,true,x+1,y-1)); //Capture of enemy
    }
  }


  //+0 +1
  if (y < 7)
  {
    //Is it a capture
    if (GetPiece(x+0,y+1).IsNull() == true)
    {
      moves.push_back(ChessMove(king,x,y,false,x+0,y+1)); //No capture
    }
    else if (GetPiece(x+0,y+1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(king,x,y,true,x+0,y+1)); //Capture of enemy
    }
  }
  //-1 +1
  if (y < 7 && x > 0)
  {
    //Is it a capture
    if (GetPiece(x-1,y+1).IsNull() == true)
    {
      moves.push_back(ChessMove(king,x,y,false,x-1,y+1)); //No capture
    }
    else if (GetPiece(x-1,y+1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(king,x,y,true,x-1,y+1)); //Capture of enemy
    }
  }
  //+1 +1
  if (y < 7 && x < 7)
  {
    //Is it a capture
    if (GetPiece(x+1,y+1).IsNull() == true)
    {
      moves.push_back(ChessMove(king,x,y,false,x+1,y+1)); //No capture
    }
    else if (GetPiece(x+1,y+1).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(king,x,y,true,x+1,y+1)); //Capture of enemy
    }
  }


  //-1 +0
  if (x > 0)
  {
    //Is it a capture
    if (GetPiece(x-1,y+0).IsNull() == true)
    {
      moves.push_back(ChessMove(king,x,y,false,x-1,y+0)); //No capture
    }
    else if (GetPiece(x-1,y+0).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(king,x,y,true,x-1,y+0)); //Capture of enemy
    }
  }
  //+1 +1
  if (x < 7)
  {
    //Is it a capture
    if (GetPiece(x+1,y+0).IsNull() == true)
    {
      moves.push_back(ChessMove(king,x,y,false,x+1,y+0)); //No capture
    }
    else if (GetPiece(x+1,y+0).GetColor() != piece.GetColor())
    { //Is it an enemy?
      moves.push_back(ChessMove(king,x,y,true,x+1,y+0)); //Capture of enemy
    }
  }

  //Can do castling?
  if (this->CanDoCastlingLong(piece.GetColor()))
    moves.push_back(ChessMove(king,x,y,false,x-2,y));
  if (this->CanDoCastlingShort(piece.GetColor()))
    moves.push_back(ChessMove(king,x,y,false,x+2,y));

  return moves;
}
//---------------------------------------------------------------------------



#pragma package(smart_init)


