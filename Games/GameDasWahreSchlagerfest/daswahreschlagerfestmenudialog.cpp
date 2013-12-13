//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a truely fun game
Copyright (C) 2003-2012 Richel Bilderbeek

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

#include "daswahreschlagerfestwidget.h"
#include "trace.h"

int ribi::DasWahreSchlagerfestMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  std::cout
    << this->GetAbout().GetFileTitle() << " cannot be run in console mode\n"
    << std::endl;
  return 0;
}

const ribi::About ribi::DasWahreSchlagerfestMenuDialog::GetAbout() const noexcept
{
  return About(
    "Richel Bilderbeek",
    "Das Wahre Schlagerfest",
    "a truely fun game",
    "the 9th of August 2012",
    "2003-2012",
    "http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm",
    GetVersion(),
    GetVersionHistory());
}

const ribi::Help ribi::DasWahreSchlagerfestMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::DasWahreSchlagerfestMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramDasWahreSchlagerfest
  };
  assert(p);
  return p;
}

const std::string ribi::DasWahreSchlagerfestMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

const std::vector<std::string> ribi::DasWahreSchlagerfestMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2003-09-30: version 1.1: Windows-only version",
    "2012-07-21: version 2.0: ported to cross-platform",
    "2012-07-29: version 2.1: changed graphics to old-school",
    "2012-08-09: version 2.2: changed graphics, changed new tile selection (rendering the eat-it all tile) obsolete"
  };
}

#ifndef NDEBUG
void ribi::DasWahreSchlagerfestMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::DasWahreSchlagerfestMenuDialog::Test");
  DasWahreSchlagerfestWidget();
  TRACE("Finished ribi::DasWahreSchlagerfestMenuDialog::Test successfully");
}
#endif
