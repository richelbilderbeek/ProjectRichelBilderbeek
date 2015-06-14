#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testmultivectormenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/units/unit.hpp>
#include <boost/units/systems/si.hpp>

#include "multivector.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

#pragma GCC diagnostic pop

ribi::TestMultiVectorMenuDialog::TestMultiVectorMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestMultiVectorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::TestMultiVectorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ToolTestMultiVector",
    "tests the MultiVector class",
    "the 14th of June 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolTestMultiVector.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("MultiVector version: " + MultiVector<int>::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestMultiVectorMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestMultiVectorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestMultiVector
  };
  assert(p);
  return p;
}

std::string ribi::TestMultiVectorMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::TestMultiVectorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-06-14: version 1.0: initial versioning",
  };
}

#ifndef NDEBUG
void ribi::TestMultiVectorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    TestMultiVector();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
