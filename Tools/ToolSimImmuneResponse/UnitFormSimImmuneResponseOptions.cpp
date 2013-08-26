//---------------------------------------------------------------------------
/*
  SimImmuneResponse. Active simulation about the human immune response
  Copyright (C) 2008  Richèl Bilderbeek

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
#include <memory>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSimImmuneResponseOptions.h"
#include "UnitFormSimImmuneResponseMain.h"
#include "UnitFormSimImmuneResponseAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimImmuneResponseOptions *FormSimImmuneResponseOptions;
//---------------------------------------------------------------------------
__fastcall TFormSimImmuneResponseOptions::TFormSimImmuneResponseOptions(TComponent* Owner)
  : TForm(Owner),
    mFormMain(dynamic_cast<TFormSimImmuneResponseMain*>(Owner))
{
  assert(mFormMain!=0);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimImmuneResponseOptions::ButtonQuitClick(
      TObject *Sender)
{
  Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TFormSimImmuneResponseOptions::ButtonProduceBcellClick(
      TObject *Sender)
{
  mFormMain->AddCell(bCell);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimImmuneResponseOptions::ButtonProduceCtlClick(
      TObject *Sender)
{
  mFormMain->AddCell(cytotoxicTcell);
}
//---------------------------------------------------------------------------

void __fastcall TFormSimImmuneResponseOptions::ButtonProduceMacrophageClick(
      TObject *Sender)
{
  mFormMain->AddCell(macrophageWithoutVirusParticles);
}
//---------------------------------------------------------------------------

void __fastcall TFormSimImmuneResponseOptions::ButtonProduceThelperCellClick(
      TObject *Sender)
{
  mFormMain->AddCell(tHelperCell);
}
//---------------------------------------------------------------------------

void __fastcall TFormSimImmuneResponseOptions::ButtonAboutClick(
      TObject *Sender)
{
  //
  std::auto_ptr<TFormSimImmuneResponseAbout> f(new TFormSimImmuneResponseAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormSimImmuneResponseOptions::ButtonRestartClick(
      TObject *Sender)
{
  //
  mFormMain->Restart();
}
//---------------------------------------------------------------------------

