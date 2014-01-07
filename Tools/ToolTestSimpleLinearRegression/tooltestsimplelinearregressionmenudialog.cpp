#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "tooltestsimplelinearregressionmenudialog.h"

#include <cassert>
#include <iostream>

#include "simplelinearregression.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::ToolTestSimpleLinearRegressionMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

const ribi::About ribi::ToolTestSimpleLinearRegressionMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolTestSimpleLinearRegression",
    "tests a simple linear regression",
    "the 28th of August 2013",
    "2013-2014",
    "http://www.richelbilderbeek.nl/ToolTestSimpleLinearRegression.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("SimpleLinearRegression version: " + SimpleLinearRegression::GetVersion());
  return a;
}

const ribi::Help ribi::ToolTestSimpleLinearRegressionMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::ToolTestSimpleLinearRegressionMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestSimpleLinearRegression
  };
  assert(p);
  return p;
}

const std::string ribi::ToolTestSimpleLinearRegressionMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::ToolTestSimpleLinearRegressionMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-08-27: version 1.0: initial version",
    "2013-08-28: version 1.1: isolated and templated SimpleLinearRegression class",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::ToolTestSimpleLinearRegressionMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::ToolTestSimpleLinearRegressionMenuDialog::Test");
  TRACE("Finished ribi::ToolTestSimpleLinearRegressionMenuDialog::Test successfully");
}
#endif
