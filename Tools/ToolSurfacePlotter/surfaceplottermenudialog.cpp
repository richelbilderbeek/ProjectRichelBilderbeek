//---------------------------------------------------------------------------
/*
SurfacePlotter, plots a bivariate function
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolSurfacePlotter.htm
//---------------------------------------------------------------------------
#include "surfaceplottermenudialog.h"

#include <cassert>
#include <iostream>

#include "fparser.hh"

#include "drawcanvas.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::SurfacePlotterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc < 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  const int w { 78 };
  const int h { 18 };
  boost::shared_ptr<DrawCanvas> canvas { new DrawCanvas(78,18) };

  FunctionParser f;

  //Parse the formula
  const std::string formula { "sin(x / 10.0) + cos(y / 5.0)" };
  f.Parse(formula.c_str(),"x,y");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    std::cout << "Function cannot not be parsed" << std::endl;
    return 1;
  }

  //Y-X ordered
  std::vector<std::vector<double> > v(h,std::vector<double>(w,0.0));
  for (int y=0; y!=h; ++y)
  {
    for (int x=0; x!=w; ++x)
    {
      const double xs[2] = { static_cast<double>(x),static_cast<double>(y) };
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
  canvas->DrawSurface(v);
  std::cout << (*canvas) << std::endl;

  return 0;
}

ribi::About ribi::SurfacePlotterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SurfacePlotter",
    "plots a bivariate function",
    "the 7th of July 2014",
    "2012-2015",
    "http://www.richelbilderbeek.nl/ToolSurfacePlotter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("Rectangle version: " + Rect::GetVersion());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("DrawCanvas version: " + DrawCanvas::GetVersion());
  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  return a;
}

ribi::Help ribi::SurfacePlotterMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::SurfacePlotterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramSurfacePlotter
  };
  assert(p);
  return p;
}

std::string ribi::SurfacePlotterMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

std::vector<std::string> ribi::SurfacePlotterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-02-07: version 1.0: initial Windows-only version",
    "2010-02-15: version 1.1: let user specify the range of x and y coordinats",
    "2012-07-07: version 2.0: port to Qt",
    "2014-03-07: version 2.1: command-line version plots a hard-coded function",
    "2014-07-07: version 2.2: added Qwt spectrogram"
  };
}

#ifndef NDEBUG
void ribi::SurfacePlotterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
