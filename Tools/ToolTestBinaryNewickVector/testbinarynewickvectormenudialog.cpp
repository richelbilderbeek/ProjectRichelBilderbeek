#include "testbinarynewickvectormenudialog.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "binarynewickvector.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::TestBinaryNewickVectorMenuDialog::TestBinaryNewickVectorMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestBinaryNewickVectorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestBinaryNewickVectorMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestBinaryNewickVector",
    "GUI tool to test BinaryNewickVector",
    "the 6th of December 2013",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolTestBinaryNewickVector.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("BigInt: version 2010.04.30");
  a.AddLibrary("BinaryNewickVector: " + BinaryNewickVector::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestBinaryNewickVectorMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      //Options
    },
    {
      //Example uses
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestBinaryNewickVectorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramTestBinaryNewickVector);
  assert(p);
  return p;
}

std::string ribi::TestBinaryNewickVectorMenuDialog::GetVersion() const noexcept
{
  return "3.2";
}

std::vector<std::string> ribi::TestBinaryNewickVectorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-08-20: Version 1.0: initial version, tool was called TestNewickVector",
    "2010-08-21: Version 1.1: added more debug checks, added IsBinary,  GetSimpler and GetRootBranches",
    "2010-08-24: Version 1.2: calculates the total number of derived Newicks and (related to this) the number of symmetries in a Newick",
    "2010-08-25: Version 1.3: calculates the Ewens probability of simple Newicks",
    "2010-09-04: Version 1.4: '(1,(3))' is added to the set of invalid Newicks",
    "2010-09-16: Version 1.5: added library version numbers, created difference in debug and release version, fixed a bug in BinaryNewickVector::GetSimplerNewicks, added '(0)' to the set of invalid Newicks",
    "2010-10-01: Version 1.6: transition from CLN to BigInt library, so TestBinaryNewickVector can run under Windows. Kept checks comparing CLN and BigInt library in under Ubuntu",
    "2011-02-20: Version 2.0: major revision of architecture, removed use of CLN library, renamed program to TestBinaryNewickVector",
    "2011-03-01: Version 3.0: major rewrite of algorithms",
    "2011-03-08: Version 3.1: minor rewrite of algorithms",
    "2013-12-06: Version 3.2: conformized to ProjectRichelBilderbeek"
  };
}

#ifndef NDEBUG
void ribi::TestBinaryNewickVectorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    BinaryNewickVector::Test();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
