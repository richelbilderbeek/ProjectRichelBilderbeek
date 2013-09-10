//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
Copyright (C) 2012-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "createqtprojectzipfilemenudialog.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "qtcreatorprofilezipscript.h"
#include "trace.h"
#pragma GCC diagnostic pop

const ribi::About ribi::CreateQtProjectZipFile::MenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "CreateQtProjectZipFile",
    "tool to create a zip file from a Qt project",
    "the 18th of May 2013",
    "2012-2013",
    "http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("QtCreatorProFileZipScript version: " + QtCreatorProFileZipScript::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::CreateQtProjectZipFile::MenuDialog::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> ribi::CreateQtProjectZipFile::MenuDialog::GetVersionHistory()
{
  return {
    "2012-02-25: version 1.0: initial version",
    "2012-05-29: version 1.1: small fix due to new boost::filesystem",
    "2012-05-30: version 1.2: added Test method",
    "2012-06-10: version 1.3: added Path class for cleaner code",
    "2013-05-19: version 2.0: support for any depth of folder tree"
  };
}
