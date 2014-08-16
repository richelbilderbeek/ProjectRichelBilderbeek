//---------------------------------------------------------------------------
/*
  PokeVolley, Pokemon volleyball game
<<<<<<< HEAD
  Copyright (C) 2005  Richèl Bilderbeek
=======
  Copyright (C) 2005  Richel Bilderbeek
>>>>>>> develop

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
#ifndef UnitFormMainH
#define UnitFormMainH
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
        TImage *ImagePlayer2;
        TImage *ImageBall;
        TImage *ImagePlayer1;
        TImage *ImageBackground;
        TImage *ImageBuffer;
        TImage *ImageBasket1;
        TImage *ImageBasket2;
        TTimer *Timer1;
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
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
  const Extctrls::TImage * GetRandomBasket1() const;
  const Extctrls::TImage * GetRandomBasket2() const;
public:		// User declarations
  __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
