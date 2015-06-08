//---------------------------------------------------------------------------
/*
MusicTheory, tool for visualizing my music theory
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolMusicTheory.htm
//---------------------------------------------------------------------------
#include "musictheorymenudialog.h"

#include <cassert>
#include <iostream>
#include "musicchord.h"
#include "musicnote.h"
#include "musicscale.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

int ribi::MusicTheoryMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::MusicTheoryMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "MusicTheory",
    "tool for visualizing my music theory",
    "the 11th of August 2012",
    "2012-2015",
    "http://www.richelbilderbeek.nl/ToolMusicTheory.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("Music::Chord version: " + Music::Chord::GetVersion());
  a.AddLibrary("Music::Note version: " + Music::Note::GetVersion());
  a.AddLibrary("Music::Scale version: " + Music::Scale::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::MusicTheoryMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::MusicTheoryMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramMusicTheory
  };
  assert(p);
  return p;
}

std::string ribi::MusicTheoryMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::MusicTheoryMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-08-10: version 1.0: initial version",
    "2012-08-11: version 1.1: changes in the background, support crosscompiling to Windows",
    "2012-08-17: version 1.2: added multi-scale chord relations"
  };
}

#ifndef NDEBUG
void ribi::MusicTheoryMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
