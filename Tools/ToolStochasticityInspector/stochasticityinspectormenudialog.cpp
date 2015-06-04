#include "stochasticityinspectormenudialog.h"

#include <cassert>
#include <iostream>

#include "brownianmotionprocess.h"
#include "ornsteinuhlenbeckprocess.h"
#include "richelbilderbeekprogram.h"
#include "stochasticityinspectormaindialog.h"
#include "trace.h"
#include "testtimer.h"

int ribi::StochasticityInspectorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::StochasticityInspectorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "StochasticityInspector",
    "tool to inspect stochasticity",
    "the 26th of May 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolStochasticityInspector.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::StochasticityInspectorMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::StochasticityInspectorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramStochasticityInspector
  };
  assert(p);
  return p;
}

std::string ribi::StochasticityInspectorMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::StochasticityInspectorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-05-26: version 1.0: initial version",
  };
}

#ifndef NDEBUG
void ribi::StochasticityInspectorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::bm::Process::Test();
    ribi::ou::Process::Test();
    StochasticityInspectorMainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
