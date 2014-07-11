/*
  SimBrainiac, a simulation of Brainiacs interacting
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
#ifndef UnitFormSimBrainiacMenuH
#define UnitFormSimBrainiacMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSimBrainiacMenu : public TForm
{
__published:	// IDE-managed Components
        TButton *ButtonStart;
        TPanel *PanelNcorrectQuestionLevels;
        TPanel *PanelNhasQuestionLevels;
        TImage *ImageNcorrectQuestionLevelsUp;
        TImage *ImageNhasQuestionLevelsUp;
        TImage *ImageNhasQuestionLevelsDown;
        TImage *Image1;
        TButton *ButtonManual;
        TButton *ButtonAbout;
        TButton *ButtonQuit;
        TPanel *PanelNbrainiacs;
        TImage *ImageNbrainiacsPlus;
        TImage *ImageNbrainiacsMinus;
        void __fastcall ButtonStartClick(TObject *Sender);
        void __fastcall ImageNcorrectQuestionLevelsDownClick(
          TObject *Sender);
        void __fastcall ImageNcorrectQuestionLevelsUpClick(
          TObject *Sender);
        void __fastcall ImageNhasQuestionLevelsDownClick(TObject *Sender);
        void __fastcall ImageNhasQuestionLevelsUpClick(TObject *Sender);
        void __fastcall ButtonQuitClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall ButtonManualClick(TObject *Sender);
        void __fastcall ImageNbrainiacsMinusClick(TObject *Sender);
        void __fastcall ImageNbrainiacsPlusClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSimBrainiacMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimBrainiacMenu *FormSimBrainiacMenu;
//---------------------------------------------------------------------------
#endif
