//---------------------------------------------------------------------------
/*
  The Chris Wiley Project, simulation on mixed-pair mating
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

#include "UnitMain.h"
#include "UnitAboutBox2.h"
#include "UnitThreeDotsChasing.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner)
{
  #ifdef NDEBUG
    OutputDebugString("NDEBUG defined. No output anymore");
    this->Caption = this->Caption + " NoDebug";
  #else
    OutputDebugString("NDEBUG not defined.");
    this->Caption = this->Caption + " Debug";
  #endif

  setCursor("CursorPiedFlycatcher.cur");
  StringGridTest->Cells[0][0] = "";
  StringGridTest->Cells[1][0] = "Female" ;
  StringGridTest->Cells[2][0] = "Male #1";
  StringGridTest->Cells[3][0] = "Male #2";
  StringGridTest->Cells[4][0] = "Male #3";
  StringGridTest->Cells[5][0] = "Male #4";
  StringGridTest->Cells[0][1] = "SpeciesValue";
  StringGridTest->Cells[1][1] = "-1.0" ;
  StringGridTest->Cells[2][1] = "-1.0";
  StringGridTest->Cells[3][1] = "-0.5";
  StringGridTest->Cells[4][1] = "0.5";
  StringGridTest->Cells[5][1] = "1.0";
  StringGridTest->Cells[0][2] = "Trait/Preference";
  StringGridTest->Cells[1][2] = "1.0" ;
  StringGridTest->Cells[2][2] = "-1.0";
  StringGridTest->Cells[3][2] = "-0.5";
  StringGridTest->Cells[4][2] = "0.5";
  StringGridTest->Cells[5][2] = "1.0";

  //Fill in StringGridParameters
  StringGridParameters->RowCount = 23;
  StringGridParameters->Cells[0][ 0] = "Parameter";             StringGridParameters->Cells[1][ 0] = "Value";
  StringGridParameters->Cells[0][ 1] = "Number of females";     StringGridParameters->Cells[1][ 1] = "1000";
  StringGridParameters->Cells[0][ 2] = "Number of males";       StringGridParameters->Cells[1][ 2] = "1000";
  StringGridParameters->Cells[0][ 3] = "Best-of-how-much";      StringGridParameters->Cells[1][ 3] = "5";
  StringGridParameters->Cells[0][ 4] = "Assessing error A";     StringGridParameters->Cells[1][ 4] = "0.001";
  StringGridParameters->Cells[0][ 5] = "Assessing error B";     StringGridParameters->Cells[1][ 5] = "0.001";
  StringGridParameters->Cells[0][ 6] = "Mean trait A";          StringGridParameters->Cells[1][ 6] = "-1.0";
  StringGridParameters->Cells[0][ 7] = "StdDev trait A";        StringGridParameters->Cells[1][ 7] = "0.0";
  StringGridParameters->Cells[0][ 8] = "Mean trait B";          StringGridParameters->Cells[1][ 8] = "1.0";
  StringGridParameters->Cells[0][ 9] = "StdDev trait B";        StringGridParameters->Cells[1][ 9] = "0.0";
  StringGridParameters->Cells[0][10] = "Mean preference A";     StringGridParameters->Cells[1][10] = "-1.0";
  StringGridParameters->Cells[0][11] = "StdDev preference A";   StringGridParameters->Cells[1][11] = "0.0";
  StringGridParameters->Cells[0][12] = "Mean preference B";     StringGridParameters->Cells[1][12] = "1.0";
  StringGridParameters->Cells[0][13] = "StdDev preference B";   StringGridParameters->Cells[1][13] = "0.0";
  StringGridParameters->Cells[0][14] = "Number of simulations"; StringGridParameters->Cells[1][14] = "1";
  StringGridParameters->Cells[0][15] = "Number of generations"; StringGridParameters->Cells[1][15] = "1";
  StringGridParameters->Cells[0][16] = "Number of offspring";   StringGridParameters->Cells[1][16] = "6";
  StringGridParameters->Cells[0][17] = "SurviveSpeciesAlpha";   StringGridParameters->Cells[1][17] = "1.0";
  StringGridParameters->Cells[0][18] = "SurviveSpeciesBeta";    StringGridParameters->Cells[1][18] = "10.0";
  StringGridParameters->Cells[0][19] = "SigmaSquared";          StringGridParameters->Cells[1][19] = "1.0";
  StringGridParameters->Cells[0][20] = "Cost trait";            StringGridParameters->Cells[1][20] = "0.1";
  StringGridParameters->Cells[0][21] = "Cost preference";       StringGridParameters->Cells[1][21] = "0.01";
  StringGridParameters->Cells[0][22] = "Mutation rate";         StringGridParameters->Cells[1][22] = "0.01";

  PageControlSimChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonRunClick(TObject *Sender)
{
  //Check the input in own scope
  if (checkInput()==false) return;

  StatusBarMain->Panels->Items[0]->Text = "Running simulation";
  setCursor("CursorPiedFlycatcherSleeping.cur");
  Refresh(); //To draw this text to the StatusBar

  emptyChart(ChartBias);
  emptyChart(ChartMateFraction);

  //Read parameters
  Parameters parameters = readStringGrid();
  parameters.matingSystem   = (RadioGroupGamy->ItemIndex  == 0 ? monogamy : polygyny);

  switch(RadioGroupFemaleSampling->ItemIndex)
  {
    case 0: parameters.femaleSampling = bestOfNconspicific;           break;
    case 1: parameters.femaleSampling = bestOfNextremeTrait;          break;
    case 2: parameters.femaleSampling = bestOfNclosestTrait;          break;
    case 3: parameters.femaleSampling = fixedThresholdConspicific;    break;
    case 4: parameters.femaleSampling = fixedThresholdTraitSign;      break;
    case 5: parameters.femaleSampling = fixedThresholdProbabilistic; break;
    default: assert(!"Unknown index of RadioGroupTestSampling"); std::exit(1);
  }

  parameters.densityDependentSelection = (RadioGroupDensityDependentSelection->ItemIndex == 0 ? afterMating : beforeMating );

  //Show parameters
  RichEditOutput->Lines->Clear();
  RichEditOutput->Lines->Add("Number of males: " + IntToStr(parameters.nMales));
  RichEditOutput->Lines->Add("Number of males: " + IntToStr(parameters.nMales));
  RichEditOutput->Lines->Add("Number of females: " + IntToStr(parameters.nFemales));
  RichEditOutput->Lines->Add("Best of how much: " + IntToStr(parameters.bestOfHowMuch));
  RichEditOutput->Lines->Add("Assessing error A: " + FloatToStr(parameters.assessingErrorA));
  RichEditOutput->Lines->Add("Assessing error B: " + FloatToStr(parameters.assessingErrorB));
  RichEditOutput->Lines->Add("Mean trait A: " + FloatToStr(parameters.meanTraitA));
  RichEditOutput->Lines->Add("StdDev trait A: " + FloatToStr(parameters.stdDevTraitA));
  RichEditOutput->Lines->Add("Mean trait males B: " + FloatToStr(parameters.meanTraitB));
  RichEditOutput->Lines->Add("StdDev trait males B: " + FloatToStr(parameters.stdDevTraitB));
  RichEditOutput->Lines->Add("Mean preference A: " + FloatToStr(parameters.meanPreferenceA));
  RichEditOutput->Lines->Add("StdDev preference A: " + FloatToStr(parameters.stdDevPreferenceA));
  RichEditOutput->Lines->Add("Mean preference males B: " + FloatToStr(parameters.meanPreferenceB));
  RichEditOutput->Lines->Add("StdDev preference males B: " + FloatToStr(parameters.stdDevPreferenceB));

  RichEditOutput->Lines->Add("Number of simulation: " + IntToStr(parameters.nSimulations));
  RichEditOutput->Lines->Add("Number of generations: " + IntToStr(parameters.nGenerations));
  RichEditOutput->Lines->Add("Number of offspring per couple: " + IntToStr(parameters.nOffspring));
  RichEditOutput->Lines->Add("SurviveSpeciesAlpha: " + FloatToStr(parameters.surviveSpeciesAlpha));
  RichEditOutput->Lines->Add("SurviveSpeciesBeta: " + FloatToStr(parameters.surviveSpeciesBeta));
  RichEditOutput->Lines->Add("SigmaSquared: " + FloatToStr(parameters.sigmaSquared));
  RichEditOutput->Lines->Add("Cost trait: " + FloatToStr(parameters.costTrait));
  RichEditOutput->Lines->Add("Cost preference: " + FloatToStr(parameters.costPreference));
  RichEditOutput->Lines->Add("Mutation rate: " + FloatToStr(parameters.mutationRate));
  RichEditOutput->Lines->Add(parameters.matingSystem  == monogamy ? "Mating system: monogamy" : "Mating system: polygyny" );
  switch(parameters.femaleSampling)
  {
    case bestOfNconspicific:
      RichEditOutput->Lines->Add("Female sampling: Best-Of-N conspicific");
      break;
    case bestOfNextremeTrait:
      RichEditOutput->Lines->Add("Female sampling: Best-Of-N extreme trait");
      break;
    case bestOfNclosestTrait:
      RichEditOutput->Lines->Add("Female sampling: Best-Of-N closest trait");
      break;
    case fixedThresholdConspicific:
      RichEditOutput->Lines->Add("Female sampling: Fixed threshold conspicific");
      break;
    case fixedThresholdTraitSign:
      RichEditOutput->Lines->Add("Female sampling: Fixed threshold trait sign");
      break;
    case fixedThresholdProbabilistic:
      RichEditOutput->Lines->Add("Female sampling: Fixed threshold probabilistic");
      break;
  }
  RichEditOutput->Lines->Add(parameters.densityDependentSelection==beforeMating ? "Density dependent selection: before mating" : "Density dependent selection: after mating");

  //Start simulation
  const double deltaFraction
    = (PageControlSim->ActivePageIndex == 1 ? EditFractionStep->Text.ToDouble() : 1.0);
  const double fractionFrom
    = (PageControlSim->ActivePageIndex == 1 ? EditFractionFrom->Text.ToDouble() : EditFraction->Text.ToDouble());
  const double fractionTo
    = (PageControlSim->ActivePageIndex == 1 ? EditFractionTo->Text.ToDouble() : 1.0);

  std::string lastErrorMessage;
  for (double fraction = fractionFrom; fraction < fractionTo; fraction+=deltaFraction)
  //double fraction = 0.9;
  {
    ProgressBarSim->Position = fraction * ProgressBarSim->Max;
    ProgressBarSim->Refresh();
    emptyChart(ChartBiasTime);
    emptyChart(ChartMateTime);
    emptyChart(ChartPopSize);
    emptyChart(ChartTraitPreference);

    parameters.fractionMaleA   = fraction;
    parameters.fractionFemaleA = fraction;
    //parameters.nGenerations = 1;
    const unsigned int nSimulations = parameters.nSimulations;
    std::vector<TimeSeries> allTimeSeries; //Size 0, use push_back
    for (unsigned int simulation = 0; simulation < nSimulations; ++simulation)
    {
      //Stick parameter in simulation and run it
      std::auto_ptr<Simulation> simulation(new Simulation(parameters));
      //simulation->showPopulation(StringGridDebug);
      simulation->execute();
      //Get the results from the sim
      //const TimeSeries thisSimTimeSeries = simulation->getTimeSeries();
      //timeSeries.push_back(thisSimTimeSeries);
      allTimeSeries.push_back(simulation->getTimeSeries());
      lastErrorMessage = simulation->mError;
    }
    //Plot the average of the results
    TimePoint timePointMean, timePointStdError;
    getMeanAndStdErrorEndPoint(allTimeSeries,timePointMean,timePointStdError);
    TimeSeries timeSeriesMean, timeSeriesStdError;
    getMeanAndStdErrorTimeSeries(allTimeSeries,timeSeriesMean, timeSeriesStdError);
    plotTimePoint(timePointMean, timePointStdError,fraction);
    plotTimeSeries(timeSeriesMean, timeSeriesStdError);
  }

  setCursor("CursorPiedFlycatcher.cur");
  StatusBarMain->Panels->Items[0]->Text = toAnsiString(lastErrorMessage);
  if (BitBtn1->Tag==0) PlaySound("PiedFlycatcher.wav",0,SND_FILENAME | SND_ASYNC);

}
//---------------------------------------------------------------------------

//Checks the input, returns true if all valid
bool TFormMain::checkInput()
{
  int checkInt; bool check; double checkDouble;
  //nFemales
  check = TryStrToInt(StringGridParameters->Cells[1][1],checkInt);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'nFemales' is not a valid input"; return false; }
  if (checkInt <= 0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'nFemales' should be positive"; return false; }
  //nMales
  check = TryStrToInt(StringGridParameters->Cells[1][2],checkInt);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'nMales' is not a valid input"; return false; }
  if (checkInt <= 0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'nMales' should be positive"; return false; }
  //bestOfHowMuch
  if (   RadioGroupFemaleSampling->ItemIndex == 0
      || RadioGroupFemaleSampling->ItemIndex == 1
      || RadioGroupFemaleSampling->ItemIndex == 2 ) //If female uses bestOfHowMuch
  {
    check = TryStrToInt(StringGridParameters->Cells[1][3],checkInt);
    if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'bestOfHowMuch' is not a valid input"; return false; }
    if (checkInt <= 0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'bestOfHowMuch' should be bigger then 0"; return false; }
  }
  //assessingErrorA
  check = TryStrToFloat(StringGridParameters->Cells[1][4],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'assessingErrorA' is not a valid input"; return false; }
  if (checkDouble < 0.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'assessingErrorA' should be positive"; return false; }
  if (checkDouble > 1.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'assessingErrorA' should be smaller or equal to 1.0"; return false; }
  //assessingErrorB
  check = TryStrToFloat(StringGridParameters->Cells[1][5],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'assessingErrorB' is not a valid input"; return false; }
  if (checkDouble < 0.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'assessingErrorB' should be positive"; return false; }
  if (checkDouble > 1.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'assessingErrorB' should be smaller or equal to 1.0"; return false; }
  //Mean trait males A
  check = TryStrToFloat(StringGridParameters->Cells[1][6],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Mean trait males A' is not a valid input"; return false; }
  //StdDev trait males A
  check = TryStrToFloat(StringGridParameters->Cells[1][7],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'StdDev trait males A' is not a valid input"; return false; }
  //Mean trait males B
  check = TryStrToFloat(StringGridParameters->Cells[1][8],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Mean trait males B' is not a valid input"; return false; }
  //StdDev trait males B
  check = TryStrToFloat(StringGridParameters->Cells[1][9],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'StdDev trait males B' is not a valid input"; return false; }
  //Mean preference males A
  check = TryStrToFloat(StringGridParameters->Cells[1][10],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Mean preference males A' is not a valid input"; return false; }
  //StdDev preference males A
  check = TryStrToFloat(StringGridParameters->Cells[1][11],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'StdDev preference males A' is not a valid input"; return false; }
  //Mean preference males B
  check = TryStrToFloat(StringGridParameters->Cells[1][12],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Mean preference males B' is not a valid input"; return false; }
  //StdDev preference males B
  check = TryStrToFloat(StringGridParameters->Cells[1][13],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'StdDev preference males B' is not a valid input"; return false; }
  //Number of simulations
  check = TryStrToInt(StringGridParameters->Cells[1][14],checkInt);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Number of simulations' is not a valid input"; return false; }
  if (checkInt <= 0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Number of simulations' should be positive"; return false; }
  //Number of generations
  check = TryStrToInt(StringGridParameters->Cells[1][15],checkInt);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Number of generations' is not a valid input"; return false; }
  if (checkInt <= 0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Number of generations' should be positive"; return false; }
  //Number of offspring
  check = TryStrToInt(StringGridParameters->Cells[1][16],checkInt);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Number of offspring' is not a valid input"; return false; }
  if (checkInt <= 0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Number of offspring' should be positive"; return false; }
  //SurviveSpeciesAlpha
  check = TryStrToFloat(StringGridParameters->Cells[1][17],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'SurviveSpeciesAlpha' is not a valid input"; return false; }
  if (checkDouble < 0.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'SurviveSpeciesAlpha' should be positive"; return false; }
  if (checkDouble > 1.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'SurviveSpeciesAlpha' should be smaller or equal to 1.0"; return false; }
  //SurviveSpeciesBeta
  check = TryStrToFloat(StringGridParameters->Cells[1][18],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'SurviveSpeciesBeta' is not a valid input"; return false; }
  if (checkDouble < 0.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'SurviveSpeciesBeta' should be positive"; return false; }
  //SigmaSquared
  check = TryStrToFloat(StringGridParameters->Cells[1][19],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'SigmaSquared' is not a valid input"; return false; }
  if (checkDouble <= 0.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'SigmaSquared' should be positive"; return false; }
  //CostTrait
  check = TryStrToFloat(StringGridParameters->Cells[1][20],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'CostTrait' is not a valid input"; return false; }
  if (checkDouble < 0.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'CostTrait' should be positive"; return false; }
  //CostPreference
  check = TryStrToFloat(StringGridParameters->Cells[1][21],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'CostPreference' is not a valid input"; return false; }
  if (checkDouble < 0.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'CostPreference' should be positive"; return false; }
  //MutationRate
  check = TryStrToFloat(StringGridParameters->Cells[1][22],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'MutationRate' is not a valid input"; return false; }
  if (checkDouble < 0.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'MutationRate' should be positive"; return false; }

  return true;
}
//---------------------------------------------------------------------------
void TFormMain::plotTimePoint(
  const TimePoint& mean,
  const TimePoint& stdError,
  const double& chartX)
{
  ChartBias->Series[0]->AddXY(chartX,mean.mateTally.calculateBiasA());
  ChartBias->Series[1]->AddXY(chartX,mean.mateTally.calculateBiasB());
  ChartBias->Series[2]->AddXY(chartX,mean.mateTally.calculateFractionMixedPairs());

  ChartMateFraction->Series[0]->AddXY(chartX,mean.mateTally.getNmateAA());
  ChartMateFraction->Series[1]->AddXY(chartX,mean.mateTally.getNmateAB());
  ChartMateFraction->Series[2]->AddXY(chartX,mean.mateTally.getNmateBA());
  ChartMateFraction->Series[3]->AddXY(chartX,mean.mateTally.getNmateBB());

}
//---------------------------------------------------------------------------
void TFormMain::plotTimeSeries(
  const TimeSeries& mean,
  const TimeSeries& stdError)
{
  emptyChart(ChartPopSize);
  emptyChart(ChartMateTime);
  const unsigned int nGenerations = mean.timePoints.size();
  for (unsigned i=0; i<nGenerations; ++i)
  {
    const double iD = static_cast<double>(i);
    /*
    ChartPopSize->Series[0]->AddXY(iD+0.00,mean.timePoints[i].speciesTallyOffspring.getNfemalesA());
    ChartPopSize->Series[1]->AddXY(iD+0.00,mean.timePoints[i].speciesTallyOffspring.getNfemaleHybridsA());
    ChartPopSize->Series[2]->AddXY(iD+0.00,mean.timePoints[i].speciesTallyOffspring.getNfemaleHybridsB());
    ChartPopSize->Series[3]->AddXY(iD+0.00,mean.timePoints[i].speciesTallyOffspring.getNfemalesB());
    ChartPopSize->Series[4]->AddXY(iD+0.00,mean.timePoints[i].speciesTallyOffspring.getNmalesA());
    ChartPopSize->Series[5]->AddXY(iD+0.00,mean.timePoints[i].speciesTallyOffspring.getNmaleHybridsA());
    ChartPopSize->Series[6]->AddXY(iD+0.00,mean.timePoints[i].speciesTallyOffspring.getNmaleHybridsB());
    ChartPopSize->Series[7]->AddXY(iD+0.00,mean.timePoints[i].speciesTallyOffspring.getNmalesB());
    ChartPopSize->Series[8]->AddXY(iD+0.00,mean.timePoints[i].speciesTallyOffspring.getNall());

    ChartPopSize->Series[0]->AddXY(iD+0.20,mean.timePoints[i].speciesTallyAfterSpeciesSelection.getNfemalesA());
    ChartPopSize->Series[1]->AddXY(iD+0.20,mean.timePoints[i].speciesTallyAfterSpeciesSelection.getNfemaleHybridsA());
    ChartPopSize->Series[2]->AddXY(iD+0.20,mean.timePoints[i].speciesTallyAfterSpeciesSelection.getNfemaleHybridsB());
    ChartPopSize->Series[3]->AddXY(iD+0.20,mean.timePoints[i].speciesTallyAfterSpeciesSelection.getNfemalesB());
    ChartPopSize->Series[4]->AddXY(iD+0.20,mean.timePoints[i].speciesTallyAfterSpeciesSelection.getNmalesA());
    ChartPopSize->Series[5]->AddXY(iD+0.20,mean.timePoints[i].speciesTallyAfterSpeciesSelection.getNmaleHybridsA());
    ChartPopSize->Series[6]->AddXY(iD+0.20,mean.timePoints[i].speciesTallyAfterSpeciesSelection.getNmaleHybridsB());
    ChartPopSize->Series[7]->AddXY(iD+0.20,mean.timePoints[i].speciesTallyAfterSpeciesSelection.getNmalesB());
    ChartPopSize->Series[8]->AddXY(iD+0.20,mean.timePoints[i].speciesTallyAfterSpeciesSelection.getNall());

    ChartPopSize->Series[0]->AddXY(iD+0.40,mean.timePoints[i].speciesTallyAfterTraitSelection.getNfemalesA());
    ChartPopSize->Series[1]->AddXY(iD+0.40,mean.timePoints[i].speciesTallyAfterTraitSelection.getNfemaleHybridsA());
    ChartPopSize->Series[2]->AddXY(iD+0.40,mean.timePoints[i].speciesTallyAfterTraitSelection.getNfemaleHybridsB());
    ChartPopSize->Series[3]->AddXY(iD+0.40,mean.timePoints[i].speciesTallyAfterTraitSelection.getNfemalesB());
    ChartPopSize->Series[4]->AddXY(iD+0.40,mean.timePoints[i].speciesTallyAfterTraitSelection.getNmalesA());
    ChartPopSize->Series[5]->AddXY(iD+0.40,mean.timePoints[i].speciesTallyAfterTraitSelection.getNmaleHybridsA());
    ChartPopSize->Series[6]->AddXY(iD+0.40,mean.timePoints[i].speciesTallyAfterTraitSelection.getNmaleHybridsB());
    ChartPopSize->Series[7]->AddXY(iD+0.40,mean.timePoints[i].speciesTallyAfterTraitSelection.getNmalesB());
    ChartPopSize->Series[8]->AddXY(iD+0.40,mean.timePoints[i].speciesTallyAfterTraitSelection.getNall());
    */
    ChartPopSize->Series[0]->AddXY(iD+0.60,mean.timePoints[i].speciesTallyAfterDensityDependentSelection.getNfemalesA());
    ChartPopSize->Series[1]->AddXY(iD+0.60,mean.timePoints[i].speciesTallyAfterDensityDependentSelection.getNfemalesB());
    ChartPopSize->Series[2]->AddXY(iD+0.60,mean.timePoints[i].speciesTallyAfterDensityDependentSelection.getNmalesA());
    ChartPopSize->Series[3]->AddXY(iD+0.60,mean.timePoints[i].speciesTallyAfterDensityDependentSelection.getNmalesB());
    //ChartPopSize->Series[4]->AddXY(iD+0.60,mean.timePoints[i].speciesTallyAfterDensityDependentSelection.getNall());

    ChartMateTime->Series[0]->AddXY(iD,mean.timePoints[i].mateTally.getNmateAA());
    ChartMateTime->Series[1]->AddXY(iD,mean.timePoints[i].mateTally.getNmateAB());
    ChartMateTime->Series[2]->AddXY(iD,mean.timePoints[i].mateTally.getNmateBA());
    ChartMateTime->Series[3]->AddXY(iD,mean.timePoints[i].mateTally.getNmateBB());
    ChartMateTime->Series[4]->AddXY(iD,mean.timePoints[i].mateTally.getNmateAll());

    ChartBiasTime->Series[0]->AddXY(iD,mean.timePoints[i].mateTally.calculateBiasA());
    ChartBiasTime->Series[1]->AddXY(iD,mean.timePoints[i].mateTally.calculateBiasB());
    ChartBiasTime->Series[2]->AddXY(iD,mean.timePoints[i].mateTally.calculateFractionMixedPairs());

    const unsigned int nTraits = mean.timePoints[i].traits.size();
    for (unsigned int j=0; j<nTraits; ++j) ChartTraitPreference->Series[0]->AddXY(iD,mean.timePoints[i].traits[j]);
    const unsigned int nPreferences = mean.timePoints[i].preferences.size();
    for (unsigned int j=0; j<nPreferences; ++j) ChartTraitPreference->Series[1]->AddXY(iD,mean.timePoints[i].preferences[j]);
    const unsigned int nSpeciesValues = mean.timePoints[i].descents.size();
    for (unsigned int j=0; j<nSpeciesValues; ++j) ChartTraitPreference->Series[2]->AddXY(iD,mean.timePoints[i].descents[j]);
  }
}
//---------------------------------------------------------------------------
void TFormMain::setCursor(const String& cursorName)
{
  TCursor myCursor = static_cast<TCursor>(22);
  Screen->Cursors[22] = LoadCursorFromFile(cursorName.c_str());
  Cursor = myCursor;
  FormMain->Cursor = myCursor;
  PageControlMain->Cursor = myCursor;
  StringGridParameters->Cursor = myCursor;
  PanelLeft->Cursor = myCursor;
  ChartBias->Cursor = myCursor;
  ChartPopSize->Cursor = myCursor;
  ChartMateTime->Cursor = myCursor;
  ButtonRun->Cursor = myCursor;
  ProgressBarSim->Cursor = myCursor;
  RadioGroupGamy->Cursor = myCursor;
  RadioGroupFemaleSampling->Cursor = myCursor;
  RichEditOutput->Cursor = myCursor;
  RichEdit2->Cursor = myCursor;
}
//---------------------------------------------------------------------------
Parameters TFormMain::readStringGrid() const
{
  Parameters parameters;
  parameters.nFemales            = StringGridParameters->Cells[1][ 1].ToInt();
  parameters.nMales              = StringGridParameters->Cells[1][ 2].ToInt();
  parameters.bestOfHowMuch       = StringGridParameters->Cells[1][ 3].ToInt();
  parameters.assessingErrorA     = StringGridParameters->Cells[1][ 4].ToDouble();
  parameters.assessingErrorB     = StringGridParameters->Cells[1][ 5].ToDouble();
  parameters.meanTraitA          = StringGridParameters->Cells[1][ 6].ToDouble();
  parameters.stdDevTraitA        = StringGridParameters->Cells[1][ 7].ToDouble();
  parameters.meanTraitB          = StringGridParameters->Cells[1][ 8].ToDouble();
  parameters.stdDevTraitB        = StringGridParameters->Cells[1][ 9].ToDouble();
  parameters.meanPreferenceA     = StringGridParameters->Cells[1][10].ToDouble();
  parameters.stdDevPreferenceA   = StringGridParameters->Cells[1][11].ToDouble();
  parameters.meanPreferenceB     = StringGridParameters->Cells[1][12].ToDouble();
  parameters.stdDevPreferenceB   = StringGridParameters->Cells[1][13].ToDouble();
  parameters.nSimulations        = StringGridParameters->Cells[1][14].ToInt();
  parameters.nGenerations        = StringGridParameters->Cells[1][15].ToInt();
  parameters.nOffspring          = StringGridParameters->Cells[1][16].ToInt();
  parameters.surviveSpeciesAlpha = StringGridParameters->Cells[1][17].ToDouble();
  parameters.surviveSpeciesBeta  = StringGridParameters->Cells[1][18].ToDouble();
  parameters.sigmaSquared        = StringGridParameters->Cells[1][19].ToDouble();
  parameters.costTrait           = StringGridParameters->Cells[1][20].ToDouble();
  parameters.costPreference      = StringGridParameters->Cells[1][21].ToDouble();
  parameters.mutationRate        = StringGridParameters->Cells[1][22].ToDouble();
  return parameters;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonTestClick(TObject *Sender)
{
  std::auto_ptr<StateFemaleSamplingBase> femaleSampling;
  switch(RadioGroupFemaleSampling->ItemIndex)
  {
    case 0: femaleSampling.reset(new StateFemaleSamplingBestOfNconspicific); break;
    case 1: femaleSampling.reset(new StateFemaleSamplingBestOfNextremeTrait); break;
    case 2: femaleSampling.reset(new StateFemaleSamplingBestOfNclosestTrait); break;
    case 3: femaleSampling.reset(new StateFemaleSamplingFixedThresholdConspicific); break;
    case 4: femaleSampling.reset(new StateFemaleSamplingFixedThresholdTraitSign); break;
    case 5: femaleSampling.reset(new StateFemaleSamplingFixedThresholdProbabilistic); break;
    default: assert(!"Unknown index of RadioGroupTestSampling"); std::exit(1);
  }

  Parameters parameters = readStringGrid();
  const double femaleSpeciesValue = StringGridTest->Cells[1][1].ToDouble();
  const double maleSpeciesValue1  = StringGridTest->Cells[2][1].ToDouble();
  const double maleSpeciesValue2  = StringGridTest->Cells[3][1].ToDouble();
  const double maleSpeciesValue3  = StringGridTest->Cells[4][1].ToDouble();
  const double maleSpeciesValue4  = StringGridTest->Cells[5][1].ToDouble();
  const double femalePreference   = StringGridTest->Cells[1][2].ToDouble();
  const double maleTrait1         = StringGridTest->Cells[2][2].ToDouble();
  const double maleTrait2         = StringGridTest->Cells[3][2].ToDouble();
  const double maleTrait3         = StringGridTest->Cells[4][2].ToDouble();
  const double maleTrait4         = StringGridTest->Cells[5][2].ToDouble();
  std::vector<Female> females = Bird::createTestFemales(parameters,femaleSpeciesValue, femalePreference);
  std::vector<Male> males = Bird::createTestMales(
    parameters,
    maleSpeciesValue1, maleTrait1,
    maleSpeciesValue2, maleTrait2,
    maleSpeciesValue3, maleTrait3,
    maleSpeciesValue4, maleTrait4
    );

  std::vector<unsigned int> histogramWinner(4);
  for (unsigned int i=0; i<4; ++i) histogramWinner[i]=0;

  for (unsigned int i=0; i<1000; ++i)
  {
    const unsigned int winnerIndex = femaleSampling->getWinnerIndex(males,females[0],parameters);
    ++(histogramWinner[winnerIndex]);
  }
  emptyChart(ChartTest);
  ChartTest->Series[0]->AddXY(0.0,histogramWinner[0]);
  ChartTest->Series[0]->AddXY(1.0,histogramWinner[1]);
  ChartTest->Series[0]->AddXY(2.0,histogramWinner[2]);
  ChartTest->Series[0]->AddXY(3.0,histogramWinner[3]);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonTestSurvivalSpeciesClick(TObject *Sender)
{
  ChartTestProbabilities->Series[0]->Clear();
  const double alpha = StringGridParameters->Cells[1][17].ToDouble();
  const double beta  = StringGridParameters->Cells[1][18].ToDouble();
  ChartTestProbabilities->Title->Text->Clear();
  ChartTestProbabilities->Title->Text->Add("const double y = 1.0 - (alpha * std::exp(-beta * descent * descent))");
  ChartTestProbabilities->Title->Text->Add("SurviveSpeciesAlpha: " + FloatToStr(alpha) + ", SurviveSpeciesBeta: " + FloatToStr(beta));
  ChartTestProbabilities->BottomAxis->Title->Caption = "SpeciesValue/descent";
  ChartTestProbabilities->LeftAxis->Title->Caption = "Chance of survival";
  for (double descent = -1.0; descent<1.0; descent+=0.01)
  {
    const double surviveSpecies = Simulation::chanceToSurviveSpecies(descent,alpha,beta);
    ChartTestProbabilities->Series[0]->AddXY(descent,surviveSpecies);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  TCursor myCursor = static_cast<TCursor>(22);
  Screen->Cursors[22] = LoadCursorFromFile("CursorPiedFlycatcher.cur");
  Cursor = myCursor;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonSaveClick(TObject *Sender)
{
  std::auto_ptr<TStringList> stringList(new TStringList);

  stringList->Add(" ");
  stringList->Add("Parameters: ");

  if (PageControlSim->ActivePageIndex==0)
  {
    stringList->Add("FractionA : " + EditFraction->Text);
  }
  else
  {
    stringList->Add(
      "Fration A from: " + EditFractionFrom->Text
      + " to: " + EditFractionTo->Text
      + " in steps of: " + EditFractionStep->Text);
  }

  stringList->AddStrings(getStringGrid(StringGridParameters).release());

  switch(RadioGroupGamy->ItemIndex)
  {
    case 0: //monogamous
      stringList->Add("Mating system: monogamous");
      break;
    case 1: //polygynous
      stringList->Add("Mating system: polygynous");
      break;
  }

  switch(RadioGroupFemaleSampling->ItemIndex)
  {
    case 0: //bestOfNconspicific:
      stringList->Add("Female sampling: Best-Of-N conspicific");
      break;
    case 1: //bestOfNextremeTrait:
      stringList->Add("Female sampling: Best-Of-N extreme trait");
      break;
    case 2: //bestOfNclosestTrait:
      stringList->Add("Female sampling: Best-Of-N closest trait");
      break;
    case 3: //fixedThresholdConspicific:
      stringList->Add("Female sampling: Fixed threshold conspicific");
      break;
    case 4: //fixedThresholdTraitSign:
      stringList->Add("Female sampling: Fixed threshold trait sign");
      break;
    case 5: //fixedThresholdProbabilistic:
      stringList->Add("Female sampling: Fixed threshold probabilistic");
      break;
  }

  switch(RadioGroupDensityDependentSelection->ItemIndex)
  {
    case 0:
      stringList->Add("Density dependent selection: in reproduction, after mating");
      break;
    case 1:
      stringList->Add("Density dependent selection: after selection, before mating");
      break;
  }

  stringList->Add(" ");
  stringList->Add("Biases in time: ");
  stringList->Add("Time,BiasA,BiasB,Fraction of mixed pairs");
  stringList->AddStrings(getChart(ChartBiasTime).release());

  Dot("Trait and preferences in time");
  stringList->Add(" ");
  stringList->Add("Traits in time");
  stringList->Add("Time,Traits");
  stringList->AddStrings(getChartSeries(ChartTraitPreference->Series[0]).release());

  stringList->Add(" ");
  stringList->Add("Traits in time");
  stringList->Add("Time,Preference");
  stringList->AddStrings(getChartSeries(ChartTraitPreference->Series[1]).release());

  stringList->Add(" ");
  stringList->Add("Descent in time");
  stringList->Add("Time,Descent");
  stringList->AddStrings(getChartSeries(ChartTraitPreference->Series[2]).release());

  Dot("Number of matings in time");
  stringList->Add(" ");
  stringList->Add("Number of matings in time");
  stringList->Add("Time,AA,AB,BA,BB,Sum");
  stringList->AddStrings(getChart(ChartMateTime).release());

  Dot("number of individuals in time");
  stringList->Add(" ");
  stringList->Add("Number of individuals in time");
  stringList->Add("Time,FemalesA,FemalesB,MalesA,MalesB");
  stringList->AddStrings(getChart(ChartPopSize).release());

  Dot("Biases for different fractions of maleA: ");
  stringList->Add(" ");
  stringList->Add("Biases for different fractions of maleA: ");
  stringList->Add("Fraction,BiasA,BiasB,Fraction of mixed pairs");
  stringList->AddStrings(getChart(ChartBias).release());

  Dot("Number of matings for different proportions of maleA: ");
  stringList->Add(" ");
  stringList->Add("Number of matings for different proportions of maleA: ");
  stringList->Add("Fraction,AA,AB,BA,BB");
  stringList->AddStrings(getChart(ChartMateFraction).release());

  if (SaveDialog1->Execute()==true)
  {
    stringList->SaveToFile(SaveDialog1->FileName);
  }

  RichEditOutput->Lines = stringList.release();

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtn1Click(TObject *Sender)
{
/*
  if (BitBtn1->Tag==1)
  {
    BitBtn1->Glyph->LoadFromFile("PiedFlycatcher.bmp");
    BitBtn1->Tag=0;
  }
  else
  {
    BitBtn1->Glyph->LoadFromFile("PiedFlycatcherSleeping.bmp");
    BitBtn1->Tag=1;
  }
  */
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
std::string toString(const String& ansi)
{
  const char * myChar = ansi.c_str();
  const std::string myString = myChar;
  return myString;
}
//---------------------------------------------------------------------------
String toAnsiString(const std::string& myString)
{
  const char * myChar = myString.c_str();
  const String myAnsi = myChar;
  return myAnsi;
}
//---------------------------------------------------------------------------
void emptyChart(TChart* chart)
{
  const int nSeries = chart->SeriesCount();
  for (int i=0; i<nSeries; ++i)
  {
    chart->Series[i]->Clear();
  }
}
//---------------------------------------------------------------------------
std::auto_ptr<TStringList> getStringGrid(const TStringGrid * stringGrid)
{
  //Those Borland people were not const correct, so I need a const cast here
  //Grumble, grumble...
  TStringGrid * grid = const_cast<TStringGrid*>(stringGrid);
  const String seperator = ",";

  std::auto_ptr<TStringList> stringList(new TStringList);
  const int maxy = grid->RowCount;
  const int maxx = grid->ColCount;
  for (int y=0; y<maxy; ++y)
  {
    String myString;
    for (int x=0; x<maxx-1; ++x)
    {
      myString+=grid->Cells[x][y] + seperator; //This function should have been const, as it is a read function
    }
    myString+=grid->Cells[maxx-1][y];
    stringList->Add(myString);
  }
  return stringList;
}
//---------------------------------------------------------------------------
std::auto_ptr<TStringList> getChart(const TChart * anyChart)
{
  //Those Borland people were not const correct, so I need a const cast here
  //Grumble, grumble...
  TChart * chart = const_cast<TChart*>(anyChart);
  const String seperator = ",";
  std::auto_ptr<TStringList> stringList(new TStringList);

  //Copy the pointers to the values
  std::vector< TChartValueList* > xValuesVector;
  std::vector< TChartValueList* > yValuesVector;
  const int nSeries = chart->SeriesCount();
  for (int i=0; i<nSeries; ++i)
  {
    xValuesVector.push_back(chart->Series[i]->XValues);
    yValuesVector.push_back(chart->Series[i]->YValues);
    //Assume there are as many X's as Y's
    assert(xValuesVector[i]->Count()==yValuesVector[i]->Count());
  }

  //Make a nice collumn of X values and then all Y values
  const int nRows = xValuesVector[0]->Count();
  #ifndef NDEBUG
    for (int i=0; i<nSeries; ++i)
    {
    assert(xValuesVector[i]->Count()==nRows);
    assert(yValuesVector[i]->Count()==nRows);
    }
  #endif

  const unsigned int nCols = xValuesVector.size();
  assert(nCols == yValuesVector.size());

  for (int y=0; y<nRows; ++y)
  {
    String myString = FloatToStr(xValuesVector[0]->operator [](y)) + seperator;
    for (unsigned int x=0; x<nCols-1; ++x)
    {
      myString+=FloatToStr(yValuesVector[x]->operator [](y)) + seperator;
    }
    myString+=FloatToStr(yValuesVector[nCols-1]->operator [](y));
    stringList->Add(myString);
  }

  return stringList;
}
//---------------------------------------------------------------------------
std::auto_ptr<TStringList> getChartSeries(const TChartSeries * series)
{
  std::auto_ptr<TStringList> stringList(new TStringList);
  const String seperator = ",";

  //Copy the pointers to the values
  TChartValueList * xValues = series->XValues;
  TChartValueList * yValues = series->YValues;
  //Assume there are as many X's as Y's
  assert(xValues->Count()==yValues->Count());

  const int nRows = xValues->Count();
  double x = -1.0;
  String myString;
  for (int y=0; y<nRows; ++y)
  {
    const double thisX = xValues->operator [](y);
    if (x!=thisX)
    {
      stringList->Add(myString);
      myString = FloatToStr(thisX) + seperator + FloatToStr(yValues->operator [](y)) + seperator;
      x = thisX;
    }
    else
    {
      myString += FloatToStr(yValues->operator [](y))+seperator;
    }
  }

  stringList->Add(myString);
  return stringList;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonTestTraitClick(TObject *Sender)
{
  ChartTestProbabilities->Series[0]->Clear();
  const double costTrait = StringGridParameters->Cells[1][20].ToDouble();
  ChartTestProbabilities->Title->Text->Clear();
  ChartTestProbabilities->Title->Text->Add("const double survival = std::exp(-costTrait * trait * trait);");
  ChartTestProbabilities->Title->Text->Add("costTrait: " + FloatToStr(costTrait));
  ChartTestProbabilities->BottomAxis->Title->Caption = "Species trait";
  ChartTestProbabilities->LeftAxis->Title->Caption = "Chance of survival";
  for (double maleTrait = -1.0; maleTrait<1.0; maleTrait+=0.01)
  {
    const double survivalTrait = Simulation::chanceToSurviveTrait(maleTrait,costTrait);
    ChartTestProbabilities->Series[0]->AddXY(maleTrait,survivalTrait);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonTestPreferenceClick(TObject *Sender)
{
  ChartTestProbabilities->Series[0]->Clear();
  const double costPreference = StringGridParameters->Cells[1][21].ToDouble();

  ChartTestProbabilities->Title->Text->Clear();
  ChartTestProbabilities->Title->Text->Add("const double survival = std::exp(-costPreference * preference * preference");
  ChartTestProbabilities->Title->Text->Add("costPreference: " + FloatToStr(costPreference));
  ChartTestProbabilities->BottomAxis->Title->Caption = "Species preference";
  ChartTestProbabilities->LeftAxis->Title->Caption = "Chance of survival";
  for (double femalePreference = -1.0; femalePreference<1.0; femalePreference+=0.01)
  {
    const double survivalPreference = Simulation::chanceToSurvivePreference(femalePreference,costPreference);
    ChartTestProbabilities->Series[0]->AddXY(femalePreference,survivalPreference);
  }

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonTestProbabilisticMatingClick(TObject *Sender)
{
  const double femalePreference = 0.0;
  const double sigmaSquared = StringGridParameters->Cells[1][19].ToDouble();
  ChartTestProbabilities->Series[0]->Clear();
  ChartTestProbabilities->Title->Text->Clear();
  ChartTestProbabilities->Title->Text->Add("const double chanceToMate =std::exp(-(maleTrait-femalePreference)*(maleTrait-femalePreference)/sigmaSquared);");
  ChartTestProbabilities->Title->Text->Add("FemalePreference: 0.0 (in this example)");
  ChartTestProbabilities->Title->Text->Add("sigmaSquared: " + FloatToStr(sigmaSquared));
  ChartTestProbabilities->BottomAxis->Title->Caption = "Male trait";
  ChartTestProbabilities->LeftAxis->Title->Caption = "Chance to mate";
  for (double maleTrait = -1.0; maleTrait<1.0; maleTrait+=0.01)
  {
    const double chanceToMate =
      StateFemaleSamplingFixedThresholdProbabilistic::getChanceToMate(femalePreference, maleTrait, sigmaSquared);
    ChartTestProbabilities->Series[0]->AddXY(maleTrait,chanceToMate);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridParametersSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
  //Show help
  switch (ARow)
  {
    case  1: StringGridParameters->Hint = "Number of females used in every generation"; break;
    case  2: StringGridParameters->Hint = "Number of males used in every generation"; break;
    case  3: StringGridParameters->Hint = "Number of males the female can sample from"; break;
    case  4: StringGridParameters->Hint = "Assessing error made by species A (0.0 = perfect sampling, 1.0=random mating)"; break;
    case  5: StringGridParameters->Hint = "Assessing error made by species B (0.0 = perfect sampling, 1.0=random mating)"; break;
    case  6: StringGridParameters->Hint = "Initial mean trait of species A"; break;
    case  7: StringGridParameters->Hint = "Initial StdDev of the trait of species A"; break;
    case  8: StringGridParameters->Hint = "Initial mean trait of species B"; break;
    case  9: StringGridParameters->Hint = "Initial StdDev of the trait of species B"; break;
    case 10: StringGridParameters->Hint = "Initial mean preference of species A"; break;
    case 11: StringGridParameters->Hint = "Initial StdDev of the preference of species A"; break;
    case 12: StringGridParameters->Hint = "Initial mean preference of species B"; break;
    case 13: StringGridParameters->Hint = "Initial StdDev of the preference of species B"; break;
    case 14: StringGridParameters->Hint = "Number of simulations of which the results are an average of"; break;
    case 15: StringGridParameters->Hint = "Number of generations"; break;
    case 16: StringGridParameters->Hint = "Number of offspring produced (used when density dependent selection = before reproduction)"; break;
    case 17: StringGridParameters->Hint = "Chance to die of pure hybrids (0.0 = Hybrids have equal survival, 1.0 = hybrids will die by chance 100%)"; break;
    case 18: StringGridParameters->Hint = "Increase in fitmess from hybrids to pure species (0.0 = hybrids and pure have equal survival, 100.0 = pure species have 100% survival)"; break;
    case 19: StringGridParameters->Hint = "Choosiness of female (only used in probabilistic mating, 1000.0 = random mating, 0.001 = very choosy"; break;
    case 20: StringGridParameters->Hint = "Cost trait in survival/trait (0.0 = trait is costless, 10.0 = trait is expensive)"; break;
    case 21: StringGridParameters->Hint = "Cost preference in survival/preference (0.0 = preference is costless, 10.0 = preference is expensive)"; break;
    case 22: StringGridParameters->Hint = "Standard deviation of mutation rate"; break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonTestHelpClick(TObject *Sender)
{
  ShowMessage(
    "These tests show the functions used."
    "\nThe results shown are derived from the functions used in the simulation"
    "\n(so no code duplication, except in the Chart titles)"
    "\nThe parameters used are from the Parameter StringGrid on the left."
    "\nNote that for these functions, the parameters are NOT checked."
    "\nTherefore, it is possible to give in a negative cost for trait,"
    "\nwhich will also yield a result, but when starting the simulation,"
    "\nthese values WILL be checked."
    );
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RadioGroupFemaleSamplingClick(TObject *Sender)
{
  switch(RadioGroupFemaleSampling->ItemIndex)
  {
    case 0: //Best of N conspicific
      RadioGroupFemaleSampling->Hint = "The female chooses a conspicific from a lek of N males";
      break;
    case 1: //Best of N most extreme trait
      RadioGroupFemaleSampling->Hint = "The female chooses a male with the most extreme trait from a lek of N males. If her preference is smaller then 0.0, she prefers a male with trait smaller then 0.0";
      break;
    case 2: //Best of N closest trait-preference
      RadioGroupFemaleSampling->Hint = "The female chooses a male with trait closest near her preference from a lek of N males";
      break;
    case 3: //Fixed threshold conspicific
      RadioGroupFemaleSampling->Hint = "The female searches infinitely for a conspicific";
      break;
    case 4: //Fixed threshold same trait sign
      RadioGroupFemaleSampling->Hint = "The female searches infinitely for a male with the same trait sign as her preference (i.e. a negative-preference female prefers a negative-trait male)";
      break;
    case 5: //Fixed threshold probabilistic
      RadioGroupFemaleSampling->Hint = "The female searches infinitely for a male with trait close to her preference. The chance she will mate with him is defined by SigmaSquared";
      break;
  }
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::RadioGroupDensityDependentSelectionClick(
      TObject *Sender)
{
  switch(RadioGroupDensityDependentSelection->ItemIndex)
  {
    case 0: //In reproduction, nOffspring = popSize parents
      RadioGroupDensityDependentSelection->Hint = "In reproduction, there are offspring produced until the original fractions of speciesA and speciesB are reached for a population size of nMales + nFemales";
    case 1: //After selection, nMatureOffspring = popSize parents
      RadioGroupDensityDependentSelection->Hint = "After selection, before mating, the population is cut down to the needed fractions of speciesA and speciesB to a population size of nMales + nFemales";
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RadioGroupGamyClick(TObject *Sender)
{
  switch(RadioGroupGamy->ItemIndex)
  {
    case 0: //Monogamy
      RadioGroupGamy->Hint = "After a female has selected a male, they will be a couple for life (that is, one generation)";
      break;
    case 1: //Polygyny
      RadioGroupGamy->Hint = "A male can mate with multiple females";
      break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PageControlSimChange(TObject *Sender)
{
  //ShowMessage("TEST" + IntToStr(PageControlSim->ActivePageIndex));
  if (PageControlSim->ActivePageIndex == 0)
  {
    //Single fraction sim (in time)
    PageControlMain->Pages[0]->TabVisible = true;
    PageControlMain->Pages[1]->TabVisible = true;
    PageControlMain->Pages[2]->TabVisible = true;
    PageControlMain->Pages[3]->TabVisible = true;
    PageControlMain->Pages[4]->TabVisible = false;
    PageControlMain->Pages[5]->TabVisible = false;
  }
  else
  {
    //Range of fractions sim
    PageControlMain->Pages[0]->TabVisible = false;
    PageControlMain->Pages[1]->TabVisible = false;
    PageControlMain->Pages[2]->TabVisible = false;
    PageControlMain->Pages[3]->TabVisible = false;
    PageControlMain->Pages[4]->TabVisible = true;
    PageControlMain->Pages[5]->TabVisible = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (BitBtn1->Tag==1)
  {
    BitBtn1->Glyph->LoadFromFile("PiedFlycatcher.bmp");
    BitBtn1->Tag=0;
  }
  else
  {
    BitBtn1->Glyph->LoadFromFile("PiedFlycatcherSleeping.bmp");
    BitBtn1->Tag=1;
  }
  if (Button == mbRight &&  X < 10 && Y < 10)
  {
    std::auto_ptr<TFormAboutBox2> aboutBox(new TFormAboutBox2(this));
    std::auto_ptr<TFormThreeDotsChasing> threeDotsChasing(new TFormThreeDotsChasing(this));
    //const int sumWidth = aboutBox->Width + threeDotsChasing->Width;
    aboutBox->Show();
    aboutBox->Left = 0;
    threeDotsChasing->ShowModal();
  }

}
//---------------------------------------------------------------------------

