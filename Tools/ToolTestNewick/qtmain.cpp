//---------------------------------------------------------------------------
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
//---------------------------------------------------------------------------
#include <QApplication>
//---------------------------------------------------------------------------
#include "newick.h"
#include "qttestnewickdialog.h"
#include "testnewick.h"
#include "testnewickdialog.h"
#include "trace.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  START_TRACE();
  if (argc == 1)
  {
    QApplication a(argc, argv);
    QtTestNewickDialog w;
    w.show();
    return a.exec();
  }
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
               TestNewick::m_flag_two_digit_newick
             | TestNewick::m_flag_newick_vector)),
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
      = TestNewickDialog::GetAbout().CreateAboutText();
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
      << TestNewick::m_flag_binary_newick_vector << ": BinaryNewickVector\n"
      << TestNewick::m_flag_many_digit_newick << ": ManyDigitNewick\n"
      << TestNewick::m_flag_newick_vector << ": NewickVector (*)\n"
      << TestNewick::m_flag_ravindran << ": Ravindran\n"
      << TestNewick::m_flag_sorted_binary_newick_vector << ": SortedBinaryNewickVector\n"
      << TestNewick::m_flag_two_digit_newick << ": TwoDigitNewick (**)\n"
      << TestNewick::m_flag_all << ": All\n"
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
      = TestNewickDialog::GetAbout().CreateLicenceText();
    std::copy(
      v.begin(),
      v.end(),
      std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }
  if (m.count("v") || m.count("version"))
  {
    const std::vector<std::string> v
      = TestNewickDialog::GetVersionHistory();
    std::copy(
      v.begin(),
      v.end(),
      std::ostream_iterator<std::string>(std::cout,"\n"));
    return 0;
  }

  if (!Newick::IsNewick(newick_str))
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
  TestNewickDialog dialog(
      TestNewick::m_flag_two_digit_newick
    | TestNewick::m_flag_newick_vector);
  dialog.DoCalculate(newick_str,theta_str);
  //Display the results
  std::copy(
    dialog.GetTable().begin(),
    dialog.GetTable().end(),
    std::ostream_iterator<TestNewickResult>(std::cout,"\n"));


}
//---------------------------------------------------------------------------

