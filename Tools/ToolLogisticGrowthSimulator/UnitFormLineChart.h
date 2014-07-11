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
#ifndef UnitFormLineChartH
#define UnitFormLineChartH
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
class TFormLineChart : public TForm
{
__published:	// IDE-managed Components
        TChart *mChart;
        TFastLineSeries *Series1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormLineChart(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLineChart *FormLineChart;
//---------------------------------------------------------------------------
#endif
