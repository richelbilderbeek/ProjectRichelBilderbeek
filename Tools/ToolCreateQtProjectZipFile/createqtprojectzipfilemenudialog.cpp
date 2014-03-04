//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
Copyright (C) 2012-2014 Richel Bilderbeek

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

#include <iostream>

#include "fileio.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "createqtprojectzipfilemaindialog.h"
#include "qtcreatorprofilezipscript.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::CreateQtProjectZipFile::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::CreateQtProjectZipFile::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  assert(argc > 0);
  if (argc != 3 || (argv[1] != "-f" && argv[1] != "--folder"))
  {
    std::cout << this->GetHelp() << '\n';
    return 1;
  }
  const std::string folder { argv[2] };
  if (!fileio::IsFolder(folder))
  {
    std::cout
      << "Invalid folder '" << folder << "'\n"
      << "Please supply a valid folder name\n";
    return 1;
  }
  if (folder.substr(0,6) != "../../")
  {
    std::cout
      << "Folder must start with '../../'\n"
      << "Please supply a folder name starting with '/../..'\n";
    return 1;
  }
  std::cout << CreateQtProjectZipFileMainDialog(folder).GetScript() << '\n';
  return 0;
}

const ribi::About ribi::CreateQtProjectZipFile::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "CreateQtProjectZipFile",
    "tool to create a zip file from a Qt project",
    "the 27th of January 2014",
    "2012-2014",
    "http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("QtCreatorProFileZipScript version: " + QtCreatorProFileZipScript::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const ribi::Help ribi::CreateQtProjectZipFile::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      //Options
      Help::Option('f',"folder","the source folder to have a zip script generated of")
    },
    {
      //Example uses
      "CreateQtProjectZipFile -f MyFolder",
      "CreateQtProjectZipFile --folder MyFolder",
    }
  );
}

const boost::shared_ptr<const ribi::Program> ribi::CreateQtProjectZipFile::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramCreateQtProjectZipFile
  };
  assert(p);
  return p;
}

const std::string ribi::CreateQtProjectZipFile::MenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

const std::vector<std::string> ribi::CreateQtProjectZipFile::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-02-25: version 1.0: initial version",
    "2012-05-29: version 1.1: small fix due to new boost::filesystem",
    "2012-05-30: version 1.2: added Test method",
    "2012-06-10: version 1.3: added Path class for cleaner code",
    "2013-05-19: version 2.0: support for any depth of folder tree",
    "2014-01-27: version 2.1: also copies the included .pri files' content",
  };
}

#ifndef NDEBUG
void ribi::CreateQtProjectZipFile::MenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::CreateQtProjectZipFile::MenuDialog::Test()");
  TRACE("Finished ribi::CreateQtProjectZipFile::MenuDialog::Test() successfully");
}
#endif
