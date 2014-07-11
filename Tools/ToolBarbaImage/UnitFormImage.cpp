//---------------------------------------------------------------------------
/*
  BarbaImage, tool to perform image manipulations
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
#include <cassert>
#include <stdexcept>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormImage.h"
#include "UnitFormBarbaImageMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormImage *FormImage;
//---------------------------------------------------------------------------
__fastcall TFormImage::TFormImage(TComponent* Owner, TFormBarbaImageMain * const formMain)
        : TForm(Owner), mFormMain(formMain)
{
  assert(mFormMain!=0 && "FormMain must not be NULL");
  SetAllDisabled();
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemLoadClick(TObject *Sender)
{
  if (OpenDialog->Execute() == false) return;
  Image->Picture->LoadFromFile(OpenDialog->FileName);

  if (Image->Picture->Bitmap->PixelFormat != pf24bit)
  {
    ShowMessage("Image must be a 24-bit bitmap");
    SetAllDisabled();
    return;
  }
  ClientWidth  = Image->Picture->Bitmap->Width;
  ClientHeight = Image->Picture->Bitmap->Height;
  SetAllEnabled();
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemSaveClick(TObject *Sender)
{
  if (SaveDialog->Execute() == false) return;
  Image->Picture->SaveToFile(SaveDialog->FileName);
}
//---------------------------------------------------------------------------
void TFormImage::SetAllEnabled()
{
  const int nItems = PopupMenu->Items->Count;
  for (int i=0; i!=nItems; ++i)
  {
    PopupMenu->Items->operator [](i)->Enabled = true;
  }
  Image->Visible = true;
}
//---------------------------------------------------------------------------
void TFormImage::SetAllDisabled()
{
  const int nItems = PopupMenu->Items->Count;
  for (int i=0; i!=nItems; ++i)
  {
    PopupMenu->Items->operator [](i)->Enabled = false;
  }
  ItemLoad->Enabled = true; //ItemLoad must always be enabled
  Image->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemConvertToGreyClick(TObject *Sender)
{
  mFormMain->ConvertToGrey(Image);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemEnhanceContrastClick(TObject *Sender)
{
  mFormMain->EnhanceContrast(Image);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemHistogramEqualizationClick(TObject *Sender)
{
  mFormMain->DoHistogramEqualization(Image);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemThresholdFilterColorClick(TObject *Sender)
{
  mFormMain->ThresholdFilterColor(this);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  mFormMain->RemoveMe(this);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemThresholdFilterNoColorClick(
      TObject *Sender)
{
  mFormMain->ThresholdFilterNoColor(this);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemExtractBlueClick(TObject *Sender)
{
  mFormMain->ExtractBlue(this->Image);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemExtractGreenClick(TObject *Sender)
{
  mFormMain->ExtractGreen(this->Image);
}
//---------------------------------------------------------------------------
void __fastcall TFormImage::ItemExtractRedClick(TObject *Sender)
{
  mFormMain->ExtractRed(this->Image);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ItemAddColoredNoiseClick(TObject *Sender)
{
  mFormMain->AddColoredNoise(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ItemBleachClick(TObject *Sender)
{
  mFormMain->Bleach(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormImage::ItemDarkenClick(TObject *Sender)
{
  mFormMain->Darken(this);
}
//---------------------------------------------------------------------------

