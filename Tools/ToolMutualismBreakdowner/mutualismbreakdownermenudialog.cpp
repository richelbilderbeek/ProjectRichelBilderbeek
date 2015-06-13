//---------------------------------------------------------------------------
/*
MutualismBreakdowner, seagrass model
Copyright (C) 2015 Richel Bilderbeek

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
//System expert: Greg Fivash
//Model development: Greg Fivash (major), Richel Bilderbeek (minor)
//Programming: Richel Bilderbeek
//
//From http://www.richelbilderbeek.nl/ToolMutualismBreakdowner.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "mutualismbreakdownermenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QFile>

//#include "asciiarter.h"
#include "mutualismbreakdownermenudialog.h"
#include "fileio.h"
//#include "imagecanvas.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::mb::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::mb::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1 || argc > 4)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 0;
}

ribi::About ribi::mb::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Greg Fivash and Richel Bilderbeek",
    "MutualismBreakdowner",
    "simulation",
    "the 12th of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolMutualismBreakdowner.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

boost::shared_ptr<const ribi::Program> ribi::mb::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramMutualismBreakdowner);
  assert(p);
  return p;
}

std::string ribi::mb::MenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::mb::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-05-03: Version 0.1: initial version with 3 ODEs",
    "2015-05-05: Version 1.0: implemented system of 4 ODEs, added menu screens",
    "2015-05-12: Version 2.0: implemented system of 2 ODEs",
    "2015-05-13: Version 2.1: added spatial model"
  };
}

ribi::Help ribi::mb::MenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "MutualismBreakdowner",
    "Seagrass model",
    {
      //No additional options
    },
    {
    }
  );
}

#ifndef NDEBUG
void ribi::mb::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
