//---------------------------------------------------------------------------
/*
 *  PokeVolley. A simple game.
 *  Copyright (C) 2005  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
// The program was created at the 24th of September of 2005
// The program can be downloaded at http://www.richelbilderbeek.nl
// The author's e-mail adress can be found at http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <AppEvnts.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
  TImage *PlayerRight;
  TImage *Ball;
  TImage *PlayerLeft;
  TImage *BackGround;
  TImage *Buffer;
  TImage *BasketLeft;
  TImage *BasketRight;
  TImageList *ImageListBasketLeft;
  TImageList *ImageListBasketRight;
        TTimer *Timer1;
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
  const bool mBigImages;
  bool mKeyA, mKeyD, mKeyLeft, mKeyRight, mKeyW, mKeyUp, mKeyS, mKeyDown;

  double mBallX, mBallY;
  double mBallSpeedX, mBallSpeedY;

  double mPlayerLeftX, mPlayerLeftY;
  double mPlayerRightX, mPlayerRightY;
  double mPlayerLeftSpeedX, mPlayerLeftSpeedY;
  double mPlayerRightSpeedX, mPlayerRightSpeedY;
  bool mPlayerLeftJumps, mPlayerRightJumps;

  int mScoreLeft, mScoreRight;
  void resetCoordinats();
  void moveBall();
  void movePlayers();
  void detectCollision();
  void processKeys();
public:		// User declarations
  __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
