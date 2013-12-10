//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "connectthreemenudialog.h"


#include "connectthree.h"
#include "connectthreewidget.h"

#include <cassert>
#include <iostream>
#pragma GCC diagnostic pop

int ribi::ConnectThreeMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

const ribi::About ribi::ConnectThreeMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ConnectThree",
    "connect-three game",
    "the 1st of August 2013",
    "2010-2013",
    "http://www.richelbilderbeek.nl/GameConnectThree.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("ConnectThree version: " + ConnectThree::GetVersion());
  a.AddLibrary("ConnectThreeWidget version: " + ConnectThreeWidget::GetVersion());
  a.AddLibrary("Special thanks to Mark Wiering for his excellent bug reports");
  return a;
}

const ribi::Help ribi::ConnectThreeMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::ConnectThreeMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramConnectThree
  };
  assert(p);
  return p;
}

const std::string ribi::ConnectThreeMenuDialog::GetVersion() const noexcept
{
  return "6.5";
}

const std::vector<std::string> ribi::ConnectThreeMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-xx-xx: version 1.0: initial version as part of K3OpEenRij",
    "2011-01-10: version 5.0: initial Qt4 version",
    "2011-01-11: version 5.2: support that the game can end in a draw",
    "2011-04-22: version 6.0: major architectural changes",
    "2011-04-24: version 6.1: fixed a bug that showed when deploying to my WtWebsite",
    "2011-04-25: version 6.2: hopefully fixed the bug as in 6.1, fixed desktop version",
    "2013-07-11: version 6.3: transitioned to Qt5 and Boost 1.54.0",
    "2013-07-21: version 6.4: improved looks",
    "2013-08-06: version 6.5: facilitate K3OpEenRij using ConnectThree classes"
  };
}

#ifndef NDEBUG
void ribi::X::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::X::Test");
  TRACE("Finished ribi::X::Test successfully");
}
#endif
