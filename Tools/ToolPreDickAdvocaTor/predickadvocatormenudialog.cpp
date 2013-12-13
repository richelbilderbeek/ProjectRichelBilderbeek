#include "predickadvocatormenudialog.h"

#include <cassert>
#include <iostream>

#include "trace.h"

int ribi::PreDickAdvocaTorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::PreDickAdvocaTorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PreDickAdvocaTor",
    "tool to correctly predict WC scores", //if the lucky number is correct and the truth becomes reality
    "the 3rd of December 2013",
    "20010-2013",
    "http://www.richelbilderbeek.nl/ToolPreDickAdvocaTor.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("ProFile version: " + QtCreatorProFile::GetVersion());
  return a;
}

const ribi::Help ribi::PreDickAdvocaTorMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::PreDickAdvocaTorMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramPreDickAdvocaTor
  };
  assert(p);
  return p;
}

const std::string ribi::PreDickAdvocaTorMenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::PreDickAdvocaTorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-xx-xx: version 1.0: initial version",
    "2013-12-03: version 2.0: improved user experience, prepare for next WC"
  };
}

#ifndef NDEBUG
void ribi::PreDickAdvocaTorMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PreDickAdvocaTorMenuDialog::Test");
  TRACE("Finished ribi::PreDickAdvocaTorMenuDialog::Test successfully");
}
#endif
