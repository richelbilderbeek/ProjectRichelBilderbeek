//---------------------------------------------------------------------------
/*
TestQrcFile, tool to test the QrcFile class
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
//From http://www.richelbilderbeek.nl/ToolTestQrcFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testqrcfilemenudialog.h"

#include <cassert>
#include <iostream>

#include <QFile>

#include "fileio.h"
#include "qrcfile.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::TestQrcFileMenuDialog::TestQrcFileMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestQrcFileMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
      std::cout << "Please specify a full Qt Creator (.qrc) project filename.\n";
    }
    else if (filename.substr(filename.size() - 4,4) != ".qrc")
    {
      std::cout << "Please specify a filename ending on .qrc.\n";
    }
    else if (!fileio::FileIo().IsRegularFile(filename))
    {
      std::cout << "Please specify a Qt Creator Resource (.qrc) filename that exists.\n";
    }
    else
    {
      QrcFile p(filename);
      std::cout << p << '\n';
      return 0;
    }
    return 1;
  }
  std::cout << GetHelp() << '\n';
  return 1;
}

ribi::About ribi::TestQrcFileMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestQrcFile",
    "tool to test the QrcFile class",
    "the 20th of May 2013",
    "2012-2015",
    "http://www.richelbilderbeek.nl/ToolTestQrcFile.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());

  return a;
}

ribi::Help ribi::TestQrcFileMenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('f',"filename","filename of the Qt Resource file (.qrc) file")
    },
    {
      GetAbout().GetFileTitle() + " -f somefile.qrc",
      GetAbout().GetFileTitle() + " --filename somefile.qrc"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestQrcFileMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestQrcFile
  };
  assert(p);
  return p;
}

std::string ribi::TestQrcFileMenuDialog::GetVersion() const noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::TestQrcFileMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-06-13: version 1.0: initial version",
    "2013-05-20: version 1.1: some GUI modifications",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole",
    "2014-01-27: version 1.3: removed use of Boost.Filesystem and Boost.Program_Options",
  };
}

#ifndef NDEBUG
void ribi::TestQrcFileMenuDialog::Test() noexcept
{
  //Test exactly once
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  assert(fileio::FileIo().IsRegularFile("../../Tools/ToolTestQrcFile/ToolTestQrcFile.qrc"));
  {
    QrcFile f("../../Tools/ToolTestQrcFile/ToolTestQrcFile.qrc");
    assert(f.GetFiles().count("R.png"));
  }
}
#endif

