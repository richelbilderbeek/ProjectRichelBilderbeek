/*
  SimBrainiac, a simulation of Brainiacs interacting
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
#ifndef UnitFormSimBrainiacGraphH
#define UnitFormSimBrainiacGraphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include "UnitBrainiac.h"
//---------------------------------------------------------------------------
class TFormSimBrainiacGraph : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TChart *Chart2;
        TLineSeries *Series1;
        TLineSeries *PointSeries1;
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormSimBrainiacGraph(TComponent* Owner);
  void Plot(const std::vector<Brainiac>& brainiacs);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimBrainiacGraph *FormSimBrainiacGraph;
//---------------------------------------------------------------------------
#endif
