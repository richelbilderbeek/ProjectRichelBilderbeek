//---------------------------------------------------------------------------
/*
TestFunctionParser, tool to demonstrate Warp's FunctionParser class
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestFunctionParser.htm
//---------------------------------------------------------------------------
#include "testfunctionparsermenudialog.h"

#include <cassert>
#include <iostream>

#include "fparser.hh"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::TestFunctionParserMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestFunctionParserMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestFunctionParser",
    "tool to demonstrate Warp's FunctionParser class",
    "the 3rd of Januari 2015",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolTestFunctionParser.htm",
    GetVersion(),
    GetVersionHistory());
  #ifdef _WIN32
  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  #else
  a.AddLibrary("Warp's FunctionParser version: 4.5.1");
  #endif
  return a;
}

ribi::Help ribi::TestFunctionParserMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestFunctionParserMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestFunctionParser
  };
  assert(p);
  return p;
}
std::string ribi::TestFunctionParserMenuDialog::GetVersion() const noexcept
{
  return "2.6";
}

std::vector<std::string> ribi::TestFunctionParserMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-02-02: Version 1.0: initial C++ Builder desktop version",
    "2011-06-24: Version 2.0: port to Qt Creator desktop version",
    "2011-06-24: Version 2.1: added web version",
    "2011-08-31: Version 2.2: added image to Welcome to web version",
    "2013-04-22: Version 2.3: added image to Welcome to desktop version",
    "2013-11-05: version 2.4: conformized for ProjectRichelBilderbeekConsole",
    "2014-07-04: version 2.5: added console version",
    "2015-01-03: version 2.6: set locale to English in Desktop version" //SET_LOCALE_TO_ENGLISH_QTTESTFUNCTIONPARSERMAINDIALOG
  };
}

#ifndef NDEBUG
void ribi::TestFunctionParserMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Test the parsing of the FunctionParser
  {
    FunctionParser f;
    f.Parse("sin(x)","x");
    assert(f.GetParseErrorType() == FunctionParser::FP_NO_ERROR);
  }
  {
    FunctionParser f;
    f.Parse("0.0","x");
    assert(f.GetParseErrorType() == FunctionParser::FP_NO_ERROR);
  }
  {
    FunctionParser f;
    f.Parse("0,0","x"); //Dutch, should fail!
    assert(f.GetParseErrorType() != FunctionParser::FP_NO_ERROR);
  }
}
#endif
