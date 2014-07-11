//---------------------------------------------------------------------------
/*
  SurfacePlotter, plot a user-defined 2D function
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
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelTop;
        TLabel *Label1;
        TEdit *EditFormula;
        TButton *ButtonAbout;
        TImage *Image;
        TPanel *PanelStatus;
        TPanel *PanelBottom;
        TPanel *PanelMiddle;
        TPanel *PanelMidLeft;
        TEdit *EditXmin;
        TEdit *EditXmax;
        TEdit *EditYmax;
        TEdit *EditYmin;
        TLabel *LabelXmin;
        TLabel *LabelXmax;
        TLabel *LabelYmax;
        TLabel *LabelYmin;
        void __fastcall OnEditFormulaChange(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall OnEditRangeChange(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
const bool IsDouble(const String& s);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRescale.htm
const double Rescale(
  const double value,
  const double oldMin,
  const double oldMax,
  const double newMin,
  const double newMax);
//---------------------------------------------------------------------------

#endif
