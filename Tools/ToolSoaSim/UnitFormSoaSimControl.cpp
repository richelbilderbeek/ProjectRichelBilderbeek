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
#include <ctime>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSoaSimControl.h"
#include "UnitFormSoaSimMain.h"
#include "UnitFormSoaSimChart.h"
#include "UnitFormSoaSimAdd.h"
#include "UnitFormSoaSimAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSoaSimControl *FormSoaSimControl;
//---------------------------------------------------------------------------
__fastcall TFormSoaSimControl::TFormSoaSimControl(TComponent* Owner)
  : TForm(Owner),
  mFormSoaSimMain(0),
  mFormSoaSimChart(0),
  mFormSoaSimAddPerson(0)
{
  std::srand( std::clock() );
}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimControl::FormShow(TObject *Sender)
{
  if (mFormSoaSimMain == 0)
  {
    mFormSoaSimMain = new TFormSoaSimMain(this);
    mFormSoaSimMain->WindowState = wsMaximized;
  }
  if (mFormSoaSimChart == 0)
  {
    mFormSoaSimChart = new TFormSoaSimChart(this);
    mFormSoaSimChart->Visible = CheckBoxShowChart->Checked;
  }
  if (mFormSoaSimAddPerson == 0)
  {
    mFormSoaSimAddPerson = new TFormSoaSimAddPerson(this);
    mFormSoaSimAddPerson->Visible = CheckBoxAddPerson->Checked;
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimControl::TimerMeasureTimer(TObject *Sender)
{
  if (mFormSoaSimMain == 0 || mFormSoaSimChart == 0) return;

  mFormSoaSimChart->Chart1->Series[0]->AddY( mFormSoaSimMain->GetPercentageInfected() );
}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimControl::CheckBoxAddPersonClick(TObject *Sender)
{
  mFormSoaSimAddPerson->Visible = CheckBoxAddPerson->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFormSoaSimControl::CheckBoxShowChartClick(TObject *Sender)
{
  mFormSoaSimChart->Visible = CheckBoxShowChart->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimControl::ButtonClearAllClick(TObject *Sender)
{
  mFormSoaSimChart->Chart1->Series[0]->Clear();
  mFormSoaSimMain->ClearPersons();
}
//---------------------------------------------------------------------------
void __fastcall TFormSoaSimControl::ButtonAboutClick(TObject *Sender)
{
  boost::shared_ptr<TFormSoaSimAbout> f(new TFormSoaSimAbout(0));
  f->ShowModal();
          
}
//---------------------------------------------------------------------------
