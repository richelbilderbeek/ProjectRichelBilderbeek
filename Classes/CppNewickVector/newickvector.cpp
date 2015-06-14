//---------------------------------------------------------------------------
/*
NewickVector, class to store a Newick as a std::vector<int>
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
//From http://www.richelbilderbeek.nl/CppNewickVector.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "newickvector.h"

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <functional>
#include <map>
#include <numeric>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/lexical_cast.hpp>

#include "BigIntegerLibrary.hh"

#include "fuzzy_equal_to.h"
#include "newick.h"
#include "testtimer.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::NewickVector::NewickVector(const std::string& s)
  : m_v{Newick().StringToNewick(s)}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(Newick().IsNewick(s));
  //Can this be added?
  //assert(m_v.empty() || Newick().IsNewick(m_v));
}

ribi::NewickVector::NewickVector(const std::vector<int>& v)
  : m_v{v}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_v.empty() || Newick().IsNewick(m_v));
}

const BigInteger ribi::NewickVector::CalcComplexity() const
{
  return Newick().CalcComplexity(m_v);
}

double ribi::NewickVector::CalcDenominator(const double theta) const
{
  return Newick().CalcDenominator(Peek(),theta);
}

const BigInteger ribi::NewickVector::CalcNumOfCombinations() const
{
  assert(Newick().IsNewick(m_v));
  return Newick().CalcNumOfCombinationsBinary(m_v);
}

const BigInteger ribi::NewickVector::CalcNumOfSymmetries() const
{
  assert(Newick().IsNewick(m_v));
  assert(Newick().IsBinaryNewick(m_v));
  return Newick().CalcNumOfSymmetriesBinary(m_v);
}

double ribi::NewickVector::CalculateProbability(
  const std::string& newick_str,
  const double theta)
{
  assert(Newick().IsNewick(newick_str));
  assert(theta > 0.0);
  NewickVector newick(newick_str);
  NewickStorage<NewickVector> storage(newick);
  return CalculateProbabilityInternal(
    newick,
    theta,
    storage);
}

double ribi::NewickVector::CalculateProbabilityInternal(
  const NewickVector& n,
  const double theta,
  NewickStorage<NewickVector>& storage)
{
  //#define DEBUG_NEWICKVECTOR_CALCULATEPROBABILITYINTERNAL
  #ifdef  DEBUG_NEWICKVECTOR_CALCULATEPROBABILITYINTERNAL
  TRACE_FUNC();
  TRACE(n.ToStr());
  #endif

  while(1)
  {
    //Is n already known?
    {
      const double p = storage.Find(n);
      if (p!=0.0)
      {
        return p;
      }
    }

    //Check for simple phylogeny
    if (n.IsSimple())
    {
      const double p = n.CalcProbabilitySimpleNewick(theta);
      storage.Store(n,p);
      return p;
    }
    //Complex
    //Generate other Newicks and their coefficients
    std::vector<double> coefficients;
    std::vector<NewickVector> newicks;
    {
      const double d = n.CalcDenominator(theta);
      #ifdef DEBUG_NEWICKVECTOR_CALCULATEPROBABILITYINTERNAL
      TRACE("Denominator for "
        + n.ToStr()
        + " = "
        + boost::lexical_cast<std::string>(d));
      #endif
      typedef std::pair<std::vector<int>,int> NewickFrequencyPair;
      const std::vector<NewickFrequencyPair> newick_freqs
        = Newick().GetSimplerNewicksFrequencyPairs(n.Peek());
      for(const NewickFrequencyPair& p: newick_freqs)
      {
        const int frequency = p.second;
        assert(frequency > 0);
        if (frequency == 1)
        {
          newicks.push_back(p.first);
          coefficients.push_back(theta / d);
        }
        else
        {
          const double f_d = static_cast<double>(frequency);
          newicks.push_back(p.first);
          coefficients.push_back( (f_d*(f_d-1.0)) / d);
        }
        #ifdef DEBUG_NEWICKVECTOR_CALCULATEPROBABILITYINTERNAL
        TRACE("NewickVector "
          + Newick::NewickToString(p.first)
          + " has coefficient "
          + boost::lexical_cast<std::string>(coefficients.back()));
        #endif
      }
    }
    //Ask help about these new Newicks
    {
      const int sz = newicks.size();
      assert(newicks.size() == coefficients.size() );
      double p = 0.0;
      for (int i=0; i!=sz; ++i)
      {
        //Recursive function call
        p+=(coefficients[i] * CalculateProbabilityInternal(newicks[i],theta,storage));
      }
      storage.Store(n,p);
      return p;
    }
  }
}

double ribi::NewickVector::CalcProbabilitySimpleNewick(const double theta) const
{
  assert(Newick().IsSimple(m_v));
  assert(theta > 0.0);
  return Newick().CalcProbabilitySimpleNewick(m_v,theta);
}

int ribi::NewickVector::FindPosAfter(const std::vector<int>& v,const int x, const int index) const
{
  const int sz = v.size();
  for (int i=index; i!=sz; ++i)
  {
    assert(i >= 0);
    assert(i < sz);
    if (v[i]==x) return i;
  }
  return sz;
}

int ribi::NewickVector::FindPosBefore(const std::vector<int>& v,const int x, const int index) const
{

  for (int i=index; i!=-1; --i)
  {
    #ifndef NDEBUG
    const int sz = static_cast<int>(v.size());
    assert(i >= 0);
    assert(i < sz);
    #endif
    if (v[i]==x) return i;
  }
  return -1;
}

const std::vector<ribi::NewickVector> ribi::NewickVector::GetSimplerNewicks() const
{
  assert(Newick().IsNewick(m_v));
  const std::vector<std::vector<int> > v
    = Newick().GetSimplerBinaryNewicks(m_v);
  std::vector<NewickVector> w(std::begin(v),std::end(v));
  return w;
}

const std::pair<ribi::NewickVector,ribi::NewickVector> ribi::NewickVector::GetRootBranches() const
{
  assert(Newick().IsNewick(m_v));
  std::pair<std::vector<int>,std::vector<int> > p
    = Newick().GetRootBranchesBinary(m_v);
  return p;
}

std::string ribi::NewickVector::GetVersion() noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::NewickVector::GetVersionHistory() noexcept
{
  return {
    "2009-06-01: Version 1.0: Initial version",
    "2010-08-10: Version 1.1: Major architectural revision",
    "2011-02-20: Version 1.2: Removed helper functions from global namespace",
    "2011-02-22: Version 2.0: Changed file management",
    "2011-04-08: Version 2.1: fixed error forgiven by G++, but fatal for i686-pc-mingw32-qmake"
  };
}

 bool ribi::NewickVector::IsCloseBracketRight(const int pos) const
{
  const int sz = m_v.size();

  assert(pos >= 0);
  assert(pos < sz);
  assert(m_v[pos]==1);

  for (int i=pos+1; i!=sz; ++i) //+1 because v[pos]==1
  {
    const int x = m_v[i];
    if (x == Newick::bracket_close) return true;
    if (x == Newick::bracket_open) return false;
  }
  //There will always be a final closing bracket at the right
  // that is not stored in a SortedNewickVector's std::vector
  return true;
}

bool ribi::NewickVector::IsOpenBracketLeft(const int pos) const
{
  assert(pos >= 0);
  assert(pos < static_cast<int>(m_v.size()));
  assert(m_v[pos]==1);

  for (int i=pos-1; i!=-1; --i) //-1, because v[pos]==1
  {
    const int x = m_v[i];
    if (x == Newick::bracket_open) return true;
    if (x == Newick::bracket_close) return false;
  }
  //There will always be a trailing opening bracket at the left
  // that is not stored in a SortedNewickVector's std::vector
  return true;
}

bool ribi::NewickVector::IsSimple() const
{
  return Newick().IsSimple(m_v);
}

//Does the following conversions:
// (5,(5,1)) -> (5,6)
// (4,(5,1)) -> (4,6)
// (4,(3,1)) -> (4,4)
// (4,(1,1)) -> (4,2)
// string_pos points at an index in the string current.newick after the '1'
// For example, for (4,(3,1)) the string_pos equals 7
// num is the other value between brackets
// For example, for (4,(3,1)) num will equal 3
// (5,(5,1)) -> (5,6)
// -> sz = 9
// -> bracket_open_pos  = 3
// -> bracket_close_pos = 7
// -> sz_loss = 4 = 7 - 3 = bracket_close_pos - bracket_open_pos
// -> new_sz = 5
const ribi::NewickVector ribi::NewickVector::LoseBrackets(const int x, const int i) const
{
  assert(i >= 0);
  assert(i < Size());
  assert(m_v[i] == 1);
  assert(x>0);
  std::vector<int> v_copy = m_v;

  const int bracket_open_pos
    = FindPosBefore(m_v,Newick::bracket_open,i);
  assert(bracket_open_pos > -1);
  const int bracket_close_pos
    = FindPosAfter(m_v,Newick::bracket_close,i);
  assert(bracket_close_pos < Size());
  const int sz = Size();
  const int sz_lose = bracket_close_pos - bracket_open_pos;
  const int sz_new = sz - sz_lose;
  v_copy[bracket_open_pos] = x+1;
  const std::vector<int>::iterator begin_iter(&v_copy[bracket_close_pos+1]);
  const std::vector<int>::iterator output_iter(&v_copy[bracket_open_pos+1]);
  std::copy(begin_iter,v_copy.end(),output_iter);
  v_copy.resize(sz_new);

  return NewickVector(v_copy);
}

bool ribi::NewickVector::NewickCompare(
  const std::vector<int>& lhs,
  const std::vector<int>& rhs) noexcept
{
  const int l_sz = lhs.size();
  const int r_sz = rhs.size();
  if (l_sz < r_sz) return true;
  if (l_sz > r_sz) return false;

  typedef std::vector<int>::const_iterator Iter;
  Iter lhs_iter = lhs.begin();
  const Iter lhs_end = lhs.end();
  Iter rhs_iter = rhs.begin();

  for ( ; lhs_iter != lhs_end; ++lhs_iter, ++rhs_iter)
  {
    const int x_l = *lhs_iter;
    const int x_r = *rhs_iter;
    if (x_l < x_r) return true;
    if (x_l > x_r) return false;
  }
  return false;
}

int ribi::NewickVector::Size() const noexcept
{
  return boost::numeric_cast<int>(m_v.size());
}

const ribi::NewickVector ribi::NewickVector::TermIsNotOne(const int i) const
{
  assert(m_v[i]>1);
  std::vector<int> v(m_v);
  --v[i];
  return NewickVector(v);
}

//TermIsOne is called whenever a '1' is found in a newick structure
//string_pos has the index of the character after this '1'
// (when a string has multiple 1's, TermIsOne is called for each '1',
//  with each time a different string_pos)
//If this '1' is between two brackets, with one other number,
//  these two numbers are added and the brackets are removed
//If this '1' is not between two brackets,
//  the newick string returned is empty
//Conversion examples
// (3,(15,1)), string_pos 8 -> (3,16)
//         ^   EXIT1
// (2,(23,1)), string_pos 8 -> (2,24)
//         ^   EXIT1
// (1,(20,5)), string_pos 2 -> [empty]
//   ^         EXIT-2
// (1,(1,1)), string_pos 2 -> [empty]
//   ^         EXIT-2
// (1,(1,1)), string_pos 5 -> (1,2)
//      ^      EXIT-2
// (1,(1,1)), string_pos 7 -> (1,2)
//        ^    EXIT-1
// ((1,2,3),3), string_pos 3 -> (3,3) //Might be incorrect: algorithm holds for two numbers between brackets
//    ^
const ribi::NewickVector ribi::NewickVector::TermIsOne(const int i) const
{
  const int sz = m_v.size();

  //assert(new_newick.empty());
  assert(i < sz);
  assert(m_v[i] == 1); //Must be a 1

  const bool open_bracket_left
    = IsOpenBracketLeft(i);
  const bool close_bracket_right
    = IsCloseBracketRight(i);

  if (open_bracket_left == true
    && close_bracket_right == true)
  {
    //Find other_value
    int other_value = 0;
    //If adjecent to the left is a comma
    // and subsequently a value,
    if (i > 0
      && m_v[i-1]  > 0)
    {
      other_value = m_v[i-1];
    }
    else if (i + 1 < sz
      && m_v[i+1]  > 0)
    {
      other_value = m_v[i+1];
    }

    assert(other_value >= 1);
    return LoseBrackets(other_value,i);
  }

  //Return an empty SortedNewickVector
  return NewickVector(std::vector<int>());
}

#ifndef NDEBUG
void ribi::NewickVector::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};

  //Test simplification of trinary Newick
  {
    //Simple trinary Newick
    {
      const std::string s = "(2,3,4)";
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().IsTrinaryNewick(n));
      const std::vector<std::vector<int> > ns = Newick().GetSimplerNewicks(n);
      #ifdef DEBUG_BO_2_3_4_BC
      for(const std::vector<int>& v: ns)
      {
        TRACE(Newick::NewickToString(v));
      }
      #endif
      assert(ns.size() == 3);

      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("(1,3,4)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("(2,2,4)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("(2,3,3)")) != ns.end());
    }
    //Simple trinary Newick
    {
      const std::string s = "(1,2,3)";
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().IsTrinaryNewick(n));
      const std::vector<std::vector<int> > ns = Newick().GetSimplerNewicks(n);
      assert(ns.size() == 4);
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("(3,3)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("(2,4)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("(1,1,3)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("(1,2,2)")) != ns.end());
    }
    //Complex trinary Newick
    {
      const std::string s = "((2,3),(4,5),(6,7))";
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().IsTrinaryNewick(n));
      const std::vector<std::vector<int> > ns = Newick().GetSimplerNewicks(n);
      assert(ns.size() == 6);
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,3),(4,5),(6,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,2),(4,5),(6,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,3),(3,5),(6,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,3),(4,4),(6,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,3),(4,5),(5,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,3),(4,5),(6,6))")) != ns.end());
    }
    //Another trinary Newick
    {
      const std::string s = "((2,3),(1,5),(6,7))";
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().IsTrinaryNewick(n));
      const std::vector<std::vector<int> > ns = Newick().GetSimplerNewicks(n);
      assert(ns.size() == 6);
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,3),(1,5),(6,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,2),(1,5),(6,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,3),6,(6,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,3),(1,4),(6,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,3),(1,5),(5,7))")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,3),(1,5),(6,6))")) != ns.end());
    }
    //Another trinary Newick
    {
      const std::string s = "((1,2,3),(4,5,6),1)";
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().IsTrinaryNewick(n));
      const std::vector<std::vector<int> > ns = Newick().GetSimplerNewicks(n);
      assert(ns.size() == 7);
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((3,3),(4,5,6),1)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((2,4),(4,5,6),1)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,1,3),(4,5,6),1)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,2,2),(4,5,6),1)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,2,3),(3,5,6),1)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,2,3),(4,4,6),1)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,2,3),(4,5,5),1)")) != ns.end());
    }
    //Another trinary Newick
    {
      const std::string s = "((1,(1,1,1)),1)";
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().IsTrinaryNewick(n));
      const std::vector<std::vector<int> > ns = Newick().GetSimplerNewicks(n);
      assert(ns.size() == 6);
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,(2,1)),1)")) != ns.end());
    }
    //Another trinary Newick
    {
      const std::string s = "(1,(1,1),1)";
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().IsTrinaryNewick(n));
      const std::vector<std::vector<int> > ns = Newick().GetSimplerNewicks(n);
      //#define DEBUG_BO_1_BO_1_1_BC_1
      #ifdef  DEBUG_BO_1_BO_1_1_BC_1
      TRACE(boost::lexical_cast<std::string>(ns.size()));
      for(const std::vector<int>& v: ns)
      {
        TRACE(Newick::NewickToString(v));
      }
      #endif
      assert(ns.size() == 4);
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("(1,2,1)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,1),2)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("(2,(1,1))")) != ns.end());
    }
    //Another trinary Newick
    {
      const std::string s = "((1,(2,3,4)),5)";
      const std::vector<int> n = Newick().StringToNewick(s);
      assert(Newick().IsTrinaryNewick(n));
      const std::vector<std::vector<int> > ns = Newick().GetSimplerNewicks(n);
      assert(ns.size() == 4);
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,(1,3,4)),5)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,(2,2,4)),5)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,(2,3,3)),5)")) != ns.end());
      assert(std::find(ns.begin(),ns.end(),
        Newick().StringToNewick("((1,(2,3,4)),4)")) != ns.end());
    }
  }

  //Check that well-formed Newicks are confirmed valid
  {
    const std::vector<std::string> v = Newick().CreateValidNewicks();
    for(const std::string& s: v)
    {
      if (verbose) { TRACE("I must be accepted: " + s); }
      //Check if valid newicks (as std::string) are marked as valid
      try
      {
        Newick().CheckNewick(s);
      }
      catch (std::exception& e)
      {
        std::cerr << "(" << __FILE__ << "," << __LINE__ << ") "
          << s << ": " << e.what() << '\n'
        ;
      }
      //Check if valid newicks (as std::vector) are marked as valid
      try
      {
        const std::vector<int> n = Newick().StringToNewick(s);
        Newick().CheckNewick(n);
        assert(Newick().IsNewick(n));
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (converted to std::vector<int>): "
          << e.what()
        ;
      }
      //Check std::string conversion (from NewickVector(std::string))
      try
      {
        NewickVector temp(s);
        assert(s == temp.ToStr());
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (NewickVector from std::string): "
          << e.what()
        ;
      }
      //Check std::string conversion (from NewickVector(std::vector<int>))
      try
      {
        const std::vector<int> n = Newick().StringToNewick(s);
        NewickVector temp(n);
        assert(s == temp.ToStr());
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (NewickVector from std::vector<int>): "
          << e.what()
        ;
      }
      assert(Newick().IsNewick(s));
      //Check the simpler Newicks
      {
        const std::vector<std::vector<int> > simpler
          = Newick().GetSimplerNewicks(
            Newick().StringToNewick(s));
        for(const std::vector<int> simple: simpler)
        {
          assert(Newick().IsNewick(simple));
          Newick().CheckNewick(simple);
        }
      }
      //Check the branches
      #ifndef NDEBUG
      if (!Newick().IsUnaryNewick(Newick().StringToNewick(s)))
      {
        const std::vector<std::vector<int> > b
            = Newick().GetRootBranches(
              Newick().StringToNewick(s));
        for(const std::vector<int>& c: b)
        {
          assert(Newick().IsNewick(c));
        }
      }
      #endif
    }
  }
  //Check if ill-formed Newicks are rejected
  {
    const std::vector<std::string> v = Newick().CreateInvalidNewicks();
    for(const std::string& s: v)
    {
      if (verbose) { TRACE("I must be rejected: " + s); }
      assert(!Newick().IsNewick(s));
    }
  }

  //Check that well-formed Newicks are confirmed valid
  {
    const std::vector<std::string> v = Newick().CreateValidNewicks();
    for(const std::string& s: v)
    {
      if (verbose) { TRACE("I must be accepted: " + s); }
      //Check if valid newicks (as std::string) are marked as valid
      try
      {
        Newick().CheckNewick(s);
      }
      catch (std::exception& e)
      {
        std::cerr << "(" << __FILE__ << "," << __LINE__ << ") "
          << s << ": " << e.what() << '\n';
      }
      //Check if valid newicks (as std::vector) are marked as valid
      try
      {
        const std::vector<int> n = Newick().StringToNewick(s);
        Newick().CheckNewick(n);
        assert(Newick().IsNewick(n));
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (converted to std::vector<int>): "
          << e.what();
      }
      //Check std::string conversion (from NewickVector(std::string))
      try
      {
        NewickVector temp(s);
        assert(s == temp.ToStr());
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (NewickVector from std::string): "
          << e.what();
      }
      //Check std::string conversion (from NewickVector(std::vector<int>))
      try
      {
        const std::vector<int> n = Newick().StringToNewick(s);
        NewickVector temp(n);
        assert(s == temp.ToStr());
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (NewickVector from std::vector<int>): "
          << e.what();
      }
      assert(Newick().IsNewick(s));
      //Check the simpler Newicks
      if (Newick().IsBinaryNewick(Newick().StringToNewick(s)))
      {
        const std::vector<std::vector<int> > simpler
          = Newick().GetSimplerBinaryNewicks(
            Newick().StringToNewick(s));
        for(const std::vector<int> simple: simpler)
        {
          assert(Newick().IsNewick(simple));
          Newick().CheckNewick(simple);
        }
      }
      //Check the branches
      if (Newick().IsBinaryNewick(Newick().StringToNewick(s)))
      {
        const std::pair<std::vector<int>,std::vector<int> > b
            = Newick().GetRootBranchesBinary(Newick().StringToNewick(s));
        assert(Newick().IsNewick(b.first));
        assert(Newick().IsNewick(b.second));
      }
    }
  }
  //Calculate N1
  #ifndef NDEBUG
  {
    const double theta = 23.45;
    //Calculate probability the short way
    const std::string n1 = "((1,1),1,1)";
    const std::string n2 = "(1,(1,1),1)";
    const std::string n3 = "(1,1,(1,1))";
    const double p1 = ribi::NewickVector::CalculateProbability(n1,theta);
    const double p2 = ribi::NewickVector::CalculateProbability(n2,theta);
    const double p3 = ribi::NewickVector::CalculateProbability(n3,theta);
    //Calculate probability via testable binary Newicks
    const double p4
      = theta
      / Newick().CalcDenominator(Newick().StringToNewick(n1),theta)
      * ( (2.0 * ribi::NewickVector::CalculateProbability("(1,1,2)",theta) )
        + (2.0 * ribi::NewickVector::CalculateProbability("(2,(1,1))",theta) ) );
    const double p5
      = theta
      / Newick().CalcDenominator(Newick().StringToNewick(n1),theta)
      * ( (2.0 * ribi::NewickVector::CalculateProbability("(1,2,1)",theta) )
        + (2.0 * ribi::NewickVector::CalculateProbability("(2,(1,1))",theta) ) );
    const double p6
      = theta
      / Newick().CalcDenominator(Newick().StringToNewick(n1),theta)
      * ( (2.0 * ribi::NewickVector::CalculateProbability("(2,1,1)",theta) )
        + (2.0 * ribi::NewickVector::CalculateProbability("(2,(1,1))",theta) ) );
    assert(ribi::fuzzy_equal_to()(p1,p2));
    assert(ribi::fuzzy_equal_to()(p1,p3));
    assert(ribi::fuzzy_equal_to()(p1,p4));
    assert(ribi::fuzzy_equal_to()(p1,p5));
    assert(ribi::fuzzy_equal_to()(p1,p6));
  }
  //Calculate N2
  {
    const double theta = 12.34;
    //Calculate probability the short way
    const std::string n = "((1,1,1),1)";
    const double p1 = ribi::NewickVector::CalculateProbability(n,theta);
    //Calculate probability via testable binary Newicks
    const double p2
      = theta
      / Newick().CalcDenominator(Newick().StringToNewick(n),theta)
      * 6.0
      * ribi::NewickVector::CalculateProbability("((2,1),1)",theta);
    assert(ribi::fuzzy_equal_to()(p1,p2));
  }

  //Testing the known probabilities
  {
    const std::vector<boost::tuple<std::string,double,double> > v
      = Newick().GetKnownProbabilities();
    for(const auto& t:  v)
    {
      const std::string newick_str = boost::get<0>(t);
      const double theta = boost::get<1>(t);
      const double p1 = boost::get<2>(t);
      const double p2 = ribi::NewickVector::CalculateProbability(newick_str,theta);
      assert(ribi::fuzzy_equal_to(0.001)(p1,p2));
    }
  }
  #endif
}
#endif

std::string ribi::NewickVector::ToStr() const
{
  assert(Newick().IsNewick(m_v));
  return Newick().NewickToString(m_v);
}

bool ribi::operator<(const NewickVector& lhs, const NewickVector& rhs)
{
  return ribi::NewickVector::NewickCompare(lhs.Peek(),rhs.Peek());
}
