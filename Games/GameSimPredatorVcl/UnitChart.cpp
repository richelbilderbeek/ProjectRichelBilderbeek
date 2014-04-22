//---------------------------------------------------------------------------
/*
 *  SimPredator. A simple game to demonstrate selection and mutation
 *  Copyright (C) 2006  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
// The program was developed from 19-05-2006 to 18-07-2006
// The program can be downloaded at http://www.richelbilderbeek.nl
// The author's e-mail adress can be found at http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitChart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormChart *FormChart;
//---------------------------------------------------------------------------
__fastcall TFormChart::TFormChart(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormChart::Timer1Timer(TObject *Sender)
{
  TextContinue->Enabled = true;
  Timer1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormChart::TextContinueClick(TObject *Sender)
{
  this->ModalResult = mrOk;
  //this->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TFormChart::FormShow(TObject *Sender)
{
  TextContinue->Enabled = false;
  Timer1->Enabled = true;

  #ifdef RICHEL_BILDERBEEK_IS_TESTING
  Timer1->Interval = 100;
  #endif

}
//---------------------------------------------------------------------------


