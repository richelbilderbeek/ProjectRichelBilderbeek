//---------------------------------------------------------------------------
/*
Encranger, encryption tool
Copyright (C) 2009-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolEncranger.htm
//---------------------------------------------------------------------------
#include "toolencrangermenudialog.h"
#include "loopreader.h"
#include "encranger.h"

const ribi::About ribi::ToolEncrangerMenuDialog::GetAbout() noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolEncranger",
    "tool to test the Encranger class",
    "the 27th of September 2013",
    "2009-2013",
    "http://www.richelbilderbeek.nl/ToolEncranger.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  return a;
}

const std::string ribi::ToolEncrangerMenuDialog::GetVersion() noexcept
{
  return "2.5";
}

const std::vector<std::string> ribi::ToolEncrangerMenuDialog::GetVersionHistory() noexcept
{
  return {
    "2009-08-22: Version 1.0: initial version (then called 'Encranger') programmed in C++ Builder",
    "2011-03-06: Version 2.0: port to Qt Creator, renamed application to ToolEncranger",
    "2011-03-22: Version 2.1: seperated GUI from logic, added website version",
    "2011-04-25: Version 2.2: removed website version\'s Close button",
    "2011-06-22: Version 2.3: improved website version",
    "2011-08-31: Version 2.4: added arrows and Welcome image",
    "2013-09-27: Version 2.5: conformized for ProjectRichelBilderbeek",
  };
}
