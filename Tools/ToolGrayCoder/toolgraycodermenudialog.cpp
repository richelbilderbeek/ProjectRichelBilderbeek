//---------------------------------------------------------------------------
/*
GrayCoder, tool to convert integers to and from Gray code
Copyright (C) 2009-2013 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolGrayCoder.htm
//---------------------------------------------------------------------------
#include "toolgraycodermenudialog.h"

#include "trace.h"

const ribi::About ribi::GrayCoderMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "GrayCoder",
    "tool to convert integers to and from Gray code",
    "the 26th of August 2013",
    "2009-2013",
    "http://www.richelbilderbeek.nl/ToolGrayCoder.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::GrayCoderMenuDialog::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> ribi::GrayCoderMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2009-05-02: version 1.0: initial version in C++ Builder");
  v.push_back("2013-08-26: version 2.0: port to Qt Creator console application");
  return v;
}
