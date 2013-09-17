//---------------------------------------------------------------------------
/*
  Rubik's Clock Simulator. Simulates Rubik's Clock.
  Copyright (C) 2007  Richel Bilderbeek

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
#ifndef UnitFormRubiksClockMainH
#define UnitFormRubiksClockMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "UnitRubiksClock.h"
//---------------------------------------------------------------------------
class TFormRubiksClockMain : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageClockFront;
        TImage *ImageClockBack;
        TPanel *Panel1;
        TButton *ButtonAbout;
        TButton *ButtonShuffle;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall ImageClockFrontMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ImageClockBackMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall ButtonShuffleClick(TObject *Sender);
private:	// User declarations
  RubiksClock mClock;
  void DrawScreen();
public:		// User declarations
        __fastcall TFormRubiksClockMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRubiksClockMain *FormRubiksClockMain;
//---------------------------------------------------------------------------
void DrawRubiksClock(
  const RubiksClockTimes& times,
  const RubiksClockPegs& pegs,
  const TColor colorCasing,
  const TColor colorClock,
  TImage * const image);

void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );

#endif
