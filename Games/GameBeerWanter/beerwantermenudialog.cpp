//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#include "beerwantermenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QFile>

#include "beerwantermaindialog.h"
#include "fileio.h"
#include "imagecanvas.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::BeerWanterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
  }

  //Display a beer
  if (argc == 2 && (argv[1] == "-s" || argv[1] == "--show"))
  {
    const std::string filename { fileio::FileIo().GetTempFileName(".png") };
    QFile qfile(BeerWanterMainDialog::GetResourceFilename().c_str());
    qfile.copy(filename.c_str());
    assert(fileio::FileIo().IsRegularFile(filename)
      && "BeerWanter resource must exist");

    const int n_cols = 78;
    const boost::shared_ptr<ImageCanvas> canvas {
      new ImageCanvas(
        filename,
        n_cols
      )
    };

    fileio::FileIo().DeleteFile(filename);
    std::cout << (*canvas) << std::endl;
    return 0;
  }

  if (argc == 1)
  {
    std::cout
      << std::endl
      << GetAbout().GetFileTitle() << " cannot be run in console mode\n"
      << std::endl;
  }
  return 0;
}

ribi::About ribi::BeerWanterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "BeerWanter",
    "a simple game",
    "the 16th of January 2014",
    "2005-2015",
    "http://www.richelbilderbeek.nl/GameBeerWanter.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("ImageCanvas version: " + ImageCanvas::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  return a;
}

ribi::Help ribi::BeerWanterMenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('s',"show","show a beer")
    },
    {
      GetAbout().GetFileTitle() + " --show"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::BeerWanterMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramBeerWanter
  };
  assert(p);
  return p;
}

std::string ribi::BeerWanterMenuDialog::GetVersion() const noexcept
{
  return "7.2";
}

std::vector<std::string> ribi::BeerWanterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2005-11-16: version 1.0: (at that time called) 'Beerwanter 1' was programmed in C++ using the C++ Builder IDE during a 'Spass programmieren' session, which made BeerWanter a game for Windows users only",
    "2005-11-18: version 2.0: (at that time called) 'Beerwanter 2' was programmed after the success of BeerWanter 1.0. The game was made tougher",
    "2005-11-22: version 3.0: (at that time called) 'Beerwanter 3' was programmed after the success of BeerWanter 2.0. The game was made even tougher",
    "2010-06-23: version 4.0: port code to Qt Creator, BeerWanter is now cross-platform. The game its name is changed back to 'BeerWanter'",
    "2010-06-24: version 5.0: improved the GUI, changed the beer sprite to an adaptation of my favorite beer",
    "2010-10-10: version 5.1: (temporary NDS-only fork) start of port to NDS",
    "2010-10-11: version 5.2: BeerWanter is one project again and build for NDS, Ubuntu and Windows",
    "2010-12-19: version 6.0: seperated project files for NDS, Ubuntu and Windows development. Preparation for seperating game logic from GUI",
    "2010-12-23: version 6.1: added ClickWilBeSuccess method, fixed bug in BeerWanterMainDialog::ShakeWindow",
    "2012-03-06: version 7.0: added menu, conformized project architecture for ProjectRichelBilderbeek",
    "2013-07-13: version 7.1: added libcvautomation script to beat the game, improved desktop menu and about screen",
    "2014-01-16: version 7.2: added command line command 'show'"
  };
}

#ifndef NDEBUG
void ribi::BeerWanterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Main dialog
  {
    const int screen_width = 640;
    const int screen_height = 400;
    const int sprite_width = 32;
    const int sprite_height = 48;
    const int window_width = 320;
    const int window_height = 200;

    BeerWanterMainDialog(
      screen_width,
      screen_height,
      sprite_width,
      sprite_height,
      window_width,
      window_height
    );
  }
  //Resources
  {
    const std::string filename { fileio::FileIo().GetTempFileName(".png") };
    QFile qfile(BeerWanterMainDialog::GetResourceFilename().c_str());
    qfile.copy(filename.c_str());
    assert(fileio::FileIo().IsRegularFile(filename)
      && "BeerWanter resource must exist");
    fileio::FileIo().DeleteFile(filename);
  }
}
#endif
