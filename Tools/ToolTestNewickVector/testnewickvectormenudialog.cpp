#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testnewickvectormenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QFile>

#include "binarynewickvector.h"
#include "newick.h"
#include "fileio.h"
#include "richelbilderbeekprogram.h"
#include "newickvector.h"
#include "testnewickvectordialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::TestNewickVectorMenuDialog::TestNewickVectorMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestNewickVectorMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc > 0) //Always
  {
    std::cout << GetHelp() << '\n';
    return 0;
  }
  return 0;
}

ribi::About ribi::TestNewickVectorMenuDialog::GetAbout() const noexcept
{
  About about(
    "Richel Bilderbeek",
    "TestNewickVector",
    "tool to test the NewickVector class",
    "at the 25th of April 2011",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestNewickVector.htm",
    GetVersion(),
    GetVersionHistory());
  about.AddLibrary("BigInt: version 2010.04.30");
  about.AddLibrary("BinaryNewickVector: " + BinaryNewickVector::GetVersion());
  about.AddLibrary("NewickVector: " + NewickVector::GetVersion());
  return about;
}

std::string ribi::TestNewickVectorMenuDialog::GetVersion() const noexcept
{
  return "3.2";
}

std::vector<std::string> ribi::TestNewickVectorMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-02-20: Version 1.0: initial version",
    "2011-03-09: Version 2.0: calculates Newick probabilities",
    "2011-03-26: Version 3.0: seperated GUI from logic, added web version",
    "2011-04-25: Version 3.1: removed web version\'s Close button",
    "2011-06-07: Version 3.2: added command-line call",
    "2015-06-14: Version 3.3: created menu dialog for conforming to ProjectRichelBilderbeek"
  };
}

ribi::Help ribi::TestNewickVectorMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      //No additional options
    },
    {
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestNewickVectorMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p(new ProgramTestNewickVector);
  assert(p);
  return p;
}

#ifndef NDEBUG
void ribi::TestNewickVectorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    fileio::FileIo();
    Newick().Test();
    BinaryNewickVector::Test();
    TestNewickVectorDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
