#include "fisherwrightermenudialog.h"

#include <cassert>
#include <iostream>


#include "container.h"
#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#include "beast.h"
#include "counter.h"
#include "dna_r.h"
#include "ribi_rinside.h"
#include "phylogeny_r.h"
#include "newickutils.h"

ribi::fw::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::fw::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::fw::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "FisherWrighter",
    "does a Fisher-Wright simulation",
    "on the 13th of June 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/ToolFisherWrighter.htm",
    GetVersion(),
    GetVersionHistory()
  );

  a.AddLibrary("BeastR version: " + ribi::Beast().GetVersion());
  a.AddLibrary("Container version: " + ribi::Container().GetVersion());
  a.AddLibrary("Counter version: " + ribi::Counter().GetVersion());
  a.AddLibrary("DnaR version: " + ribi::DnaR().GetVersion());
  a.AddLibrary("FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("NewickUtils version: " + ribi::NewickUtils().GetVersion());
  a.AddLibrary("PhylogenyR version: " + ribi::PhylogenyR().GetVersion());
  a.AddLibrary("Rinside version: " + ribi::Rinside().GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::fw::MenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::fw::MenuDialog::GetProgram() const noexcept
{
  boost::shared_ptr<const ribi::Program> p {
    new ribi::ProgramFisherWrighter
  };
  assert(p);
  return p;
}

std::string ribi::fw::MenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::fw::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-06-13: version 1.0: started versioning",
  };
}

#ifndef NDEBUG
void ribi::fw::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    MenuDialog().GetAbout();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);

}
#endif
