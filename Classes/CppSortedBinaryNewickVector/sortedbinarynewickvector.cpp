//---------------------------------------------------------------------------
/*
  The Rampal Etienne Project, calculates the probability of a phylogeny
  (C) 2009-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "sortedbinarynewickvector.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

#include <boost/numeric/conversion/cast.hpp>

#include "binarynewickvector.h"
#include "newick.h"

#pragma GCC diagnostic pop

ribi::SortedBinaryNewickVector::SortedBinaryNewickVector(const SortedBinaryNewickVector& rhs)
  : m_v(rhs.Peek())
{
  assert(Newick::IsNewick(m_v));
  assert(Newick::IsUnaryNewick(m_v) || Newick::IsBinaryNewick(m_v));
  //Assume rhs is sorted
}

ribi::SortedBinaryNewickVector::SortedBinaryNewickVector(const std::vector<int>& any_v)
  : m_v(any_v)
{
  assert(Empty()
    || ( Newick::IsNewick(m_v)
      && (Newick::IsUnaryNewick(m_v)
      || Newick::IsBinaryNewick(m_v))));
  Sort();
}

ribi::SortedBinaryNewickVector::SortedBinaryNewickVector(const BinaryNewickVector& rhs)
  : m_v(rhs.Peek())
{
  assert(Newick::IsNewick(m_v));
  assert(Newick::IsUnaryNewick(m_v)
      || Newick::IsBinaryNewick(m_v));
  Sort();
}

bool ribi::operator<(const SortedBinaryNewickVector& lhs, const SortedBinaryNewickVector& rhs)
{
  //return lhs.v < rhs.v;
  return ribi::SortedBinaryNewickVector::NewickCompare(lhs.Peek(),rhs.Peek());
}

double ribi::SortedBinaryNewickVector::CalculateProbability(
  const std::string& newick_str,
  const double theta)
{
  assert(Newick::IsNewick(newick_str));
  assert(Newick::IsUnaryNewick(Newick::StringToNewick(newick_str))
      || Newick::IsBinaryNewick(Newick::StringToNewick(newick_str)));
  assert(theta > 0.0);
  SortedBinaryNewickVector newick(newick_str);
  NewickStorage<SortedBinaryNewickVector> storage(newick);
  return Newick::CalculateProbability(
    newick,
    theta,
    storage);

}

std::string ribi::SortedBinaryNewickVector::ToStr() const
{
  return Newick::NewickToString(Peek());
}

 double ribi::SortedBinaryNewickVector::CalcDenominator(
   const double theta) const
{
  return Newick::CalcDenominator(Peek(),theta);
}

//From a certain SortedBinaryNewickVector,
//returns the probability
 double ribi::SortedBinaryNewickVector::CalcProbabilitySimpleNewick(const double theta) const
{
  assert(IsSimple());

  const int sz = m_v.size();

  int n=0;
  int k=0;
  double probability = 1.0;

  for (int i=0; i!=sz; ++i)
  {
    if (m_v[i]>0)
    {
      const int ni = m_v[i];
      ++k;
      ++n;
      for (int p=1; p!=ni; ++p, ++n)
      {
        probability *= (static_cast<double>(p) / ( static_cast<double>(n) + theta));
      }
      probability /= ( static_cast<double>(n) + theta);
    }
  }
  probability *= (static_cast<double>(n)+theta)
    * std::pow(theta,static_cast<double>(k-1));
  return probability;
}

int ribi::SortedBinaryNewickVector::FindPosAfter(const std::vector<int>& v,const int x, const int index)
{
  const int sz = v.size();
  for (int i=index; i!=sz; ++i)
  {
    if (v[i]==x) return i;
  }
  return sz;
}

int ribi::SortedBinaryNewickVector::FindPosBefore(const std::vector<int>& v,const int x, const int index)
{

  for (int i=index; i!=-1; --i)
  {
    if (v[i]==x) return i;
  }
  return -1;
}

std::string ribi::SortedBinaryNewickVector::GetVersion() noexcept
{
  return "3.0";
}

std::vector<std::string> ribi::SortedBinaryNewickVector::GetVersionHistory() noexcept
{
  return {
    "2011-03-11: Version 3.0: initial versioning, following BinaryNewickVector"
  };
}

bool ribi::SortedBinaryNewickVector::IsCloseBracketRight(const int pos) const
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

 bool ribi::SortedBinaryNewickVector::IsOpenBracketLeft(const int pos) const
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

//If there is at least one bracket open
 bool ribi::SortedBinaryNewickVector::IsSimple() const
{
  return Newick::IsSimple(Peek());
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
const ribi::SortedBinaryNewickVector ribi::SortedBinaryNewickVector::LoseBrackets(const int x, const int i) const
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

  return SortedBinaryNewickVector(v_copy);
}

const ribi::SortedBinaryNewickVector ribi::SortedBinaryNewickVector::TermIsNotOne(const int i) const
{
  assert(m_v[i]>1);
  std::vector<int> v(m_v);
  --v[i];
  return SortedBinaryNewickVector(v);
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
const ribi::SortedBinaryNewickVector ribi::SortedBinaryNewickVector::TermIsOne(const int i) const
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
  return SortedBinaryNewickVector(std::vector<int>());
}

void ribi::SortedBinaryNewickVector::Sort()
{
  //return;
  #ifndef _WIN32
    //g++ has some trouble with type conversions
    typedef std::vector<int>::const_iterator Iter;
    const Iter b = m_v.begin();
    const Iter e = m_v.end();
    m_v = Sort(b,e);
  #else
    m_v = Sort(m_v.begin(),m_v.end());
  #endif
}

const std::vector<int> ribi::SortedBinaryNewickVector::Sort(
  const std::vector<int>::const_iterator b,
  const std::vector<int>::const_iterator e) const
{
  int level = 0;
  std::vector<int> v;
  std::vector<std::vector<int> > v_sub;
  std::vector<int>::const_iterator b_sub(e); //e, because g++ does not allow a null
  for (std::vector<int>::const_iterator i = b; i!=e; ++i)
  {
    const int x = *i;
    if (x == Newick::bracket_open)
    {
      ++level;
      if (level == 1)
      {
        //i+1, because the branch starts directly after the bracket open
        b_sub = i + 1;
      }
    }
    else if (x == Newick::bracket_close)
    {
      if (level == 1)
      {
        //i, because the branch ends directly before the bracket open
        //TRACE(ToString(std::vector<int>(b_sub,i),false));
        v_sub.push_back(Sort(b_sub,i));
        b_sub = e; //e, because g++ does not allow a null
      }
      --level;
    }
    else if (level==0)
    {
      //x is a value
      v.push_back(x);
    }
  }

  //assert(std::find(v.begin(),v.end(),
  //  std::bind1st(std::equal_to<int>(),
  //    static_cast<int>(Newick::bracket_open)))
  //  == v.end()); //v must not contain brackets open
  //assert(std::find(v.begin(),v.end(),
  //  std::bind1st(std::equal_to<int>(),
  //    static_cast<int>(Newick::bracket_close)))
  //  == v.end()); //v must not contain brackets close

  std::sort(std::begin(v),std::end(v)); //v only contains values
  std::sort(v_sub.begin(),v_sub.end(),NewickCompare);

  //TRACE("Level 0 entries: " + ToString(v,false));

  //Concatenate the values in v with the sorted branches in v_sub
  const int n_subs = v_sub.size();
  for (int i=0; i!=n_subs; ++i)
  {
    //TRACE("Level 1 entries: " + ToString(std::vector<int>(v_sub[i].begin(),v_sub[i].end()),false));
    v.push_back(Newick::bracket_open);
    std::copy(v_sub[i].begin(),v_sub[i].end(),std::back_inserter(v));
    v.push_back(Newick::bracket_close);
  }

  //TRACE("Sort to std::vector: " + ToString(v,false));
  assert(e - b == static_cast<int>(v.size()));
  return v;
}

bool ribi::SortedBinaryNewickVector::NewickCompare(
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
