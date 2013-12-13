#include "k3opeenrijmenudialog.h"

#include <cassert>
#include <iostream>

#include "connectthree.h"
#include "connectthreewidget.h"
#include "trace.h"

int ribi::K3OpEenRijMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::K3OpEenRijMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "K3OpEenRij",
    "K3-themed connect-three game",
    "the 6th of August 2013",
    "2007-2013",
    "http://www.richelbilderbeek.nl/GameK3OpEenRij.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("ConnectThree version: " + ConnectThree::GetVersion());
  a.AddLibrary("ConnectThreeWidget version: " + ConnectThreeWidget::GetVersion());
  a.AddLibrary("Special thanks to Mark Wiering for his excellent bug reports");
  return a;
}

const ribi::Help ribi::K3OpEenRijMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::K3OpEenRijMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramK3OpEenRij
  };
  assert(p);
  return p;
}

const std::string ribi::K3OpEenRijMenuDialog::GetVersion() const noexcept
{
  return "6.0";
}

const std::vector<std::string> ribi::K3OpEenRijMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-01-03: version 3.0: initial C++ Builder verion",
    "2009-12-31: version 4.0: replaced Kathleen by Josje, game arena always visible, made screens smaller, removed useless JPEGs",
    "2013-08-06: version 5.0: port to Qt Creator",
    "2013-08-06: version 5.1: allow selection of both Kathleen and Josje",
    "2013-08-09: version 6.0: implemented suggestions and bugfixes from Mark Wiering's report"
  };
}

#ifndef NDEBUG
void ribi::K3OpEenRijMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::K3OpEenRijMenuDialog::Test");
  TRACE("Finished ribi::K3OpEenRijMenuDialog::Test successfully");
}
#endif
