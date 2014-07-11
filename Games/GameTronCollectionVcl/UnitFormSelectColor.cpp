//---------------------------------------------------------------------------
/*
  The Tron Collection, three simple tron games
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
#include <cmath>
#include <algorithm>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSelectColor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSelectColor *FormSelectColor;
//---------------------------------------------------------------------------
__fastcall TFormSelectColor::TFormSelectColor(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSelectColor::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch (Key)
  {
    case VK_F1 : ModalResult = 10; break;
    case VK_F2 : ModalResult = 11; break;
    case VK_F3 : ModalResult = 12; break;
    case VK_F4 : ModalResult = 13; break;
    case VK_F5 : ModalResult = 14; break;
    case VK_F6 : ModalResult = 15; break;
    case VK_F7 : ModalResult = 16; break;
    case VK_F8 : ModalResult = 17; break;
    case VK_F9 : ModalResult = 18; break;
    case VK_F10: ModalResult = 19; break;
    case 49:     ModalResult = 20; break;
    case 50:     ModalResult = 21; break;
    case 51:     ModalResult = 22; break;
    case 52:     ModalResult = 23; break;
    case 53:     ModalResult = 24; break;
    case 54:     ModalResult = 25; break;
    case 55:     ModalResult = 26; break;
    case 56:     ModalResult = 27; break;
    case 57:     ModalResult = 28; break;
    case 48:     ModalResult = 29; break;
  }
}
//---------------------------------------------------------------------------

