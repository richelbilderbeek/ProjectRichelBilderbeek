#include "testmanydigitnewickmenudialog.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "newickvector.h"
#include "manydigitnewick.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TestManyDigitNewickMenuDialog::TestManyDigitNewickMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestManyDigitNewickMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc > 3)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  return 0;
}

ribi::About ribi::TestManyDigitNewickMenuDialog::GetAbout() const noexcept
{
  About about(
    "Richel Bilderbeek",
    "TestManyDigitNewick",
    "tool to test the two-digit-Newick architecture",
    "the 8th of May 2014",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolTestManyDigitNewick",
    GetVersion(),
    GetVersionHistory());

  about.AddLibrary("BigInt: version 2010.04.30");
  about.AddLibrary("NewickVector: version " + NewickVector::GetVersion());
  about.AddLibrary("ManyDigitNewick: version " + ManyDigitNewick::GetVersion());
  return about;
}

ribi::Help ribi::TestManyDigitNewickMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestManyDigitNewickMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramTestManyDigitNewick
  };
  assert(p);
  return p;
}

std::string ribi::TestManyDigitNewickMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::TestManyDigitNewickMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-03-02: version 1.0: initial version copied and from TestTwoDigitNewick",
    "2014-05-08: version 1.1: conformized with ProjectRichelBilderbeek"
  };
}

#ifndef NDEBUG
void ribi::TestManyDigitNewickMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    NewickVector::Test();
    ManyDigitNewick();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
