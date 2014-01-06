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

#include "trace.h"
#include "qtcreatorprofile.h"
#pragma GCC diagnostic pop

int ribi::TestQtCreatorProFileMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::TestQtCreatorProFileMenuDialog::GetAbout() const noexcept
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

const ribi::Help ribi::TestQtCreatorProFileMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::TestQtCreatorProFileMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestQtCreatorProFile
  };
  assert(p);
  return p;
}

const std::string ribi::TestQtCreatorProFileMenuDialog::GetVersion() const noexcept
{
  return "1.3";
}

const std::vector<std::string> ribi::TestQtCreatorProFileMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-xx-xx: version 1.0: initial version, called TestProFile",
    "2012-02-27: version 1.1: initial version with About information",
    "2013-05-18: version 1.2: renamed this tool to TestQtCreatorProFile",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole"
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
  TRACE("Finished ribi::TestQtCreatorProFileMenuDialog::Test successfully");
}
#endif
