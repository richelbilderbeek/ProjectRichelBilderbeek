//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a truely fun game
Copyright (C) 2003-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm
//---------------------------------------------------------------------------
#include "daswahreschlagerfestmenudialog.h"

#include <cassert>
#include <iostream>

#include "daswahreschlagerfestwidget.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"

int ribi::DasWahreSchlagerfestMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

  if (argc == 2 && (argv[1] == "-d" || argv[1] == "--demo"))
  {
    DasWahreSchlagerfestWidget w;
    std::cout << w << std::endl;

    for (int i=0; i!=100; ++i)
    {
      switch((std::rand() >> 4) % 4)
      {
        case 0: //Prefer downwards
        case 1: w.PressKey(ribi::DasWahreSchlagerfestWidget::Key::down); break;
        case 2: w.PressKey(ribi::DasWahreSchlagerfestWidget::Key::left); break;
        case 3: w.PressKey(ribi::DasWahreSchlagerfestWidget::Key::right); break;
      }
      std::cout << w << std::endl;
    }
  }
  if (argc == 2 && (argv[1] == "-p" || argv[1] == "--play"))
  {
    DasWahreSchlagerfestWidget w;

    while (1)
    {
      std::cout
        << std::endl
        << w << std::endl
        << std::endl;

      char c;
      std::cin >> c;

      if (!std::cin)
      {
        std::cout << "Please type 'a', 's', 'd' or 'q'" << std::endl;
        continue;
      }

      switch(c)
      {
        case 's': w.PressKey(ribi::DasWahreSchlagerfestWidget::Key::down); break;
        case 'a': w.PressKey(ribi::DasWahreSchlagerfestWidget::Key::left); break;
        case 'd': w.PressKey(ribi::DasWahreSchlagerfestWidget::Key::right); break;
        case 'q': return 0;
      }
    }
  }
  return 0;
}

ribi::About ribi::DasWahreSchlagerfestMenuDialog::GetAbout() const noexcept
{
  return About(
    "Richel Bilderbeek",
    "Das Wahre Schlagerfest",
    "a truely fun game",
    "the 10th of February 2014",
    "2003-2014",
    "http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm",
    GetVersion(),
    GetVersionHistory()
  );
}

ribi::Help ribi::DasWahreSchlagerfestMenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('d',"demo","See a demo"),
      Help::Option('p',"play","Play the game"),
    },
    {
      GetAbout().GetFileTitle() + " -d",
      GetAbout().GetFileTitle() + " --demo",
      GetAbout().GetFileTitle() + " -p",
      GetAbout().GetFileTitle() + " --play"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::DasWahreSchlagerfestMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramDasWahreSchlagerfest
  };
  assert(p);
  return p;
}

std::string ribi::DasWahreSchlagerfestMenuDialog::GetVersion() const noexcept
{
  return "2.5";
}

std::vector<std::string> ribi::DasWahreSchlagerfestMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2003-09-30: version 1.1: Windows-only version",
    "2012-07-21: version 2.0: ported to cross-platform",
    "2012-07-29: version 2.1: changed graphics to old-school",
    "2012-08-09: version 2.2: changed graphics, changed new tile selection (rendering the eat-it all tile) obsolete"
    "2014-01-30: version 2.3: added command-line demo and play mode",
    "2014-01-31: version 2.4: added terminal-like mode from command-line",
    "2014-02-10: version 2.5: added terminal-like mode in desktop version"
  };
}

#ifndef NDEBUG
void ribi::DasWahreSchlagerfestMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::DasWahreSchlagerfestMenuDialog::Test");
  DasWahreSchlagerfestWidget();
  TRACE("Finished ribi::DasWahreSchlagerfestMenuDialog::Test successfully");
}
#endif
