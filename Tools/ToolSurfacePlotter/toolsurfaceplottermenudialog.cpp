//---------------------------------------------------------------------------
/*
SurfacePlotter, plots a bivariate function
Copyright (C) 2010-2012  Richel Bilderbeek

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
#include "toolsurfaceplottermenudialog.h"

#include <cassert>
#include <iostream>

#include "profile.h"

int ribi::ToolSurfacePlotterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

const ribi::About ribi::ToolSurfacePlotterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "SurfacePlotter",
    "plots a bivariate function",
    "the 14th of July 2012",
    "2012",
    "http://www.richelbilderbeek.nl/ToolSurfacePlotter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("Rectangle version: " + Rect::GetVersion());

  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  return a;
}

const ribi::Help ribi::ToolSurfacePlotterMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::ToolSurfacePlotterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramSurfacePlotter
  };
  assert(p);
  return p;
}

const std::string ribi::ToolSurfacePlotterMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::ToolSurfacePlotterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-02-07: version 1.0: initial Windows-only version",
    "2010-02-15: version 1.1: let user specify the range of x and y coordinats",
    "2012-07-07: version 2.0: port to Qt"
  };
}
