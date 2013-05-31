//---------------------------------------------------------------------------
/*
SimplifyNewick, tool to randomly simplify Newick phylogenies
Copyright (C) 2010-2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolSimplifyNewick.htm
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
//---------------------------------------------------------------------------
#include <QtGui/QApplication>
//---------------------------------------------------------------------------
#include "newickvector.h"
#include "dialogsimplifynewick.h"
#include "newick.h"
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppAskUserForString.htm
const std::string AskUserForString()
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppStrToLower.htm
const std::string StrToLower(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(),std::ptr_fun<int,int>(std::tolower));
  return s;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileExists.htm
bool FileExists(const std::string& fileName)
{
  std::fstream fin;
  fin.open(fileName.c_str(),std::ios::in);
  return fin.is_open();
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& fileName)
{
  assert(FileExists(fileName)==true);
  std::vector<std::string> myVector;
  std::ifstream in(fileName.c_str());
  std::string myString;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,myString);
    myVector.push_back(myString);
  }
  return myVector;
}
//---------------------------------------------------------------------------
const std::vector<std::string> GetBadlyFormedNewicks()
{
  std::vector<std::string> v;
  v.push_back("1,(2,3))");
  v.push_back("(1,(2,3)");
  v.push_back("(1,((2,3))");
  v.push_back("(1,(2,3)))");

  v.push_back("(((1,(2,3)),4)");
  v.push_back("((2,((1,3)),4)");
  v.push_back("((2,(3,1))),4)");
  v.push_back("((2,(3,4)),1))");

  return v;
}
//---------------------------------------------------------------------------
const std::vector<std::string> GetWellFormedNewicks()
{
  std::vector<std::string> v;
  v.push_back("(1,(2,3))");
  v.push_back("(2,(1,3))");
  v.push_back("(2,(3,1))");
  v.push_back("(1,(1,1))");

  v.push_back("((1,(2,3)),4)");
  v.push_back("((2,(1,3)),4)");
  v.push_back("((2,(3,1)),4)");
  v.push_back("((2,(3,4)),1)");
  v.push_back("((1,(1,1)),1)");

  v.push_back("(1,((20,(30,40)),50))");
  v.push_back("(10,((1,(30,40)),50))");
  v.push_back("(10,((20,(1,40)),50))");
  v.push_back("(10,((20,(30,1)),50))");
  v.push_back("(10,((20,(30,40)),1))");
  v.push_back("(1,((1,(1,1)),1))");

  v.push_back("(((1,(20,30)),40),50)");
  v.push_back("(((10,(1,30)),40),50)");
  v.push_back("(((10,(20,1)),40),50)");
  v.push_back("(((10,(20,30)),1),50)");
  v.push_back("(((10,(20,30)),40),1)");
  v.push_back("(((11,(1,1)),1),1)");

  v.push_back("(1,(((200,(300,400)),500),600))");
  v.push_back("(100,(((1,(300,400)),500),600))");
  v.push_back("(100,(((200,(1,400)),500),600))");
  v.push_back("(100,(((200,(300,1)),500),600))");
  v.push_back("(100,(((200,(300,400)),1),600))");
  v.push_back("(100,(((200,(300,400)),500),1))");
  v.push_back("(1,(((1,(1,1)),1),1))");

  v.push_back("((((1,(200,300)),400),500),600)");
  v.push_back("((((100,(1,300)),400),500),600)");
  v.push_back("((((100,(200,1)),400),500),600)");
  v.push_back("((((100,(200,300)),1),500),600)");
  v.push_back("((((100,(200,300)),400),1),600)");
  v.push_back("((((100,(200,300)),400),500),1)");
  v.push_back("((((1,(1,1)),1),1),1)");

  v.push_back("(1,(1,1),(1,1))");
  return v;
}
//---------------------------------------------------------------------------
void TestNewickMustFail(const std::string& s)
{
  try
  {
    const NewickVector n(s);
  }
  catch(std::invalid_argument& e)
  {
    //No problem
    return;
  }
  std::stringstream err_msg;
  err_msg << "Test that had to fail succeeded from newick '" << s << '\'';
  throw std::logic_error(err_msg.str());
}
//---------------------------------------------------------------------------
void TestNewick(const std::string& s)
{
  const NewickVector n(s);
  std::cout  << "Obtaining simpler newicks of " << s;

  const std::vector<NewickVector> v = n.GetSimplerNewicks();

  if (v.empty()) std::cout << "[no simpler newick obtained]\n";
  typedef std::vector<NewickVector>::const_iterator Iterator;
  const Iterator j = v.end();
  for (Iterator i=v.begin(); i!=j; ++i)
  {
    std::cout << (*i).ToStr();
  }

  std::cout << std::endl;
}
//---------------------------------------------------------------------------
void TestNewicksFromFile()
{
  if (!FileExists("subs_in.txt")) throw std::runtime_error("File subs_in.txt must exist");
  const std::vector<std::string> newicks = FileToVector("subs_in.txt");

  //std::vector<std::string>::const_iterator newick_str = newicks.begin();
  //const std::vector<std::string>::const_iterator last_newick_str = newicks.end();

  std::ofstream f("subs_out.txt");

  BOOST_FOREACH(const std::string& s, newicks)
  {
    if (s.empty()) continue;
    f << s;
    NewickVector n(s);

    const std::vector<NewickVector> simplers = n.GetSimplerNewicks();
    BOOST_FOREACH(const NewickVector& simple,simplers)
    {
      f << '\t' << simple.ToStr();
    }
    f << '\n';

  }
}
//---------------------------------------------------------------------------
void TestPredefinedNewicks()
{
  const std::vector<std::string> newicks = GetWellFormedNewicks();
  std::vector<std::string>::const_iterator newick_str = newicks.begin();
  const std::vector<std::string>::const_iterator last_newick_str = newicks.end();

  for ( ; newick_str!=last_newick_str; ++newick_str)
  {
    TestNewick(*newick_str);
  }
}
//---------------------------------------------------------------------------
void TestNewicksManually()
{
  while(1)
  {
    std::cout << "Please enter a Newick, for example '(1,(2,3))'. Press enter to quit.\n";
    const std::string s = AskUserForString();
    if (s.empty()) return;
    try
    {
      TestNewick(s);
    }
    catch (std::invalid_argument& e)
    {
      std::cout << "Invalid input: " << e.what() << '\n' << std::endl;
    }
  }
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc==1)
  {
    QApplication a(argc, argv);
    DialogSimplifyNewick d;
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
    NewickVector n(argv[1]);
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
  RandomizeTimer();
  #endif

  const std::string s_in(argv[1]);
  const BigInteger max_complexity =
    (argc == 3
    ? BigInteger(boost::lexical_cast<int>(argv[2]))
    : Newick::CalcComplexity(NewickVector(s_in).Peek()) - 1);
  const std::string s_out = SimplifyNewick(s_in,max_complexity);
  std::cout << s_out << '\n';
}

