//---------------------------------------------------------------------------
/*
  Logistic Growth Simulator, logistic growth simulation
  Copyright (C) 2009  Richel Bilderbeek

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

#include "UnitFormMain.h"
//---------------------------------------------------------------------------
#include <map>
#include <algorithm>
#include "UnitFormLineChart.h"
#include "UnitFormScatterplot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner),
  mChartBegin(new TFormLineChart(0)),
  mChartEnd(new TFormLineChart(0)),
  mChartFeigenNvalues(new TFormLineChart(0)),
  mChartFeigenValues(new TFormScatterplot(0))
{

}
//---------------------------------------------------------------------------
Parameters TFormMain::GetParams() const
{
  Parameters params;
  params.mR = this->GetR();
  params.mK = this->GetK();
  return params;
}
//---------------------------------------------------------------------------
double TFormMain::GetR() const
{
  return static_cast<double>(TrackBar1->Position) / 1000.0;
}
//---------------------------------------------------------------------------
double TFormMain::GetK() const
{
  return 1.0;
}
//---------------------------------------------------------------------------
double TFormMain::GetXzero() const
{
  return 0.1;
}
//---------------------------------------------------------------------------
int TFormMain::GetT() const
{
  return 10000;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TrackBar1Change(TObject *Sender)
{
  const double r = this->GetR();

  Editor1->Cells[1][1] = r;
  const Parameters params = GetParams();
  const double xZero = this->GetXzero();
  mSimulation.reset(new Simulation(xZero,params));
  const int maxTime = this->GetT();
  mSimulation->Run(maxTime);
  std::vector<double> popSizes = mSimulation->GetPopSizes();
  mChartBegin->mChart->Series[0]->Clear();
  mChartBegin->mChart->Series[0]->AddArray(&popSizes[0],1000-1);
  mChartBegin->mChart->Refresh();
  mChartEnd->mChart->Series[0]->Clear();
  mChartEnd->mChart->Series[0]->AddArray(&popSizes[9000],1000-1);
  mChartEnd->mChart->Refresh();

  std::map<double,char> histogram;
  typedef std::vector<double>::const_iterator Iter;
  for (Iter i = &popSizes[9000]; i!=popSizes.end(); ++i)
  {
    histogram[*i] = '0';
  }
  const int nEquil = histogram.size();
  Editor1->Cells[1][2] = nEquil;

  Refresh();

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
  const int maxx = 800;
  const int maxy = 600;
  //This -> Topleft
  this->Left   = 0;
  this->Top    = 0;
  this->Width  = maxx / 2;
  this->Height = maxy / 2;

  //Begin -> TopRight
  mChartBegin->Caption = "Begin";
  mChartBegin->Left = maxx / 2;
  mChartBegin->Width = maxx /2 ;
  mChartBegin->Top = 0;
  mChartBegin->Height = maxy / 2;
  mChartBegin->Show();

  //End -> BottomLeft
  mChartEnd->Caption = "End";
  mChartEnd->Left = 0;
  mChartEnd->Width = maxx / 2;
  mChartEnd->Height = maxy / 2;
  mChartEnd->Top = maxy / 2;
  mChartEnd->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonCreateFeigenClick(TObject *Sender)
{
  const int maxx = 800;
  const int maxy = 600;

  //FeigenValues -> BottomRight
  mChartFeigenValues->Caption = "Feigen";
  mChartFeigenValues->Left = 0;
  mChartFeigenValues->Width = maxx / 2;
  mChartFeigenValues->Top = maxy / 2;
  mChartFeigenValues->Height = maxy / 2;

  //Feigen -> BottomRight
  mChartFeigenNvalues->Caption = "Feigen";
  mChartFeigenNvalues->Left = maxx / 2;
  mChartFeigenNvalues->Width = maxx / 2;
  mChartFeigenNvalues->Top = maxy / 2;
  mChartFeigenNvalues->Height = maxy / 2;

  //Calculate the feigenbaum
  {
    for (int i=1; i<4000; ++i)
    {
      Parameters params;
      params.mR = static_cast<double>(i) / 1000.0;
      params.mK = 1.0;
      Simulation sim(0.1,params);
      sim.Run(10000);
      std::vector<double> popSizes = sim.GetPopSizes();
      //How many equilibria does it have?
      std::map<double,char> histogram;
      typedef std::vector<double>::const_iterator Iter;
      for (Iter i = &popSizes[9000]; i!=popSizes.end(); ++i)
      {
        histogram[*i] = '0';
      }

      typedef std::map<double,char>::const_iterator IterMap;
      for (IterMap i = histogram.begin(); i!=histogram.end(); ++i)
      {
        mChartFeigenValues->mChart->Series[0]->AddXY(params.mR, (*i).first);
      }

      const int nEquil = histogram.size();
      mChartFeigenNvalues->mChart->Series[0]->AddXY(params.mR,nEquil);


    }


    Refresh();

  }

  mChartFeigenValues->Show();
  mChartFeigenNvalues->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonAboutClick(TObject *Sender)
{
  ShowMessage(
    "  Logistic Growth Simulator, logistic growth simulation                  \n"
    "  Copyright (C) 2009  Richel Bilderbeek                                  \n"
    "                                                                         \n"
    "  This program is free software: you can redistribute it and/or modify   \n"
    "  it under the terms of the GNU General Public License as published by   \n"
    "  the Free Software Foundation, either version 3 of the License, or      \n"
    "  (at your option) any later version.                                    \n"
    "                                                                         \n"
    "  This program is distributed in the hope that it will be useful,        \n"
    "  but WITHOUT ANY WARRANTY; without even the implied warranty of         \n"
    "  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          \n"
    "  GNU General Public License for more details.                           \n"
    "  You should have received a copy of the GNU General Public License      \n"
    "  along with this program.  If not, see <http://www.gnu.org/licenses/>.  ");


}
//---------------------------------------------------------------------------

