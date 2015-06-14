//---------------------------------------------------------------------------
/*
BinaryNewickVector, class to store a Newick as a std::vector<int>
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
//From http://www.richelbilderbeek.nl/CppBinaryNewickVector.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "binarynewickvector.h"

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
#include "testtimer.h"
#include "newick.h"

#pragma GCC diagnostic pop

ribi::BinaryNewickVector::BinaryNewickVector(const std::string& s) noexcept
  : m_v{Newick().StringToNewick(s)}
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(Newick().IsUnaryNewick(Newick().StringToNewick(s))
      || Newick().IsBinaryNewick(Newick().StringToNewick(s)));

  //Can I add these as well?
  //assert(Newick().IsUnaryNewick(m_v) || Newick().IsBinaryNewick(m_v));
  //assert(m_v.empty() || Newick::IsNewick(m_v));
}

ribi::BinaryNewickVector::BinaryNewickVector(const std::vector<int>& v) noexcept
  : m_v{v}
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(Newick().IsUnaryNewick(m_v) || Newick().IsBinaryNewick(m_v));
  assert(m_v.empty() || Newick().IsNewick(m_v));
}

double ribi::BinaryNewickVector::CalcDenominator(const double theta) const noexcept
{
  return Newick().CalcDenominator(Peek(),theta);
}

const BigInteger ribi::BinaryNewickVector::CalcNumOfCombinations() const noexcept
{
  assert(Newick().IsNewick(m_v));
  return Newick().CalcNumOfCombinationsBinary(m_v);
}

const BigInteger ribi::BinaryNewickVector::CalcNumOfSymmetries() const noexcept
{
  assert(Newick().IsNewick(m_v));
  return Newick().CalcNumOfSymmetriesBinary(m_v);
}

double ribi::BinaryNewickVector::CalcProbabilitySimpleNewick(const double theta) const noexcept
{
  assert(Newick().IsSimple(m_v));
  assert(theta > 0.0);
  return Newick().CalcProbabilitySimpleNewick(m_v,theta);
}

double ribi::BinaryNewickVector::CalculateProbability(
  const std::string& newick_str,
  const double theta
) noexcept
{
  assert(Newick().IsNewick(newick_str));
  assert(Newick().IsUnaryNewick(Newick().StringToNewick(newick_str))
      || Newick().IsBinaryNewick(Newick().StringToNewick(newick_str)));
  assert(theta > 0.0);
  BinaryNewickVector newick(newick_str);
  NewickStorage<BinaryNewickVector> storage(newick);
  return CalculateProbabilityInternal(
    newick,
    theta,
    storage);

}

double ribi::BinaryNewickVector::CalculateProbabilityInternal(
  const BinaryNewickVector& n,
  const double theta,
  NewickStorage<BinaryNewickVector>& storage) noexcept
{
  //#define DEBUG_BINARYNEWICKVECTOR_CALCULATEPROBABILITYINTERNAL
  while(1)
  {
    try
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
      std::vector<BinaryNewickVector> newicks;
      {
        const double d = n.CalcDenominator(theta);
        #ifdef DEBUG_BINARYNEWICKVECTOR_CALCULATEPROBABILITYINTERNAL
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
          #ifdef DEBUG_BINARYNEWICKVECTOR_CALCULATEPROBABILITYINTERNAL
          TRACE("BinaryNewickVector "
            + Newick::NewickToString(p.first)
            + " has coefficient "
            + boost::lexical_cast<std::string>(coefficients.back())
            + '\n';
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
    catch (std::bad_alloc& e)
    {
      storage.CleanUp();
      std::cerr << "std::bad_alloc\n";
    }
    catch (std::exception& e)
    {
      storage.CleanUp();
      std::cerr << "std::exception";
    }
    catch (...)
    {
      storage.CleanUp();
      std::cerr << "Unknown exception\n";
    }
  }
}

std::vector<ribi::BinaryNewickVector> ribi::BinaryNewickVector::GetSimplerNewicks() const noexcept
{
  assert(Newick().IsNewick(m_v));
  const std::vector<std::vector<int> > v = Newick().GetSimplerBinaryNewicks(m_v);
  std::vector<BinaryNewickVector> w(std::begin(v),std::end(v));
  return w;
}

std::pair<ribi::BinaryNewickVector,ribi::BinaryNewickVector>
  ribi::BinaryNewickVector::GetRootBranches() const noexcept
{
  assert(Newick().IsNewick(m_v));
  std::pair<std::vector<int>,std::vector<int> > p
    = Newick().GetRootBranchesBinary(m_v);
  return p;
}

std::string ribi::BinaryNewickVector::GetVersion() noexcept
{
  return "3.1";
}

std::vector<std::string> ribi::BinaryNewickVector::GetVersionHistory() noexcept
{
  return {
    "2009-06-01: Version 1.0: Initial version",
    "2010-08-10: Version 1.1: Major architectural revision",
    "2011-02-20: Version 1.2: Removed helper functions from global namespace",
    "2011-02-22: Version 2.0: Changed file management",
    "2011-03-01: Version 3.0: major rewrite of algorithms",
    "2011-04-08: Version 3.1: fixed error forgiven by G++, but fatal for i686-pc-mingw32-qmake"
  };
}

 bool ribi::BinaryNewickVector::IsCloseBracketRight(const int pos) const noexcept
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
  // that is not stored in a SortedBinaryNewickVector's std::vector
  return true;
}

bool ribi::BinaryNewickVector::IsOpenBracketLeft(const int pos) const noexcept
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
  // that is not stored in a SortedBinaryNewickVector's std::vector
  return true;
}

bool ribi::BinaryNewickVector::IsSimple() const noexcept
{
  return Newick().IsSimple(m_v);
}

//void ribi::BinaryNewickVector::SetTheta(const double theta)
//{
//  assert(theta > 0.0);
//  m_theta = theta;
//}

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
ribi::BinaryNewickVector ribi::BinaryNewickVector::LoseBrackets(const int x, const int i) const noexcept
{
  assert(i >= 0);
  assert(i < Size());
  assert(m_v[i] == 1);
  assert(x>0);
  std::vector<int> v_copy = m_v;

  const int bracket_open_pos
    = Newick().FindPosBefore(m_v,ribi::Newick::bracket_open,i);
  assert(bracket_open_pos > -1);
  const int bracket_close_pos
    = Newick().FindPosAfter(m_v,Newick::bracket_close,i);
  assert(bracket_close_pos < Size());
  const int sz = Size();
  const int sz_lose = bracket_close_pos - bracket_open_pos;
  const int sz_new = sz - sz_lose;
  v_copy[bracket_open_pos] = x+1;
  const std::vector<int>::iterator begin_iter(&v_copy[bracket_close_pos+1]);
  const std::vector<int>::iterator output_iter(&v_copy[bracket_open_pos+1]);
  std::copy(begin_iter,v_copy.end(),output_iter);
  v_copy.resize(sz_new);

  return BinaryNewickVector(v_copy);
}

bool ribi::BinaryNewickVector::NewickCompare(
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

int ribi::BinaryNewickVector::Size() const noexcept
{
  return boost::numeric_cast<int>(m_v.size());
}

ribi::BinaryNewickVector ribi::BinaryNewickVector::TermIsNotOne(const int i) const noexcept
{
  assert(m_v[i]>1);
  std::vector<int> v(m_v);
  --v[i];
  return BinaryNewickVector(v);
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
ribi::BinaryNewickVector ribi::BinaryNewickVector::TermIsOne(const int i) const noexcept
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

  //Return an empty SortedBinaryNewickVector
  return BinaryNewickVector(std::vector<int>());
}


#ifndef NDEBUG
void ribi::BinaryNewickVector::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Newick();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};

  //Check that well-formed Newicks are confirmed valid
  {
    const auto v = Newick().CreateValidNewicks();
    for(const auto& s: v)
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
      //Check std::string conversion (from BinaryNewickVector(std::string))
      if ( !Newick().IsUnaryNewick(Newick().StringToNewick(s))
        && !Newick().IsBinaryNewick(Newick().StringToNewick(s)))
      {
        continue;
      }
      try
      {
        BinaryNewickVector temp(s);
        assert(s == temp.ToStr());
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (BinaryNewickVector from std::string): "
          << e.what();
      }
      //Check std::string conversion (from BinaryNewickVector(std::vector<int>))
      try
      {
        const std::vector<int> n = Newick().StringToNewick(s);
        BinaryNewickVector temp(n);
        assert(s == temp.ToStr());
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (BinaryNewickVector from std::vector<int>): "
          << e.what();
      }
      assert(Newick().IsNewick(s));
      //Check the simpler Newicks
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
      //Check the branches, only of binary Newicks
      if (Newick().IsBinaryNewick(Newick().StringToNewick(s)))
      {
        const std::pair<std::vector<int>,std::vector<int> > b
            = Newick().GetRootBranchesBinary(Newick().StringToNewick(s));
        assert(Newick().IsNewick(b.first));
        assert(Newick().IsNewick(b.second));
      }
    }
  }
}
#endif

std::string ribi::BinaryNewickVector::ToStr() const noexcept
{
  assert(Newick().IsNewick(m_v));
  return Newick().NewickToString(m_v);
}

bool ribi::operator<(const BinaryNewickVector& lhs, const BinaryNewickVector& rhs) noexcept
{
  return ribi::BinaryNewickVector::NewickCompare(lhs.Peek(),rhs.Peek());
}

