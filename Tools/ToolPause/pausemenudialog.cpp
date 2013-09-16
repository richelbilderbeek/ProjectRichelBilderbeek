//---------------------------------------------------------------------------
/*
Pause, tool to do nothing
Copyright (C) 2010-2013 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolPause.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "pausemenudialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>
#pragma GCC diagnostic pop

void ribi::PauseMenuDialog::Execute(const int argc, const char * const argv[]) noexcept
{
  assert(argc >= 1);
  if (argc == 1)
  {
    Wait(10.0);
  }
  else
  {
    try
    {
      const double t = boost::lexical_cast<double>(argv[1]);
      Wait(t);
    }
    catch (boost::bad_lexical_cast&)
    {
      Wait(10.0);
    }
  }
}

const ribi::About ribi::PauseMenuDialog::GetAbout() noexcept
{
  About a(
    "Richel Bilderbeek",
    "Pause",
    "tool to do nothing",
    "the 25th of May 2013",
    "2010-2012",
    "http://www.richelbilderbeek.nl/ToolPause.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("AsciiArter version: " + AsciiArter::GetVersion());
  return a;
}

const std::string ribi::PauseMenuDialog::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::PauseMenuDialog::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2010-xx-xx: Version 1.0: initial version");
  v.push_back("2013-05-25: Version 1.1: added menu, conformized towards ProjectRichelBilderbeek");
  return v;
}

void ribi::PauseMenuDialog::Wait(const double n_secs) noexcept
{
  boost::timer t;
  while (t.elapsed() < n_secs) {}
}
