//---------------------------------------------------------------------------
/*
  The Chris Wiley Project, simulation on mixed-pair mating
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
#ifndef UnitMainH
#define UnitMainH
#include <Chart.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Series.hpp>
#include <StdCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
#include <mmsystem.h>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//#include <Buttons.hpp>
//#include <utility>
//#include <functional>
//#include <iterator>
#include <string>
#include <vector>
#include <memory>
#include "UnitSimulation.h"
#include "UnitTimeSeries.h"
#include "UnitParameters.h"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
  TStringGrid *StringGridParameters;
  TButton *ButtonRun;
  TStatusBar *StatusBarMain;
        TChart *ChartBias;
        TLineSeries *Series1;
        TLineSeries *Series2;
        TLineSeries *Series3;
        TPanel *PanelLeft;
        TRadioGroup *RadioGroupGamy;
        TRadioGroup *RadioGroupFemaleSampling;
        TProgressBar *ProgressBarSim;
  TPageControl *PageControlMain;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TRichEdit *RichEdit2;
        TRadioGroup *RadioGroupDensityDependentSelection;
        TTabSheet *TabSheet7;
        TChart *ChartPopSize;
        TLineSeries *Series12;
        TLineSeries *Series13;
        TPanel *PanelLeftTop;
        TLineSeries *Series16;
        TLineSeries *Series19;
        TEdit *EditFractionFrom;
        TEdit *EditFractionTo;
        TEdit *EditFractionStep;
        TLabel *Label3;
        TLabel *Label4;
        TTabSheet *TabSheet6;
        TChart *ChartMateTime;
        TLineSeries *Series20;
        TLineSeries *Series21;
        TLineSeries *Series22;
        TLineSeries *Series23;
        TTabSheet *TabSheet2;
        TPanel *PanelTest;
        TChart *ChartTest;
        TStringGrid *StringGridTest;
        TButton *ButtonTest;
        TBarSeries *Series4;
        TTabSheet *TabSheet5;
        TChart *ChartTraitPreference;
        TPointSeries *Series5;
        TPointSeries *Series6;
        TLineSeries *Series7;
        TTabSheet *TabSheet12;
        TChart *ChartMateFraction;
        TLineSeries *Series9;
        TLineSeries *Series10;
        TLineSeries *Series11;
        TLineSeries *Series24;
        TPointSeries *Series25;
        TPanel *Panel1;
        TPageControl *PageControlSim;
        TTabSheet *TabSheet13;
        TTabSheet *TabSheet14;
        TLabel *Label1;
        TEdit *EditFraction;
        TLabel *Label2;
        TPageControl *PageControl2;
        TTabSheet *TabSheet8;
        TTabSheet *TabSheet9;
        TPanel *PanelTestProbTop;
        TButton *ButtonTestSurvivalSpecies;
        TChart *ChartTestProbabilities;
        TLineSeries *Series26;
        TBitBtn *BitBtn1;
        TTabSheet *TabSheet10;
        TChart *ChartBiasTime;
        TLineSeries *Series27;
        TLineSeries *Series28;
        TLineSeries *Series29;
        TButton *ButtonSave;
        TSaveDialog *SaveDialog1;
        TRichEdit *RichEditOutput;
        TButton *ButtonTestTrait;
        TButton *ButtonTestPreference;
        TButton *ButtonTestProbabilisticMating;
  TButton *ButtonTestHelp;
        TTabSheet *TabSheetAbout;
        TRichEdit *RichEditAbout;
  void __fastcall ButtonRunClick(TObject *Sender);
        void __fastcall ButtonTestClick(TObject *Sender);
        void __fastcall ButtonTestSurvivalSpeciesClick(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall ButtonSaveClick(TObject *Sender);
        void __fastcall ButtonTestTraitClick(TObject *Sender);
        void __fastcall ButtonTestPreferenceClick(TObject *Sender);
        void __fastcall ButtonTestProbabilisticMatingClick(TObject *Sender);
  void __fastcall StringGridParametersSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall ButtonTestHelpClick(TObject *Sender);
  void __fastcall RadioGroupFemaleSamplingClick(TObject *Sender);
  void __fastcall RadioGroupDensityDependentSelectionClick(
          TObject *Sender);
  void __fastcall RadioGroupGamyClick(TObject *Sender);
  void __fastcall PageControlSimChange(TObject *Sender);
  void __fastcall BitBtn1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
  void setCursor(const String& cursorName);
  bool checkInput();
  void TFormMain::plotTimePoint(
    const TimePoint& mean,
    const TimePoint& stdError,
    const double& chartX);
  void TFormMain::plotTimeSeries(
    const TimeSeries& mean,
    const TimeSeries& stdError);
  Parameters readStringGrid() const;
public:		// User declarations
  __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
std::string toString(const String& ansi);
String toAnsiString(const std::string& myString);
void emptyChart(TChart* chart);
std::auto_ptr<TStringList> getStringGrid(const TStringGrid * stringGrid);
std::auto_ptr<TStringList> getChart(const TChart * anyChart);
std::auto_ptr<TStringList> getChartSeries(const TChartSeries * series);


#endif
