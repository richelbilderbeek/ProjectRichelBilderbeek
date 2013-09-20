//---------------------------------------------------------------------------
/*
QmakeWatcher, tool to watch qmake's .pro to Makefile conversion
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
//From http://www.richelbilderbeek.nl/ToolQmakeWatcher.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qmakewatchermenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

const ribi::About ribi::QmakeWatcherMenuDialog::GetAbout() noexcept
{
  ribi::About a {
    "Richel Bilderbeek",
    "QmakeWatcher",
    "tool to watch qmake's .pro to Makefile conversion",
    "the 20th of September 2013",
    "2010-2013",
    "http://www.richelbilderbeek.nl/ToolQmakeWatcher.htm",
    GetVersion(),
    GetVersionHistory()
  };
  //a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  //a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::QmakeWatcherMenuDialog::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::QmakeWatcherMenuDialog::GetVersionHistory() noexcept
{
  return {
    "2013-09-20: version 1.0: initial version, conformized for ProjectRichelBilderbeek"
  };
}
