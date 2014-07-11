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
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include "UnitChessBoard.h"
#include "UnitChessPiece.h"
#include "UnitCoordinatGetter.h"
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSearchAndDestroyChess2.h"
#include "UnitFormPressKey.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSearchAndDestroyChess2 *FormSearchAndDestroyChess2;
//---------------------------------------------------------------------------
__fastcall TFormSearchAndDestroyChess2::TFormSearchAndDestroyChess2(
    TComponent* Owner,
    const bool isWhiteHuman,
    const bool isBlackHuman)
  : TForm(Owner),
    mIsWhiteHuman(isWhiteHuman),
    mIsBlackHuman(isBlackHuman),
    mCursorX(3),
    mCursorY(3),
    mSelectX(-1),
    mSelectY(-1)
{
  RandomizeTimer();

  this->Width  = Screen->Width  / 2;
  this->Height = Screen->Height / 2;
  this->Left   = Screen->Width  / 4;
  this->Top    = Screen->Height / 4;

  ImageSelected->Picture->Bitmap->TransparentColor = clLime;
  ImageSelected->Transparent = true;
  ImageCursor->Picture->Bitmap->TransparentColor = clLime;
  ImageCursor->Transparent = true;
  ImageCross->Picture->Bitmap->TransparentColor = clLime;
  ImageCross->Transparent = true;
  OnResize(0);

  if (mIsWhiteHuman)
  {
    const String s = "Player white, please press a key to start game.";
    boost::shared_ptr<TFormPressKey> form(new TFormPressKey(0,s));
    form->ShowModal();
  }

  Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormSearchAndDestroyChess2::FormResize(TObject *Sender)
{
  ImageBuffer->Picture->Bitmap->Width  = ClientWidth;
  ImageBuffer->Picture->Bitmap->Height = ClientHeight;

  DrawChessBoard();
}
//---------------------------------------------------------------------------
void TFormSearchAndDestroyChess2::DrawChessBoard()
{
  const std::vector<std::vector<bool> > inSight = mGame.GetInSight();
  const double squareWidth  = static_cast<double>(ClientWidth ) / 8.0;
  const double squareHeight = static_cast<double>(ClientHeight) / 8.0;
  //The CoordinatGetter transforms the coordinats of the board,
  //according to the player whose turn it is 
  const CoordinatGetter coordinatGetter ( mGame.GetWhoseTurn());

  //Draw squares, question marks and pieces
  {
    const ChessBoard board = mGame.GetBoard();

    //Draw all squares on buffer (clearing it)
    for (int y=0; y!=8; ++y)
    {
      for (int x=0; x!=8; ++x)
      {
        const TImage * const image
          = ( (x + y) % 2 == 0 ? ImageWhiteSquare : ImageBlackSquare);
        //Draw it
        ImageBuffer->Canvas->StretchDraw(
          TRect( TPoint( ( coordinatGetter.GetX(x) + 0 ) * squareWidth ,
                         ( coordinatGetter.GetY(y) + 0 ) * squareHeight),
                 TPoint( ( coordinatGetter.GetX(x) + 1 ) * squareWidth ,
                         ( coordinatGetter.GetY(y) + 1 ) * squareHeight)
            ), image->Picture->Graphic);
      }
    }

    //Draw all question marks and pieces
    for (int y=0; y!=8; ++y)
    {
      for (int x=0; x!=8; ++x)
      {
        const TImage * const image = GetImage(inSight[y][x],board.GetPiece(x,y));
        if( image == 0) continue;
        //Draw it
        ImageBuffer->Canvas->StretchDraw(
          TRect( TPoint( ( coordinatGetter.GetX(x) + 0 ) * squareWidth ,
                         ( coordinatGetter.GetY(y) + 0 ) * squareHeight),
                 TPoint( ( coordinatGetter.GetX(x) + 1 ) * squareWidth ,
                         ( coordinatGetter.GetY(y) + 1 ) * squareHeight)
            ), image->Picture->Graphic);

      }
    }
  }

  //Draw selected
  if (mSelectX != -1)
  {
    //Draw selection cursor
    ImageBuffer->Canvas->StretchDraw(
      TRect( TPoint( ( coordinatGetter.GetX(mSelectX) + 0 ) * squareWidth ,
                     ( coordinatGetter.GetY(mSelectY) + 0 ) * squareHeight),
             TPoint( ( coordinatGetter.GetX(mSelectX) + 1 ) * squareWidth ,
                     ( coordinatGetter.GetY(mSelectY) + 1 ) * squareHeight)
        ), ImageSelected->Picture->Graphic);

    //If a chesspiece is selected, draw the crosses on the areas which
    //are valid moves
    if (mGame.GetBoard().GetPiece(mSelectX, mSelectY).IsNull() == false)
    {
      const std::vector<ChessMove> possibleMoves
        = mGame.GetBoard().GetAllValidMoves(mSelectX,mSelectY);
      typedef std::vector<ChessMove>::const_iterator Iterator;
      const Iterator lastMove = possibleMoves.end();
      for (Iterator possibleMove = possibleMoves.begin();
        possibleMove != lastMove;
        ++possibleMove)
      {
        ImageBuffer->Canvas->StretchDraw(
          TRect(
            TPoint( ( coordinatGetter.GetX(possibleMove->x2) + 0 ) * squareWidth ,
                    ( coordinatGetter.GetY(possibleMove->y2) + 0 ) * squareHeight),
            TPoint( ( coordinatGetter.GetX(possibleMove->x2) + 1 ) * squareWidth ,
                    ( coordinatGetter.GetY(possibleMove->y2) + 1 ) * squareHeight)
            ), ImageCross->Picture->Graphic);
      }
    }
  }

  //Draw cursor
  ImageBuffer->Canvas->StretchDraw(
    TRect( TPoint( ( coordinatGetter.GetX(mCursorX) + 0 ) * squareWidth ,
                   ( coordinatGetter.GetY(mCursorY) + 0 ) * squareHeight),
           TPoint( ( coordinatGetter.GetX(mCursorX) + 1 ) * squareWidth ,
                   ( coordinatGetter.GetY(mCursorY) + 1 ) * squareHeight)
      ), ImageCursor->Picture->Graphic);

  //Draw board and pieces to screen
  this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
  //ImageBuffer->Visible = true;
}
//---------------------------------------------------------------------------
const TImage * const TFormSearchAndDestroyChess2::GetImage(
  const bool inSight,
  const ChessPiece& piece) const
{
  //Visible?
  if (inSight== false) return ImageQuestionMark;
  //Piece located there?
  //No piece present? Then return null
  if (piece.IsNull()==true) { return 0; }
  //Piece present, draw a piece
  //Which color and type?
  const EnumChessPieceColor pieceColor = piece.GetColor();
  switch ( piece.GetType() )
  {
    case king  : return ( pieceColor == white ? ImageWhiteKing   : ImageBlackKing  );
    case queen : return ( pieceColor == white ? ImageWhiteQueen  : ImageBlackQueen );
    case rook  : return ( pieceColor == white ? ImageWhiteRook   : ImageBlackRook  );
    case bishop: return ( pieceColor == white ? ImageWhiteBishop : ImageBlackBishop);
    case knight: return ( pieceColor == white ? ImageWhiteKnight : ImageBlackKnight);
    case pawn  : return ( pieceColor == white ? ImageWhitePawn   : ImageBlackPawn  );
  }
  assert(!"Should not get here. Unknown piece type");
  throw std::logic_error("Unknown piece type");

}
//---------------------------------------------------------------------------
void __fastcall TFormSearchAndDestroyChess2::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  switch (Key)
  {
    case VK_LEFT: case 65: //A
      if (mGame.GetWhoseTurn()==white)
      {
        --mCursorX; if (mCursorX < 0) mCursorX = 0;
      }
      else
      {
        ++mCursorX; if (mCursorX > 7) mCursorX = 7;
      }
      break;
    case VK_RIGHT: case 68: //D
      if (mGame.GetWhoseTurn()==white)
      {
        ++mCursorX; if (mCursorX > 7) mCursorX = 7;
      }
      else
      {
        --mCursorX; if (mCursorX < 0) mCursorX = 0;
      }
      break;
    case VK_DOWN: case 83: //W
      if (mGame.GetWhoseTurn()==white)
      {
        --mCursorY; if (mCursorY < 0) mCursorY = 0;
      }
      else
      {
        ++mCursorY; if (mCursorY > 7) mCursorY = 7;
      }
      break;
    case VK_UP: case 87: //S
      if (mGame.GetWhoseTurn()==white)
      {
        ++mCursorY; if (mCursorY > 7) mCursorY = 7;
      }
      else
      {
        --mCursorY; if (mCursorY < 0) mCursorY = 0;
      }
      break;
    case VK_RETURN: case VK_SPACE:
      DoSelect(mCursorX, mCursorY);
    default: return;
  }
  this->DrawChessBoard();
}
//---------------------------------------------------------------------------
void TFormSearchAndDestroyChess2::DoMove()
{
  const int x1 = mSelectX;
  const int y1 = mSelectY;
  const int x2 = mCursorX;
  const int y2 = mCursorY;
  if (mSelectX == -1) return;
  if (mCursorX == -1) return;
  assert(x1 >=0);
  assert(x2 >=0);
  assert(x1 < 8);
  assert(x2 < 8);
  assert(y1 >=0);
  assert(y2 >=0);
  assert(y1 < 8);
  assert(y2 < 8);
  const ChessPiece piece = mGame.GetBoard().GetPiece(x1,y1);
  assert(piece.IsNull()==false
    && "User must not be able to select an empty square do do a move from");
  const EnumChessPieceType type = piece.GetType();
  const ChessPiece victim = mGame.GetBoard().GetPiece(x2,y2);
  const bool capture = (victim.IsNull()==true ? false : true);
  const ChessMove move(type,x1,y1,capture,x2,y2);
  this->DoMove(move);
  mSelectX = -1;
  mSelectY = -1;
}
//---------------------------------------------------------------------------
void TFormSearchAndDestroyChess2::DoMove(const ChessMove& move)
{
  if (mGame.CanDoMove(move)==false)
  {
    //Nothing happens anymore...
  }
  else
  {
    //A move takes place
    mGame.DoMove(move);
    //Change player

    //Turn off timer
    Timer1->Enabled = false;
    //Clear the buffer
    ImageBuffer->Canvas->StretchDraw(
      TRect(TPoint(0,0),TPoint(ClientWidth,ClientHeight)),
      ImageQuestionMark->Picture->Graphic );
    //Show the background
    this->Canvas->StretchDraw(
      TRect(TPoint(0,0),TPoint(ClientWidth,ClientHeight)),
      ImageQuestionMark->Picture->Graphic );

        //Game over?
    if (mGame.IsGameOver()==true)
    {
      const String s
        = "Player "
        + String(mGame.GetWinner() == white ? "white" : "black")
        + " has won the game!";
      boost::shared_ptr<TFormPressKey> form(new TFormPressKey(0,s));
      form->ShowModal();
      mGame = ChessGame();
    }
    else
    {
      if (IsCurrentPlayerHuman()==true)
      {
        //Ask for another player
        const String s
          = "Player "
          + String(mGame.GetWhoseTurn() == white ? "white" : "black")
          + ", please press a key to make your move.";
        boost::shared_ptr<TFormPressKey> form(new TFormPressKey(0,s));
        form->ShowModal();
      }
    }
    //Turn back timer on
    Timer1->Enabled = true;
    if (IsCurrentPlayerHuman()==true)
    {
      //On to the next player
      mCursorX = std::rand() % 8;
      mCursorY = std::rand() % 8;
      //Draw the chessboard
      DrawChessBoard();
    }
  }
}
//---------------------------------------------------------------------------
const bool TFormSearchAndDestroyChess2::IsCurrentPlayerHuman() const
{
  return ( (mGame.GetWhoseTurn() == white && mIsWhiteHuman == true)
    || (mGame.GetWhoseTurn() == black && mIsBlackHuman == true) );
}
//---------------------------------------------------------------------------
void __fastcall TFormSearchAndDestroyChess2::Timer1Timer(TObject *Sender)
{
  if (IsCurrentPlayerHuman()==false)
  {
    const ChessMove move = mGame.SuggestMove();
    this->DoMove(move);
  }
  else
  {
    DrawChessBoard();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormSearchAndDestroyChess2::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (mGame.GetWhoseTurn()==white)
  {
    mCursorX = 0 + (X / (ClientWidth  / 8));
    mCursorY = 7 - (Y / (ClientHeight / 8));
  }
  else
  {
    mCursorX = 7 - (X / (ClientWidth  / 8));
    mCursorY = 0 + (Y / (ClientHeight / 8));
  }

  if (mCursorX < 0) mCursorX = 0;
  if (mCursorY < 0) mCursorY = 0;
  if (mCursorX > 7) mCursorX = 7;
  if (mCursorY > 7) mCursorY = 7;

  DoSelect(mCursorX, mCursorY);
}
//---------------------------------------------------------------------------
void TFormSearchAndDestroyChess2::DoSelect(const int cursorX, const int cursorY)
{
  if ( mSelectX == -1
    && mSelectY == -1
    && mGame.GetBoard().GetPiece(cursorX,cursorY).IsNull()==false)
  {
    //Nothing selected until now
    mSelectX = cursorX;
    mSelectY = cursorY;
  }
  else if (
       mSelectX != -1
    && mSelectY != -1
    && mGame.GetBoard().GetPiece(mSelectX,mSelectY).IsNull() == false
    && mGame.GetBoard().GetPiece(mSelectX,mSelectY).GetColor() == mGame.GetWhoseTurn()
    && mGame.GetBoard().GetPiece(cursorX,cursorY).IsNull() == false
    && mGame.GetBoard().GetPiece(cursorX,cursorY).GetColor() == mGame.GetWhoseTurn() )
  {
    //Selected a piece of own color and now selecting another piece
    //of own color
    mSelectX = cursorX;
    mSelectY = cursorY;
  }
  else
  {
    DoMove();
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer()
{
  std::srand(std::time(0));
}
//---------------------------------------------------------------------------

