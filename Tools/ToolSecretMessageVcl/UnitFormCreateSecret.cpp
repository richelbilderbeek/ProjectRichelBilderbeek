//---------------------------------------------------------------------------
/*
  Secret Message, tool to add secret messages to images
  Copyright (C) 2009  Richel Bilderbeek

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
#include <vcl.h>
#pragma hdrstop

#include "UnitFunctions.h"
#include "UnitFormCreateSecret.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormCreateSecret *FormCreateSecret;
//---------------------------------------------------------------------------
__fastcall TFormCreateSecret::TFormCreateSecret(TComponent* Owner)
  : TForm(Owner)
{
  ImageResult->Stretch = false;
  ImageResult->Align = alClient;
  OnResize(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateSecret::PanelLoadOriginalMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (OpenDialog->Execute() == false) return;
  ImageOriginal->Picture->LoadFromFile(OpenDialog->FileName);

  //Valid bitmap?
  if ( ImageOriginal->Picture->Bitmap == 0
    || ImageOriginal->Picture->Bitmap->PixelFormat != pf24bit)
  {
    PanelLoadMessage->Visible = false;
    return;
  }

  PanelLoadMessage->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateSecret::PanelLoadMessageMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
  if (OpenDialog->Execute() == false) return;
  ImageMessage->Picture->LoadFromFile(OpenDialog->FileName);

  //Valid bitmap?
  if ( ImageMessage->Picture->Bitmap == 0
    || ImageMessage->Picture->Bitmap->PixelFormat != pf24bit)
  {
    PanelSave->Visible = false;
    return;
  }


  PanelSave->Visible = true;
  AddMessageRed(ImageOriginal,ImageMessage,ImageResult);
  ImageResult->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateSecret::PanelSaveMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (SaveDialog->Execute() == false) return;
  ImageResult->Picture->SaveToFile(SaveDialog->FileName);
  
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateSecret::FormResize(TObject *Sender)
{
  const int width = ClientWidth / 3;
  PanelLoadOriginal->Width = width;
  PanelLoadMessage->Width = width;
  PanelSave->Width = width;
}
//---------------------------------------------------------------------------
