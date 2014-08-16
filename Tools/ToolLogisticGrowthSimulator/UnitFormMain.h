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
#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <memory>
#include "UnitSimulation.h"
class TFormLineChart;
class TFormScatterplot;
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TTrackBar *TrackBar1;
        TValueListEditor *Editor1;
        TButton *ButtonCreateFeigen;
        TButton *ButtonAbout;
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ButtonCreateFeigenClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
        std::auto_ptr<Simulation> mSimulation;
        std::auto_ptr<TFormLineChart> mChartBegin;
        std::auto_ptr<TFormLineChart> mChartEnd;
        std::auto_ptr<TFormLineChart> mChartFeigenNvalues;
        std::auto_ptr<TFormScatterplot> mChartFeigenValues;
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
        Parameters GetParams() const;
        double GetR() const;
        double GetK() const;
        double GetXzero() const;
        int GetT() const;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
