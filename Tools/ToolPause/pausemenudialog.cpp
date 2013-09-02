//---------------------------------------------------------------------------
/*
Pause, tool to do nothing
Copyright (C) 2010-2013 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolPause.htm
//---------------------------------------------------------------------------
//#include header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "pausemenudialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>
#pragma GCC diagnostic pop

void PauseMenuDialog::Execute(const int argc, const char * const argv[])
{
  assert(argc >= 1);
  if (argc == 1)
  {
    Wait(10.0);
  }
  else
  {
    try
    {
      const double t = boost::lexical_cast<double>(argv[1]);
      Wait(t);
    }
    catch (boost::bad_lexical_cast&)
    {
      Wait(10.0);
    }
  }
}

const About PauseMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "Pause",
    "tool to do nothing",
    "the 25th of May 2013",
    "2010-2012",
    "http://www.richelbilderbeek.nl/ToolPause.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("AsciiArter version: " + AsciiArter::GetVersion());
  return a;
}

const std::string PauseMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> PauseMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-xx-xx: Version 1.0: initial version");
  v.push_back("2013-05-25: Version 1.1: added menu, conformized towards ProjectRichelBilderbeek");
  return v;
}

void PauseMenuDialog::Wait(const double n_secs)
{
  boost::timer t;
  while (t.elapsed() < n_secs) {}
}
