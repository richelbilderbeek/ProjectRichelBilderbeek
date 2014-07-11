//---------------------------------------------------------------------------
/*
  Super Tron, a simple game
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
#ifndef UnitFormSuperTronMenuH
#define UnitFormSuperTronMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include "UnitSuperTronPlayer.h"
//---------------------------------------------------------------------------
class TFormSuperTronMenu : public TForm
{
__published:	// IDE-managed Components
        TButton *ButtonStart;
        TPanel *PanelSpeed;
        TPanel *PanelSpeedValue;
        TTrackBar *TrackBarSpeed;
        TPanel *PanelWidth;
        TPanel *PanelWidthValue;
        TTrackBar *TrackBarWidth;
        TPanel *PanelHeight;
        TPanel *PanelHeightValue;
        TTrackBar *TrackBarHeight;
        TPanel *PanelWorld;
        TPanel *PanelCanThroughOwnColor;
        TImage *ImageWorldDonut;
        TImage *ImageCannotWalkThroughOwnColor;
        TImage *ImageWorldFlat;
        TImage *ImageCanWalkThroughOwnColorChosen;
        TImage *ImageCanWalkThroughOwnColor;
        TImage *ImageWorldChosen;
        TStaticText *StaticText1;
        TStaticText *TextWalkThroughOwnColor;
        TButton *ButtonCalibrate;
        TPanel *PanelNplayers;
        TImage *ImageNplayersPlus;
        TImage *ImageNplayersMinus;
        TStaticText *TextNplayers;
        TPanel *PanelSpeedText;
        TPanel *PanelWidthText;
        TPanel *PanelHeightText;
        TButton *ButtonAbout;
  TPanel *PanelNangles;
  TPanel *PanelNanglesValue;
  TTrackBar *TrackBarNangles;
  TPanel *PanelNanglesLeft;
        void __fastcall ButtonCalibrateClick(TObject *Sender);
        void __fastcall ImageNplayersMinusClick(TObject *Sender);
        void __fastcall ImageNplayersPlusClick(TObject *Sender);
        void __fastcall TrackBarSpeedChange(TObject *Sender);
        void __fastcall TrackBarWidthChange(TObject *Sender);
        void __fastcall TrackBarHeightChange(TObject *Sender);
        void __fastcall ImageWorldFlatClick(TObject *Sender);
        void __fastcall ImageWorldDonutClick(TObject *Sender);
        void __fastcall ButtonStartClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ImageCanWalkThroughOwnColorClick(TObject *Sender);
        void __fastcall ImageCannotWalkThroughOwnColorClick(
          TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
  void __fastcall TrackBarNanglesChange(TObject *Sender);
private:	// User declarations
  typedef SuperTronPlayer Player;
  std::vector<Player> mPlayers;
  bool mDonutShapedWorld;
  bool mCanWalkThroughOwnColor;
public:		// User declarations
        __fastcall TFormSuperTronMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSuperTronMenu *FormSuperTronMenu;
//---------------------------------------------------------------------------

#endif
