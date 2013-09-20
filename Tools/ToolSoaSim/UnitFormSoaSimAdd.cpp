//---------------------------------------------------------------------------
/*
  SoaSim, a simulator of sexually transmitted diseases
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
//From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <cassert>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSoaSimAdd.h"
#include "UnitFormSoaSimControl.h"
#include "UnitFormSoaSimMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSoaSimAddPerson *FormSoaSimAddPerson;
//---------------------------------------------------------------------------
__fastcall TFormSoaSimAddPerson::TFormSoaSimAddPerson(TComponent* Owner)
  : TForm(Owner),
  mFormSoaSimControl(dynamic_cast<TFormSoaSimControl*>(Owner))
{
  assert(mFormSoaSimControl!=0);
}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimAddPerson::ButtonAddStandardClick(TObject *Sender)
{
  //
  const bool isInfected = (ComboBoxStandardInfected->ItemIndex == 0 ? true : false);
  switch(ComboBoxStandardType->ItemIndex)
  {
    case 0: mFormSoaSimControl->mFormSoaSimMain->AddBadBoy(isInfected); break;
    case 1: mFormSoaSimControl->mFormSoaSimMain->AddPartyAnimal(isInfected); break;
    case 2: mFormSoaSimControl->mFormSoaSimMain->AddWiseGuy(isInfected); break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimAddPerson::ButtonAddCustomClick(TObject *Sender)
{
  const bool isInfected = (ComboBoxCustomInfected->ItemIndex == 0 ? true : false);
  const double pProposeSafe = EditPproposeSafe->Text.ToDouble();
  const double pAgreeSafe   = EditPagreeSafe->Text.ToDouble();
  const double pAgreeUnsafe = EditPagreeUnsafe->Text.ToDouble();

  mFormSoaSimControl->mFormSoaSimMain->AddCustomPerson(
    pProposeSafe,
    pAgreeSafe,
    pAgreeUnsafe,
    isInfected);
}
//---------------------------------------------------------------------------
