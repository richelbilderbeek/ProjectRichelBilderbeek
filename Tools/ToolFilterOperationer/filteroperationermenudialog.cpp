#include "filteroperationermenudialog.h"

#include <cassert>
#include <iostream>

#include "trace.h"

int ribi::FilterOperationerMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::FilterOperationerMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "FilterOperationer",
    "tool to perform image filter operations",
    "on the 29th of November 2013",
    "2008-2014",
    "http://www.richelbilderbeek.nl/ToolFilterOperationer.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  a.AddLibrary("Test image from http://sipi.usc.edu");

  return a;
}

const ribi::Help ribi::FilterOperationerMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::FilterOperationerMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramFilterOperationer
  };
  assert(p);
  return p;
}

const std::string ribi::FilterOperationerMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::FilterOperationerMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2008-xx-17: version 1.0: initial Windows-only version",
    "2013-11-29: version 2.0: port to Qt",
    "2013-12-19: version 2.1: allowed saving of images in desktop version"
  };
}

#ifndef NDEBUG
void ribi::FilterOperationerMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::FilterOperationerMenuDialog::Test");
  TRACE("Finished ribi::FilterOperationerMenuDialog::Test successfully");
}
#endif
