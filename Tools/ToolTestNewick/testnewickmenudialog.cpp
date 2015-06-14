#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testnewickmenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/units/unit.hpp>
#include <boost/units/systems/si.hpp>

#include "multivector.h"
#include "newick.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"
#include "testnewick.h"
#include "testnewickdialog.h"
#pragma GCC diagnostic pop

ribi::TestNewickMenuDialog::TestNewickMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestNewickMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  for (int i=0; i!=argc-1; ++i) //-1 because the next argument will be used
  {
    if (argv[i] == "-f" || argv[i] == "--typeinfo")
    {
      std::cout
        << "Algorithm types:\n"
        << ribi::TestNewick::m_flag_binary_newick_vector << ": BinaryNewickVector\n"
        << ribi::TestNewick::m_flag_many_digit_newick << ": ManyDigitNewick\n"
        << ribi::TestNewick::m_flag_newick_vector << ": NewickVector (*)\n"
        << ribi::TestNewick::m_flag_sorted_binary_newick_vector << ": SortedBinaryNewickVector\n"
        << ribi::TestNewick::m_flag_two_digit_newick << ": TwoDigitNewick (**)\n"
        << ribi::TestNewick::m_flag_all << ": All\n"
        << '\n'
        << "(*) Recommended for unary and binary phylogenies\n"
        << "(**) Recommended for phylogenies of higher arities\n"
        << '\n'
        << "Multiple algorithms can be run sequentially by adding these values\n"
      ;
      return 0;
    }
  }

  //newick_str
  std::string newick_str{"((2,2),2)"};
  for (int i=0; i!=argc-1; ++i) //-1 because the next argument will be used
  {
    if (argv[i] == "-n" || argv[i] == "--newick")
    {
      newick_str = argv[i+1];
    }
  }

  if (!ribi::Newick().IsNewick(newick_str))
  {
    std::cout << "Invalid phylogeny\n";
    return 1;
  }

  double theta{0.0};
  for (int i=0; i!=argc-1; ++i) //-1 because the next argument will be used
  {
    if (argv[i] == "-e" || argv[i] == "--theta")
    {
      try
      {
        theta = std::stod(argv[i+1]);
      }
      catch (std::exception& e)
      {
        std::cout << "Please supply a floating point value value for theta";
        return 1;
      }
    }
  }
  if (theta <= 0.0)
  {
    std::cout << "Please supply a positive non-zero value value for theta";
    return 1;
  }

  ribi::TestNewickDialog dialog(
      ribi::TestNewick::m_flag_two_digit_newick
    | ribi::TestNewick::m_flag_newick_vector);
  dialog.DoCalculate(newick_str,theta);
  //Display the results
  std::copy(
    dialog.GetTable().begin(),
    dialog.GetTable().end(),
    std::ostream_iterator<TestNewickResult>(std::cout,"\n")
  );
  std::cout << std::endl;

  return 0;
}

ribi::About ribi::TestNewickMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestNewick",
    "tests the Newick classes",
    "the 14th of June 2015",
    "2015-2015",
    "http://www.richelbilderbeek.nl/TestNewick.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("MultiVector version: " + MultiVector<int>::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestNewickMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('f',"typeinfo","Shows help about the types of algorithms"),
      Help::Option('n',"newick","phylogeny in Newick format, default: '((2,2),2);'"),
      Help::Option('e',"theta","mution * population size"),
      Help::Option('t',"types","algorithms used")
    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestNewickMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestMultiVector
  };
  assert(p);
  return p;
}

std::string ribi::TestNewickMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::TestNewickMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2015-06-14: version 1.0: initial versioning",
  };
}

#ifndef NDEBUG
void ribi::TestNewickMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    NewickCpp98();
    Newick();
    TestNewickDialog();
    TestMultiVector();
    TestNewickMenuDialog().GetAbout();
  }
  const TestTimer test_timer(__func__,__FILE__,2.0);
  TestNewickMenuDialog().Execute( { "-e","1","-n","((2,2),2)"} );
}
#endif
