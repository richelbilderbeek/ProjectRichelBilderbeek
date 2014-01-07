#include "functionplottermenudialog.h"

#include <iostream>

#include "profile.h"
#include "trace.h"

int ribi::FunctionPlotterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::FunctionPlotterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "FunctionPlotter",
    "plots a function",
    "the 5th of December 2013",
    "2013-2014",
    "http://www.richelbilderbeek.nl/FunctionPlotter.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("Rectangle version: " + Rect::GetVersion());

  a.AddLibrary("Warp's FunctionParser version: 4.4.3");
  return a;
}

const ribi::Help ribi::FunctionPlotterMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::FunctionPlotterMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramFunctionPlotter
  };
  assert(p);
  return p;
}

const std::string ribi::FunctionPlotterMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::FunctionPlotterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-xx-xx: version 1.0: initial Windows-only version",
    "2010-xx-xx: version 1.1: added integration",
    "2013-12-05: version 2.0: port to Qt"
  };
}

#ifndef NDEBUG
void ribi::FunctionPlotterMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::FunctionPlotterMenuDialog::Test");
  TRACE("Finished ribi::FunctionPlotterMenuDialog::Test successfully");
}
#endif
