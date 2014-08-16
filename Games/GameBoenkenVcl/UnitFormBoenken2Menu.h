/*
  Boenken 2, a simple game
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
#ifndef UnitFormBoenken2MenuH
#define UnitFormBoenken2MenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "UnitEnums.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormBoenken2Menu : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelNunits;
        TImage *ImageNunitsPlus;
        TImage *ImageNunitsMinus;
        TButton *ButtonStart;
        TButton *ButtonCalibrate;
        TButton *ButtonAbout;
        TPanel *PanelNred;
        TImage *ImageNredPlus;
        TImage *ImageNredMinus;
        TPanel *PanelNblue;
        TImage *ImageNbluePlus;
        TImage *ImageNblueMinus;
        TPanel *PanelControls;
        TPanel *PanelGraphics;
        TStaticText *TextNred;
        TStaticText *TextNunits;
        TStaticText *TextControls;
        TStaticText *TextGraphics;
        TStaticText *TextNblue;
        TImage *ImageGraphicsOldSchool;
        TImage *ImageControlsTwo;
        TImage *ImageGraphicsNewSchool;
        TImage *ImageControlsFour;
        TImage *ImageGraphicsChosen;
        TImage *ImageControlsChosen;
        TStaticText *TextFriction;
        TPanel *PanelFriction;
        TTrackBar *TrackBarFriction;
        TPanel *PanelFrictionValue;
        void __fastcall ButtonStartClick(TObject *Sender);
        void __fastcall ButtonCalibrateClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall ImageNunitsMinusClick(TObject *Sender);
        void __fastcall ImageNunitsPlusClick(TObject *Sender);
        void __fastcall ImageNredMinusClick(TObject *Sender);
        void __fastcall ImageNredPlusClick(TObject *Sender);
        void __fastcall ImageNblueMinusClick(TObject *Sender);
        void __fastcall ImageNbluePlusClick(TObject *Sender);
        void __fastcall ImageGraphicsOldSchoolClick(TObject *Sender);
        void __fastcall ImageGraphicsNewSchoolClick(TObject *Sender);
        void __fastcall ImageControlsTwoClick(TObject *Sender);
        void __fastcall ImageControlsFourClick(TObject *Sender);
        void __fastcall TrackBarFrictionChange(TObject *Sender);
private:	// User declarations
  //std::vector<Player> mPlayers;
  EnumGraphics mGraphics;
  EnumControls mControls;
  double mFriction;
  std::vector<Player> mPlayerRedKeys;
  std::vector<Player> mPlayerBlueKeys;
public:		// User declarations
        __fastcall TFormBoenken2Menu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBoenken2Menu *FormBoenken2Menu;
//---------------------------------------------------------------------------
void DrawGlobeMinus(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
void DrawGlobePlus(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);


#endif
