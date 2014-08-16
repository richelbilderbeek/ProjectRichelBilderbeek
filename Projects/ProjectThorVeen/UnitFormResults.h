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
#ifndef UnitFormResultsH
#define UnitFormResultsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
class SimulationParameters;
//---------------------------------------------------------------------------
class TFormResults : public TForm
{
__published:	// IDE-managed Components
  TPageControl *PageControlMain;
  TTabSheet *TabSheet3;
  TRichEdit *RichEditResults;
  TTabSheet *TabSheet6;
  TChart *ChartNumbers;
  TLineSeries *Series2;
  TLineSeries *Series3;
  TLineSeries *Series4;
  TLineSeries *Series5;
  TLineSeries *Series6;
  TTabSheet *TabSheet8;
  TRichEdit *RichEditPedigree;
  TPanel *Panel1;
  TButton *ButtonSavePedigree;
  TTabSheet *TabSheet9;
  TChart *ChartTraits;
  TLineSeries *Series7;
  TLineSeries *Series8;
  TLineSeries *Series9;
  TSaveDialog *SaveDialogPedigree;
  TTabSheet *TabSheet1;
  TChart *Chart1;
  TLineSeries *Series1;
  TLineSeries *Series10;
  TLineSeries *Series11;
  void __fastcall ButtonSavePedigreeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormResults(TComponent* Owner);
  void displayResults();
  void display(const boost::shared_ptr<SimulationParameters>& simParams);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormResults *FormResults;
//---------------------------------------------------------------------------
#endif
