//---------------------------------------------------------------------------
/*
  The Thor Veen Project, simulation to investigate honest signalling
  Copyright (C) 2006  Richel Bilderbeek

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
//---------------------------------------------------------------------------
#include "UnitFormTest.h"
//---------------------------------------------------------------------------
#include <string>
#include "UnitHelperFunctions.h"
#include "UnitSimulationFunctions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTest *FormTest;
//---------------------------------------------------------------------------
__fastcall TFormTest::TFormTest(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormTest::EditPlayHawkChange(TObject *Sender)
{
  double alpha = 0.0;
  double beta  = 0.0;
  if (helper::isDouble(EditPlayHawkAlpha->Text.c_str(),alpha)==true
   && helper::isDouble(EditPlayHawkBeta->Text.c_str(), beta)==true)
  {
    ChartTest->Series[0]->Clear();
    ChartTest->Title->Text->Clear();
    ChartTest->Title->Text->Add("The chance to play hawk for diffent values of condition");
    ChartTest->Title->Text->Add("Alpha: " + FloatToStr(alpha));
    ChartTest->Title->Text->Add("Beta: " + FloatToStr(beta));
    ChartTest->LeftAxis->Title->Caption = "Chance to play hawk";
    ChartTest->BottomAxis->Title->Caption = "Condition";
    for(double x = -1.0; x<1.0; x+=0.1)
    {

      const double y = simFunc::logisticEquation(x,alpha,beta);
      ChartTest->Series[0]->AddXY(x,y);
    }
  }

}
//---------------------------------------------------------------------------
