//---------------------------------------------------------------------------
/*
RandomCode, tool to generate random C++ code
Copyright (C) 2007-2012  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------


#include "randomcode.h"

#include "randomcodemenudialog.h"

int ribi::RandomCodeMenuDialog::ExecuteSpecific(const std::vector<std::string>& /*argv*/) noexcept
{
  assert(!"TODO");
  return 1;
}

const ribi::About ribi::RandomCodeMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "RandomCode",
    "tool to generate random C++ code",
    "the 25th of December 2012",
    "2007-2012",
    "http://www.richelbilderbeek.nl/ToolRandomCode.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("RandomCode version: " + RandomCode::GetVersion());
  return a;
}

const ribi::Help ribi::RandomCodeMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::RandomCodeMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramRandomCode
  };
  assert(p);
  return p;
}

const std::string ribi::RandomCodeMenuDialog::GetVersion() const noexcept
{
  return "4.2";
}

const std::vector<std::string> ribi::RandomCodeMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-xx-xx: version 1.0: initial version in C++ Builder",
    "2010-12-03: version 2.0: port to Qt Creator",
    "2011-01-07: version 3.0: added menu, reworked file architecture",
    "2011-04-24: version 4.0: major architectural change, created web version",
    "2011-08-31: version 4.1: added Welcome picture for web version",
    "2012-12-25: version 4.2: added menu for desktop version"
  };
}
