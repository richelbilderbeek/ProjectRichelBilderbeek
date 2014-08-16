//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
Copyright (C) 2010-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#include "pictocodemenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

int ribi::PicToCodeMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::PicToCodeMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PicToCode",
    "tool to convert a picture to C++ code",
    "the 18th of April 2011",
    "2010-2014",
    "http://www.richelbilderbeek.nl/ToolPicToCode.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::PicToCodeMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::PicToCodeMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramPicToCode
  };
  assert(p);
  return p;
}

std::string ribi::PicToCodeMenuDialog::GetVersion() const noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::PicToCodeMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-10-10: version 1.0: initial version",
    "2010-10-11: version 1.1: added tranparency support",
    "2011-04-18: version 1.2: added support for QPixmap",
    "2011-04-18: version 1.3: added menu, added web application",
    "2013-11-04: version 1.4: conformized to ProjectRichelBilderbeekConsole",
  };
}

#ifndef NDEBUG
void ribi::PicToCodeMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
