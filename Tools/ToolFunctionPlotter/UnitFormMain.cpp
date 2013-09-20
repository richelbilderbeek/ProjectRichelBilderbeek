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
#include <vcl.h>
#pragma hdrstop

#include <sstream>
#include <boost/scoped_ptr.hpp>
#include "UnitFunctionParser.h"

#include "UnitFormMain.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
  OnEditChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OnEditChange(TObject *Sender)
{
  FunctionParser f;

  //Parse the formula
  f.Parse(EditFormula->Text.c_str(),"x");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    PanelStatus->Caption = "Function could not be parsed";
    return;
  }

  if (!IsDouble(EditXmin->Text.c_str()))
  {
    PanelStatus->Caption = "Value of x_min is not a valid double";
    return;
  }
  if (!IsDouble(EditXmax->Text.c_str()))
  {
    PanelStatus->Caption = "Value of x_max is not a valid double";
    return;
  }
  const double x_min = EditXmin->Text.ToDouble();
  const double x_max = EditXmax->Text.ToDouble();
  if (x_min >= x_max)
  {
    PanelStatus->Caption = "Value of x_min must be smaller than x_max";
    return;
  }

  const double dx = (x_max - x_min) / 100.0;
  Series->Clear();

  for (double x = x_min; x < x_max; x+=dx)
  {
    //Evaluate the parsed formula
    const double xs[1] = { x };
    const double y = f.Eval(xs);
    if (f.EvalError()!=0)
    {
      continue;
    }
    Series->AddXY(x,y);
  }
  PanelStatus->Caption = "Function plotted successfully";

}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppIsDouble.htm
const bool IsDouble(const String& s)
{
  try
  {
    s.ToDouble();
    return true;
  }
  catch (EConvertError& e)
  {
    return false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::OnRangeChange(TObject *Sender)
{
  if (!IsDouble(EditXmin->Text.c_str()))
  {
    PanelStatus->Caption = "Value of x_min is not a valid double";
    return;
  }
  if (!IsDouble(EditXmax->Text.c_str()))
  {
    PanelStatus->Caption = "Value of x_max is not a valid double";
    return;
  }
  const double x_min = EditXmin->Text.ToDouble();
  const double x_max = EditXmax->Text.ToDouble();
  if (x_min >= x_max)
  {
    PanelStatus->Caption = "Value of x_min must be smaller than x_max";
    return;
  }
  Chart->BottomAxis->Minimum = x_min;
  Chart->BottomAxis->Maximum = x_max;

  PanelStatus->Caption = "Chart rescaled successfully";
  OnEditChange(0);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonApproxIntegralClick(TObject *Sender)
{
  FunctionParser f;

  //Parse the formula
  f.Parse(EditFormula->Text.c_str(),"x");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    PanelStatus->Caption = "Function could not be parsed";
    return;
  }

  if (!IsDouble(EditXmin->Text.c_str()))
  {
    PanelStatus->Caption = "Value of x_min is not a valid double";
    return;
  }
  if (!IsDouble(EditXmax->Text.c_str()))
  {
    PanelStatus->Caption = "Value of x_max is not a valid double";
    return;
  }
  const double x_min = EditXmin->Text.ToDouble();
  const double x_max = EditXmax->Text.ToDouble();
  if (x_min >= x_max)
  {
    PanelStatus->Caption = "Value of x_min must be smaller than x_max";
    return;
  }


  const double dx = (x_max - x_min) / 10000.0;
  double sumy = 0.0;

  for (double x = x_min; x < x_max; x+=dx)
  {
    //Evaluate the parsed formula
    const double xs[1] = { x };
    const double y = f.Eval(xs);
    if (f.EvalError()!=0)
    {
      continue;
    }
    sumy+=y;
  }
  const double surface = sumy * dx;
  PanelStatus->Caption = "Approximated surface under curve: " + FloatToStr(surface);
}
//---------------------------------------------------------------------------

