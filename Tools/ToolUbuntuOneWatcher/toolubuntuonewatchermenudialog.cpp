//---------------------------------------------------------------------------
/*
UbuntuOneWatcher, solver of quadratic equations
Copyright (C) 2008-2013 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolUbuntuOneWatcher.htm
//---------------------------------------------------------------------------
#include "toolubuntuonewatchermenudialog.h"

#include "trace.h"

const ribi::About ribi::UbuntuOneWatcherMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "UbuntuOneWatcher",
    "tool to see what Ubuntu One is doing",
    "the 15th of Oktober 2013",
    "2010-2013",
    "http://www.richelbilderbeek.nl/ToolUbuntuOneWatcher.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::UbuntuOneWatcherMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::UbuntuOneWatcherMenuDialog::GetVersionHistory()
{
  return {
    "2010-09-26: version 1.0: initial version",
    "2013-10-14: version 1.1: conformized to ProjectRichelBilderbeek"
  };
}
