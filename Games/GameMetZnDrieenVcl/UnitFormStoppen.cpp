//---------------------------------------------------------------------------
/*
    Met Z'n Drieën. A 3-player tic-tac-toe-like game.
    Copyright (C) 2010  Richel Bilderbeek

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

#include "UnitFormStoppen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormStoppen *FormStoppen;
//---------------------------------------------------------------------------
__fastcall TFormStoppen::TFormStoppen(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormStoppen::OnAgainClick(TObject *Sender)
{
  this->ModalResult = 1;
}
//---------------------------------------------------------------------------

void __fastcall TFormStoppen::OnQuitClick(TObject *Sender)
{
  this->ModalResult = 2;
}
//---------------------------------------------------------------------------

