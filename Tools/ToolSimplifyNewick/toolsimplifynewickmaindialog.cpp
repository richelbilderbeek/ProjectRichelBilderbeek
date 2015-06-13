//---------------------------------------------------------------------------
/*
SimplifyNewick, tool to randomly simplify Newick phylogenies
Copyright (C) 2010-2015 Richel Bilderbeek

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
#include "simplifynewickmaindialog.h"

#include <iostream>

#include "newick.h"
#include "newickvector.h"

/*

std::vector<std::string> ribi::ToolSimplifyNewickMainDialog::GetBadlyFormedNewicks()
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

std::vector<std::string> ribi::ToolSimplifyNewickMainDialog::GetWellFormedNewicks()
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

void ribi::ToolSimplifyNewickMainDialog::TestNewickMustFail(const std::string& s)
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

void ribi::ToolSimplifyNewickMainDialog::TestNewick(const std::string& s)
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

void ribi::ToolSimplifyNewickMainDialog::TestNewicksFromFile()
{
  if (!FileExists("subs_in.txt")) throw std::runtime_error("File subs_in.txt must exist");
  const std::vector<std::string> newicks = FileToVector("subs_in.txt");

  //std::vector<std::string>::const_iterator newick_str = newicks.begin();
  //const std::vector<std::string>::const_iterator last_newick_str = newicks.end();

  std::ofstream f("subs_out.txt");

  for(const std::string& s: newicks)
  {
    if (s.empty()) continue;
    f << s;
    NewickVector n(s);

    const std::vector<NewickVector> simplers = n.GetSimplerNewicks();
    for(const NewickVector& simple: simplers)
    {
      f << '\t' << simple.ToStr();
    }
    f << '\n';

  }
}

void ribi::ToolSimplifyNewickMainDialog::TestPredefinedNewicks()
{
  const std::vector<std::string> newicks = GetWellFormedNewicks();
  std::vector<std::string>::const_iterator newick_str = newicks.begin();
  const std::vector<std::string>::const_iterator last_newick_str = newicks.end();

  for ( ; newick_str!=last_newick_str; ++newick_str)
  {
    TestNewick(*newick_str);
  }
}

void ribi::ToolSimplifyNewickMainDialog::TestNewicksManually()
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
*/
std::string ribi::ToolSimplifyNewickMainDialog::SimplifyNewick(
  const std::string& s,
  const BigInteger& max_complexity)
{
  std::unique_ptr<const NewickVector> n{ new NewickVector(s) };
  while (1)
  {
    const BigInteger complexity = Newick().CalcComplexity(n->Peek());
    if (complexity <= max_complexity) return n->ToStr();
    const std::vector<std::pair<std::vector<int>,int> > v
      = Newick().GetSimplerNewicksFrequencyPairs(n->Peek());
    if (v.empty()) return n->ToStr();
    const int sum = SumSecond(v);

    const int index_chosen = std::rand() % sum;
    //std::clog << "Index chosen: " << index_chosen << '\n';
    int current_sum = 0;
    for (int i=0; ;++i)
    {
      assert(i != boost::numeric_cast<int>(v.size()));
      current_sum+=v[i].second;
      //std::clog << "Index " << i << ", sum: " << current_sum << '\n';
      if (current_sum >= index_chosen)
      {
        //std::clog << "Index " << i << " chosen\n";
        n.reset(new NewickVector(v[i].first));
        break;
      }
    }
  }
}

///SimplifyNewickFreqInd simplifies a Newick below a certain
///complexity, independent of the frequencies in the
///phylogeny.
///For example, for the phylogeny (100,2), SimplifyNewickFreqInd
///returns (99,2) as often as (100,1).
///From http://www.richelbilderbeek.nl/CppSimplifyNewickFreqInd.htm
/*
const std::string SimplifyNewickFreqInd(
  const std::string& s, const cln::cl_I& max_complexity)
{
  BinaryNewickVector n(s);
  while (1)
  {
    const cln::cl_I complexity = CalcComplexity(n.Get());
    if (complexity <= max_complexity) return n.ToStr();
    const std::vector<NewickVector> v = n.GetSimplerNewicks();
    if (v.empty()) return n.ToStr();
    const int i = std::rand() % boost::numeric_cast<int>(v.size());
    n = v[i];
  }
}
*/

int ribi::ToolSimplifyNewickMainDialog::SumSecond(
  const std::vector<std::pair<std::vector<int>,int> >& v) noexcept
{
  int sum = 0;
  typedef std::pair<std::vector<int>,int> Pair;
  for(const Pair& p: v)
  {
    sum+=p.second;
  }
  return sum;
}
