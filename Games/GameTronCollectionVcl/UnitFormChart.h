//---------------------------------------------------------------------------
/*
  The Tron Collection, three simple tron games
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
#ifndef UnitFormChartH
#define UnitFormChartH
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
//---------------------------------------------------------------------------
class TFormChart : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TBarSeries *Series1;
        TBarSeries *Series2;
        TTimer *Timer1;
        TPanel *Panel1;
        TButton *ButtonClose;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ButtonCloseClick(TObject *Sender);
private:	// User declarations
  bool mCanClose;
public:		// User declarations
  __fastcall TFormChart(
    TComponent* Owner,
    const std::vector<int>& losses,
    const std::vector<int>& wins);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormChart *FormChart;
//---------------------------------------------------------------------------
#endif
