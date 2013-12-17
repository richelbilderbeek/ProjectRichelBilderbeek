#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testreversimenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include "reversi.h"
#include "testreversimaindialog.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TestReversiMenuDialog::TestReversiMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestReversiMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc != 1 )
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  TestReversiMainDialog d;
  d.Execute();
  return 0;
}

const ribi::About ribi::TestReversiMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestReversi",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/ToolTestReversi.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Reversi version: " + Reversi::GetVersion());
  return a;
}

const boost::shared_ptr<const ribi::Program> ribi::TestReversiMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramTestReversi);
  assert(p);
  return p;
}

const std::string ribi::TestReversiMenuDialog::GetVersion() const noexcept
{
  return "5.2";
}

const std::vector<std::string> ribi::TestReversiMenuDialog::GetVersionHistory() const noexcept
{
  return {
    //"2006-12-13: Version 1.0: initial C++ Builder version, called 'TestReversi'",
  };
}

const ribi::Help ribi::TestReversiMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "TestReversi",
    "Tool to test the reversi classes",
    {
    },
    {
    }
  );
}

#ifndef NDEBUG
void ribi::TestReversiMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestReversiMenuDialog::Test()");
  TRACE("Finished ribi::TestReversiMenuDialog::Test()");
}
#endif
