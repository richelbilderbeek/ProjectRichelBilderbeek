#include "paperrockscissorsmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "trace.h"

int ribi::PaperRockScissorsMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::PaperRockScissorsMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PaperRockScissors",
    "",
    "",
    "",
    "http://www.richelbilderbeek.nl/GamePaperRockScissors.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::PaperRockScissorsMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::PaperRockScissorsMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramPaperRockScissors
  };
  assert(p);
  return p;
}

const std::string ribi::PaperRockScissorsMenuDialog::GetVersion() const noexcept
{
  return "0.1";
}

const std::vector<std::string> ribi::PaperRockScissorsMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-07-13: version 0.1: conformized to ProjectRichelBilderbeekConsoleS"
  };
}

#ifndef NDEBUG
void ribi::PaperRockScissorsMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PaperRockScissorsMenuDialog::Test");
  TRACE("Finished ribi::PaperRockScissorsMenuDialog::Test successfully");
}
#endif
