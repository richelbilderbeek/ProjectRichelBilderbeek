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

#include "UnitFormResults.h"
//---------------------------------------------------------------------------
#include <string>
#include "UnitSimulationParameters.h"
#include "UnitHelperFunctions.h"
#include "UnitResults.h"
#include "UnitBirdWatcher.h"
#include "UnitSimulationFunctions.h"
#include "Assert.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormResults *FormResults;
//---------------------------------------------------------------------------
__fastcall TFormResults::TFormResults(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormResults::ButtonSavePedigreeClick(TObject *Sender)
{
  if (!SaveDialogPedigree->Execute()) return;
  RichEditPedigree->Lines->SaveToFile(SaveDialogPedigree->FileName);
}
//---------------------------------------------------------------------------
void TFormResults::displayResults()
{
  helper::emptyChart(ChartNumbers);
  helper::emptyChart(ChartTraits);
  RichEditPedigree->Lines->Clear();

  const Results * results = Results::instance();
  helper::plot(results->mNsingleFemales, ChartNumbers->Series[0]);
  helper::plot(results->mNsingleMales  , ChartNumbers->Series[1]);
  helper::plot(results->mNcouples      , ChartNumbers->Series[2]);
  helper::plot(results->mNmigrants     , ChartNumbers->Series[3]);
  helper::plot(results->mNdead         , ChartNumbers->Series[4]);
  helper::log(results->mLog            , RichEditResults);
  const BirdWatcher * birdWatcher = BirdWatcher::instance();
  const std::vector<std::string> pedigree = birdWatcher->getPedigree();
  helper::log(pedigree,RichEditPedigree);

  const std::vector<double> meanPlayHawkAlpha = birdWatcher->getMeansPlayHawkAlpha();
  const std::vector<double> meanPlayHawkBeta  = birdWatcher->getMeansPlayHawkBeta();
  Assert(meanPlayHawkAlpha.size()==meanPlayHawkBeta.size());
  std::vector<double> meanPlayHawk;
  { //Calculate meanPlayHawk (from logistic equation)
    const int size = meanPlayHawkAlpha.size();
    meanPlayHawk.resize(size);
    for (int i=0; i<size; ++i)
    {
      meanPlayHawk[i] = simFunc::logisticEquation(0.0,meanPlayHawkAlpha[i],meanPlayHawkBeta[i]);
    }
  }


  ChartTraits->Series[0]->AddArray(&meanPlayHawkAlpha[0], meanPlayHawkAlpha.size()-1);
  ChartTraits->Series[1]->AddArray(&meanPlayHawkBeta[0] , meanPlayHawkBeta.size()-1);
  ChartTraits->Series[2]->AddArray(&meanPlayHawk[0]     , meanPlayHawk.size()-1);
}
//---------------------------------------------------------------------------
void TFormResults::display(const boost::shared_ptr<SimulationParameters>& simParams)
{
  Assert(simParams.get()!=0);
  std::vector<std::string> text = simParams->getText();

  RichEditResults->Lines->Add("Simulation parameters");
  //String Text;
  const int size = text.size();
  for (int i=0; i<size; ++i)
  {
    RichEditResults->Lines->Add(text[i].c_str());
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
