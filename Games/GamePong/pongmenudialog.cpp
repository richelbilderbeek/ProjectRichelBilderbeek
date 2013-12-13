#include "pongmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "trace.h"

int ribi::PongMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  std::cout
    << this->GetAbout().GetFileTitle() << " cannot be run in console mode\n"
    << std::endl;
  return 0;
}

const ribi::About ribi::PongMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Pong",
    "Pong clone",
    "today",
    "2013-x",
    "http://www.richelbilderbeek.nl/GamePong.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::PongMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::PongMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramPong
  };
  assert(p);
  return p;
}

const std::string ribi::PongMenuDialog::GetVersion() const noexcept
{
  return "0.1";
}

const std::vector<std::string> ribi::PongMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07: version 0.1: conformized to ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::PongMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PongMenuDialog::Test");
  TRACE("Finished ribi::PongMenuDialog::Test successfully");
}
#endif
