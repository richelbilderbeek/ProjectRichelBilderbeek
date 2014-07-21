#include "testconceptmapmenudialog.h"

#include <cassert>
#include <iostream>

//#include "qtrateconceptmap.h"
#include "container.h"
#include "fileio.h"
#include "ribi_regex.h"
#include "conceptmap.h"
#include "conceptmapwidget.h"
#include "richelbilderbeekprogram.h"
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
    "on the 18th of May 2014",
    "2013-2014",
    "http://www.richelbilderbeek.nl/ToolTestConceptMap.htm",
    GetVersion(),
    GetVersionHistory());

  a.AddLibrary("apfloat version: 2.4.1");
  a.AddLibrary("ConceptMap version: " + ribi::cmap::ConceptMap::GetVersion());
  a.AddLibrary("ConceptMapWidget version: " + cmap::Widget().GetVersion());
  a.AddLibrary("Container version: " + ribi::Container().GetVersion());
  a.AddLibrary("FileIo version: " + ribi::fileio::FileIo().GetVersion());
  a.AddLibrary("ribi::Regex version: " + ribi::Regex::GetVersion());
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
  return "1.1";
}

std::vector<std::string> ribi::TestConceptMapMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-12-03: version 1.0: initial version",
    "2014-05-18: version 1.1: added testing Example"
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
  TRACE("Started ribi::TestConceptMapMenuDialog::Test");
  ribi::cmap::Widget();
  TRACE("ribi::TestConceptMapMenuDialog finished successfully");
}
#endif
