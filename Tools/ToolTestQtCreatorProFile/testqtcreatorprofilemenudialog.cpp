//---------------------------------------------------------------------------
/*
TestQtCreatorProFile, tool to test the QtCreatorProFile class
Copyright (C) 2010-2014 Richel Bilderbeek

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

#include <cassert>
#include <iostream>

#include "fileio.h"
#include "trace.h"
#include "qtcreatorprofile.h"
#pragma GCC diagnostic pop

ribi::TestQtCreatorProFileMenuDialog::TestQtCreatorProFileMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestQtCreatorProFileMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 3 && (argv[1] == "-f" || argv[1] == "--filename"))
  {
    const std::string filename = argv[2];
    if (filename.empty())
    {
      std::cout << "Please specify a filename.\n";
    }
    else if (filename.size() < 5)
    {
      std::cout << "Please specify a full Qt Creator (.pro) project filename.\n";
    }
    else if (filename.substr(filename.size() - 4,4) != ".pro")
    {
      std::cout << "Please specify a filename ending on .pro.\n";
    }
    else if (!fileio::FileIo().IsRegularFile(filename))
    {
      std::cout << "Please specify a Qt Creator (.pro) project filename that exists.\n";
    }
    else
    {
      const boost::shared_ptr<const QtCreatorProFile> p(
        new QtCreatorProFile(filename));
      std::cout << (*p) << '\n';
      return 0;
    }
    return 1;
  }
  std::cout << GetHelp() << '\n';
  return 1;
}

ribi::About ribi::TestQtCreatorProFileMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestQtCreatorProFile",
    "tool to test the QtCreatorProFile class",
    "the 18th May 2013",
    "2010-2014",
    "http://www.richelbilderbeek.nl/ToolTestQtCreatorProFile.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("QtCreatorProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestQtCreatorProFileMenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('f',"filename","filename of Qt Creator project (.pro) file")
    },
    {
      GetAbout().GetFileTitle() + " -f Project1.pro",
      GetAbout().GetFileTitle() + " --filename Project1.pro"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestQtCreatorProFileMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestQtCreatorProFile
  };
  assert(p);
  return p;
}

std::string ribi::TestQtCreatorProFileMenuDialog::GetVersion() const noexcept
{
  return "1.4";
}

std::vector<std::string> ribi::TestQtCreatorProFileMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-xx-xx: version 1.0: initial version, called TestProFile",
    "2012-02-27: version 1.1: initial version with About information",
    "2013-05-18: version 1.2: renamed this tool to TestQtCreatorProFile",
    "2013-11-05: version 1.3: conformized for ProjectRichelBilderbeekConsole",
    "2014-01-27: version 1.4: removed Boost.Filesystem and Boost.Program_Options"
  };
}

#ifndef NDEBUG
void ribi::TestQtCreatorProFileMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestQtCreatorProFileMenuDialog::Test");
  {
    std::stringstream s;
    s
      << "SOURCES += qtmain.cpp" << '\n'
    ;
    const std::string filename = fileio::FileIo().GetTempFileName(".pro");
    {
      std::ofstream f(filename.c_str());
      f << s.str();
    }
    assert(fileio::FileIo().IsRegularFile(filename));
    const boost::shared_ptr<const QtCreatorProFile> p(
      new QtCreatorProFile(filename)
    );
    assert(p->GetSources().size() == 1);
    TRACE(*p);

    fileio::FileIo().DeleteFile(filename);
  }
  {
    std::stringstream s;
    s
      << "include(../../DesktopApplication.pri)" << '\n'
      << "" << '\n'
      << "#Libs" << '\n'
      << "include(../../Libraries/Boost.pri)" << '\n'
      << "" << '\n'
      << "#Console" << '\n'
      << "include(../../Classes/CppAbout/CppAbout.pri)" << '\n'
      << "include(../../Classes/CppFileIo/CppFileIo.pri)" << '\n'
      << "include(../../Classes/CppHelp/CppHelp.pri)" << '\n'
      << "include(../../Classes/CppMenuDialog/CppMenuDialog.pri)" << '\n'
      << "include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)" << '\n'
      << "include(../../Classes/CppTrace/CppTrace.pri)" << '\n'
      << "" << '\n'
      << "#Desktop" << '\n'
      << "include(../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri)" << '\n'
      << "include(../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)" << '\n'
      << "" << '\n'
      << "#Specific for this application" << '\n'
      << "include(../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri)" << '\n'
      << "include(../../Classes/CppQrcFile/CppQrcFile.pri)" << '\n'
      << "include(../../Tools/ToolTestQtCreatorProFile/ToolTestQtCreatorProFileDesktop.pri)" << '\n'
      << "" << '\n'
      << "SOURCES += qtmain.cpp" << '\n'
    ;
    const std::string filename = fileio::FileIo().GetTempFileName(".pro");
    {
      std::ofstream f(filename.c_str());
      f << s.str();
    }
    assert(fileio::FileIo().IsRegularFile(filename));
    const boost::shared_ptr<const QtCreatorProFile> p(
      new QtCreatorProFile(filename)
    );
    assert(p->GetSources().size() == 1);
    TRACE(*p);

    fileio::FileIo().DeleteFile(filename);
  }
  TRACE("Finished ribi::TestQtCreatorProFileMenuDialog::Test successfully");
}
#endif
