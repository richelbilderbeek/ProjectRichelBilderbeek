//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a truely fun game
Copyright (C) 2003-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm
//---------------------------------------------------------------------------
#include "daswahreschlagerfestmenudialog.h"

#include <cassert>
#include <iostream>

#include "daswahreschlagerfestterminal.h"
#include "daswahreschlagerfestwidget.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

int ribi::dws::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  Terminal terminal;

  if (argc == 2 && (argv[1] == "-d" || argv[1] == "--demo"))
  {
    terminal.SetAutoPlay(true);
  }
  Widget w(&terminal);
  w.Execute();
  return 0;
}

ribi::About ribi::dws::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Das Wahre Schlagerfest",
    "a truely fun game",
    "the 10th of February 2014",
    "2003-2015",
    "http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  return a;
}

ribi::Help ribi::dws::MenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('d',"demo","See a demo"),
      Help::Option('p',"play","Play the game"),
    },
    {
      GetAbout().GetFileTitle() + " -d",
      GetAbout().GetFileTitle() + " --demo",
      GetAbout().GetFileTitle() + " -p",
      GetAbout().GetFileTitle() + " --play"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::dws::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramDasWahreSchlagerfest
  };
  assert(p);
  return p;
}

std::string ribi::dws::MenuDialog::GetVersion() const noexcept
{
  return "3.0";
}

std::vector<std::string> ribi::dws::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2003-09-30: version 1.1: first VCL (Windows-only) version",
    "2012-07-21: version 2.0: ported to Qt (cross-platform)",
    "2012-07-29: version 2.1: changed graphics to old-school",
    "2012-08-09: version 2.2: changed graphics, changed new tile selection (rendering the eat-it all tile) obsolete"
    "2014-01-30: version 2.3: added command-line demo and play mode",
    "2014-01-31: version 2.4: added terminal-like mode from command-line",
    "2014-02-10: version 2.5: added terminal-like mode in desktop version",
    "2015-08-28: version 3.0: removed terminal-like mode in desktop version, ported to NDS"
  };
}

#ifndef NDEBUG
void ribi::dws::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  Terminal terminal;
  Widget widget(&terminal);
  widget.Execute();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
