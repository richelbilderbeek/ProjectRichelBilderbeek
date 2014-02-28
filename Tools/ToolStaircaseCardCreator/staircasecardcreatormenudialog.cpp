#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "staircasecardcreatormenudialog.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/scoped_ptr.hpp>

#include "staircasecard.h"
#include "fileio.h"
#include "textcanvas.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::scc::StaircaseCardCreatorMenuDialog::StaircaseCardCreatorMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::scc::StaircaseCardCreatorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());

  boost::shared_ptr<StaircaseCard> card {
    new StaircaseCard(10,30)
  };
  std::cout << (*card->ToTextCanvasCompact()) << '\n';
  std::cout << '\n';
  std::cout << (*card->ToTextCanvas()) << '\n';
  return 0;
}

const ribi::About ribi::scc::StaircaseCardCreatorMenuDialog::GetAbout() const noexcept
{
  ribi::About a {
    "Richel Bilderbeek",
    "StaircaseCardCreator",
    "tool to generate staircase cards",
    "the 26th of Februari 2014",
    "2010-2014",
    "http://www.richelbilderbeek.nl/ToolStaircaseCardCreator.htm",
    GetVersion(),
    GetVersionHistory()
  };
  a.AddLibrary("FileIo version: " + fileio::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}


const ribi::Help ribi::scc::StaircaseCardCreatorMenuDialog::GetHelp() const noexcept
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

const boost::shared_ptr<const ribi::Program> ribi::scc::StaircaseCardCreatorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramStaircaseCardCreator);
  assert(p);
  return p;
}

const std::string ribi::scc::StaircaseCardCreatorMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::scc::StaircaseCardCreatorMenuDialog::GetVersionHistory() const noexcept
{
  const std::vector<std::string> v {
    "20xx-xx-xx: version 1.0: initial version",
    "2014-02-26: version 1.1: first versioning"
  };
  return v;
}

#ifndef NDEBUG
void ribi::scc::StaircaseCardCreatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::scc::StaircaseCardCreatorMenuDialog::Test()");
  TRACE("Finished ribi::scc::StaircaseCardCreatorMenuDialog::Test()");
}
#endif
