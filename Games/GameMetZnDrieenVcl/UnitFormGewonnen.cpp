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

#include <cassert>
#include "UnitFormGewonnen.h"
#include "UnitFormSprites.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormGewonnen *FormGewonnen;
//---------------------------------------------------------------------------
__fastcall TFormGewonnen::TFormGewonnen(TComponent* Owner,
  const int winner_index,
  const bool is_human)
        : TForm(Owner)
{
  assert(FormSprites);
  Extctrls::TImage * i = 0;
  if (winner_index == 0)
  {
    i = (is_human ? FormSprites->ImagePlayer1 : FormSprites->ImageComputer1);
  }
  else if (winner_index == 1)
  {
    i = (is_human ? FormSprites->ImagePlayer2 : FormSprites->ImageComputer2);
  }
  else if (winner_index == 2)
  {
    i = (is_human ? FormSprites->ImagePlayer3 : FormSprites->ImageComputer3);
  }
  assert(i);
  Image->Picture->Graphic = i->Picture->Graphic;
}
//---------------------------------------------------------------------------

void __fastcall TFormGewonnen::OnAnyClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

