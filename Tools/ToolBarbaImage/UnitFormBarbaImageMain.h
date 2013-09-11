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
#ifndef UnitFormBarbaImageMainH
#define UnitFormBarbaImageMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include <vector>
struct TFormImage;
//---------------------------------------------------------------------------
class TFormBarbaImageMain : public TForm
{
__published:	// IDE-managed Components
        TPopupMenu *PopupMenu;
        TMenuItem *ItemCreateWindow;
        TMenuItem *ItemCascade;
        TMenuItem *ItemTile;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *ItemAbout;
        void __fastcall ItemCreateWindowClick(TObject *Sender);
        void __fastcall ItemCascadeClick(TObject *Sender);
        void __fastcall ItemTileClick(TObject *Sender);
        void __fastcall ItemAboutClick(TObject *Sender);
private:	// User declarations
  std::vector<TFormImage*> mChildren;
  TFormImage * const CreateFormImage();
  int mChildIndex;
public:		// User declarations
  __fastcall TFormBarbaImageMain(TComponent* Owner);
  void AddColoredNoise(TFormImage * const formSource);
  void Bleach(TFormImage * const formSource);
  void Darken(TFormImage * const formSource);
  void DoHistogramEqualization(const TImage * const source);
  void ThresholdFilterColor(TFormImage * const formSource);
  void ThresholdFilterNoColor(TFormImage * const formSource);
  void EnhanceContrast(const TImage * const source);
  void ConvertToGrey(const TImage * const source);

  void ExtractBlue(const TImage * const source);
  void ExtractGreen(const TImage * const source);
  void ExtractRed(const TImage * const source);

  void RemoveMe(TFormImage * const formImage);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormBarbaImageMain *FormBarbaImageMain;
//---------------------------------------------------------------------------
const TRect GetWindowRect(const TForm * const form);

void SetWindowRect(TForm * const form, const TRect& rect);


#endif
