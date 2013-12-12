//---------------------------------------------------------------------------
/*
TestQrcFile, tool to test the QrcFile class
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
//From http://www.richelbilderbeek.nl/ToolTestQrcFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testqrcfilemenudialog.h"

#include <cassert>
#include <iostream>

#include <QFile>

#include "trace.h"
#include "qrcfile.h"

#pragma GCC diagnostic pop

int ribi::TestQrcFileMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

const ribi::About ribi::TestQrcFileMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestQrcFile",
    "tool to test the QrcFile class",
    "the 20th of May 2013",
    "2012-2013",
    "http://www.richelbilderbeek.nl/ToolTestQrcFile.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());

  return a;
}

const ribi::Help ribi::TestQrcFileMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::TestQrcFileMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestQrcFile
  };
  assert(p);
  return p;
}

const std::string ribi::TestQrcFileMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::TestQrcFileMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2012-06-13: version 1.0: initial version",
    "2013-05-20: version 1.1: some GUI modifications",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::TestQrcFileMenuDialog::Test() noexcept
{
  //Test exactly once
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  assert(QFile::exists("../ToolTestQrcFile/ToolTestQrcFile.qrc"));
  {
    QrcFile f("../ToolTestQrcFile/ToolTestQrcFile.qrc");
    assert(f.GetFiles().count("R.png"));
  }
}
#endif

