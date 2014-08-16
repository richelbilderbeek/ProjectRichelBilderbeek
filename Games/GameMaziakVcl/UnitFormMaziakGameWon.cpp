//---------------------------------------------------------------------------
/*
  Maziak, a simple maze game
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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitFormMaziakGameWon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMaziakGameWon *FormMaziakGameWon;
//---------------------------------------------------------------------------
__fastcall TFormMaziakGameWon::TFormMaziakGameWon(TComponent* Owner)
        : TForm(Owner), mCanClose(false)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGameWon::OnAnyClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGameWon::TimerCanCloseTimer(TObject *Sender)
{
  mCanClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGameWon::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (mCanClose == true) Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGameWon::TimerAnimationTimer(TObject *Sender)
{
  ++TimerAnimation->Tag;
  //Clear the buffer
  ImageBuffer->Canvas->Draw(0,0,ImageEmpty->Picture->Graphic);
  //Draw right image on buffer
  const TImage * const image = (TimerAnimation->Tag % 2 ? ImagePlayerWon1 : ImagePlayerWon2);
  ImageBuffer->Canvas->Draw(0,0,image->Picture->Graphic);
  //Draw buffer on canvar
  TRect r(ClientRect);
  r.top+=ImageTop->Height;
  r.bottom-=ImageBottom->Height;
  this->Canvas->StretchDraw(r,ImageBuffer->Picture->Graphic);

}
//---------------------------------------------------------------------------

