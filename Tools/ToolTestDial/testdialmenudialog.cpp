//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestDial.htm
//---------------------------------------------------------------------------
#include "testdialmenudialog.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/date_time/posix_time/posix_time.hpp>

#include "dial.h"
#include "dialwidget.h"
#include "drawcanvas.h"
#include "richelbilderbeekprogram.h"
#include "textcanvas.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

int ribi::TestDialMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  //Get the local time
  boost::posix_time::ptime now
    = boost::posix_time::second_clock::local_time();
  //Convert the time to std::stringstream
  std::stringstream s;
  s << now.time_of_day();
  const std::string t { s.str() };

  //Read the number of hours
  int hour = 0;
  try
  {
    const int first_digit { boost::lexical_cast<unsigned char,int>(t[0]) };
    hour = first_digit;
    const int second_digit { boost::lexical_cast<unsigned char,int>(t[1]) };
    hour = (10*first_digit) + second_digit;
  }
  catch (boost::bad_lexical_cast&)
  {
  }

  //Set the position like a clock would
  const double position = static_cast<double>(hour % 12) / 12.0;

  const boost::shared_ptr<DialWidget> widget(
    new DialWidget(position)
  );


  std::cout << (*widget->ToTextCanvas(10)) << '\n';
  {
    const boost::shared_ptr<ribi::DrawCanvas> canvas {
      widget->ToDrawCanvas(10)
    };
    canvas->SetColorSystem(CanvasColorSystem::invert);
    std::cout << (*canvas) << '\n';
  }
  std::cout << "Current time: " << t << std::endl;
  return 0;
}

ribi::About ribi::TestDialMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestDial",
    "tool to test the Dial and DialWidget classes",
    "the 17th of January 2014",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestDial.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("Dial version: " + Dial::GetVersion());
  a.AddLibrary("DialWidget version: " + DialWidget::GetVersion());
  a.AddLibrary("TextCanvas version: " + TextCanvas::GetVersion());
  return a;
}

ribi::Help ribi::TestDialMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestDialMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestDial
  };
  assert(p);
  return p;
}

std::string ribi::TestDialMenuDialog::GetVersion() const noexcept
{
  return "2.3";
}

std::vector<std::string> ribi::TestDialMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-04-11: Version 1.0: initial version, web version not yet working",
    "2011-04-11: Version 1.1: got the web version working",
    "2011-06-27: Version 1.2: split up logic and graphics of user interfaces",
    "2011-07-16: Version 1.3: updated to new Dial version",
    "2011-08-07: Version 2.0: conformized architure for MysteryMachine",
    "2011-08-31: Version 2.1: added more testing option, added image to Welcome page of website version",
    "2013-11-05: version 2.2: conformized for ProjectRichelBilderbeekConsole",
    "2014-01-17: version 2.3: added displayal as text in desktop application"
  };
}

#ifndef NDEBUG
void ribi::TestDialMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    const boost::shared_ptr<DialWidget> dial(
      new DialWidget
    );
    assert(dial->GetDial());
  }
}
#endif
