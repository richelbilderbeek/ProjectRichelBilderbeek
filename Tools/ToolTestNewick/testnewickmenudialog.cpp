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
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"

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
  /*


  // Declare the supported options.
  boost::program_options::options_description d(
    "Allowed options for TestNewick");
  std::string newick_str;
  std::string theta_str;
  std::string types_str;
  d.add_options()
      ("about,a",
        "shows the about information")
      ("help,h",
        "produce this help message")
      ("typeinfo,i",
        "Shows help about the types of algorithms")
      ("licence,l",
        "Shows this program's licence")
      ("version,v",
        "shows the version number")
      ("newick",
         boost::program_options::value<std::string>(&newick_str)->default_value("((2,2),2)"),
         "phylogeny in Newick format")
      ("theta",
         boost::program_options::value<std::string>(&theta_str)->default_value(
           boost::lexical_cast<std::string>(10.0)),
         "mutation parameter")
      ("types",
         boost::program_options::value<std::string>(&types_str)->default_value(
           boost::lexical_cast<std::string>(
               ribi::TestNewick::m_flag_two_digit_newick
             | ribi::TestNewick::m_flag_newick_vector)),
         "types of algorithms used")
      ;

  boost::program_options::variables_map m;
  boost::program_options::store(
    boost::program_options::parse_command_line(
      argc, argv, d), m);
  boost::program_options::notify(m);

  if (m.count("a") || m.count("about"))
  {
    const std::vector<std::string> v
      = ribi::TestNewickDialog::GetAbout().CreateAboutText();
    std::copy(
      v.begin(),
      v.end(),
      std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  if (m.count("h") || m.count("help"))
  {
    //Display the options_description
    std::cout << d << "\n";
    return 0;
  }
  if (m.count("i") || m.count("typeinfo"))
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
      << "Multiple algorithms can be run sequentially by adding these values";
    return 0;
  }
  if (m.count("l") || m.count("licence"))
  {
    const std::vector<std::string> v
      = ribi::TestNewickDialog::GetAbout().CreateLicenceText();
    std::copy(
      v.begin(),
      v.end(),
      std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  if (m.count("v") || m.count("version"))
  {
    const std::vector<std::string> v
      = ribi::TestNewickDialog::GetVersionHistory();
    std::copy(
      v.begin(),
      v.end(),
      std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }

  if (!ribi::Newick::IsNewick(newick_str))
  {
    std::cout << "Invalid phylogeny\n";
    return 1;
  }
  try
  {
    boost::lexical_cast<double>(theta_str);
  }
  catch(boost::bad_lexical_cast&)
  {
    std::cout << "Invalid theta\n";
    return 1;
  }
  ribi::TestNewickDialog dialog(
      ribi::TestNewick::m_flag_two_digit_newick
    | ribi::TestNewick::m_flag_newick_vector);
  dialog.DoCalculate(newick_str,theta_str);
  //Display the results
  std::copy(
    dialog.GetTable().begin(),
    dialog.GetTable().end(),
    std::ostream_iterator<TestNewickResult>(std::cout,"\n"));


  */

  return 1;
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
    TestMultiVector();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
