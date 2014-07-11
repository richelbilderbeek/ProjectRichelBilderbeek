//---------------------------------------------------------------------------
/*
    Reversi, a simple board game
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
#include <vcl.h>
#pragma hdrstop

#include "UnitFormRestart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRestart *FormRestart;
//---------------------------------------------------------------------------
__fastcall TFormRestart::TFormRestart(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormRestart::PanelYesClick(TObject *Sender)
{
  ModalResult = EditSize->Text.ToIntDef(8);
}
//---------------------------------------------------------------------------
void __fastcall TFormRestart::PanelNoClick(TObject *Sender)
{
  ModalResult = -1;
}
//---------------------------------------------------------------------------
