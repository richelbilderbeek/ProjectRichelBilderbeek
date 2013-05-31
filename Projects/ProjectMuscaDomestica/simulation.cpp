//---------------------------------------------------------------------------
/*
  Project Musca Domestica, simulation in which sex-ratio can evolve
  Copyright (C) 2009  Richl Bilderbeek

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

#include "simulation.h"

/*
//In this version:
//S system back again

//Fly with the whole set of autosomes
//---------------------------------------------------------------------------
//dispersal before mating, monoandry
//---
#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include <mmsystem.h>
#include "Random.h"
#include <vector.h>
#include "UnitFormMain.h"
#include "richel001.h"
#include "Fly2.cpp"

//define NDEBUG to enquicken your code
//#define NDEBUG
//The assertion macro
#include <assert.h>

//static const TCursor crFly = 1;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//CHOOSE ONE OF THREE TO DEFINE
#define MALESDISPERSE
//#define FEMALESDISPERSE
//#define BOTHDISPERSE

//CHOOSE ONE OF BOTH TO DEFINE
#define FIRSTDISPERSE
//#define FIRSTMATING

//CHOOSE ONE OF FOUR TO DEFINE
#define FATHERCONTROL
//#define MOTHERCONTROL
//#define BOTHCONTROL
//#define ZYGOTECONTROL

//NEEDED TO RUN THE PROGRAM
#define IDOISEENLEIPO

unsigned int CalculateStdDevTime;
unsigned int NIslands;                                    //Number of islands-subpopulations
unsigned int MaxFPopSize;                                  //carrying capacity of one island  for females
unsigned int MaxMPopSize;                                  //carrying capacity of one island  for males
unsigned int NGenerations;                               //number of generations
unsigned int NRuns;                                        //number of runs
double PMut;                                   //Maximal mutation || chance of mutation
vector <Fly> FPop;                                  //vector containing all females within the whole population
vector <Fly> MPop;                                  //vector containing all males within the whole population
vector <Fly> OffFPop;                               //female offspring from every female of FPop
vector <Fly> OffMPop;                               //male offspring from every female of FPop
vector <double> OurDataSet;
unsigned int maleCounter=0;                         //number of males offspring from all females
unsigned int femaleCounter=0;                       //number of females offspring from all females
double SLocusCounter=0;
void (*NextGeneration) (vector<Fly>&,vector<Fly>&,vector<Fly>&,vector<Fly>&,int,int);
Fly (*CreateOffspring) (const Fly &,const Fly &);

void ResetCounters(void)
  {
  maleCounter=0; femaleCounter=0;
  SLocusCounter=0.0;
  }

void ClearTotalChart(TChart * Chart1)
  {
  int counter; for (counter=0; counter < Chart1->SeriesCount(); counter++)
    {
    Chart1->Series[counter]->Clear();
    }//Next counter
  }

#include "FlyFunctions.h"
#include "quick.h"
#include "nextgeneration.h"
#include "layout.h"
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm1::MenuItemStartSimulationClick(TObject *Sender)
{
ButtonStart->Click();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MenuItemSaveThisRunResultsClick(TObject *Sender)
{
SeveResults(RichEditOutput,RadioGroupDispersingSex);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MenuItemSaveRunsResultsClick(TObject *Sender)
{
SeveResults(RichEditOutput,RadioGroupDispersingSex);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonStartClick(TObject *Sender)
{
Application->Icon->LoadFromFile("musca.ico");
Form1->Icon->LoadFromFile("musca.ico");
InitializeParameters(ValueListEditor1,
                     RadioGroupDispersingSex->ItemIndex,
                     RadioGroupWhoIsInControl->ItemIndex,
                     RichEditOutput,
                     Chart1);
//Initialize the three counters
unsigned int Generation, SimRun;
FPop.resize(NIslands*MaxFPopSize);
MPop.resize(NIslands*MaxMPopSize);
OffFPop.resize(NIslands*MaxFPopSize);
OffMPop.resize(NIslands*MaxMPopSize);
OurDataSet.resize(NGenerations);

for(SimRun=0;SimRun<NRuns;SimRun++)      //for every run
  {
  InitFPop();
  InitMPop();
  ClearTotalChart(Chart1);
  for(Generation=0;Generation<NGenerations;Generation++)       //for every population
    {
    NextGeneration(MPop, FPop, OffMPop, OffFPop, MaxMPopSize, MaxFPopSize);
    NextGeneration(OffMPop, OffFPop, MPop, FPop, MaxMPopSize, MaxFPopSize);
    ShowOnChart(Chart1,Generation,ImageIdo,ImageMagda,ImageFly);
    //Chart1->Update();
    Chart1->Refresh();
    ResetCounters();
    }//Next generation
  double OurMean, OurStdDev;
  SafeMeanAndStdDev(&OurDataSet[OurDataSet.size()-CalculateStdDevTime-1],CalculateStdDevTime, OurMean, OurStdDev);
  RichEditOutput->Lines->Add( (String) OurMean + "\t" + (String) OurStdDev );
  Chart1->Title->Text->SetText(("Run number: "+IntToStr(SimRun)).c_str());
  Chart1->Update();
  }//Next run

//Saving results to file
//RichEditOutput->Lines->SaveToFile(IntToStr(random(1000000))+".dat");
//Changing icons for visual signal
Form1->Icon->LoadFromFile("smiley.ico");
Application->Icon->LoadFromFile("smiley.ico");
//Playing sound for audio signal
PlaySound("richelslaatlaag.wav",NULL, SND_FILENAME | SND_ASYNC);
//Sending an E-mail with results
//if (NMSMTP1->Connected==false) NMSMTP1->Connect();
//  NMSMTP1->PostMessageA->Body->Add(RichEditOutput->Text);
//NMSMTP1->SendMail();
//exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
TCursor FlyCursor = (TCursor) 22;
Screen->Cursors[FlyCursor]=LoadCursorFromFile("fly.cur");
Cursor=FlyCursor;
ButtonStart->Cursor=FlyCursor;
RadioGroupDispersingSex->Cursor=FlyCursor;
RadioGroupWhoIsInControl->Cursor=FlyCursor;
RadioGroupOrderOfEvents->Cursor=FlyCursor;
BitBtn1->Cursor=FlyCursor;
ValueListEditor1->Cursor=FlyCursor;

#ifdef FIRSTDISPERSE
  RadioGroupOrderOfEvents->Caption="First dispersal";
  OutputDebugString("First dispersal");
#endif
#ifdef FIRSTMATING
  RadioGroupOrderOfEvents->Caption="First mating";
  OutputDebugString("First mating");
#endif
}
//---------------------------------------------------------------------------




void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
PlaySound("FlySound.wav",NULL, SND_FILENAME | SND_ASYNC);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
ShowMessage(
  "Project Musca Domestica, simulation in which sex-ratio can evolve     \n"
  "Copyright (C) 2009  Richl Bilderbeek                                 \n"
  "                                                                      \n"
  "This program is free software: you can redistribute it and/or modify  \n"
  "it under the terms of the GNU General Public License as published by  \n"
  "the Free Software Foundation, either version 3 of the License, or     \n"
  "(at your option) any later version.                                   \n"
  "                                                                      \n"
  "This program is distributed in the hope that it will be useful,       \n"
  "but WITHOUT ANY WARRANTY; without even the implied warranty of        \n"
  "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         \n"
  "GNU General Public License for more details.                          \n"
  "                                                                      \n"
  "You should have received a copy of the GNU General Public License     \n"
  "along with this program.  If not, see <http://www.gnu.org/licenses/>. "
  );
}
//---------------------------------------------------------------------------


*/
