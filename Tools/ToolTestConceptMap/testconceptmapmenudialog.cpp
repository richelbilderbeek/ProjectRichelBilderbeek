#include "testconceptmapmenudialog.h"

#include <cassert>
#include <iostream>

//#include "qtconceptmapratewidget.h"

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

const ribi::About ribi::TestConceptMapMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestConceptMap",
    "tests the ConceptMap classes",
    "on the 3rd of December 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolTestConceptMap.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtConceptMap version: " + cmap::QtConceptMap::GetVersion());
  //a.AddLibrary("Test image from http://sipi.usc.edu");

  return a;
}

const ribi::Help ribi::TestConceptMapMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::TestConceptMapMenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramTestConceptMap
  };
  assert(p);
  return p;
}

const std::string ribi::TestConceptMapMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::TestConceptMapMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-12-03: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::TestConceptMapMenuDialog::Test() noexcept
{

}
#endif
