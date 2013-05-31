//---------------------------------------------------------------------------
/*
  The Rampal Etienne Project, calculates the probability of a phylogeny
  (C) 2009 Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <algorithm>
#include <cmath>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <QtGui/QApplication>
//---------------------------------------------------------------------------
#include "binarynewickvector.h"
#include "dialogrampaltest.h"
#include "newick.h"
#include "test.h"
//---------------------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetRandomUniform.htm
double GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------
template <typename T>
const T AskUserForInput()
{
  T t;
  std::getline(std::cin,t);
  return t;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppAskUserForDouble.htm
const std::string AskUserForNewick()
{
  while (1)
  {
    std::cout << "Please enter a newick or press enter to quit:\n";
    const std::string s = AskUserForInput<std::string>();
    if (s.empty()) return std::string();
    try
    {
      BinaryNewickVector n(s);
      return s;
    }
    catch(std::invalid_argument& e)
    {
      std::cout << "Invalid input: " << e.what() << "\n";
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppAskUserForDouble.htm
double AskUserForTheta()
{
  while (1)
  {
    std::cout << "Please enter a value for theta or press enter to quit:\n";
    const std::string s = AskUserForInput<std::string>();
    if (s.empty()) return 0.0;
    try
    {
      const double x = boost::lexical_cast<double>(s);
      if (x <= 0.0)
      {
        std::cout << "Theta must be a positive non-zero value\n";
        continue;
      }
      return x;
    }
    catch(...)
    {
      std::cout << "Theta must be a positive non-zero value\n";
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer()
{
  std::srand(std::time(0));
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppStrToLower.htm
const std::string StrToLower(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(),std::ptr_fun<int,int>(std::tolower));
  return s;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetPath.htm
//Returns the path, without a trailing backslash '\'
const std::string GetPath(const std::string& fileName)
{
  #ifndef USE_WINDOWS
  const int endOfPathIndex = fileName.rfind("/",fileName.size());
  #else
  const int endOfPathIndex = fileName.rfind("\\",fileName.size());
  #endif
  assert(endOfPathIndex < static_cast<int>(fileName.size()));
  return fileName.substr(0,endOfPathIndex);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetCurrentFolder.htm
const std::string GetCurrentFolder(const std::string& s)
{
  return GetPath(s);
}
//---------------------------------------------------------------------------
void ShowCorrectUse()
{
  std::cout
    << "Incorrect use of ProjectTestMain\n"
    << "\n"
    << "ProjectTestMain [theta input parameter] [newick input parameter] [test parameters]\n"
    << "\n"
    << "Theta input parameters: \n"
    << "  -any positive non-zero value, for example '10.0'\n"
    << "  -m: manual input of thetas\n"
    << "  -r: random theta\n"
    << "\n"
    << "Input parameters: \n"
    << "  -any newick string, for example '(1,(2,3))\n"
    << "  -m: manual input of newick strings\n"
    << "  -r: random newick strings\n"
    << "\n"
    << "Test parameters: \n"
    << " i &  1: use Ravindran\n"
    << " i &  2: use SortedNewick\n"
    << " i &  4: use SmartSortedNewick\n"
    << " i &  8: use RampalMain_Endversion2\n"
    << " i & 16: use TestTwoDigitNewickDebug\n"
    << " i & 32: use TestTwoDigitNewickRelease\n"
    << " 63: use all\n"
    << std::endl;
}
//---------------------------------------------------------------------------
///ProjectRampalTest is the testing facility of ProjectRampal.
///A newly developed brach of the project can be tested with
///this program in terms of obtaining the right output and speed.
///ProjectRampalTest forbids the use of a release mode,
///because its purpose is to test the code.
int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    QApplication a(argc, argv);
    DialogRampalTest d;
    d.show();
    return a.exec();
  }

  std::cout << GetCurrentFolder(argv[0]) << "/" << argv[0]
    << " (version 300.0)\n";
  #ifdef NDEBUG
    std::cout
      << "ProjectTest cannot be run in no-debug mode!\n"
      << "Please recompile without the NDEBUG #define"
      << std::endl;
    return 1;
  #endif

  if (argc!=4) { ShowCorrectUse(); return 0; }

  const std::string argv1 = StrToLower(argv[1]);
  const std::string argv2 = StrToLower(argv[2]);
  //Check if the fourth argument is an integer
  try
  {
    boost::lexical_cast<int>(argv[3]);
  }
  catch (boost::bad_lexical_cast&)
  {
    ShowCorrectUse();
    return 1;
  }
  const int argv3 = boost::lexical_cast<int>(argv[3]);
  //Test sanity of input
  //First parameter: theta
  {
    try { boost::lexical_cast<double>(argv1); } //Is it a double?
    catch(...)
    {
      if (argv1!="-m" && argv1!="-r") { ShowCorrectUse(); return 0; }
    }
  }
  //Second parameter: phylogeny
  {
    try { BinaryNewickVector n(argv2); } //Is it a newick?
    catch(...)
    {
      if (argv2!="-m" && argv2!="-r" ) { ShowCorrectUse(); return 0; }
    }
  }
  //Third parameter: test
  {
    if (argv3 <= 0 || argv3 > 63) { ShowCorrectUse(); return 0; }
  }
  //Input is sane

  RandomizeTimer();

  std::ofstream file("Results.txt");
  file << "Results of " << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << "\n";
  file.close();

  std::cout << std::setprecision(10);

  while (1)
  {
    //Obtain theta
    //Theta input parameters:
    // -any positive non-zero value, for example '10.0'
    // -f: theta values from file 'test_thetas.txt'
    // -m: manual input of thetas
    double theta = 0.0;
    if (argv1 == "-m")
    {
      theta = AskUserForTheta();
      if (theta==0.0) break;
    }
    else if (argv1 == "-r")
    {
      theta = GetRandomUniform() * 100.0;
    }
    else
    {
      theta = boost::lexical_cast<double>(argv1);
    }

    //Obtain newick
    std::string newick;
    //Input parameters:
    // -any newick string, for example '(1,(2,3))'
    // -m: manual input of newick strings
    // -p: predefined newick strings
    // -r: random newick strings
    if (argv2 == "-m")
    {
      newick = AskUserForNewick();
      if (newick.empty()) break;
    }
    else if (argv2 == "-r")
    {
      newick = Newick::CreateRandomNewick(7,7);
    }
    else
    {
      newick = argv2;
    }

    std::ofstream file("Results.txt", std::ios_base::app);
    file << std::setprecision(99);

    //Create all tests
    std::vector<boost::shared_ptr<Test> > tests
      = Test::CreateTests(newick,theta,argv3);

    //Execute all tests
    BOOST_FOREACH(boost::shared_ptr<Test> t,tests)
    {
      t->Execute();
    }

    //Show test results
    std::cout
      << '\n'
      << "Theta: '" << theta << "'\n"
      << "Newick: '" << newick << "'\n"
      << "Number of combinations: "
      << Newick::CalcNumOfCombinations(BinaryNewickVector(newick).Get())
      << "\n\n\n\n\n"
      << "TestName\t\t\tProbability\tTime\n";

    BOOST_FOREACH(boost::shared_ptr<Test> t,tests)
    {
      std::cout
        << t->GetTestName()
        << "\t" << t->GetProbability()
        //<< '\t' << t->GetEwensProbability()
        << '\t' << t->GetTime()
        << '\n';
      file
        << t->GetTestName()
        << '\t' << t->GetNewick()
        << '\t' << t->GetProbability()
        << '\t' << t->GetEwensProbability()
        << '\t' << t->GetTime()
        << '\n';
    }

    //Probably we're done,
    //except if the user wants to input another value manually
    if (argv1!="-m" && argv2!="-m") break;
  }
}
//---------------------------------------------------------------------------























//---------------------------------------------------------------------------
const std::vector<std::string> CreateTestNewicks()
{
  std::vector<std::string> v;
  v.push_back("((2,2),2)");
  v.push_back("((2,2),3)");
  v.push_back("((2,3),3)");
  v.push_back("((3,3),3)");
  v.push_back("((5,5),5)");
  v.push_back("(((2,2),2),2)");
  v.push_back("(((2,2),2),3)");
  v.push_back("(((2,2),3),3)");
  v.push_back("(((2,3),3),3)");
  v.push_back("(((3,3),3),3)");
  v.push_back("(((5,5),5),5)");
  v.push_back("((100,100),10)");
  v.push_back("((100,100),20)");
  v.push_back("((100,100),30)");
  v.push_back("((100,100),40)");
  v.push_back("((100,100),50)");
  v.push_back("((100,100),60)");
  v.push_back("((100,100),70)");
  v.push_back("((100,100),80)");
  v.push_back("((100,100),90)");
  v.push_back("((10,100),100)");
  v.push_back("((20,100),100)");
  v.push_back("((30,100),100)");
  v.push_back("((40,100),100)");
  v.push_back("((50,100),100)");
  v.push_back("((60,100),100)");
  v.push_back("((70,100),100)");
  v.push_back("((80,100),100)");
  v.push_back("((90,100),100)");
  v.push_back("((1000,100),10)");
  v.push_back("((1000,100),20)");
  v.push_back("((1000,100),30)");
  v.push_back("((1000,100),40)");
  v.push_back("((1000,100),50)");
  v.push_back("((1000,100),60)");
  v.push_back("((1000,100),70)");
  v.push_back("((1000,100),80)");
  v.push_back("((1000,100),90)");
  v.push_back("((100,100),100)");
  v.push_back("((10,1000),100)");
  v.push_back("((10,100),1000)");
  v.push_back("((20,1000),100)");
  v.push_back("((20,100),1000)");
  v.push_back("((30,1000),100)");
  v.push_back("((30,100),1000)");
  v.push_back("((40,1000),100)");
  v.push_back("((40,100),1000)");
  v.push_back("((50,1000),100)");
  v.push_back("((50,100),1000)");
  v.push_back("((60,1000),100)");
  v.push_back("((60,100),1000)");
  v.push_back("((70,1000),100)");
  v.push_back("((70,100),1000)");
  v.push_back("((80,1000),100)");
  v.push_back("((80,100),1000)");
  v.push_back("((90,1000),100)");
  v.push_back("((90,100),1000)");
  v.push_back("((1000,100),100)");
  v.push_back("((100,100),1000)");
  v.push_back("((((2,2),2),2),2)");
  v.push_back("((((2,2),2),2),3)");
  v.push_back("((((2,2),2),3),3)");
  v.push_back("((((2,2),3),3),3)");
  v.push_back("((((2,3),3),3),3)");
  v.push_back("((((3,3),3),3),3)");
  v.push_back("((((5,5),5),5),5)");
  v.push_back("(((((2,2),2),2),2),2)");
  v.push_back("(((((2,2),2),2),2),3)");
  v.push_back("(((((2,2),2),2),3),3)");
  v.push_back("(((((2,2),2),3),3),3)");
  v.push_back("(((((2,2),3),3),3),3)");
  v.push_back("(((((2,3),3),3),3),3)");
  v.push_back("(((((3,3),3),3),3),3)");
  v.push_back("(((((5,5),5),5),5),5)");
  v.push_back("((((((2,2),2),2),2),2),2)");
  v.push_back("((((((2,2),2),2),2),2),3)");
  v.push_back("((((((2,2),2),2),2),3),3)");
  v.push_back("((((((2,2),2),2),3),3),3)");
  v.push_back("((((((2,2),2),3),3),3),3)");
  v.push_back("((((((2,2),3),3),3),3),3)");
  v.push_back("((((((2,3),3),3),3),3),3)");
  v.push_back("((((((3,3),3),3),3),3),3)");
  v.push_back("((((((5,5),5),5),5),5),5)");
  v.push_back("(((((((2,2),2),2),2),2),2),2)");
  v.push_back("(((((((2,2),2),2),2),2),2),3)");
  v.push_back("(((((((2,2),2),2),2),2),3),3)");
  v.push_back("(((((((2,2),2),2),2),3),3),3)");
  v.push_back("(((((((2,2),2),2),3),3),3),3)");
  v.push_back("(((((((2,2),2),3),3),3),3),3)");
  v.push_back("(((((((2,2),3),3),3),3),3),3)");
  v.push_back("(((((((2,3),3),3),3),3),3),3)");
  v.push_back("(((((((3,3),3),3),3),3),3),3)");
  v.push_back("(((((((5,5),5),5),5),5),5),5)");
  v.push_back("((((((((2,2),2),2),2),2),2),2),2)");
  v.push_back("((((((((2,2),2),2),2),2),2),2),3)");
  v.push_back("((((((((2,2),2),2),2),2),2),3),3)");
  v.push_back("((((((((2,2),2),2),2),2),3),3),3)");
  v.push_back("((((((((2,2),2),2),2),3),3),3),3)");
  v.push_back("((((((((2,2),2),2),3),3),3),3),3)");
  v.push_back("((((((((2,2),2),3),3),3),3),3),3)");
  v.push_back("((((((((2,2),3),3),3),3),3),3),3)");
  v.push_back("((((((((2,3),3),3),3),3),3),3),3)");
  v.push_back("((((((((3,3),3),3),3),3),3),3),3)");
  v.push_back("((((((((5,5),5),5),5),5),5),5),5)");
  v.push_back("(((((((((2,2),2),2),2),2),2),2),2),2)");
  v.push_back("(((((((((2,2),2),2),2),2),2),2),3),3)");
  v.push_back("(((((((((2,2),2),2),2),2),2),3),3),3)");
  v.push_back("(((((((((2,2),2),2),2),2),3),3),3),3)");
  v.push_back("(((((((((2,2),2),2),2),3),3),3),3),3)");
  v.push_back("(((((((((2,2),2),2),3),3),3),3),3),3)");
  v.push_back("(((((((((2,2),2),3),3),3),3),3),3),3)");
  v.push_back("(((((((((2,2),3),3),3),3),3),3),3),3)");
  v.push_back("(((((((((2,3),3),3),3),3),3),3),3),3)");
  v.push_back("(((((((((5,5),5),5),5),5),5),5),5),5)");
  v.push_back("((((((((((2,2),2),2),2),2),2),2),2),2),2)");
  v.push_back("((((((((((2,2),2),2),2),2),2),2),3),3),3)");
  v.push_back("((((((((((2,2),2),2),2),2),2),3),3),3),3)");
  v.push_back("((((((((((2,2),2),2),2),2),3),3),3),3),3)");
  v.push_back("((((((((((2,2),2),2),2),3),3),3),3),3),3)");
  v.push_back("((((((((((2,2),2),2),3),3),3),3),3),3),3)");
  v.push_back("((((((((((2,2),2),3),3),3),3),3),3),3),3)");
  v.push_back("((((((((((2,2),3),3),3),3),3),3),3),3),3)");
  v.push_back("(((((((((((2,2),2),2),2),2),2),2),2),2),2),2)");
  v.push_back("(((((((((((2,2),2),2),2),2),2),2),3),3),3),3)");
  v.push_back("(((((((((((2,2),2),2),2),2),2),3),3),3),3),3)");
  v.push_back("(((((((((((2,2),2),2),2),2),3),3),3),3),3),3)");
  v.push_back("(((((((((((2,2),2),2),2),3),3),3),3),3),3),3)");
  v.push_back("((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2)");
  v.push_back("((((((((((((2,2),2),2),2),2),2),2),3),3),3),3),3)");
  v.push_back("(((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2)");
  v.push_back("((((((((((((((2,2),2),2),2),2),2),2),2),2),2),2),2),2),2)");
  return v;
}
//---------------------------------------------------------------------------
