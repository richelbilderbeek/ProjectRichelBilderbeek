//---------------------------------------------------------------------------
/*
StaircaseCardCreator, tool to generate staircase cards
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolStaircaseCardCreator.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "staircasecardcreatormenudialog.h"

#include <algorithm>
#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/scoped_ptr.hpp>

#include <QImage>

#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "staircasecard.h"
#include "textcanvas.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::scc::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::scc::MenuDialog::ExecuteSpecific(const std::vector<std::string>& /* argv */) noexcept
{
  //const int argc = static_cast<int>(argv.size());
  {
    std::srand(std::time(0));
    boost::shared_ptr<StaircaseCard> card {
      new StaircaseCard(8,10)
    };
    card->ShuffleAesthetic();
    std::cout << (*card->ToTextCanvasCompact()) << '\n';
    std::cout << (*card->ToTextCanvas()) << '\n';
  }
  return 0;
}

ribi::About ribi::scc::MenuDialog::GetAbout() const noexcept
{
  ribi::About a {
    "Richel Bilderbeek",
    "StaircaseCardCreator",
    "tool to generate staircase cards",
    "the 6th of March 2014",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolStaircaseCardCreator.htm",
    GetVersion(),
    GetVersionHistory()
  };
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}


ribi::Help ribi::scc::MenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::scc::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramStaircaseCardCreator);
  assert(p);
  return p;
}

std::string ribi::scc::MenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::scc::MenuDialog::GetVersionHistory() const noexcept
{
  const std::vector<std::string> v {
    "2010-xx-xx: version 1.0: initial version",
    "2014-02-26: version 1.1: first versioning",
    "2014-03-06: version 1.2: added aesthetic functions"
  };
  return v;
}

#ifndef NDEBUG
void ribi::scc::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
