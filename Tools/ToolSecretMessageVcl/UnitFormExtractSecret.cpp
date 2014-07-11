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

#include "UnitFormExtractSecret.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormExtractSecret *FormExtractSecret;
//---------------------------------------------------------------------------
__fastcall TFormExtractSecret::TFormExtractSecret(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormExtractSecret::PanelExtractSecretMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
  if (OpenDialog->Execute() == false) return;
  ImageSecret->Picture->LoadFromFile(OpenDialog->FileName);

  //Valid bitmap?
  if ( ImageSecret->Picture->Bitmap == 0
    || ImageSecret->Picture->Bitmap->PixelFormat != pf24bit)
  {
    ImageSecret->Visible = false;
    return;
  }
  ImageSecret->Visible = true;
  ExtractMessageRed(ImageSecret,ImageSecret);
}
//---------------------------------------------------------------------------
