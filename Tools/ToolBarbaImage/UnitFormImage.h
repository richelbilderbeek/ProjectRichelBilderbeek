//---------------------------------------------------------------------------
/*
  BarbaImage, tool to perform image manipulations
  Copyright (C) 2008  Richèl Bilderbeek

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
#ifndef UnitFormImageH
#define UnitFormImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormBarbaImageMain;

class TFormImage : public TForm
{
__published:	// IDE-managed Components
        TImage *Image;
        TPopupMenu *PopupMenu;
        TMenuItem *ItemHistogramEqualization;
        TMenuItem *ItemLoad;
        TMenuItem *ItemSave;
        TMenuItem *N1;
        TOpenDialog *OpenDialog;
        TSaveDialog *SaveDialog;
        TMenuItem *ItemConvertToGrey;
        TMenuItem *ItemEnhanceContrast;
        TMenuItem *ItemThresholdFilterColor;
        TMenuItem *ItemThresholdFilterNoColor;
        TMenuItem *ItemExtractBlue;
        TMenuItem *ItemExtractGreen;
        TMenuItem *ItemExtractRed;
        TMenuItem *ItemAddColoredNoise;
        TMenuItem *ItemBleach;
        TMenuItem *ItemDarken;
        void __fastcall ItemHistogramEqualizationClick(TObject *Sender);
        void __fastcall ItemLoadClick(TObject *Sender);
        void __fastcall ItemSaveClick(TObject *Sender);
        void __fastcall ItemConvertToGreyClick(TObject *Sender);
        void __fastcall ItemEnhanceContrastClick(TObject *Sender);
        void __fastcall ItemThresholdFilterColorClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ItemThresholdFilterNoColorClick(TObject *Sender);
        void __fastcall ItemExtractBlueClick(TObject *Sender);
        void __fastcall ItemExtractGreenClick(TObject *Sender);
        void __fastcall ItemExtractRedClick(TObject *Sender);
        void __fastcall ItemAddColoredNoiseClick(TObject *Sender);
        void __fastcall ItemBleachClick(TObject *Sender);
        void __fastcall ItemDarkenClick(TObject *Sender);
private:	// User declarations
  TFormBarbaImageMain * const mFormMain;
  void SetAllDisabled();
public:		// User declarations
  __fastcall TFormImage(TComponent* Owner, TFormBarbaImageMain * const formMain);
  void SetAllEnabled();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImage *FormImage;
//---------------------------------------------------------------------------
#endif
