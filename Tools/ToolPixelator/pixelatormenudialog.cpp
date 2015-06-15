#include "pixelatormenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

int ribi::PixelatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  return 0;
}

ribi::About ribi::PixelatorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Pixelator",
    "tool to pixelate image",
    "the 28th of November 2013",
    "2008-2015",
    "http://www.richelbilderbeek.nl/ToolPixelator.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::PixelatorMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::PixelatorMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramPixelator
  };
  assert(p);
  return p;
}

std::string ribi::PixelatorMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::PixelatorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2008-03-01: version 1.0: initial Windows-only version",
    "2013-11-28: version 2.0: port to Qt"
  };
}

#ifndef NDEBUG
void ribi::PixelatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
