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
#include <vcl.h>
#pragma hdrstop

#include "UnitFormTrackBar.h"
#include "UnitFormImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTrackBar *FormTrackBar;
//---------------------------------------------------------------------------
__fastcall TFormTrackBar::TFormTrackBar(
  TComponent* Owner,
  const TImage * const source,
  TFormImage * const target,
  void(*anyFunction)(const TImage * const, const int, TImage * const) )
  : TForm(Owner),
    mSource(source),
    mTarget(target),
    mFunction(anyFunction)
{
  assert(mSource!=0 && "Source must not be NULL");
  assert(mTarget!=0 && "Target must not be NULL");
  assert(anyFunction!=0 && "Function pointer must not be NULL");
}
//---------------------------------------------------------------------------
void __fastcall TFormTrackBar::TrackBarChange(TObject *Sender)
{
  mFunction(mSource,TrackBar->Position,mTarget->Image);
  //Redraw the image
  //mTarget->Canvas->Draw(0,0,mTarget->Image->Picture->Graphic);
  mTarget->Canvas->StretchDraw(
    mTarget->Image->ClientRect,
    mTarget->Image->Picture->Graphic);

}
//---------------------------------------------------------------------------
