//---------------------------------------------------------------------------
#include "UnitMainSTL.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//This STL compatible version can be compiled by
//#defining USE_STL_ONLY

#pragma argsused
int main(int argc, char* argv[])
{
  if (argc<2)
  {
    std::cout << "Please enter name of data file after file name,"
      << "\ne.g. ProjectChrisWileySTL data.txt" << std::endl;
      return 0;
  }
  if (fileExists(argv[1])==false)
  {
    std::cout << "Please enter a VALID and EXISTING name of data file after file name." << std::endl;
    return 0;
  }

  Parameters parameters = readParametersFromFile(argv[1]);

  #ifdef NDEBUG
    OutputDebugString("NDEBUG defined. No debugging output.");
  #else
    OutputDebugString("NDEBUG not defined.");
  #endif

  Simulation simulation(parameters);
  //std::auto_ptr<Simulation> simulation(new Simulation(
  return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//#include "UnitRandom.h"

#include "UnitMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner)
{

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
  StringGridParameters->Cells[0][ 6] = "Mean trait A";          StringGridParameters->Cells[1][ 6] = "0.0";
  StringGridParameters->Cells[0][ 7] = "StdDev trait A";        StringGridParameters->Cells[1][ 7] = "0.0";
  StringGridParameters->Cells[0][ 8] = "Mean trait B";          StringGridParameters->Cells[1][ 8] = "0.0";
  StringGridParameters->Cells[0][ 9] = "StdDev trait B";        StringGridParameters->Cells[1][ 9] = "0.0";
  StringGridParameters->Cells[0][10] = "Mean preference A";     StringGridParameters->Cells[1][10] = "0.0";
  StringGridParameters->Cells[0][11] = "StdDev preference A";   StringGridParameters->Cells[1][11] = "0.0";
  StringGridParameters->Cells[0][12] = "Mean preference B";     StringGridParameters->Cells[1][12] = "0.0";
  StringGridParameters->Cells[0][13] = "StdDev preference B";   StringGridParameters->Cells[1][13] = "0.0";
  StringGridParameters->Cells[0][14] = "Number of simulations"; StringGridParameters->Cells[1][14] = "1";
  StringGridParameters->Cells[0][15] = "Number of generations"; StringGridParameters->Cells[1][15] = "1";
  StringGridParameters->Cells[0][16] = "Number of offspring";   StringGridParameters->Cells[1][16] = "6";
  StringGridParameters->Cells[0][17] = "SurviveSpeciesAlpha";   StringGridParameters->Cells[1][17] = "1.0";
  StringGridParameters->Cells[0][18] = "SurviveSpeciesBeta";    StringGridParameters->Cells[1][18] = "10.0";
  StringGridParameters->Cells[0][19] = "SigmaSquared";          StringGridParameters->Cells[1][19] = "1.0";
  StringGridParameters->Cells[0][20] = "Cost trait";            StringGridParameters->Cells[1][20] = "0.00";
  StringGridParameters->Cells[0][21] = "Cost preference";       StringGridParameters->Cells[1][21] = "0.00";
  StringGridParameters->Cells[0][22] = "Mutation rate";         StringGridParameters->Cells[1][22] = "0.00";
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
  emptyChart(ChartMateTime);
  emptyChart(ChartMateFraction);
  emptyChart(ChartPopSize);
  emptyChart(ChartTraitPreference);

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
  RichEdit1->Lines->Clear();
  RichEdit1->Lines->Add("Number of males: " + IntToStr(parameters.nMales));
  RichEdit1->Lines->Add("Number of females: " + IntToStr(parameters.nFemales));
  RichEdit1->Lines->Add("Best of how much: " + IntToStr(parameters.bestOfHowMuch));
  RichEdit1->Lines->Add("Assessing error A: " + FloatToStr(parameters.assessingErrorA));
  RichEdit1->Lines->Add("Assessing error B: " + FloatToStr(parameters.assessingErrorB));
  RichEdit1->Lines->Add("Mean trait A: " + FloatToStr(parameters.meanTraitA));
  RichEdit1->Lines->Add("StdDev trait A: " + FloatToStr(parameters.stdDevTraitA));
  RichEdit1->Lines->Add("Mean trait males B: " + FloatToStr(parameters.meanTraitB));
  RichEdit1->Lines->Add("StdDev trait males B: " + FloatToStr(parameters.stdDevTraitB));
  RichEdit1->Lines->Add("Mean preference A: " + FloatToStr(parameters.meanPreferenceA));
  RichEdit1->Lines->Add("StdDev preference A: " + FloatToStr(parameters.stdDevPreferenceA));
  RichEdit1->Lines->Add("Mean preference males B: " + FloatToStr(parameters.meanPreferenceB));
  RichEdit1->Lines->Add("StdDev preference males B: " + FloatToStr(parameters.stdDevPreferenceB));

  RichEdit1->Lines->Add("Number of simulation: " + IntToStr(parameters.nSimulations));
  RichEdit1->Lines->Add("Number of generations: " + IntToStr(parameters.nGenerations));
  RichEdit1->Lines->Add("Number of offspring per couple: " + IntToStr(parameters.nOffspring));
  RichEdit1->Lines->Add("SurviveSpeciesAlpha: " + FloatToStr(parameters.surviveSpeciesAlpha));
  RichEdit1->Lines->Add("SurviveSpeciesBeta: " + FloatToStr(parameters.surviveSpeciesBeta));
  RichEdit1->Lines->Add("SigmaSquared: " + FloatToStr(parameters.sigmaSquared));
  RichEdit1->Lines->Add("Cost trait: " + FloatToStr(parameters.costTrait));
  RichEdit1->Lines->Add("Cost preference: " + FloatToStr(parameters.costPreference));
  RichEdit1->Lines->Add("Mutation rate: " + FloatToStr(parameters.mutationRate));
  RichEdit1->Lines->Add(parameters.matingSystem  == monogamy ? "Mating system: monogamy" : "Mating system: polygyny" );
  switch(parameters.femaleSampling)
  {
    case bestOfNconspicific:
      RichEdit1->Lines->Add("Female sampling: Best-Of-N conspicific");
      break;
    case bestOfNextremeTrait:
      RichEdit1->Lines->Add("Female sampling: Best-Of-N extreme trait");
      break;
    case bestOfNclosestTrait:
      RichEdit1->Lines->Add("Female sampling: Best-Of-N closest trait");
      break;
    case fixedThresholdConspicific:
      RichEdit1->Lines->Add("Female sampling: Fixed threshold conspicific");
      break;
    case fixedThresholdTraitSign:
      RichEdit1->Lines->Add("Female sampling: Fixed threshold trait sign");
      break;
    case fixedThresholdProbabilistic:
      RichEdit1->Lines->Add("Female sampling: Fixed threshold probabilistic");
      break;
  }
  RichEdit1->Lines->Add(parameters.densityDependentSelection==beforeMating ? "Density dependent selection: before mating" : "Density dependent selection: after mating");

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
    const TimePoint  timePointAverage = getAverageEndTimePoint(allTimeSeries);
    const TimeSeries timeSeriesAverage = getAverageTimeSeries(allTimeSeries);
    plotTimePoint(timePointAverage,fraction);
    plotTimeSeries(timeSeriesAverage);
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
  if (RadioGroupFemaleSampling->ItemIndex == 0) //If female uses bestOfHowMuch
  {
    check = TryStrToInt(StringGridParameters->Cells[1][3],checkInt);
    if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'bestOfHowMuch' is not a valid input"; return false; }
    if (checkInt <= 0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'bestOfHowMuch' should be bigger then 0"; return false; }
  }
  //assessingError
  check = TryStrToFloat(StringGridParameters->Cells[1][4],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'assessingError' is not a valid input"; return false; }
  if (checkDouble < 0.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'assessingError' should be positive"; return false; }
  if (checkDouble > 1.0) { StatusBarMain->Panels->Items[0]->Text="Parameter 'assessingError' should be positive"; return false; }

  //Mean trait males A
  check = TryStrToFloat(StringGridParameters->Cells[1][5],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Mean trait males A' is not a valid input"; return false; }
  //StdDev trait males A
  check = TryStrToFloat(StringGridParameters->Cells[1][6],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'StdDev trait males A' is not a valid input"; return false; }
  //Mean trait males B
  check = TryStrToFloat(StringGridParameters->Cells[1][7],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'Mean trait males B' is not a valid input"; return false; }
  //StdDev trait males B
  check = TryStrToFloat(StringGridParameters->Cells[1][8],checkDouble);
  if (check == false) { StatusBarMain->Panels->Items[0]->Text="Parameter 'StdDev trait males B' is not a valid input"; return false; }

  return true;
}
//---------------------------------------------------------------------------
void TFormMain::plotTimePoint(const TimePoint& timePoint, const double& chartX)
{
  ChartBias->Series[0]->AddXY(chartX,timePoint.mateTally.calculateBiasA());
  ChartBias->Series[1]->AddXY(chartX,timePoint.mateTally.calculateBiasB());
  ChartBias->Series[2]->AddXY(chartX,timePoint.mateTally.calculateFractionMixedPairs());

  ChartMateFraction->Series[0]->AddXY(chartX,timePoint.mateTally.getNmateAA());
  ChartMateFraction->Series[1]->AddXY(chartX,timePoint.mateTally.getNmateAB());
  ChartMateFraction->Series[2]->AddXY(chartX,timePoint.mateTally.getNmateBA());
  ChartMateFraction->Series[3]->AddXY(chartX,timePoint.mateTally.getNmateBB());

  //ChartMateTime->Series[0]->AddXY(chartX,timePoint.mateTally.getNmateAA());
  //ChartMateTime->Series[1]->AddXY(chartX,timePoint.mateTally.getNmateAB());
  //ChartMateTime->Series[2]->AddXY(chartX,timePoint.mateTally.getNmateBA());
  //ChartMateTime->Series[3]->AddXY(chartX,timePoint.mateTally.getNmateBB());
}
//---------------------------------------------------------------------------
void TFormMain::plotTimeSeries(const TimeSeries& timeSeries)
{
  emptyChart(ChartPopSize);
  emptyChart(ChartMateTime);
  const unsigned int nGenerations = timeSeries.timePoints.size();
  for (unsigned i=0; i<nGenerations; ++i)
  {
    const double iD = static_cast<double>(i);
    ChartPopSize->Series[0]->AddXY(iD+0.60,timeSeries.timePoints[i].speciesTallyAfterDensityDependentSelection.getNfemalesA());
    ChartPopSize->Series[3]->AddXY(iD+0.60,timeSeries.timePoints[i].speciesTallyAfterDensityDependentSelection.getNfemalesB());
    ChartPopSize->Series[4]->AddXY(iD+0.60,timeSeries.timePoints[i].speciesTallyAfterDensityDependentSelection.getNmalesA());
    ChartPopSize->Series[7]->AddXY(iD+0.60,timeSeries.timePoints[i].speciesTallyAfterDensityDependentSelection.getNmalesB());
    ChartPopSize->Series[8]->AddXY(iD+0.60,timeSeries.timePoints[i].speciesTallyAfterDensityDependentSelection.getNall());

    ChartMateTime->Series[0]->AddXY(iD,timeSeries.timePoints[i].mateTally.getNmateAA());
    ChartMateTime->Series[1]->AddXY(iD,timeSeries.timePoints[i].mateTally.getNmateAB());
    ChartMateTime->Series[2]->AddXY(iD,timeSeries.timePoints[i].mateTally.getNmateBA());
    ChartMateTime->Series[3]->AddXY(iD,timeSeries.timePoints[i].mateTally.getNmateBB());
    ChartMateTime->Series[4]->AddXY(iD,timeSeries.timePoints[i].mateTally.getNmateAll());

    const unsigned int nTraits = timeSeries.timePoints[i].traits.size();
    for (unsigned int j=0; j<nTraits; ++j) ChartTraitPreference->Series[0]->AddXY(iD,timeSeries.timePoints[i].traits[j]);
    const unsigned int nPreferences = timeSeries.timePoints[i].preferences.size();
    for (unsigned int j=0; j<nPreferences; ++j) ChartTraitPreference->Series[1]->AddXY(iD,timeSeries.timePoints[i].preferences[j]);
    const unsigned int nSpeciesValues = timeSeries.timePoints[i].descents.size();
    for (unsigned int j=0; j<nSpeciesValues; ++j) ChartTraitPreference->Series[2]->AddXY(iD,timeSeries.timePoints[i].descents[j]);
  }
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
void emptyChart(TChart* chart)
{
  const int nSeries = chart->SeriesCount();
  for (int i=0; i<nSeries; ++i)
  {
    chart->Series[i]->Clear();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonTestClick(TObject *Sender)
{
  std::auto_ptr<StateFemaleSamplingBase> femaleSampling;
  switch(RadioGroupTestSampling->ItemIndex)
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
  ChartTestProbabilities->Title->Text->Add("const double y = 1.0 - alpha * std::exp(-beta*x*x)");
  ChartTestProbabilities->Title->Text->Add("Alpha: " + FloatToStr(alpha) + ", Beta: " + FloatToStr(beta));
  for (double x = -1.0; x<1.0; x+=0.01)
  {
    const double y = 1.0 - alpha * std::exp(-beta*x*x);
    ChartTestProbabilities->Series[0]->AddXY(x,y);
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


void __fastcall TFormMain::BitBtn1Click(TObject *Sender)
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
}
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
*/