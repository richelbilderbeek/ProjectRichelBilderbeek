#include "testconceptmapmenudialog.h"

#include <cassert>
#include <iostream>


#include "conceptmap.h"
#include "conceptmapfactory.h"

#include "container.h"
#include "fileio.h"
#include "geometry.h"
#include "plane.h"
#include "ribi_regex.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

ribi::TestConceptMapMenuDialog::TestConceptMapMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestConceptMapMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestConceptMapMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestConceptMap",
    "tests the ConceptMap classes",
    "on the 7th of August 2014",
    "2013-2015",
    "http://www.richelbilderbeek.nl/ToolTestConceptMap.htm",
    GetVersion(),
    GetVersionHistory());

  a.AddLibrary("apfloat version: 2.4.1");
  a.AddLibrary("ConceptMap version: " + ribi::cmap::ConceptMap::GetVersion());
  a.AddLibrary("Container version: " + ribi::Container().GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("Geometry version: " + Geometry().GetVersion());
  a.AddLibrary("ribi::Regex version: " + Regex().GetVersion());
  a.AddLibrary("Plane version: " + Plane::GetVersion());
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());

  return a;
}

ribi::Help ribi::TestConceptMapMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestConceptMapMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestConceptMap
  };
  assert(p);
  return p;
}

std::string ribi::TestConceptMapMenuDialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::TestConceptMapMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-12-03: version 1.0: initial version",
    "2014-05-18: version 1.1: added testing Example",
    "2014-08-07: version 1.2: increased use of TDD"
  };
}

#ifndef NDEBUG
void ribi::TestConceptMapMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  ribi::cmap::ConceptMapFactory();
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //No test
}
#endif
