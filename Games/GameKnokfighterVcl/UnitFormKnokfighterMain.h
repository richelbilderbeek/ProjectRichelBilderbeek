//---------------------------------------------------------------------------
/*
    KnokFighter, a simple fighting game
    Copyright (C) 2005  Richel Bilderbeek and Joost van den Bogaart

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
#ifndef UnitFormKnokfighterMainH
#define UnitFormKnokfighterMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <AppEvnts.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
  TImage *ImageCanvas;
  TImage *Joost;
  TApplicationEvents *ApplicationEvents1;
  TImage *ImageBackGround;
  TTimer *TimerJoost;
  TImage *Richel;
  TTimer *TimerRichel;
  TTimer *RichelAITimer;
  TImage *RichelShadow;
  TImage *JoostShadow;
  TProgressBar *RichelHealthBar;
  TProgressBar *JoostHealthBar;
  TPanel *Panel1;
  TLabel *Label1;
  TLabel *Label2;
  TPanel *Panel2;
  TImage *Image1;
  TTimer *WolkTimer;
  TImage *Wolk;
  TImage *Startscherm;
  void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall TimerJoostTimer(TObject *Sender);
  void __fastcall TimerRichelTimer(TObject *Sender);
  void __fastcall RichelAITimerTimer(TObject *Sender);
  void __fastcall WolkTimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
