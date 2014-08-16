//---------------------------------------------------------------------------
/*
TestBroadcastServer, tool to test WtBroadcastServer
Copyright (C) 2011-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestBroadcastServer.htm
//---------------------------------------------------------------------------
#include "about.h"
#include "richelbilderbeekprogram.h"
#include "testbroadcastservermenudialog.h"
#include "trace.h"

ribi::ToolTestBroadcastServer::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::ToolTestBroadcastServer::MenuDialog::ExecuteSpecific(const std::vector<std::string>& /*argv*/) noexcept
{
  //const int argc = static_cast<int>(argv.size());
  std::cout << GetHelp() << '\n';
  return 1;
}

ribi::About ribi::ToolTestBroadcastServer::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestBroadcastServer",
    "tool to test WtBroadcastServer",
    "the 28th of April 2014",
    "2011-2014",
    "http://www.richelbilderbeek.nl/ToolTestBroadcastServer.htm",
    GetVersion(),
    GetVersionHistory()
  );
  return a;
}

ribi::Help ribi::ToolTestBroadcastServer::MenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::ToolTestBroadcastServer::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramTestBroadcastServer);
  assert(p);
  return p;

}

std::string ribi::ToolTestBroadcastServer::MenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::ToolTestBroadcastServer::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-07-27: Version 1.0: initial version",
    "2011-07-28: Version 1.1: adapted ToolTestBroadcastServer to fit within WtWebsite",
    "2011-08-01: Version 1.2: minor changes",
    "2014-04-28: Version 2.0: put in namespace ribi"
  };
}


#ifndef NDEBUG
void ribi::ToolTestBroadcastServer::MenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ToolTestBroadcastServer::MenuDialog::Test");
  TRACE("Finished ribi::ToolTestBroadcastServer::MenuDialog::Test successfully");
}
#endif
