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
#include <vcl.h>
#pragma hdrstop

#include <sstream>
#include <boost/scoped_ptr.hpp>
#include "UnitFunctionParser.h"

#include "UnitFormMain.h"
#include "UnitFormAbout.h"
#include "UnitSurfacePlotter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
  //OnAnyEditChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OnEditFormulaChange(TObject *Sender)
{
  //Obtain the range
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

  if (!IsDouble(EditYmin->Text.c_str()))
  {
    PanelStatus->Caption = "Value of y_min is not a valid double";
    return;
  }
  if (!IsDouble(EditYmax->Text.c_str()))
  {
    PanelStatus->Caption = "Value of y_max is not a valid double";
    return;
  }
  const double y_min = EditYmin->Text.ToDouble();
  const double y_max = EditYmax->Text.ToDouble();
  if (y_min >= y_max)
  {
    PanelStatus->Caption = "Value of y_min must be smaller than y_max";
    return;
  }

  FunctionParser f;

  //Parse the formula
  f.Parse(EditFormula->Text.c_str(),"x,y");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    PanelStatus->Caption = "Function could not be parsed";
    return;
  }


  //Evaluate the function in a 2D std::vector
  const int n_rows = Image->Picture->Bitmap->Height;
  const int n_cols = Image->Picture->Bitmap->Width;
  std::vector<std::vector<double> > v(n_rows,std::vector<double>(n_cols,0.0));
  const double n_rows_d = static_cast<double>(n_rows);
  const double n_cols_d = static_cast<double>(n_cols);

  for (int y = 0; y!=n_rows; ++y)
  {
    const double yD = static_cast<double>(y);
    const double y_scaled = Rescale(yD,0.0,n_rows_d,y_min,y_max);
    for (int x = 0; x!=n_cols; ++x)
    {
      const double xD = static_cast<double>(x);
      const double x_scaled = Rescale(xD,0.0,n_cols_d,x_min,x_max);
      const double xs[2] = { x_scaled,y_scaled };
      const double z = f.Eval(xs);
      if (!f.EvalError())
      {
        v[y][x] = z;
      }
      else
      {
        v[y][x] = 0.0;
      }
    }
  }

  //Plot the 2D std::vector
  SurfacePlotter plotter(Image);
  plotter.SetSurfaceGrey(v);
  //this->Canvas->StretchDraw(rect,Image->Picture->Graphic);
  Image->Refresh();

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

void __fastcall TFormMain::OnEditRangeChange(TObject *Sender)
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

  if (!IsDouble(EditYmin->Text.c_str()))
  {
    PanelStatus->Caption = "Value of y_min is not a valid double";
    return;
  }
  if (!IsDouble(EditYmax->Text.c_str()))
  {
    PanelStatus->Caption = "Value of y_max is not a valid double";
    return;
  }
  const double y_min = EditYmin->Text.ToDouble();
  const double y_max = EditYmax->Text.ToDouble();
  if (y_min >= y_max)
  {
    PanelStatus->Caption = "Value of y_min must be smaller than y_max";
    return;
  }

  OnEditFormulaChange(0);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRescale.htm
const double Rescale(
  const double value,
  const double oldMin,
  const double oldMax,
  const double newMin,
  const double newMax)
{
  assert(value >= oldMin);
  assert(value <= oldMax);
  const double oldDistance = oldMax - oldMin;
  //At which relative distance is value on oldMin to oldMax ?
  const double distance = (value - oldMin) / oldDistance;
  assert(distance >= 0.0);
  assert(distance <= 1.0);
  const double newDistance = newMax - newMin;
  const double newValue = newMin + (distance * newDistance);
  assert(newValue >= newMin);
  assert(newValue <= newMax);
  return newValue;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormResize(TObject *Sender)
{
  const int width  = Image->Width;
  const int height = Image->Height;
  const int sz = std::min(width,height);
  Image->Picture->Bitmap->Width = sz;
  Image->Picture->Bitmap->Height = sz;
  OnEditFormulaChange(0);
}
//---------------------------------------------------------------------------

