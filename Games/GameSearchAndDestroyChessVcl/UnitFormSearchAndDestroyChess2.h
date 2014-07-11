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
#ifndef UnitFormSearchAndDestroyChess2H
#define UnitFormSearchAndDestroyChess2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "UnitChessGame.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSearchAndDestroyChess2 : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBuffer;
        TImage *ImageBlackBishop;
        TImage *ImageBlackKnight;
        TImage *ImageBlackKing;
        TImage *ImageBlackPawn;
        TImage *ImageBlackQueen;
        TImage *ImageBlackRook;
        TImage *ImageWhiteKing;
        TImage *ImageWhiteQueen;
        TImage *ImageWhiteRook;
        TImage *ImageWhiteBishop;
        TImage *ImageWhiteKnight;
        TImage *ImageWhitePawn;
        TImage *ImageSelected;
        TImage *ImageCursor;
        TTimer *Timer1;
        TImage *ImageQuestionMark;
        TImage *ImageWhiteSquare;
        TImage *ImageBlackSquare;
  TImage *ImageCross;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);

private:	// User declarations
  ChessGame mGame;
  void DrawChessBoard();
  int mCursorX, mCursorY;
  int mSelectX, mSelectY;
  void DoMove();
  void DoMove(const ChessMove& move);
  const bool IsCurrentPlayerHuman() const;
  const TImage * const GetImage(
    const bool inSight,
    const ChessPiece& piece) const;
  void DoSelect(const int cursorX, const int cursorY);
public:		// User declarations
  __fastcall TFormSearchAndDestroyChess2(
    TComponent* Owner,
    const bool isWhiteHuman,
    const bool isBlackHuman);
  const bool mIsWhiteHuman;
  const bool mIsBlackHuman;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSearchAndDestroyChess2 *FormSearchAndDestroyChess2;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer();
//---------------------------------------------------------------------------

#endif
