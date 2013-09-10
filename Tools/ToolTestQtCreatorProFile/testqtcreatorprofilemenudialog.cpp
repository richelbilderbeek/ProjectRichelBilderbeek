//---------------------------------------------------------------------------
/*
TestQtCreatorProFile, tool to test the QtCreatorProFile class
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
//From http://www.richelbilderbeek.nl/ToolTestQtCreatorProFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testqtcreatorprofilemenudialog.h"

#include "trace.h"
#include "qtcreatorprofile.h"
#pragma GCC diagnostic pop

const ribi::About ribi::TestQtCreatorProFileMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestQtCreatorProFile",
    "tool to test the QtCreatorProFile class",
    "the 18th May 2013",
    "2010-2013",
    "http://www.richelbilderbeek.nl/ToolTestQtCreatorProFile.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::TestQtCreatorProFileMenuDialog::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> ribi::TestQtCreatorProFileMenuDialog::GetVersionHistory()
{
  return {
    "2010-xx-xx: version 1.0: initial version, called TestProFile",
    "2012-02-27: version 1.1: initial version with About information",
    "2013-05-18: version 1.2: renamed this tool to TestQtCreatorProFile"
  };
}

