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
#include "UnitBird.h"
#include "UnitBirdFactory.h"
#include "UnitMain.h"
#include "UnitFormParameters.h"
#include "UnitFormResults.h"
#include "UnitFormAboutTheAuthor.h"
#include "ProjectHelp.map"
//---------------------------------------------------------------------------
#include <string>
#include "Assert.h"
#include "UnitSimulation.h"
#include "UnitSimulationParameters.h"
#include "UnitHelperFunctions.h"
#include "UnitSimulationFunctions.h"
#include "UnitResults.h"
#include "UnitBirdWatcher.h"
#include "UnitExceptions.h"
#include "UnitFormTest.h"
//TEST
//#include "UnitBird.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormThorVeenProject *FormThorVeenProject;
//---------------------------------------------------------------------------
__fastcall TFormThorVeenProject::TFormThorVeenProject(TComponent* Owner)
        : TForm(Owner)
{
  //Static initializations
  BirdBase::InitBirdWatcher();
  BirdFactoryBase::InitBirdWatcher();

  #ifndef NDEBUG
    Caption = Application->Title + ": Debug version";
  #else
    Caption = Application->Title + ": NoDebug version";
  #endif
}
//---------------------------------------------------------------------------
void TFormThorVeenProject::displayResults()
{
  FormResults->displayResults();

  { //Check number of generations
    #ifndef NDEBUG

    const BirdWatcher * birdWatcher = BirdWatcher::instance();
    const int nGenerationsIndex = 1;
    Assert( FormParameters->ValueListGeneral->Cells[0][nGenerationsIndex] == "Number of generations");
    const int nGenerations = FormParameters->ValueListGeneral->Cells[1][nGenerationsIndex].ToInt();
    #ifndef __RICHEL_HACK_7615327659321765876666666222
    if (nGenerations != static_cast<int>(birdWatcher->getMeansPlayHawkAlpha().size()) )
    {
      ShowMessage(birdWatcher->getMeansPlayHawkAlpha().size());
    }

    #endif
    Assert(nGenerations == static_cast<int>(birdWatcher->getMeansPlayHawkAlpha().size()) );
    Assert(nGenerations == static_cast<int>(birdWatcher->getMeansPlayHawkBeta().size())  );
    #endif
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormThorVeenProject::Cascade1Click(TObject *Sender)
{
  Cascade();
}
//---------------------------------------------------------------------------

void __fastcall TFormThorVeenProject::Tile1Click(TObject *Sender)
{
  Tile();
}
//---------------------------------------------------------------------------
void __fastcall TFormThorVeenProject::MenuRunClick(TObject *Sender)
{
  FormResults->RichEditResults->Lines->Clear();
  helper::emptyChart(FormResults->ChartNumbers);

  StatusBar1->Panels->Items[1]->Text="Starting simulation";
  Refresh();
  const boost::shared_ptr<SimulationParameters> simParams = FormParameters->getSimulationParameters();
  Assert(simParams.get()!=0);
  FormResults->display(simParams);
  const std::auto_ptr<Simulation> simulation(new Simulation(simParams));
  simulation->execute();
  StatusBar1->Panels->Items[1]->Text="Displaying results";
  Refresh();
  displayResults();
  StatusBar1->Panels->Items[1]->Text="Finished simulation";
}
//---------------------------------------------------------------------------
void __fastcall TFormThorVeenProject::MenuEditParametersClick(
      TObject *Sender)
{
  FormParameters->WindowState = wsMaximized;
}
//---------------------------------------------------------------------------
void __fastcall TFormThorVeenProject::Exit1Click(TObject *Sender)
{
  Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TFormThorVeenProject::Test1Click(TObject *Sender)
{
  FormTest->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormThorVeenProject::About1Click(TObject *Sender)
{
  const std::auto_ptr<TFormAboutTheAuthor> form(new TFormAboutTheAuthor(0));
  form->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormThorVeenProject::Abouttheprogram1Click(
      TObject *Sender)
{
  //Application->HelpSystem->ShowTableOfContents();
  Application->HelpSystem->ShowContextHelp(IDH_OVERVIEW_INTRODUCTION,Application->HelpFile);
}
//---------------------------------------------------------------------------
void __fastcall TFormThorVeenProject::ViewResults1Click(TObject *Sender)
{
  FormResults->WindowState = wsMaximized;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

