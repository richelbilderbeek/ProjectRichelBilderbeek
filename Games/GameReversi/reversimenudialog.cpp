#include "reversimenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "reversiboard.h"
#include "reversiwidget.h"
#include "reversimaindialog.h"
#include "trace.h"

int ribi::reversi::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  MainDialog d;
  d.Execute(4);
  return 0;
}

const ribi::About ribi::reversi::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Reversi",
    "Reversi clone",
    "today",
    "200x-2013",
    "http://www.richelbilderbeek.nl/GameReversi.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const ribi::Help ribi::reversi::MenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::reversi::MenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramReversi
  };
  assert(p);
  return p;
}

const std::string ribi::reversi::MenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::reversi::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-11-07-13: version 1.1: conformized to ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::reversi::MenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::reversi::MenuDialog::Test");
  MainDialog();
  Widget();
  Board();
  TRACE("Finished ribi::reversi::MenuDialog::Test successfully");
}
#endif
