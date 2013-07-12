//---------------------------------------------------------------------------
/*
BinaryNewickVector, class to store a Newick as a std::vector<int>
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
//From http://www.richelbilderbeek.nl/CppBinaryNewickVector.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "binarynewickvector.h"

//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
#include <boost/numeric/conversion/cast.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
//---------------------------------------------------------------------------
#include "BigIntegerLibrary.hh"
//---------------------------------------------------------------------------
#include "newick.h"
//---------------------------------------------------------------------------
BinaryNewickVector::BinaryNewickVector(const std::string& s)
{
  assert(Newick::IsUnaryNewick(Newick::StringToNewick(s))
      || Newick::IsBinaryNewick(Newick::StringToNewick(s)));
  m_v = Newick::StringToNewick(s);
}
//---------------------------------------------------------------------------
BinaryNewickVector::BinaryNewickVector(const std::vector<int>& v)
{
  assert(Newick::IsUnaryNewick(v) || Newick::IsBinaryNewick(v));
  assert(v.empty() || Newick::IsNewick(v));
  m_v = v;
}
//---------------------------------------------------------------------------
double BinaryNewickVector::CalcDenominator(const double theta) const
{
  return Newick::CalcDenominator(Peek(),theta);
}
//---------------------------------------------------------------------------
const BigInteger BinaryNewickVector::CalcNumOfCombinations() const
{
  assert(Newick::IsNewick(m_v));
  return Newick::CalcNumOfCombinationsBinary(m_v);
}
//---------------------------------------------------------------------------
//#ifndef WIN32
//const cln::cl_I BinaryNewickVector::CalcNumOfCombinationsCln() const
//{
//  assert(Newick::IsNewick(m_v));
//  return Newick::CalcNumOfCombinationsCln(m_v);
//}
//#endif
//---------------------------------------------------------------------------
const BigInteger BinaryNewickVector::CalcNumOfSymmetries() const
{
  assert(Newick::IsNewick(m_v));
  return Newick::CalcNumOfSymmetriesBinary(m_v);
}
//---------------------------------------------------------------------------
double BinaryNewickVector::CalcProbabilitySimpleNewick(const double theta) const
{
  assert(Newick::IsSimple(m_v));
  assert(theta > 0.0);
  return Newick::CalcProbabilitySimpleNewick(m_v,theta);
}
//---------------------------------------------------------------------------
double BinaryNewickVector::CalculateProbability(
  const std::string& newick_str,
  const double theta)
{
  assert(Newick::IsNewick(newick_str));
  assert(Newick::IsUnaryNewick(Newick::StringToNewick(newick_str))
      || Newick::IsBinaryNewick(Newick::StringToNewick(newick_str)));
  assert(theta > 0.0);
  BinaryNewickVector newick(newick_str);
  NewickStorage<BinaryNewickVector> storage(newick);
  return CalculateProbabilityInternal(
    newick,
    theta,
    storage);

}
//---------------------------------------------------------------------------
double BinaryNewickVector::CalculateProbabilityInternal(
  const BinaryNewickVector& n,
  const double theta,
  NewickStorage<BinaryNewickVector>& storage)
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
          = Newick::GetSimplerNewicksFrequencyPairs(n.Peek());
        BOOST_FOREACH(const NewickFrequencyPair& p,newick_freqs)
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
          TRACE(std::string("BinaryNewickVector ")
            + Newick::NewickToString(p.first)
            + std::string(" has coefficient ")
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
//---------------------------------------------------------------------------
const std::vector<BinaryNewickVector> BinaryNewickVector::GetSimplerNewicks() const
{
  assert(Newick::IsNewick(m_v));
  const std::vector<std::vector<int> > v = Newick::GetSimplerBinaryNewicks(m_v);
  std::vector<BinaryNewickVector> w(v.begin(),v.end());
  return w;
}
//---------------------------------------------------------------------------
const std::pair<BinaryNewickVector,BinaryNewickVector> BinaryNewickVector::GetRootBranches() const
{
  assert(Newick::IsNewick(m_v));
  std::pair<std::vector<int>,std::vector<int> > p
    = Newick::GetRootBranchesBinary(m_v);
  return p;
}
//---------------------------------------------------------------------------
const std::string BinaryNewickVector::GetVersion()
{
  return "3.1";
}
//---------------------------------------------------------------------------
const std::vector<std::string> BinaryNewickVector::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2009-06-01: Version 1.0: Initial version");
  v.push_back("2010-08-10: Version 1.1: Major architectural revision");
  v.push_back("2011-02-20: Version 1.2: Removed helper functions from global namespace");
  v.push_back("2011-02-22: Version 2.0: Changed file management");
  v.push_back("2011-03-01: Version 3.0: major rewrite of algorithms");
  v.push_back("2011-04-08: Version 3.1: fixed error forgiven by G++, but fatal for i686-pc-mingw32-qmake");
  return v;
}
//---------------------------------------------------------------------------
 bool BinaryNewickVector::IsCloseBracketRight(const int pos) const
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
//---------------------------------------------------------------------------
bool BinaryNewickVector::IsOpenBracketLeft(const int pos) const
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
//---------------------------------------------------------------------------
bool BinaryNewickVector::IsSimple() const
{
  return Newick::IsSimple(m_v);
}
//---------------------------------------------------------------------------
//void BinaryNewickVector::SetTheta(const double theta)
//{
//  assert(theta > 0.0);
//  m_theta = theta;
//}
//---------------------------------------------------------------------------
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
const BinaryNewickVector BinaryNewickVector::LoseBrackets(const int x, const int i) const
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

  return BinaryNewickVector(v_copy);
}
//---------------------------------------------------------------------------
bool BinaryNewickVector::NewickCompare(
  const std::vector<int>& lhs,
  const std::vector<int>& rhs)
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
//---------------------------------------------------------------------------
int BinaryNewickVector::Size() const
{
  return boost::numeric_cast<int>(m_v.size());
}
//---------------------------------------------------------------------------
const BinaryNewickVector BinaryNewickVector::TermIsNotOne(const int i) const
{
  assert(m_v[i]>1);
  std::vector<int> v(m_v);
  --v[i];
  return BinaryNewickVector(v);
}
//---------------------------------------------------------------------------
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
const BinaryNewickVector BinaryNewickVector::TermIsOne(const int i) const
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
//---------------------------------------------------------------------------
void BinaryNewickVector::Test()
{

  //Check that well-formed Newicks are confirmed valid
  {
    const std::vector<std::string> v = Newick::CreateValidNewicks();
    BOOST_FOREACH(const std::string& s,v)
    {
      TRACE(std::string("I must be accepted: ") + s);
      //Check if valid newicks (as std::string) are marked as valid
      try
      {
        Newick::CheckNewick(s);
      }
      catch (std::exception& e)
      {
        std::cerr << "(" << __FILE__ << "," << __LINE__ << ") "
          << s << ": " << e.what() << '\n';
      }
      //Check if valid newicks (as std::vector) are marked as valid
      try
      {
        const std::vector<int> n = Newick::StringToNewick(s);
        Newick::CheckNewick(n);
        assert(Newick::IsNewick(n));
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (converted to std::vector<int>): "
          << e.what();
      }
      //Check std::string conversion (from BinaryNewickVector(std::string))
      if ( !Newick::IsUnaryNewick(Newick::StringToNewick(s))
        && !Newick::IsBinaryNewick(Newick::StringToNewick(s)))
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
        const std::vector<int> n = Newick::StringToNewick(s);
        BinaryNewickVector temp(n);
        assert(s == temp.ToStr());
      }
      catch (std::exception& e)
      {
        std::cerr << s
          << " (BinaryNewickVector from std::vector<int>): "
          << e.what();
      }
      assert(Newick::IsNewick(s));
      //Check the simpler Newicks
      {
        const std::vector<std::vector<int> > simpler
          = Newick::GetSimplerBinaryNewicks(
            Newick::StringToNewick(s));
        BOOST_FOREACH(const std::vector<int> simple,simpler)
        {
          assert(Newick::IsNewick(simple));
          Newick::CheckNewick(simple);
        }
      }
      //Check the branches, only of binary Newicks
      if (Newick::IsBinaryNewick(Newick::StringToNewick(s)))
      {
        const std::pair<std::vector<int>,std::vector<int> > b
            = Newick::GetRootBranchesBinary(Newick::StringToNewick(s));
        assert(Newick::IsNewick(b.first));
        assert(Newick::IsNewick(b.second));
      }
    }
  }
}
//---------------------------------------------------------------------------
const std::string BinaryNewickVector::ToStr() const
{
  assert(Newick::IsNewick(m_v));
  return Newick::NewickToString(m_v);
}
//---------------------------------------------------------------------------
bool operator<(const BinaryNewickVector& lhs, const BinaryNewickVector& rhs)
{
  //return lhs.v < rhs.v;
  return BinaryNewickVector::NewickCompare(lhs.Peek(),rhs.Peek());
}
//---------------------------------------------------------------------------
