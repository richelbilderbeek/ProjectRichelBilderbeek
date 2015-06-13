#include "testtwodigitnewickmenudialog.h"

#include <cassert>
#include <iomanip>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "richelbilderbeekprogram.h"
#include "twodigitnewick.h"
#include "testtimer.h"
#include "newick.h"
#pragma GCC diagnostic pop

int ribi::TestTwoDigitNewickMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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
  if (argc != 3)
  {
    std::cout
      << "Incorrect number of arguments:\n"
      << '\n'
      << "No arguments: start GUI version:\n"
      << "  " << argv[0] << '\n'
      << "Two arguments: start command-line version:\n"
      << "  - newick\n"
      << "  - theta\n"
      << "  \'" << argv[0] << " (2,(2,2)) " << (5.0 / 2.0) << "\'\n";
    return 1;
  }
  const std::string newick = argv[1];
  if (!ribi::Newick().IsNewick(newick))
  {
    std::cout
      << "Invalid Newick format. Use for example:\n"
      << "  \'" << argv[0] << " (2,(2,2)) " << (5.0 / 2.0) << "\'\n";
    return 1;
  }
  try
  {
    boost::lexical_cast<double>(argv[2]);
  }
  catch (boost::bad_lexical_cast&)
  {
    std::cout
      << "Invalid theta format. Use for example:\n"
      << "  \'" << argv[0] << " (2,(2,2)) " << (5.0 / 2.0) << "\'\n";
    return 1;

  }
  const double theta = boost::lexical_cast<double>(argv[2]);
  const double p = ribi::TwoDigitNewick::CalculateProbability(newick,theta);
  std::cout << std::setprecision(99) << p << '\n';
  return 0;
}

ribi::About ribi::TestTwoDigitNewickMenuDialog::GetAbout() const noexcept
{
  return About(
    "Richel Bilderbeek",
    "TestTwoDigitNewick",
    "tool to test the two-digit-Newick architecture",
    "the 8th of March 2011",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick",
    GetVersion(),
    GetVersionHistory());
};


ribi::Help ribi::TestTwoDigitNewickMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestTwoDigitNewickMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramTestTwoDigitNewick
  };
  assert(p);
  return p;
}
std::string ribi::TestTwoDigitNewickMenuDialog::GetVersion() const noexcept
{
  return "2.2";
}

std::vector<std::string> ribi::TestTwoDigitNewickMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-08-22: version 0.1: initial version, only simple Newicks",
    "2010-08-23: version 0.2: added support for more complex newicks",
    "2010-08-23: version 0.3: complex newicks supported",
    "2010-08-24: version 0.4: improved architecture",
    "2010-08-25: version 0.5: cleaned up code",
    "2010-08-25: version 0.6: added Ewens probability for simple Newicks",
    "2010-09-03: version 0.7: all TwoDigitNewicks contain correct values of m_sum_above_zero and m_sum_above_one. NewickIndex contains a new method called ConstructNewick to reconstruct BinaryNewickVector from a TwoDigitNewick.",
    "2010-09-03: version 0.8: framework to get all TwoDigitNewicks' probabilities calculated is setup",
    "2010-09-03: version 0.8.1: bug-fix: probabilities of simple Newicks can be calculated from GUI",
    "2010-09-03: version 0.8.2: bug-fix: probabilities of Newicks with multiple complex branches can be calculated",
    "2010-09-04: version 0.9: TwoDigitNewick architecture is correctly built up",
    "2010-09-04: version 0.10: Project can be built differently in debug and release mode. Application can also be called with command-line parameters",
    "2010-09-04: version 0.11: bug-fix: the Newick '(1,(1,1))' now has its probability correctly calculated",
    "2010-09-05: version 1.0: initial release",
    "2010-10-02: version 1.1: application ports to Windows",
    "2011-02-20: version 2.0: major architectural change, removed use of CLN library",
    "2011-03-01: version 2.1: major changes in Newick namespace",
    "2011-03-08: version 2.2: minor changes in Newick namespace",
  };
}

#ifndef NDEBUG
void ribi::TestTwoDigitNewickMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
