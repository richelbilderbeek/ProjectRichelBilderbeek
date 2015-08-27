//---------------------------------------------------------------------------
/*
Maziak, a simple maze game
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameMaziak.htm
//---------------------------------------------------------------------------
#include "maziakmenudialog.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "maziakmaindialog.h"
#include "maziakterminal.h"
#include "testtimer.h"
 
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::maziak::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::maziak::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  boost::shared_ptr<MainDialog> dialog {
    new MainDialog( 7 + (4 * 2) )
  };
  Terminal terminal;
  dialog->SetDisplay(&terminal);
  dialog->Execute();
  return 0;

}

ribi::About ribi::maziak::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Maziak",
    "a simple maze game",
    "the 28th of January 2014",
    "2007-2015",
    "http://www.richelbilderbeek.nl/GameMaziak.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  return a;
}

ribi::Help ribi::maziak::MenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::maziak::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramMaziak
  };
  assert(p);
  return p;
}

std::string ribi::maziak::MenuDialog::GetVersion() const noexcept
{
  return "3.0";
}

std::vector<std::string> ribi::maziak::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-10-22: version 1.0: Initial version",
    "2010-02-16: version 1.1: Changed graphics to resemble the original Maziacs more. Changed manu screen. Changed 'Game Over' screen. Changed 'Congratulations' screen.",
    "2010-02-17: version 1.2: Animated prisoners. Animated enemies. Animated player. Improved 'Menu' screen. Improved 'About' screen. Added 'What's New?' screen",
    "2010-02-18: version 1.3: Animated fights. Prevent overlapping sprites. Add 'Instructions' screen in menu. Improved 'Menu' screen",
    "2010-02-25: version 1.4: Improved 'Game Over' screen. Added animation in 'Congratulations' screen. Improved enemies' intelligence. Improved maze creation algorithm. Ensured the player is not placed too close to the exit.",
    "2010-07-31: version 2.0: Reprogrammed in Qt Creator, so Maziak is now cross-platform!",
    "2012-03-06: version 2.1: Conformized architecture and naming for ProjectRichelBilderbeek."
    "2014-01-06: version 3.0: Seperated GUI from game logic, allow console gaming"
  };
}

#ifndef NDEBUG
void ribi::maziak::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
