//---------------------------------------------------------------------------
/*
  FunctionPlotter, plots a function
  Copyright (C) 2010  Richel Bilderbeek

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
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TEdit *EditFormula;
        TLabel *Label1;
        TButton *ButtonAbout;
        TChart *Chart;
        TFastLineSeries *Series;
        TPanel *PanelBottom;
        TPanel *PanelTop;
        TEdit *EditXmin;
        TLabel *LabelXmin;
        TEdit *EditXmax;
        TLabel *LabelXmax;
        TPanel *PanelStatus;
        TButton *ButtonApproxIntegral;
        void __fastcall OnEditChange(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall OnRangeChange(TObject *Sender);
        void __fastcall ButtonApproxIntegralClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
const bool IsDouble(const String& s);
//---------------------------------------------------------------------------
#endif
