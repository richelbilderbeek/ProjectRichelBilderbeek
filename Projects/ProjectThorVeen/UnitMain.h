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
#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <BubbleCh.hpp>
#include <Dialogs.hpp>
#include <jpeg.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include <memory>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <iosfwd>
class SimulationParameters;
class BirdHawkDoveParameters;
//---------------------------------------------------------------------------
class TFormThorVeenProject : public TForm
{
  __published:	// IDE-managed Components
  TStatusBar *StatusBar1;
  TMainMenu *MainMenu1;
  TMenuItem *MenuSimulation;
  TMenuItem *Window1;
  TMenuItem *Cascade1;
  TMenuItem *Tile1;
  TMenuItem *MenuRun;
  TMenuItem *MenuEditParameters;
  TMenuItem *Help1;
  TMenuItem *About1;
  TMenuItem *Abouttheprogram1;
        TMenuItem *Exit1;
        TMenuItem *Test1;
  TMenuItem *ViewResults1;
  void __fastcall Cascade1Click(TObject *Sender);
  void __fastcall Tile1Click(TObject *Sender);
  void __fastcall MenuRunClick(TObject *Sender);
  void __fastcall MenuEditParametersClick(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall Test1Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
  void __fastcall Abouttheprogram1Click(TObject *Sender);
  void __fastcall ViewResults1Click(TObject *Sender);
  private:	// User declarations
    void displayResults();
  public:		// User declarations
    //boost::shared_ptr<SimulationParameters> getSimulationParameters() const;
    //boost::shared_ptr<BirdHawkDoveParameters> getHawkDoveParameters() const;
     __fastcall TFormThorVeenProject(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormThorVeenProject *FormThorVeenProject;
//---------------------------------------------------------------------------

#endif
