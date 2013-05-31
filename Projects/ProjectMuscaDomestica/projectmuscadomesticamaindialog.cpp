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
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WHBoxLayout>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WMenu>
#include <Wt/WStackedWidget>
#include <Wt/WTextArea>
#include <Wt/WVBoxLayout>
#include <Wt/WBorderLayout>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Must be #included after Wt header files
#include <QFile>
//---------------------------------------------------------------------------
WtWebsiteMenuDialog::WtWebsiteMenuDialog()
{
  CheckResources();
  //ShowMenuBorder(); //Not pretty
  ShowMenuHorizontal();
  //ShowMenuVertical(); //Not pretty
}
//---------------------------------------------------------------------------
void WtWebsiteMenuDialog::CheckResources()
{
  const std::vector<std::string> files
    = { "Bep.png" };
  BOOST_FOREACH(const std::string& s, files)
  {
    if (!boost::filesystem::exists(s))
    {
      const std::string filename = ":/images/" + s;
      QFile f(filename.c_str());
      f.copy(s.c_str());
      if (!boost::filesystem::exists(s)) { TRACE(s); }
      assert(boost::filesystem::exists(s));
    }
    if (!boost::filesystem::exists(s)) { TRACE(s); }
    assert(boost::filesystem::exists(s));
  }
}
//---------------------------------------------------------------------------
void WtWebsiteMenuDialog::ShowMenuBorder()
{
  //this->setContentAlignment(Wt::AlignCenter);
  Wt::WBorderLayout * const layout = new Wt::WBorderLayout(this);

  {
    Wt::WLabel * const title = new Wt::WLabel("WtWebsite (using ShowMenuBorder)");
    title->setStyleClass("title");
    layout->addWidget(title,Wt::WBorderLayout::North);
  }
  //layout->setContentsMargins(0,0,0,0);


  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = CreateNewMenu(contents,Wt::Vertical);
    //Display menu on top
    //menu->setLineHeight(0);
    //menu->setOffsets(0);
    //menu->setRenderAsList(true);
    //menu->setVerticalAlignment(Wt::AlignTop);
    //menu->setPositionScheme(Wt::Relative);
    //menu->setPositionScheme(Wt::Absolute);
    //menu->setPositionScheme(Wt::Static);
    //menu->setPositionScheme(Wt::Fixed);
    //menu->setMaximumSize(Wt::WLength::Auto,200);
    //contents->setMinimumSize(Wt::WLength::Auto,800);

    layout->addWidget(menu,Wt::WBorderLayout::West);

    //Display contents below menu
    layout->addWidget(contents,Wt::WBorderLayout::Center);
  }
}
//---------------------------------------------------------------------------
void WtWebsiteMenuDialog::ShowMenuHorizontal()
{
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("WtWebsite");
    title->setStyleClass("title");
    this->addWidget(title);
  }
  this->addWidget(new Wt::WBreak);
  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = CreateNewMenu(contents,Wt::Horizontal);
    //Display menu on top
    this->addWidget(menu);

    //Display contents below menu
    this->addWidget(contents);
  }
}
//---------------------------------------------------------------------------
void WtWebsiteMenuDialog::ShowMenuVertical()
{
  this->setContentAlignment(Wt::AlignCenter);

  Wt::WVBoxLayout * const layout_vertical = new Wt::WVBoxLayout(this);
  {
    Wt::WLabel * const title = new Wt::WLabel("WtWebsite");
    title->setStyleClass("title");
    layout_vertical->addWidget(title,0);
  }

  Wt::WHBoxLayout * const layout_horizontal = new Wt::WHBoxLayout;
  //layout_horizontal->setSpacing(0);
  //layout_horizontal->setContentsMargins(0,0,0,0);

  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    //contents->setStyleClass("wtwebsitemenu");
    Wt::WMenu * const menu = CreateNewMenu(contents,Wt::Vertical);

    //Display menu on top
    layout_horizontal->addWidget(menu,0);

    //Display contents below menu
    layout_horizontal->addWidget(contents,1);
  }
  //layout_vertical->setSpacing(0);
  //layout_vertical->setContentsMargins(0,0,0,0);
  layout_vertical->addLayout(layout_horizontal,1);
}
//---------------------------------------------------------------------------
const std::string WtWebsiteMenuDialog::GetVersion()
{
  return "0.17";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtWebsiteMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-12-20: Version 0.1: initial setup with BeerWanter and Loose");
  v.push_back("2010-12-21: Version 0.2: added System button");
  v.push_back("2010-12-22: Version 0.3: added About button");
  v.push_back("2010-12-22: Version 0.4: added What's New button. Got BeerWanter to work minimally");
  v.push_back("2010-12-24: Version 0.5: added RandomCode");
  v.push_back("2011-01-07: Version 0.6: major architecture adjustment, added TicTacToe, temporarily removed BeerWanter, Loose and System");
  v.push_back("2011-01-09: Version 0.7: added title structure, added response of WtWebsite's Close button, added ConnectThree beta");
  v.push_back("2011-01-10: Version 0.8: ConnectThree to alpha");
  v.push_back("2011-01-11: Version 0.9: ConnectThree to full version");
  v.push_back("2011-03-06: Version 0.10: Added TestTwoDigitNewick");
  v.push_back("2011-03-09: Version 0.11: Replaced TestTwoDigitNewick by TestNewick");
  v.push_back("2011-03-22: Version 0.12: Added TestEncranger");
  v.push_back("2011-03-26: Version 0.13: Replaced TestNewick by TestNewickVector");
  v.push_back("2011-03-27: Version 0.14: Added TestAsciiArter");
  v.push_back("2011-04-13: Version 0.15: Added TimePoll");
  v.push_back("2011-04-16: Version 0.16: Major architectural change: use of Wt::WMenu and WtAutoConfig");
  v.push_back("2011-04-23: Version 0.17: New version of ConnectThree, added Bep to welcome page");
  return v;
}
//---------------------------------------------------------------------------
Wt::WWidget * WtWebsiteMenuDialog::CreateNewAboutDialog() const
{
  About a(
    "Richel Bilderbeek",
    "WtWebsite",
    "Richel Bilderbeek's C++ Wt website",
    "the 23rd of April 2011",
    "2010-2011",
    "http://www.richelbilderbeek.nl/ProjectWtWebsite.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("ConnectThree version: " + ConnectThree::GetVersion());
  a.AddLibrary("ConnectThreeWidget version: " + ConnectThreeWidget::GetVersion());
  a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  a.AddLibrary("RandomCode version: " + RandomCode::GetVersion());
  a.AddLibrary("TestAsciiArterDialog version: " + TestAsciiArterDialog::GetVersion());
  a.AddLibrary("TestNewickVectorDialog version: " + TestNewickVectorDialog::GetVersion());
  a.AddLibrary("TicTacToe version: " + TicTacToe::GetVersion());
  a.AddLibrary("Wt version: " + std::string(WT_VERSION_STR));
  a.AddLibrary("WtAboutDialog version: " + WtAboutDialog::GetVersion());
  a.AddLibrary("WtAutoConfig version: " + WtAutoConfig::GetVersion());
  a.AddLibrary("WtConnectThreeWidget version: " + WtConnectThreeWidget::GetVersion());
  a.AddLibrary("WtTicTacToeWidget version: " + WtTicTacToeWidget::GetVersion());
  a.AddLibrary("WtTimePollDialog version: " + WtTimePollDialog::GetVersion());
  WtAboutDialog * const d = new WtAboutDialog(a);
  assert(d);
  return d;
}
//---------------------------------------------------------------------------
Wt::WWidget * WtWebsiteMenuDialog::CreateNewConnectThreeMenuDialog() const
{
  WtConnectThreeMenuDialog * const d
    = new WtConnectThreeMenuDialog;
  assert(d);
  return d;
}
//---------------------------------------------------------------------------
Wt::WMenu * WtWebsiteMenuDialog::CreateNewMenu(
  Wt::WStackedWidget * const contents,
  const Wt::Orientation& orientation) const
{

  Wt::WMenu * const menu = new Wt::WMenu(contents,orientation);
  //menu->setRenderAsList(false);

  //Using CSS styleclass is the best (only?) way to display the menu well
  menu->setStyleClass("wtwebsitemenu");
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
      "Welcome",
      CreateNewWelcomeDialog());
    menu->addItem(item);
  }
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
      "ConnectThree",
      CreateNewConnectThreeMenuDialog());
    menu->addItem(item);
  }
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
        "RandomCode",
        CreateNewRandomCodeDialog());
    menu->addItem(item);
  }
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
        "TestAsciiArter",
        CreateNewTestAsciiArterDialog());
    menu->addItem(item);
  }
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
        "TestEncranger",
        CreateNewTestEncrangerDialog());
    menu->addItem(item);
  }
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
        "TestNewickVector",
        CreateNewTestNewickVectorDialog());
    menu->addItem(item);
  }
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
        "TicTacToe",
        CreateNewTicTacToeDialog());
    menu->addItem(item);
  }
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
        "TimePoll",
        CreateNewTimePollDialog());
    menu->addItem(item);
  }
  {
    Wt::WMenuItem * const item = new Wt::WMenuItem(
        "About",
        CreateNewAboutDialog());
    menu->addItem(item);
  }
  return menu;
}
//---------------------------------------------------------------------------
Wt::WWidget * WtWebsiteMenuDialog::CreateNewRandomCodeDialog() const
{
  WtRandomCodeDialog * const d = new WtRandomCodeDialog;
  assert(d);
  return d;
}
//---------------------------------------------------------------------------
Wt::WWidget * WtWebsiteMenuDialog::CreateNewTestAsciiArterDialog() const
{
  WtTestAsciiArterDialog * const d = new WtTestAsciiArterDialog;
  assert(d);
  return d;
}
//---------------------------------------------------------------------------
Wt::WWidget * WtWebsiteMenuDialog::CreateNewTestEncrangerDialog() const
{
  WtTestEncrangerDialog * const d = new WtTestEncrangerDialog;
  assert(d);
  return d;
}
//---------------------------------------------------------------------------
Wt::WWidget * WtWebsiteMenuDialog::CreateNewTestNewickVectorDialog() const
{
  WtTestNewickVectorDialog * const d = new WtTestNewickVectorDialog;
  assert(d);
  return d;
}
//---------------------------------------------------------------------------
Wt::WWidget * WtWebsiteMenuDialog::CreateNewTicTacToeDialog() const
{
  WtTicTacToeMenuDialog * const d = new WtTicTacToeMenuDialog;
  assert(d);
  return d;
}
//---------------------------------------------------------------------------
Wt::WWidget * WtWebsiteMenuDialog::CreateNewTimePollDialog() const
{
  WtTimePollDialog * const d = new WtTimePollDialog;
  assert(d);
  return d;
}
//---------------------------------------------------------------------------
Wt::WWidget * WtWebsiteMenuDialog::CreateNewWelcomeDialog() const
{
  Wt::WContainerWidget * dialog = new Wt::WContainerWidget;
  dialog->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WLabel * const title = new Wt::WLabel("Welcome");
    title->setStyleClass("title");
    dialog->addWidget(title);
  }
  dialog->addWidget(new Wt::WBreak);
  new Wt::WLabel("Welcome to my Wt homepage!",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("My Wt homepage collects all my web application as one single application.",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Also it tests whether users (you) can break my applications",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("and as a test for my web server, Bep:",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WImage("Bep.png",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Picture of Bep (*)",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("All code can be found at http://www.richelbilderbeek.nl, which is my static website.",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("This page is still in its beta.",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("(*) Bep's name is enhanced in KolourPaint,",dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("picture taken by Jean-Marc Bilderbeek.",dialog);

  return dialog;
}
//---------------------------------------------------------------------------
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
