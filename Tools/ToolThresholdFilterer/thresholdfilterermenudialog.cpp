#include "thresholdfilterermenudialog.h"

#include <cassert>
#include <iostream>

#include "trace.h"

int ribi::ThresholdFiltererMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::ThresholdFiltererMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ThresholdFilterer",
    "tool to pixelate image",
    "the 28th of November 2013",
    "2008-2013",
    "http://www.richelbilderbeek.nl/ToolThresholdFilterer.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

const ribi::Help ribi::ThresholdFiltererMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::ThresholdFiltererMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramThresholdFilterer
  };
  assert(p);
  return p;
}

const std::string ribi::ThresholdFiltererMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::ThresholdFiltererMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2008-03-01: version 1.0: initial Windows-only version",
    "2013-11-28: version 2.0: port to Qt"
  };
}

#ifndef NDEBUG
void ribi::ThresholdFiltererMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ThresholdFiltererMenuDialog::Test");
  TRACE("Finished ribi::ThresholdFiltererMenuDialog::Test successfully");
}
#endif
