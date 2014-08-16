//---------------------------------------------------------------------------
/*
  Hometrainer 2, tool to make exercises and tests
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

#include "UnitFormImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormImage *FormImage;
//---------------------------------------------------------------------------
__fastcall TFormImage::TFormImage(TComponent* Owner,
    const TImage * const image)
    : TForm(Owner)
{
  Image->Picture->Graphic = image->Picture->Graphic;
  this->ClientWidth = Image->Picture->Graphic->Width;
  this->ClientHeight = Image->Picture->Graphic->Height;
}
//---------------------------------------------------------------------------
