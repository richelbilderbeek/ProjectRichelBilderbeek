#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QApplication>

#include "newickvector.h"
#include "simplifynewickmaindialog.h"
#include "qtsimplifynewickmenudialog.h"
#include "simplifynewickmaindialog.h"
#include "newick.h"
#pragma GCC diagnostic pop

void ShowProgramUse()
{
  std::cout
    << "Invalid use of SimplifyNewick\n"
    << "\n"
    << "Correct use:\n"
    << "\n"
    << "SimplifyNewick\n"
    << "SimplifyNewick [phylogeny]\n"
    << "SimplifyNewick [phylogeny] [maximum complexity]\n"
    << "\n"
    << "Example uses:"
    << "  SimplifyNewick\n"
    << "    -> start GUI mode\n"
    << "  SimplifyNewick '(((10,10),10),10)'\n"
    << "    -> simplify this phylogeny once\n"
    << "  SimplifyNewick '(((10,10),10),10)' 100\n"
    << "    -> simplify this phylogeny until complexity is lower than 100\n"
    << "\n"
    << std::endl;
}

int main(int argc, char* argv[])
{
  if (argc==1)
  {
    QApplication a(argc, argv);
    ribi::QtToolSimplifyNewickMenuDialog d;
    d.show();
    return a.exec();
  }
  if (argc > 3)
  {
    ShowProgramUse();
    return 0;
  }
  try
  {
    const ribi::NewickVector n(argv[1]);
  }
  catch (std::exception& e)
  {
    std::cerr << "Invalid Newick: " << e.what() << '\n';
    return 1;
  }
  if (argc == 3)
  {
    try
    {
      const BigInteger i(boost::lexical_cast<int>(argv[2]));
      if (i <= 0)
      {
        std::cerr << "The value of complexity must be a positive integer\n";
        return 1;
      }
    }
    catch(std::exception&)
    {
      std::cerr << "The value of complexity must be an integer\n";
      return 1;
    }
  }
  //All is well
  #ifdef NDEBUG
  std::srand(std::time(0)); //RandomizeTimer();
  #endif

  const std::string s_in(argv[1]);
  const BigInteger max_complexity =
    (argc == 3
    ? BigInteger(boost::lexical_cast<int>(argv[2]))
    : ribi::Newick::CalcComplexity(ribi::NewickVector(s_in).Peek()) - 1);
  const std::string s_out
    = ribi::ToolSimplifyNewickMainDialog::SimplifyNewick(s_in,max_complexity);
  std::cout << s_out << '\n';
  return 0;
}

