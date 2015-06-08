//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
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
//From http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "createqtprojectzipfilemenudialog.h"

#include <iostream>

#include "createqtprojectzipfilemaindialog.h"
#include "fileio.h"
#include "qrcfile.h"
#include "qtcreatorprofile.h"
#include "qtcreatorprofilezipscript.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
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
  if (argc == 1)
  {
    std::cout << this->GetHelp() << '\n';
    return 1;
  }

  std::string folder;
  for (int i=0; i!=argc-1; ++i)
  {
    if (argv[i] == "-f" || argv[i] == "--folder")
    {
      folder = argv[i+1];
      break;
    }
  }
  bool silent = false;
  for (int i=0; i!=argc; ++i)
  {
    if (argv[i] == "-s" || argv[i] == "--silent")
    {
      silent = true;
      break;
    }
  }

  if (!fileio::FileIo().IsFolder(folder))
  {
    if (!silent)
    {
      std::cout
        << "Invalid folder '" << folder << "'\n"
        << "Please supply a valid folder name\n";
    }
    return 1;
  }
  #ifdef _WIN32
  if (folder.substr(0,6) != "..\\..\\" && folder.substr(0,6) != "../../")
  {
    if (!silent)
    {
      std::cout
        << "Folder must start with '..\\..\\' or '..//..//'\n"
        << "Please supply a folder name starting with '\\..\\..' or '//..//..'\n";
    }
    return 1;
  }
  #else
  if (folder.substr(0,6) != "../../")
  {
    if (!silent)
    {
      std::cout
        << "Folder must start with '../../'\n"
        << "Please supply a folder name starting with '/../..'\n";
    }
    return 1;
  }
  #endif

  //Call the script with UNIX line endings, as
  //all Qt Creator file works with these as well
  std::string folder_unix;
  std::replace_copy(folder.begin(),folder.end(),std::back_inserter(folder_unix),'\\','/');

  const std::string script = CreateQtProjectZipFileMainDialog(folder_unix).GetScript();
  assert(!script.empty());
  if (!silent) { std::cout << script << '\n'; }
  return 0;
}

ribi::About ribi::CreateQtProjectZipFile::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "CreateQtProjectZipFile",
    "tool to create a zip file from a Qt project",
    "the 25th of April 2014",
    "2012-2015",
    "http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("QtCreatorProFileZipScript version: " + QtCreatorProFileZipScript::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::CreateQtProjectZipFile::MenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::CreateQtProjectZipFile::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramCreateQtProjectZipFile
  };
  assert(p);
  return p;
}

std::string ribi::CreateQtProjectZipFile::MenuDialog::GetVersion() const noexcept
{
  return "3.0";
}

std::vector<std::string> ribi::CreateQtProjectZipFile::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-02-25: version 1.0: initial version",
    "2012-05-29: version 1.1: small fix due to new boost::filesystem",
    "2012-05-30: version 1.2: added Test method",
    "2012-06-10: version 1.3: added Path class for cleaner code",
    "2013-05-19: version 2.0: support for any depth of folder tree",
    "2014-01-27: version 2.1: also copies the included .pri files' content",
    "2014-04-12: version 2.2: added 'silent' flag",
    "2014-04-25: version 2.3: fixed SimplifyPath bug",
    "2014-05-02: version 3.0: internally use UNIX path seperators only, fixed bug"
  };
}

#ifndef NDEBUG
void ribi::CreateQtProjectZipFile::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    {
      const std::string mypath{fileio::FileIo().GetTempFileName()};
      { std::ofstream f(mypath); f << "SOURCES += qtmain.cpp"; }
      boost::shared_ptr<QtCreatorProFile> p{new QtCreatorProFile(mypath)};
    }
    const std::string script = CreateQtProjectZipFileMainDialog("../../Tools/ToolCreateQtProjectZipFile").GetScript();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  MenuDialog d;
  #ifdef _WIN32
  d.Execute( { "CreateQtProjectZipFile", "-f", "..\\..\\Tools\\ToolCreateQtProjectZipFile", "-s" } );
  #else
  d.Execute( { "CreateQtProjectZipFile", "-f", "../../Tools/ToolCreateQtProjectZipFile", "-s" } );
  #endif
}
#endif
