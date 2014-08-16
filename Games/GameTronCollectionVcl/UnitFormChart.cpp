//---------------------------------------------------------------------------
/*
  The Tron Collection, three simple tron games
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

#include "UnitFormChart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormChart *FormChart;
//---------------------------------------------------------------------------
__fastcall TFormChart::TFormChart(
  TComponent* Owner,
  const std::vector<int>& losses,
  const std::vector<int>& wins)
  : TForm(Owner),
    mCanClose(false)
{
  assert(losses.size() == wins.size() );
  std::vector<double> lossesDouble(losses.size());
  std::vector<double> winsDouble(wins.size());
  std::copy(losses.begin(), losses.end(), lossesDouble.begin());
  std::copy(wins.begin(), wins.end(), winsDouble.begin());
  Chart1->Series[0]->AddArray( &(lossesDouble[0]), lossesDouble.size() - 1);
  Chart1->Series[1]->AddArray( &(winsDouble[0]), winsDouble.size() - 1);
}
//---------------------------------------------------------------------------
void __fastcall TFormChart::Timer1Timer(TObject *Sender)
{
  mCanClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormChart::ButtonCloseClick(TObject *Sender)
{
  if (mCanClose == true) Close();
}
//---------------------------------------------------------------------------
