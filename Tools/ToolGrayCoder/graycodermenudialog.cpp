//---------------------------------------------------------------------------
/*
GrayCoder, tool to convert integers to and from Gray code
Copyright (C) 2009-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/ToolGrayCoder.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "graycodermenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "graycodermaindialog.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::GrayCoderMenuDialog::GrayCoderMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::GrayCoderMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  //User supplied binary or decimal value?
  for (int i=0; i!=argc-1; ++i) //-1 as the next argument is used
  {
    const std::string s = argv[i];
    if (s == "-d" || s == "--dec")
    {
      try
      {
        const int x = boost::lexical_cast<int>( argv[i + 1] );
        GrayCoderMainDialog d;
        d.SetNormalInt(x);
        std::cout << d << '\n';
        return 0;
      }
      catch(boost::bad_lexical_cast&)
      {
        std::cout << "Please supply a number as decimal value\n";
        return 1;
      }
    }
    if (s == "-b" || s == "--bin")
    {
      try
      {

        const int x = GrayCoderMainDialog::BitStringToInt( argv[i + 1] );
        GrayCoderMainDialog d;
        d.SetNormalInt(x);
        std::cout << d << '\n';
        return 0;
      }
      catch(std::logic_error&)
      {
        std::cout << "Please supply a binary number\n";
        return 1;
      }
    }
  }

  std::cout << GetHelp() << '\n';
  return 1;
}

ribi::About ribi::GrayCoderMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "GrayCoder",
    "tool to convert integers to and from Gray code",
    "the 30th of September 2013",
    "2009-2015",
    "http://www.richelbilderbeek.nl/ToolGrayCoder.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::GrayCoderMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('b',"bin","decimal number to be converted to/from Gray code"),
      Help::Option('d',"dec","decimal number to be converted to/from Gray code")
    },
    {
      "GrayCoder -d 123456",
      "GrayCoder -b 010101"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::GrayCoderMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramGrayCoder
  };
  assert(p);
  return p;
}


std::string ribi::GrayCoderMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

std::vector<std::string> ribi::GrayCoderMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2009-05-02: version 1.0: initial version in C++ Builder",
    "2013-08-26: version 2.0: port to Qt Creator console application",
    "2013-09-30: version 2.1: added desktop application",
    "2013-11-01: version 2.2: added console application",
  };
}

#ifndef NDEBUG
void ribi::GrayCoderMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  GrayCoderMainDialog(0);
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
