//---------------------------------------------------------------------------
/*
Newick, Newick functions
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
//From http://www.richelbilderbeek.nl/CppNewick.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "newick.h"

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


#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "BigIntegerLibrary.hh"

#include "newickcpp98.h"
#include "testtimer.h"
#include "trace.h"

#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppAccumulate_if.htm
template
  <
  typename InputIterator,
  typename ElementType,
  typename Predicate
  >
const ElementType Accumulate_if(
  InputIterator first,
  const InputIterator last,
  ElementType init,
  const Predicate predicate)
{
  for (; first != last; ++first)
    if (predicate(*first)) init += *first;
  return init;
}

///Copy_if was dropped from the standard library by accident.
///From http://www.richelbilderbeek.nl/CppCopy_if.htm
template<typename In, typename Out, typename Pred>
Out Copy_if(In first, In last, Out res, Pred Pr)
{
  while (first != last)
  {
    if (Pr(*first))
      *res++ = *first;
    ++first;
  }
  return res;
}

//From http://www.richelbilderbeek.nl/CppFunctorIncrease.htm
struct Increase
{
  explicit Increase(const int& init_value = 0) noexcept : m_value(init_value) {}
  void operator()(int& anything) noexcept
  {
    anything = m_value;
    ++m_value;
  }
  private:
  int m_value;
};

ribi::Newick::Newick()
{
  #ifndef NDEBUG
  Test();
  #endif
}

BigInteger ribi::Newick::CalcComplexity(const std::vector<int>& v)
{
  if (v.empty()) return 0;
  //assert(IsNewick(v));
  BigInteger complexity = 1;
  int n_frequencies = 0;
  const int sz = v.size();
  for (int i=0; i!=sz; ++i)
  {
    const int x = v[i];
    if (x < 0) continue; //Ignore if x is not a number
    ++n_frequencies;
    complexity*=x;
  }
  complexity*=n_frequencies;
  return complexity;
}

double ribi::Newick::CalcDenominator(const std::vector<int>& v,const double theta)
{
  int sum_above_zero = 0;
  int sum_above_one  = 0;
  for(const int& i: v)
  {
    if (i > 0) sum_above_zero+= i;
    if (i > 1) sum_above_one += i;
  }
  const double d
    = boost::numeric_cast<double>(
      sum_above_zero * (sum_above_zero - 1))
    + (boost::numeric_cast<double>(sum_above_one)
       * theta);
  return d;
}

BigInteger ribi::Newick::CalcNumOfCombinationsBinary(const std::vector<int>& v)
{
  assert(Newick::IsNewick(v));

  //Get all positives
  std::vector<BigInteger> positives;
  Copy_if(
    v.begin(),v.end(),
    std::back_inserter(positives),
    std::bind2nd(std::greater<BigInteger>(),0));

  //Obtain numerator = (SUM(x))!
  const int sum_values = Accumulate_if(v.begin(),v.end(),0,std::bind2nd(std::greater<int>(),0));

  //std::clog << "sum_values:" << sum_values << '\n';
  BigInteger numerator = FactorialBigInt(sum_values);
  //std::clog << "Numerator:" << numerator << '\n';

  //Obtain factorialated positives
  BigInteger denominator = 1;
  for(const int& i: v)
  {
    if (i<=0) continue;
    const BigInteger i_temp = FactorialBigInt(i);
    denominator*=i_temp;
    //std::clog << "Denominator:" << denominator << '\n';
  }

  //Obtain number_of_symmetries
  const BigInteger number_of_symmetries = CalcNumOfSymmetriesBinary(v);

  //Add number_of_symmetries times a 2 to denominator terms
  for(BigInteger i=0; i!=number_of_symmetries; ++i)
  {
    denominator*=2;
    //std::clog << "Denominator:" << denominator << '\n';
  }

  //Return the division
  numerator/=denominator;
  return numerator;
}

BigInteger ribi::Newick::CalcNumOfSymmetriesBinary(std::vector<int> v)
{
  assert(IsNewick(v));
  assert(IsBinaryNewick(v));
  if (v.size() == 3) return 0;
  if (v.size() == 4) return (v[1] > 0 && v[1]==v[2] ? 1 : 0);

  const int n_reserved
    = *std::max_element(std::begin(v),std::end(v))
    + std::count_if(v.begin(), v.end(), std::bind2nd(std::greater<int>(),0));

  BigInteger n_symmetries = 0;
  int id = n_reserved + 1;

  std::map<std::pair<int,int>,int> ids;

  while (1)
  {
    //std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::clog," ")); std::clog << '\n';
    //Count number of symmetries
    assert(!v.empty());
    const std::size_t sz = v.size();
    assert(sz >= 2);
    const std::size_t j = sz - 1;
    for (std::size_t i = 0; i!=j; ++i)
    {
      if (v[i] > 0 && v[i]==v[i+1]) ++n_symmetries;
    }
    //Collect all leaves and store new leaves
    std::vector<std::pair<int,int> > leaves;
    for (std::size_t i = 0; i!=j; ++i)
    {
      if (v[i] > 0 && v[i+1] > 0)
      {
        //Keep pair sorted
        const std::pair<int,int> p
          = (v[i] <= v[i+1]
          ? std::make_pair(v[i+0],v[i+1])
          : std::make_pair(v[i+1],v[i+0]));
        //If this leaf is new, store it
        if (ids.find(p)==ids.end())
        {
          ids[p] = id;
          ++id;
        }
      }
    }
    //Generalize all leaves
    for (std::size_t i = 0; i < v.size()-1; ++i)
    {
      assert(v.size()>2);
      if (v[i] > 0 && v[i+1] > 0)
      {
        //Keep pair sorted
        const std::pair<int,int> p
          = (v[i] <= v[i+1]
          ? std::make_pair(v[i+0],v[i+1])
          : std::make_pair(v[i+1],v[i+0]));
        //If this leaf is new, store it
        assert(ids.find(p)!=ids.end() && "Leaf should have been stored already");
        assert(i > 0);
        std::vector<int> v_new;
        std::copy(v.begin(),v.begin() + i - 1,std::back_inserter(v_new));
        const int id = ids[p];
        v_new.push_back(id);
        std::copy(v.begin() + i + 3,v.end(),std::back_inserter(v_new));
        v = v_new;
        i = (i-1 > 0 ? i-1 : 0);
        //Check if there are more leaves to be generalized
        if (v.size()<=4)
        {
          //Check if the last (X,Y) is symmetrical...
          return n_symmetries + (v[1] > 0 && v[1]==v[2] ? 1 : 0);
          break;
        }
      }
    }
  }
}

double ribi::Newick::CalcProbabilitySimpleNewick(
  const std::vector<int>& v,
  const double theta)
{
  assert(IsNewick(v));
  assert(IsSimple(v));
  const int sz = v.size();

  int n=0;
  int k=0;

  double probability = 1.0;

  for (int i=0; i!=sz; ++i)
  {
    if (v[i]>0)
    {
      const int ni = v[i];
      ++k;
      ++n;
      for (int p=1; p!=ni; ++p, ++n)
      {
        probability *= (static_cast<double>(p)
          / ( static_cast<double>(n) + theta));
      }
      probability /= ( static_cast<double>(n) + theta);
    }
  }
  probability *= (static_cast<double>(n)+theta)
    * std::pow(theta,static_cast<double>(k-1));
  return probability;
}

void ribi::Newick::CheckNewick(const std::string& s)
{
  #ifndef NDEBUG
  //std::clog
  //  << "Researching Newick string: '"
  //  << s << "'\n";
  #endif

  if (s.size()<3)
    throw std::invalid_argument(
      "The Newick std::string must have a size of at least three characters");
  if (s[0]!='(')
    throw std::invalid_argument(
      "The Newick std::string must start with an opening bracket ('(').");
  if (s[s.size()-1]!=')')
    throw std::invalid_argument(
      "The Newick std::string must end with a closing bracket (')').");
  if (std::count(s.begin(),s.end(),'(')
    !=std::count(s.begin(),s.end(),')'))
    throw std::invalid_argument(
       "The Newick std::string must have as much opening "
       "as closing brackets #1");
  if (s.find("(0")!=std::string::npos)
    throw std::invalid_argument(
      "A std::string Newick frequency cannot be or "
      "start with a zero (#1)");
  if (s.find(",0")!=std::string::npos)
    throw std::invalid_argument(
      "A std::string Newick frequency cannot be or "
      "start with a zero (#2)");
  if (s.find("()")!=std::string::npos)
    throw std::invalid_argument(
      "The Newick std::string cannot have "
      "a consecutive opening and closing bracket");
  if (s.find(",,")!=std::string::npos)
    throw std::invalid_argument(
      "A Newick std::string can have no consecutive comma's");
  if (s.find("(,")!=std::string::npos)
    throw std::invalid_argument(
      "A Newick std::string cannot have comma "
      "directly after an opening bracket");
  if (s.find(",)")!=std::string::npos)
    throw std::invalid_argument(
      "A Newick std::string cannot have comma "
      "directly before a closing bracket");

  std::string s_copy = s;
  while(s_copy.size()>2) //Find a leaf and cut it until the string is empty
  {
    #ifndef NDEBUG
    //std::clog
    //  << "Researching Newick string leaf: '"
    //  << s_copy
    //  << "'\n";
    #endif
    //Find a leaf
    //Find index i (starting opening bracket) and j (closing bracket)
    const std::size_t sz = s_copy.size();
    std::size_t i = 0;
    std::size_t j = 0;
    for (i=0 ; i!=sz; ++i) //Index of opening bracket
    {
      if (s_copy[i]!='(') continue;

      assert(s_copy[i]=='(');
      assert(i+1 < s_copy.size());
      for (j=i+1; j!=sz; ++j)
      {
        if (s_copy[j]=='(') { j = 0; break; }
        if (s_copy[j]!=')') continue;
        break;
      }

      if (j ==  0) continue; //j cannot be 0 after previous for loop
      if (j == sz)
        throw std::invalid_argument(
          "The Newick std::string must have as much opening as closing brackets #2");
      break;
    }
    if (s_copy[i]!='(')
      throw std::invalid_argument(
        "The Newick std::string must have as much opening as closing brackets #3");
    //Indices i and j found
    //Is range between i and j valid?
    if (s_copy[i]!='(')
      throw std::logic_error(
        "Bilderbikkel incorrectly assumes that s_copy[i]=='('");
    if (s_copy[j]!=')')
      throw std::logic_error(
        "Bilderbikkel incorrectly assumes that s_copy[j]==')'");
    //Check the range
    for (size_t k=i+1; k!=j; ++k)
    {
      if ( s_copy[k]!='0'
        && s_copy[k]!='1'
        && s_copy[k]!='2'
        && s_copy[k]!='3'
        && s_copy[k]!='4'
        && s_copy[k]!='5'
        && s_copy[k]!='6'
        && s_copy[k]!='7'
        && s_copy[k]!='8'
        && s_copy[k]!='9'
        && s_copy[k]!='0'
        && s_copy[k]!=',')
      {
        std::stringstream err_msg;
        err_msg << "Invalid non-number character in input: '" << s_copy[k] << "'";
        throw std::invalid_argument(err_msg.str().c_str());
      }
    }
    if (i > 0 && s_copy[i-1]=='(' &&
      j +1 < sz && s_copy[j + 1] == ')')
    {
      throw std::invalid_argument(
        "Newicks must not have the form ((X))");
    }
    //Check if there is a comma somewhere between brackets
    if (i > 0 //< (1) is valid, (1,(2)) not, ((1),2) not
      && std::find(
        s_copy.begin()+i,s_copy.begin()+j,',')
          == s_copy.begin()+j)
    {
      throw std::invalid_argument(
        "The Newick std::string cannot have the sequence "
        "of an opening bracket, a value and a closing bracket "
        "as a \'complex\' leaf");
    }
    //Range is assumed valid
    //Cut the leaf (turns '(1,2)' to (9) )
    assert(s_copy[i]=='(');
    assert(s_copy[j]==')');
    const std::string s_new_1 = s_copy.substr(0,i);
    const std::string s_new_2 = s_copy.substr(j+1,sz-j-1); //OK
    const std::string s_new =  s_new_1 + "9" + s_new_2;
    s_copy = s_new;
  }
}

void ribi::Newick::CheckNewick(const std::vector<int>& v)
{
  #ifndef NDEBUG
  //std::clog << "Researching newick: '"
  //  << DumbNewickToString(v) << '\n';
  #endif

  if (v.size()<3)
    throw std::invalid_argument(
      "The Newick std::vector<int> must have a size of at least three characters");
  if (v[0]!=bracket_open)
    throw std::invalid_argument(
      "The Newick std::vector<int> must start with an opening bracket ('(').");
  if (v[v.size()-1]!=bracket_close)
    throw std::invalid_argument(
      "The Newick std::vector<int> must end with a closing bracket (')').");
  if (std::count(v.begin(),v.end(),static_cast<int>(bracket_open))
    !=std::count(v.begin(),v.end(),static_cast<int>(bracket_close)))
    throw std::invalid_argument(
       "The Newick std::string must have as much opening "
       "as closing brackets #1");
  if (std::count(v.begin(),v.end(),0))
    throw std::invalid_argument(
      "A std::vector<int> Newick frequency cannot be "
      "zero");


  std::vector<int> v_copy = v;
  while(v_copy.size()>2) //Find a leaf and cut it until the string is empty
  {
    #ifndef NDEBUG
    //std::clog << "Researching leaf: '";
    //std::copy(v_copy.begin(),v_copy.end(),std::ostream_iterator<int>(std::clog," "));
    //std::clog << "'\n";
    #endif
    //Find a leaf
    //Find index i (starting opening bracket) and j (closing bracket)
    const std::size_t sz = v_copy.size();
    std::size_t i = 0;
    std::size_t j = 0;
    for (i=0 ; i!=sz; ++i) //Index of opening bracket
    {
      if (v_copy[i]!=bracket_open) continue;

      assert(v_copy[i]==bracket_open);

      assert(i+1 < v_copy.size());

      if (v_copy[i+1]==bracket_close)
        throw std::invalid_argument(
          "The Newick std::vector<int> cannot have "
          "a consecutive opening and closing bracket");

      for (j=i+1; j!=sz; ++j)
      {
        if (v_copy[j]==bracket_open) { j = 0; break; }
        if (v_copy[j]!=bracket_close) continue;
        break;
      }
      if (i + 2 == j && j < sz - 1) //< (1) is valid, (1,(2)) not, ((1),2) not
      {
        throw std::invalid_argument(
          "The Newick std::vector<int> cannot have the sequence"
          "of an opening bracket, a value and a closing bracket"
          "as a \'complex\' leaf");
      }

      if (j ==  0) continue; //j cannot be 0 after previous for loop
      if (j == sz)
        throw std::invalid_argument(
          "The Newick std::vector<int> must have as much opening "
          "as closing brackets #2");
      break;
    }
    if (v_copy[i]!=bracket_open)
      throw std::invalid_argument(
        "The Newick std::vector<int> must have as much opening "
        "as closing brackets #3");
    //Indices i and j found
    //Is range between i and j valid?
    if (v_copy[i]!=bracket_open)
      throw std::logic_error(
        "Bilderbikkel incorrectly assumes that s_copy[i]=='('");
    if (v_copy[j]!=bracket_close)
      throw std::logic_error(
        "Bilderbikkel incorrectly assumes that s_copy[j]==')'");
    //Check the range
    for (size_t k=i+1; k!=j; ++k)
    {
      if (v_copy[k] < 0)
      {
        std::ostringstream err_msg;
        err_msg << "Invalid non-number in input: '" << v_copy[k] << "'";
        throw std::invalid_argument(err_msg.str().c_str());
      }
    }
    //Range is assumed valid
    //Cut the leaf
    //Changes '(1,2)' to '(999)'
    assert(v_copy[i]==bracket_open);
    assert(v_copy[j]==bracket_close);
    std::vector<int> v_new(v_copy.begin(),v_copy.begin() + i);
    v_new.push_back(999);
    std::copy(v_copy.begin() + j + 1, v_copy.end(),std::back_inserter(v_new));
    v_copy = v_new;
  }
}

std::vector<std::string> ribi::Newick::CreateInvalidNewicks() noexcept
{
  std::vector<std::string> v;
  v.push_back("");
  v.push_back("(");
  v.push_back(")");
  v.push_back("1");
  v.push_back("1234");
  v.push_back(")1234(");
  v.push_back("()1234()");
  v.push_back("(1234,)");
  v.push_back("(,1234,)");
  v.push_back("()");
  v.push_back("(0)");
  v.push_back("(-)");
  v.push_back("(-1)");
  v.push_back("(0,0)");
  v.push_back("(1,0)");
  v.push_back("(0,1)");
  v.push_back("(0,(1,1))");
  v.push_back("(1,(0,1))");
  v.push_back("(1,(1,0))");
  v.push_back("((0,1),1)");
  v.push_back("((1,0),1)");
  v.push_back("((1,1),0)");
  v.push_back("((2))");
  v.push_back("(1,(2,3)");
  v.push_back("(1,(2))");
  v.push_back("(1,((3)))");
  v.push_back("(11,(22,33)");
  v.push_back("(22,33),33)");
  v.push_back("1,2");
  v.push_back("(1,1),");
  v.push_back("(2,2),");
  v.push_back("((2,2),2),");
  v.push_back(",(1,1)");
  v.push_back(",(2,2)");
  v.push_back(",((2,2),2)");
  v.push_back(",(1,1),");
  v.push_back(",(2,2),");
  v.push_back("(2,(1,1)),");
  v.push_back(",((2,2),2),");
  v.push_back("(1,2");
  v.push_back("(-1,2");
  v.push_back("(1,-2");
  v.push_back("(0,-2");
  v.push_back("(-0,2");
  v.push_back("(1,,2)");
  v.push_back("(1,2))");
  v.push_back("(1,(2),3)");
  v.push_back("((1,2),(3,4))()");
  return v;
}

std::string ribi::Newick::CreateRandomNewick(const int n,const int max) noexcept
{
  const std::vector<int> v = CreateRandomBinaryNewickVector(n,max);
  return NewickToString(v);
}

std::vector<int> ribi::Newick::CreateRandomBinaryNewickVector(const int n,const int max) noexcept
{
  assert(n>0);
  assert(max>1);

  std::vector<int> v;
  v.reserve(2 + (n*2));

  v.push_back(bracket_open);

  v.push_back(1 + (std::rand() % (max-1) ));
  if (n==1)
  {
    v.push_back(bracket_close);
    return v;
  }
  v.push_back(1 + (std::rand() % (max-1) ));

  v.push_back(bracket_close); //??? IntVector format has no trailing bracket

  if (n==2)
  {
    return v;
  }

  for (int i=2; i!=n; ++i)
  {
    if ((std::rand() >> 4) % 2)
    {
      //Append
      std::vector<int> new_v;
      new_v.reserve(2 + v.size());
      new_v.push_back(bracket_open);

      std::copy(v.begin(),v.end(),std::back_inserter(new_v));

      new_v.push_back(1 + (std::rand() % (max-1)));
      new_v.push_back(bracket_close);
      std::swap(v,new_v);
    }
    else
    {
      //Prepend
      std::vector<int> new_v;
      new_v.reserve(2 + v.size());
      new_v.push_back(bracket_open);
      new_v.push_back(1 + (std::rand() % (max-1)));

      std::copy(v.begin(),v.end(),std::back_inserter(new_v));

      new_v.push_back(bracket_close);
      std::swap(v,new_v);
    }
    assert(std::count(v.begin(),v.end(),static_cast<int>(bracket_open ))
        == std::count(v.begin(),v.end(),static_cast<int>(bracket_close)));
  }
  assert(IsNewick(v));
  return v;
}

std::vector<std::string> ribi::Newick::CreateValidBinaryNewicks() noexcept
{
  std::vector<std::string> v;
  v.push_back("(1,2)");
  v.push_back("(11,22)");
  v.push_back("(1,(1,1))");
  v.push_back("(1,(1,2))");
  v.push_back("(1,(2,1))");
  v.push_back("(1,(2,2))");
  v.push_back("(1,(2,3))");
  v.push_back("(2,(1,1))");
  v.push_back("(2,(1,2))");
  v.push_back("(2,(2,1))");
  v.push_back("(2,(2,2))");
  v.push_back("(4,(2,3))");
  v.push_back("((2,3),4)");
  v.push_back("(2,((2,3),4))");
  v.push_back("(11,(22,33))");
  v.push_back("((22,33),33)");
  v.push_back("((1,2),(3,4))");
  v.push_back("(((1,2),(3,4)),5)");
  v.push_back("(1,((2,3),(4,5)))");
  v.push_back("((11,2),(3,44))");
  v.push_back("(((1,22),(33,4)),(55,6))");
  return v;
}

std::vector<std::string> ribi::Newick::CreateValidTrinaryNewicks() noexcept
{
  //#ifdef __GXX_EXPERIMENTAL_CXX0X__
  ///\note
  ///The tests below must be put back in again once
  #ifdef DEBUG_TEMP_REMOVE_2738236826438
  return
    {
      "(1,1,1)",
      "(1,2,3)",
      "((1,1),1,1)",
      "(1,(1,1),1)",
      "(1,1,(1,1))",
      "(1,(2,3,4))",
      "(1,2,(3,4))",
      "(1,2,(3,4,5))",
      "((1,2,3),4,5)",
      "(11,22,33)",
      "(11,(22,33,44))",
      "(11,22,(33,44))",
      "(11,22,(33,44,55))",
      "((11,22,33),44,55)",
      "((1,2),(3,4),(5,6))",
      "((1,2,3),(4,5),(6,7))",
      "((1,2),(3,4,5),(6,7))",
      "((1,2),(3,4),(5,6,7))",
      "((1,2,3),(4,5),(6,7))",
      "((1,2),(3,4,5),(6,7))",
      "((1,2),(3,4),(5,6,7))",
      "((1,2,3),(4,5,6),(7,8))",
      "((1,2),(3,4,5),(6,7,8))",
      "((1,2,3),(4,5),(6,7,8))",
      "((1,2,3),(4,5,6),(7,8,9))",
      "((11,22,33),(44,55,66),(77,88,99))"
    };
  #else
    return NewickCpp98().CreateValidTrinaryNewicks();
  #endif
}

std::vector<std::string> ribi::Newick::CreateValidNewicks() noexcept
{
  std::vector<std::string> v;
  {
    std::vector<std::string> w = CreateValidUnaryNewicks();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  {
    std::vector<std::string> w = CreateValidBinaryNewicks();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  {
    std::vector<std::string> w = CreateValidTrinaryNewicks();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  v.push_back("(1,2,3,4)");
  v.push_back("(1,2,3,4,5)");
  v.push_back("(1,2,3,4,5,6)");
  v.push_back("(1,2,3,4,5,6,7)");
  v.push_back("(1,2,3,4,5,6,7,8)");
  v.push_back("((1,2,3,4,5,6,7,8),(1,2,3,4,5,6,7,8),(1,2,3,4,5,6,7,8))");
  return v;
}

std::vector<std::string> ribi::Newick::CreateValidUnaryNewicks() noexcept
{
  std::vector<std::string> v;
  v.push_back("(1)");
  v.push_back("(9)");
  v.push_back("(123)");
  return v;
}

std::string ribi::Newick::DumbNewickToString(const std::vector<int>& v) noexcept
{
  std::string s;
  s.reserve(2 * v.size()); //Just a guess
  const int sz = v.size();
  for (int i=0; i!=sz; ++i)
  {
    const int x = v[i];
    if (x >= 0)
    {
      s+=boost::lexical_cast<std::string>(x);
      const int next = v[i+1];
      if (next > 0 || next == bracket_open)
      {
        s+=",";
      }
    }
    else if (x==bracket_open)
    {
      s+="(";
    }
    else if (x==bracket_close)
    {
      s+=")";
      //Final closing bracket?
      if (i+1==sz) break;
      const int next = v[i+1];
      if (next > 0 || next == bracket_open)
      {
        s+=",";
      }
    }
    else
    {
      s+="x"; //Unknown character
    }
  }
  return s;
}

std::vector<int> ribi::Newick::Factorial(const std::vector<int>& v_original) noexcept
{
  std::vector<int> v(v_original);
  std::transform(v.begin(),v.end(),v.begin(),
    [](const int i) { return Newick().Factorial(i); }
    //std::ptr_fun<int,int>(Factorial)
  );
  return v;
}

int ribi::Newick::Factorial(const int n) noexcept
{
  assert(n>=0);
  int result = 1;
  for (int i=1; i<=n; ++i)
  {
    result*=i;
  }
  return result;
}

BigInteger ribi::Newick::FactorialBigInt(const int n) noexcept
{
  assert(n>=0);
  BigInteger result = 1;
  for (int i=1; i<=n; ++i)
  {
    result*=i;
  }
  return result;
}

int ribi::Newick::FindPosAfter(const std::vector<int>& v,const int x, const int index) noexcept
{
  assert(!v.empty());
  const int sz = v.size();
  for (int i=index+1; i!=sz; ++i)
  {
    assert(i >= 0);
    assert(i < sz);
    if (v[i]==x) return i;
  }
  return sz;
}

int ribi::Newick::FindPosBefore(const std::vector<int>& v,const int x, const int index) noexcept
{
  for (int i=index-1; i!=-1; --i)
  {
    if (v[i]==x) return i;
  }
  return -1;
}

std::vector<int> ribi::Newick::GetDepth(const std::vector<int>& n) noexcept
{
  assert(IsNewick(n));
  std::vector<int> v;
  int depth = -1;
  for(const int& x: n)
  {
    if (x == Newick::bracket_open) ++depth;
    v.push_back(depth);
    if (x == Newick::bracket_close) --depth;
  }
  assert(n.size() == v.size());
  return v;
}

std::vector<int> ribi::Newick::GetFactorialTerms(const int n) noexcept
{
  assert(n > 0);
  std::vector<int> v(n);
  std::for_each(v.begin(), v.end(),Increase(1));
  assert(std::count(v.begin(),v.end(),0)==0);
  return v;
}

std::vector<boost::tuple<std::string,double,double> > ribi::Newick::GetKnownProbabilities() noexcept
{
  //#ifdef __GXX_EXPERIMENTAL_CXX0X__
  ///\note
  ///The tests below must be put back in again once
  #ifdef DEBUG_TEMP_REMOVE_2738236826438
  const std::vector<boost::tuple<std::string,double,double> > v
    = {
    //Sum equals 1
    { "(1)"  , 10.0, 1.0000000 },
    //Sum equals 2
    { "(2)"  , 10.0, 0.0909091 },
    { "(1,1)", 10.0, 0.9090909 },
    //Sum equals 3
    { "(3)"      , 10.0, 0.0151515 },
    { "(1,2)"    , 10.0, 0.0757576 },
    { "(2,1)"    , 10.0, 0.0757576 },
    { "(1,(1,1))", 10.0, 0.2525253 },
    { "((1,1),1)", 10.0, 0.2525253 },
    //Trinary
    { "(1,1,1)"  , 10.0, 0.7575758 },
    //Sum equals 4
    { "(4)"      , 10.0, 0.0034965 },
    { "(1,3)"    , 10.0, 0.0116550 },
    { "(2,2)"    , 10.0, 0.0058275 },
    { "(3,1)"    , 10.0, 0.0116550 },
    { "(1,(1,2))", 10.0, 0.0194250 },
    { "(1,(2,1))", 10.0, 0.0194250 },
    { "(2,(1,1))", 10.0, 0.0194250 },
    { "((1,2),1)", 10.0, 0.0194250 },
    { "((2,1),1)", 10.0, 0.0194250 },
    { "((1,1),2)", 10.0, 0.0194250 },
    //Trinary
    { "(1,1,2)"    , 10.0, 0.0582751 },
    { "(1,2,1)"    , 10.0, 0.0582751 },
    { "(2,1,1)"    , 10.0, 0.0582751 },
    { "(1,1,(1,1))", 10.0, 0.1295001 }, //(1)(confirmed)
    { "(1,(1,1),1)", 10.0, 0.1295001 },
    { "((1,1),1,1)", 10.0, 0.1295001 },
    { "(1,(1,1,1))", 10.0, 0.0971251 }, //(2)(confirmed)
    { "((1,1,1),1)", 10.0, 0.0971251 },
    //Quadrary
    { "(1,1,1,1)", 10.0, 0.5827505 },
    //Sum equals 5
    { "(1,4)"        , 10.0, 0.0024975 },
    { "(2,3)"        , 10.0, 0.0008325 },
    { "(3,2)"        , 10.0, 0.0008325 },
    { "(4,1)"        , 10.0, 0.0024975 },
    { "(1,(1,3))"    , 10.0, 0.0028305 },
    { "(1,(2,2))"    , 10.0, 0.0012950 },
    { "(1,(3,1))"    , 10.0, 0.0028305 },
    { "(2,(1,2))"    , 10.0, 0.0014338 },
    { "(2,(2,1))"    , 10.0, 0.0014338 },
    { "(3,(1,1))"    , 10.0, 0.0026640 },
    //Trinary
    { "(1,1,(1,2))"  , 10.0, 0.0092731 }, //(3)(confirmed)
    { "(1,1,(2,1))"  , 10.0, 0.0092731 },
    { "(1,1,(1,1,1))", 10.0, 0.0348263 }, //(4)(confirmed)
    { "(1,(1,1,1),1)", 10.0, 0.0348263 },
    { "((1,1,1),1,1)", 10.0, 0.0348263 },
    { "(2,(1,1,1))"  , 10.0, 0.0070069 }, //(5)(confirmed)
    { "((1,1,1),2)"  , 10.0, 0.0070069 },
    { "(1,1,1,(1,1))", 10.0, 0.0692918 }, //(6)(confirmed)
    { "(1,2,(1,1))"  , 10.0, 0.0092223 }, //(7)(confirmed)
    { "(2,1,(1,1))"  , 10.0, 0.0092223 },
    { "(1,(1,1),2)"  , 10.0, 0.0092223 },
    { "(2,(1,1),1)"  , 10.0, 0.0092223 },
    { "((1,1),1,2)"  , 10.0, 0.0092223 },
    { "((1,1),2,1)"  , 10.0, 0.0092223 },
    { "(1,(1,1,2))"  , 10.0, 0.0069190 }, //(9)(confirmed)
    { "(1,(1,2,1))"  , 10.0, 0.0069190 },
    { "(1,(2,1,1))"  , 10.0, 0.0069190 },
    { "((1,1,2),1)"  , 10.0, 0.0069190 },
    { "((1,2,1),1)"  , 10.0, 0.0069190 },
    { "((2,1,1),1)"  , 10.0, 0.0069190 },
    //Quadrary
    { "(1,(1,1,1,1))", 10.0, 0.0415140 }, //(8)(confirmed)
    //Pentary
    { "(1,1,1,1,1)"  , 10.0, 0.4162504 },
    //Sum equals 6
    { "(1,5)"        , 10.0, 0.0006660 },
    { "(2,4)"        , 10.0, 0.0001665 },
    { "(3,3)"        , 10.0, 0.0001110 },
    { "(1,(1,4))"    , 10.0, 0.0005804 },
    { "(1,(2,3))"    , 10.0, 0.0001679 },
    { "(1,(3,2))"    , 10.0, 0.0001679 },
    { "(1,(4,1))"    , 10.0, 0.0005804 },
    { "(2,(1,3))"    , 10.0, 0.0001991 },
    { "(2,(2,2))"    , 10.0, 0.0000925 },
    { "(2,(3,1))"    , 10.0, 0.0001991 },
    { "(3,(1,2))"    , 10.0, 0.0001880 },
    { "(3,(2,1))"    , 10.0, 0.0001880 },
    { "(4,(1,1))"    , 10.0, 0.0005043 },
    //Trinary
    { "(1,1,(1,3))"  , 10.0, 0.0012712 },
    { "(1,1,(2,2))"  , 10.0, 0.0005563 },
    { "(1,1,(3,1))"  , 10.0, 0.0012712 },
    { "(1,(1,3),1)"  , 10.0, 0.0012712 },
    { "(1,(2,2),1)"  , 10.0, 0.0005563 },
    { "(1,(3,1),1)"  , 10.0, 0.0012712 },
    { "((1,3),1,1)"  , 10.0, 0.0012712 },
    { "((2,2),1,1)"  , 10.0, 0.0005563 },
    { "((3,1),1,1)"  , 10.0, 0.0012712 },
    { "(1,2,(1,2))"  , 10.0, 0.0006346 },
    { "(2,1,(1,2))"  , 10.0, 0.0006346 },
    { "(1,2,(2,1))"  , 10.0, 0.0006346 },
    { "(2,1,(2,1))"  , 10.0, 0.0006346 },
    { "(1,(2,1),2)"  , 10.0, 0.0006346 },
    { "(1,(1,2),2)"  , 10.0, 0.0006346 },
    { "(2,(2,1),1)"  , 10.0, 0.0006346 },
    { "(2,(1,2),1)"  , 10.0, 0.0006346 },
    { "(1,3,(1,1))"  , 10.0, 0.0011913 },
    { "(1,(1,1),3)"  , 10.0, 0.0011913 },
    { "((1,1),1,3)"  , 10.0, 0.0011913 },
    { "(3,(1,1),1)"  , 10.0, 0.0011913 },
    { "((1,1),3,1)"  , 10.0, 0.0011913 },
    { "(1,1,(1,1,2))", 10.0, 0.0023165 },
    { "(1,1,(1,2,1))", 10.0, 0.0023165 },
    { "(1,1,(2,1,1))", 10.0, 0.0023165 },
    { "(1,(1,1,2),1)", 10.0, 0.0023165 },
    { "(1,(1,2,1),1)", 10.0, 0.0023165 },
    { "(1,(2,1,1),1)", 10.0, 0.0023165 },
    { "((1,1,2),1,1)", 10.0, 0.0023165 },
    { "((1,2,1),1,1)", 10.0, 0.0023165 },
    { "((2,1,1),1,1)", 10.0, 0.0023165 },
    { "(1,2,(1,1,1))", 10.0, 0.0023323 },
    { "(2,1,(1,1,1))", 10.0, 0.0023323 },
    { "(1,(1,1,1),2)", 10.0, 0.0023323 },
    { "(2,(1,1,1),1)", 10.0, 0.0023323 },
    { "((1,1,1),1,2)", 10.0, 0.0023323 },
    { "((1,1,1),2,1)", 10.0, 0.0023323 },
    //Quadrary
    { "(1,(1,1,1,2))"  , 10.0, 0.0027574 },
    { "(1,(1,1,2,1))"  , 10.0, 0.0027574 },
    { "(1,(1,2,1,1))"  , 10.0, 0.0027574 },
    { "(1,(2,1,1,1))"  , 10.0, 0.0027574 },
    { "((1,1,1,2),1)"  , 10.0, 0.0027574 },
    { "((1,1,2,1),1)"  , 10.0, 0.0027574 },
    { "((1,2,1,1),1)"  , 10.0, 0.0027574 },
    { "((2,1,1,1),1)"  , 10.0, 0.0027574 },
    { "(2,(1,1,1,1))"  , 10.0, 0.0028154 },
    { "((1,1,1,1),2)"  , 10.0, 0.0028154 },
    //Pentary
    { "(1,(1,1,1,1,1))", 10.0, 0.0183824 }, //(7)
    { "((1,1,1,1,1),1)", 10.0, 0.0183824 },
    //Hexary
    { "(1,1,1,1,1,1)"  , 10.0, 0.2775003 }
  };
  return v;
  #else
    return NewickCpp98().GetKnownProbabilities();
  #endif
}

int ribi::Newick::GetLeafMaxArity(const std::vector<int>& n) noexcept
{
  assert(IsNewick(n));
  const int size = boost::numeric_cast<int>(n.size());
  if (IsSimple(n)) return size - 2;

  int max = 0;
  for (int from = 0; from!=size; ++from)
  {
    if (n[from] != Newick::bracket_open) continue;
    for (int to = from+1; to!=size; ++to)
    {
      if (n[to] == Newick::bracket_open) break;
      if (n[to]  > 0) continue;
      if (n[to] == Newick::bracket_close)
      {
        assert(from < to);
        max = to - from - 1;
        break;
      }
    }
  }
  return max;
}

std::vector<std::vector<int> >
  ribi::Newick::GetRootBranches(const std::vector<int>& n) noexcept
{
  //#ifdef __GXX_EXPERIMENTAL_CXX0X__
  ///\note
  ///The tests below must be put back in again once
  #ifdef DEBUG_TEMP_REMOVE_2738236826438

  //#define DEBUG_GETROOTBRANCHES
  #ifdef  DEBUG_GETROOTBRANCHES
  TRACE_FUNC();
  TRACE(Newick::NewickToString(n));
  #endif

  assert(IsNewick(n));
  assert(!IsUnaryNewick(n));

  const int size = boost::numeric_cast<int>(n.size());
  std::vector<std::vector<int> > v;

  if (IsSimple(n))
  {
    for (int i=1; i!=size-1; ++i) //Skip brackets
    {
      v.push_back(
        CreateVector(
          static_cast<int>(bracket_open),
          n[i],
          static_cast<int>(bracket_close)));
    }
    assert(IsNewick(v.back()));
    assert(v.size() > 1);
    return v;
  }
  //Complex newick
  assert(!IsSimple(n));
  const std::vector<int> depth = GetDepth(n);

  assert(depth.size() == n.size());
  //Search for open and closing brackets in depth 1
  for (int i=0; i!=size; ++i)
  {
    if (depth[i] == 0 && n[i] > 0)
    {
      //C++0x initialization list
      v.push_back(
        {
          Newick::bracket_open,
          n[i],
          Newick::bracket_close
        }
      );
      assert(Newick::IsNewick(v.back()));
      continue;
    }
    if (depth[i] != 1 || n[i]!=Newick::bracket_open) continue;
    for (int j=i+1; j!=size; ++j)
    {
      if (depth[j] != 1 || n[j]!=Newick::bracket_close) continue;
      std::vector<int> w;
      w.push_back(Newick::bracket_open);
      std::copy(n.begin() + i + 1,n.begin() + j,std::back_inserter(w));
      w.push_back(Newick::bracket_close);
      assert(IsNewick(w));
      v.push_back(w);
      //Set from index i after current end
      i = j;
      break;
    }
  }
  assert(v.size() > 1);
  return v;
  #else
  return NewickCpp98().GetRootBranches(n);
  #endif
}

std::pair<std::vector<int>,std::vector<int> >
  ribi::Newick::GetRootBranchesBinary(const std::vector<int>& n) noexcept
{
  assert(IsNewick(n));
  assert(IsBinaryNewick(n) && "Only binary Newicks can have two roots");

  assert(n[0] == bracket_open);
  assert(n[n.size()-1] == bracket_close);
  const int sz = boost::numeric_cast<int>(n.size());
  //Return the answer directly is Newick consists
  //out of two values only
  if (sz==4)
  {
    assert(n[1] > 0);
    assert(n[2] > 0);
    return std::make_pair(
      CreateVector(
        static_cast<int>(bracket_open),
        n[1],
        static_cast<int>(bracket_close)),
      CreateVector(
        static_cast<int>(bracket_open),
        n[2],
        static_cast<int>(bracket_close)));
  }
  typedef std::vector<int>::const_iterator Iterator;
  const Iterator j = n.end() - 1;
  for (Iterator i = n.begin() + 2; i!=j; ++i)
  {
    std::vector<int> lhs(n.begin() + 1,i);
    std::vector<int> rhs(i,n.end() - 1);
    if ( lhs.front() != Newick::bracket_open
      || lhs.back()  != Newick::bracket_close)
    {
      lhs = Surround(lhs);
    }
    if ( rhs.front() != Newick::bracket_open
      || rhs.back()  != Newick::bracket_close)
    {
      rhs = Surround(rhs);
    }
    //std::clog
    //  << NewickToString(lhs)
    //  << " and "
    //  << NewickToString(rhs)
    //  << '\n';
    if (IsNewick(lhs) && IsNewick(rhs))
    {
      return std::make_pair(lhs,rhs);
    }
  }
  assert(!"Should not get here");
  throw std::logic_error("Should not get here");
}

std::vector<std::vector<int> >
  ribi::Newick::GetSimplerBinaryNewicks(const std::vector<int>& n) noexcept
{
  assert(IsNewick(n));
  assert(IsUnaryNewick(n) || IsBinaryNewick(n));

  std::vector<std::vector<int> > newicks;

  //If newick is simple (by counting the number of opening brackets),
  //there are no simpler Newicks
  if (std::count( n.begin(),n.end(),
    static_cast<int>(bracket_open))==1)
  {
    //Simple newicks do not need to be simplified
    assert(n.size()==3 || n.size() == 4);
    assert(n[0]==bracket_open);
    assert(n[n.size()-1]==bracket_close);
    if (n.size() == 3)
    {
      if (n[1]>1)
      {
        std::vector<int> next(n);
        --next[1];
        assert(IsNewick(next));
        newicks.push_back(next);
      }
      return newicks;
    }
    assert(n.size()==4);
    if (n[1] == 1)
    {
      std::vector<int> next
        = CreateVector(
            static_cast<int>(bracket_open),
            n[2]+1,
            static_cast<int>(bracket_close));
      assert(IsNewick(next));
      newicks.push_back(next);
    }
    else
    {
      std::vector<int> next(n);
      --next[1];
      assert(IsNewick(next));
      newicks.push_back(next);
    }
    if (n[2] == 1)
    {
      std::vector<int> next
        = CreateVector(
            static_cast<int>(bracket_open),
            n[1]+1,
            static_cast<int>(bracket_close));
      assert(IsNewick(next));
      newicks.push_back(next);
    }
    else
    {
      std::vector<int> next(n);
      --next[2];
      assert(IsNewick(next));
      newicks.push_back(next);
    }
    return newicks;
  }

  //newick is complex
  //Generate other Newicks and their coefficients
  const int sz = n.size();
  for (int i=0; i!=sz; ++i)
  {
    const int x = n[i];
    if (x < 0) //x is not a digit
    {
      continue;
    }
    if (x == 1)
    {
      //If x is not next to a digit, there is no simplification
      if (n[i-1]<0 && n[i+1]<1) continue;
      //If next to the x in a digit, merge these and remove their brackets
      //Is the 1 left of a value?
      if (n[i-1]==bracket_open)
      {
        assert(n[i+1] > 0);
        const int new_value = n[i+1] + 1;
        std::vector<int> next(n.begin(),n.begin() + i - 1);
        next.push_back(new_value);
        assert(n[i+2] < 0);
        std::copy(n.begin() + i + 3,n.end(),std::back_inserter(next));
        #ifndef NDEBUG
        if (!IsNewick(next))
        {
          std::cerr << DumbNewickToString(n)  << '\n';
          std::cerr << DumbNewickToString(next) << '\n';
          InspectInvalidNewick(std::cerr,next);
        }
        #endif
        assert(IsNewick(next));
        newicks.push_back(next);
      }
      else
      {
        //Is the 1 to the right of a value?
        assert(n[i-1] > 0); //< The other value
        const int new_value = n[i-1] + 1;
        std::vector<int> next(n.begin(),n.begin()+i-2);
        next.push_back(new_value);
        assert(n[i+1] < 0);
        std::copy(n.begin() + i + 2,n.end(),std::back_inserter(next));
        assert(IsNewick(next));
        newicks.push_back(next);
      }
    }
    else
    {
      std::vector<int> next = n;
      --next[i];
      assert(IsNewick(next));
      newicks.push_back(next);
    }
  }
  return newicks;
}

std::vector<std::vector<int> >
  ribi::Newick::GetSimplerNewicks(const std::vector<int>& n) noexcept
{
  assert(IsNewick(n));

  const std::vector<int> depths = GetDepth(n);

  std::vector<std::vector<int> > newicks;

  const int size = boost::numeric_cast<int>(n.size());
  for (int i = 0; i!=size; ++i)
  {
    assert(i >= 0);
    assert(i < size);
    if (n[i] < 1) continue;
    assert(n[i] > 0);
    if (n[i] > 1)
    {
      std::vector<int> new_newick(n);
      --new_newick[i];
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string stored = Newick::NewickToString(new_newick);
        TRACE(stored);
      }
      #endif
      newicks.push_back(new_newick);
      continue;
    }
    assert(n[i] == 1); //Most difficult...
    const int depth = depths[i];
    //j must first decrement, later increment with the same code
    int j_end  = -1;
    int j_step = -1;
    for (int j=i-1; ; j+=j_step)
    {
      //j must first decrement, later increment with the same code
      if (j == j_end
        //|| depths[j] < depth
        || (depths[j] == depth && n[j] < 0))
      {
        if (j_step == -1)
        {
          j = i + 1;
          j_end = size;
          j_step = 1;
        }
        else
        {
          break;
        }
      }
      assert(i!=j);
      assert(j >= 0);
      assert(j < size);
      //Only take frequencies of the same depth into account
      if (n[j] < 1 || depths[j] != depth) continue;
      std::vector<int> new_newick_with_zero(n);
      --new_newick_with_zero[i];
      assert(new_newick_with_zero[i] == 0);
      ++new_newick_with_zero[j];
      //Remove brackets after possibly lonely value
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string newick_str_with_zeroes = Newick::DumbNewickToString(new_newick_with_zero);
        TRACE(newick_str_with_zeroes);
        const std::string dist_i_j = boost::lexical_cast<std::string>(std::abs(i - j));
        TRACE(dist_i_j)
      }
      #endif
      //If there is only one or two values between
      //the brackets, and one of these values was a
      //1 becoming added to the other, nullify the
      //1 and both brackets:
      //'((1,1),2)' -> '(00102)' -> '(1,2)'
      if (std::abs(i - j) == 1)
        //|| (std::abs(i - j) == 2 && n[i] == 1))
      {
        const int index_bracket_open  = std::min(i,j) - 1;
        const int index_bracket_close = std::max(i,j) + 1;
        if ( new_newick_with_zero[index_bracket_open]  == Newick::bracket_open
          && new_newick_with_zero[index_bracket_close] == Newick::bracket_close)
        {
          new_newick_with_zero[index_bracket_open]  = 0;
          new_newick_with_zero[index_bracket_close] = 0;
        }
      }
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string newick_str_with_more_zeroes = Newick::DumbNewickToString(new_newick_with_zero);
        TRACE(newick_str_with_more_zeroes);
      }
      #endif
      //Remove decremented i and possibly nullified brackets
      std::vector<int> new_newick;
      std::remove_copy(
        new_newick_with_zero.begin(),
        new_newick_with_zero.end(),
        std::back_inserter(new_newick),
        0);
      //Add brackets if these are removed
      if (new_newick.front() != Newick::bracket_open
        || new_newick.back() != Newick::bracket_close)
      {
        new_newick = Surround(new_newick);
      }
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string newick_str_done = Newick::DumbNewickToString(new_newick);
        TRACE(newick_str_done);
      }
      #endif
      #define DEBUG_2436964926435498753298216832187
      #ifdef  DEBUG_2436964926435498753298216832187
      if (!IsNewick(new_newick))
      {
        TRACE(Newick::DumbNewickToString(new_newick));
      }
      #endif

      assert(IsNewick(new_newick));
      newicks.push_back(new_newick);
      continue;
    }
  }
  return newicks;
}

std::vector<std::pair<std::vector<int>,int> >
  ribi::Newick::GetSimplerNewicksFrequencyPairs(const std::vector<int>& n) noexcept
{
  //#ifdef __GXX_EXPERIMENTAL_CXX0X__
  #ifdef DEBUG_TEMP_REMOVE_2738236826438

  //#define DEBUG_GETSIMPLERNEWICKSFREQUENCYPAIRS
  assert(IsNewick(n));

  std::vector<std::pair<std::vector<int>,int> > newicks;
  const std::vector<int> depths = GetDepth(n);


  const int size = boost::numeric_cast<int>(n.size());
  for (int i = 0; i!=size; ++i)
  {
    assert(i >= 0);
    assert(i < size);
    if (n[i] < 1) continue;
    assert(n[i] > 0);
    if (n[i] > 1)
    {
      std::vector<int> new_newick(n);
      --new_newick[i];
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string stored = Newick::NewickToString(new_newick);
        TRACE(stored);
      }
      #endif
      newicks.push_back( { new_newick,n[i] } );
      continue;
    }
    assert(n[i] == 1); //Most difficult...
    const int depth = depths[i];
    //j must first decrement, later increment with the same code
    int j_end  = -1;
    int j_step = -1;
    for (int j=i-1; ; j+=j_step)
    {
      //j must first decrement, later increment with the same code
      if (j == j_end
        //|| depths[j] < depth
        || (depths[j] == depth && n[j] < 0))
      {
        if (j_step == -1)
        {
          j = i + 1;
          j_end = size;
          j_step = 1;
        }
        else
        {
          break;
        }
      }
      assert(i!=j);
      assert(j >= 0);
      assert(j < size);
      //Only take frequencies of the same depth into account
      if (n[j] < 1 || depths[j] != depth) continue;
      std::vector<int> new_newick_with_zero(n);
      --new_newick_with_zero[i];
      assert(new_newick_with_zero[i] == 0);
      ++new_newick_with_zero[j];
      //Remove brackets after possibly lonely value
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string newick_str_with_zeroes = Newick::DumbNewickToString(new_newick_with_zero);
        TRACE(newick_str_with_zeroes);
        const std::string dist_i_j = boost::lexical_cast<std::string>(std::abs(i - j));
        TRACE(dist_i_j)
      }
      #endif
      //If there is only one or two values between
      //the brackets, and one of these values was a
      //1 becoming added to the other, nullify the
      //1 and both brackets:
      //'((1,1),2)' -> '(00102)' -> '(1,2)'
      if (std::abs(i - j) == 1)
        //|| (std::abs(i - j) == 2 && n[i] == 1))
      {
        const int index_bracket_open  = std::min(i,j) - 1;
        const int index_bracket_close = std::max(i,j) + 1;
        if ( new_newick_with_zero[index_bracket_open]  == Newick::bracket_open
          && new_newick_with_zero[index_bracket_close] == Newick::bracket_close)
        {
          new_newick_with_zero[index_bracket_open]  = 0;
          new_newick_with_zero[index_bracket_close] = 0;
        }
      }
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string newick_str_with_more_zeroes = Newick::DumbNewickToString(new_newick_with_zero);
        TRACE(newick_str_with_more_zeroes);
      }
      #endif
      //Remove decremented i and possibly nullified brackets
      std::vector<int> new_newick;
      std::remove_copy(
        new_newick_with_zero.begin(),
        new_newick_with_zero.end(),
        std::back_inserter(new_newick),
        0);
      //Add brackets if these are removed
      if (new_newick.front() != Newick::bracket_open
        || new_newick.back() != Newick::bracket_close)
      {
        new_newick = Surround(new_newick);
      }
      #ifdef DEBUG_GETSIMPLERNEWICKS
      {
        const std::string newick_str_done = Newick::DumbNewickToString(new_newick);
        TRACE(newick_str_done);
      }
      #endif
      #define DEBUG_2436964926435498753298216832187
      #ifdef  DEBUG_2436964926435498753298216832187
      if (!IsNewick(new_newick))
      {
        TRACE(Newick::DumbNewickToString(new_newick));
      }
      #endif

      assert(IsNewick(new_newick));
      newicks.push_back( { new_newick, 1 } );
      continue;
    }
  }

  return newicks;
  #else
  return NewickCpp98().GetSimplerNewicksFrequencyPairs(n);
  #endif
}


std::vector<std::pair<std::vector<int>,int> >
  ribi::Newick::GetSimplerBinaryNewicksFrequencyPairs(
  const std::vector<int>& n) noexcept
{
  assert(IsNewick(n));
  assert(IsBinaryNewick(n));
  std::vector<std::pair<std::vector<int>,int> > v;

  assert(IsNewick(n));
  assert(IsBinaryNewick(n));

  //If newick is simple (by counting the number of opening brackets),
  //there are no simpler Newicks
  if (std::count( n.begin(),n.end(),
    static_cast<int>(bracket_open))==1)
  {
    //Simple newicks do not need to be simplified
    assert(n.size()==3 || n.size() == 4);
    assert(n[0]==bracket_open);
    assert(n[n.size()-1]==bracket_close);
    if (n.size() == 3)
    {
      if (n[1]>1)
      {
        std::vector<int> next(n);
        --next[1];
        assert(IsNewick(next));
        v.push_back(std::make_pair(next,n[1]));
      }
      return v;
    }
    assert(n.size()==4);
    if (n[1] == 1)
    {
      std::vector<int> next
        = CreateVector(
            static_cast<int>(bracket_open),
            n[2]+1,
            static_cast<int>(bracket_close));
      assert(IsNewick(next));
      v.push_back(std::make_pair(next,1));
    }
    else
    {
      std::vector<int> next(n);
      --next[1];
      assert(IsNewick(next));
      v.push_back(std::make_pair(next,n[1]));
    }
    if (n[2] == 1)
    {
      std::vector<int> next
        = CreateVector(
            static_cast<int>(bracket_open),
            n[1]+1,
            static_cast<int>(bracket_close));
      assert(IsNewick(next));
      v.push_back(std::make_pair(next,1));
    }
    else
    {
      std::vector<int> next(n);
      --next[2];
      assert(IsNewick(next));
      v.push_back(std::make_pair(next,n[2]));
    }
    return v;
  }

  //newick is complex
  //Generate other Newicks and their coefficients
  const int sz = n.size();
  for (int i=0; i!=sz; ++i)
  {
    const int x = n[i];
    if (x < 0) //x is not a digit
    {
      continue;
    }
    if (x == 1)
    {
      //If x is not next to a digit, there is no simplification
      if (n[i-1]<0 && n[i+1]<1) continue;
      //If next to the x in a digit, merge these and remove their brackets
      //Is the 1 left of a value?
      if (n[i-1]==bracket_open)
      {
        assert(n[i+1] > 0);
        const int new_value = n[i+1] + 1;
        std::vector<int> next(n.begin(),n.begin() + i - 1);
        next.push_back(new_value);
        assert(n[i+2] < 0);
        std::copy(n.begin() + i + 3,n.end(),std::back_inserter(next));
        #ifndef NDEBUG
        if (!IsNewick(next))
        {
          std::cerr << DumbNewickToString(n)  << '\n';
          std::cerr << DumbNewickToString(next) << '\n';
          InspectInvalidNewick(std::cerr,next);
        }
        #endif
        assert(IsNewick(next));
        v.push_back(std::make_pair(next,x));
      }
      else
      {
        //Is the 1 to the right of a value?
        assert(n[i-1] > 0); //< The other value
        const int new_value = n[i-1] + 1;
        std::vector<int> next(n.begin(),n.begin()+i-2);
        next.push_back(new_value);
        assert(n[i+1] < 0);
        std::copy(n.begin() + i + 2,n.end(),std::back_inserter(next));
        assert(IsNewick(next));
        v.push_back(std::make_pair(next,x));
      }
    }
    else
    {
      std::vector<int> next = n;
      --next[i];
      assert(IsNewick(next));
      v.push_back(std::make_pair(next,x));
    }
  }
  return v;
}

std::string ribi::Newick::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Newick::GetVersionHistory() const noexcept
{
  return {
    "20xx-xx-xx: Version 1.0: initial version",
    "2013-05-29: Version 1.1: version history"
  };
}

void ribi::Newick::InspectInvalidNewick(std::ostream& os, const std::vector<int>& v) noexcept
{
  os << "InspectInvalidNewick on: "
    << DumbNewickToString(v) << '\n';
  try
  {
    CheckNewick(v);
  }
  catch (std::exception& e)
  {
    os << "Invalidity caused by: " << e.what() << '\n';
  }
}

bool ribi::Newick::IsNewick(const std::string& s) noexcept
{
  try
  {
    CheckNewick(s);
  }
  catch (const std::exception& e)
  {
    return false;
  }
  return true;
}

bool ribi::Newick::IsSimple(const std::vector<int>& v) noexcept
{
  assert(IsNewick(v));
  //A Newick is simple if it contains no '(' after the initial one
  return std::count(
    v.begin()+1,v.end(),
    static_cast<int>(bracket_open)
  ) == 0;
}

bool ribi::Newick::IsBinaryNewick(std::vector<int> v) noexcept
{
  assert(IsNewick(v));
  if (IsUnaryNewick(v)) return false;

  while (1)
  {
    const int sz = boost::numeric_cast<int>(v.size());
    //Only numbers?
    if (IsSimple(v))
    {
      //Binary Newick has size 4, for example '(1,2)'
      return sz == 4;
    }
    if (GetLeafMaxArity(v) > 2) return false;
    v = Newick::ReplaceLeave(v,42);
  }
}

bool ribi::Newick::IsNewick(const std::vector<int>& v) noexcept
{
  try
  {
    CheckNewick(v);
  }
  catch (...)
  {
    return false;
  }
  return true;
}

///IsTrinaryNewick checks if a Newick is a trinary tree,
///that is: each node splits in three or less branches
///From http://www.richelbilderbeek.nl/CppIsTrinaryNewick.htm
bool ribi::Newick::IsTrinaryNewick(std::vector<int> v) noexcept
{
  assert(IsNewick(v));
  if (IsUnaryNewick(v)) return false;
  if (IsBinaryNewick(v)) return false;

  bool trinarity_found = false;

  while (1)
  {
    const int sz = boost::numeric_cast<int>(v.size());
    //Only numbers?
    if (IsSimple(v))
    {
      //Ternary Newick has size 5, for example '(1,2,3)'
      return trinarity_found || sz == 5;
    }
    const int leaf_max_arity = GetLeafMaxArity(v);
    if (leaf_max_arity > 3) return false;
    if (leaf_max_arity == 3) trinarity_found = true;

    v = Newick::ReplaceLeave(v,42);
  }
}

bool ribi::Newick::IsUnaryNewick(const std::vector<int>& v) noexcept
{
  assert(IsNewick(v));
  return v.size() == 3
    && v[0] == Newick::bracket_open
    && v[1] >  0
    && v[2] == Newick::bracket_close;
}

std::string ribi::Newick::NewickToString(const std::vector<int>& v)
{
  assert(v.size() > 2 && "A Newick must at least have one single value");
  assert(v[0] == bracket_open
    && "A std::vector<int> Newick must start with a bracket_open");
  assert(v[v.size() - 1] == bracket_close
    && "A std::vector<int> Newick must end with a bracket_close");
  std::string s;
  s.reserve(2 * v.size()); //Just a guess
  const int sz = v.size();
  for (int i=0; i!=sz; ++i)
  {
    const int x = v[i];
    if (x >= 0)
    {
      s+=boost::lexical_cast<std::string>(x);
      assert(i+1<sz && "Must not end with number");
      const int next = v[i+1];
      if (next > 0 || next == bracket_open)
      {
        s+=",";
      }
    }
    else if (x==bracket_open)
    {
      s+="(";
    }
    else if (x==bracket_close)
    {
      s+=")";
      //Final closing bracket?
      if (i+1==sz) break;
      const int next = v[i+1];
      if (next > 0 || next == bracket_open)
      {
        s+=",";
      }
    }
    else
    {
      assert(!"Should not get here"
        && "A std::vector<int> Newick must consist of brackets and values only");
    }
  }
  return s;
}

///SortNewick orders a Newick is such a way
///that all opening brackets are at the left side.
///For example (1,(2,3)) becomes ((2,3),1)
/*
std::string SortNewick(const std::string& newick)
{
  assert(IsNewick(newick));
  //All leaves are 'cut' by replacing them with an x
  std::string s = newick;
  std::string n = "";
  //Find initial leaf and replace it with x
  {
    const boost::xpressive::sregex r("\\(\\d+,\\d+\\)");
    std::string::const_iterator start = s.begin();
    const std::string::const_iterator end = s.end();
    boost::match_results<std::string::const_iterator> what;
    boost::regex_search(start, end, what, r);
    n = what.str();
    s = boost::regex_replace(s,r,"x");
  }
  //When all leaves are cut, s == 'x'
  while (s!="x")
  {
    //Obtain leaf with x
    const boost::xpressive::sregex r("(\\(x,\\d+\\))|(\\(\\d+,x\\))");
    std::string::const_iterator start = s.begin();
    const std::string::const_iterator end = s.end();
    boost::match_results<std::string::const_iterator> what;
    //Search for inner leaf
    boost::regex_search(start, end, what, r);
    const std::string l = what.str();
    //Search leaf for digit
    boost::regex_search(l.begin(), l.end(), what,boost::regex("\\d+"));
    //Add digit to n
    n = "(" + n + "," + what.str() + ")";
    //Replace the leaf by an x
    s = boost::regex_replace(s,r,"x");
  }
  return n;
}
*/

std::vector<int> ribi::Newick::ReplaceLeave(
  const std::vector<int>& newick,
  const int value)
{
  assert(IsNewick(newick) && "Only a valid Newick can have its leaves replaced");
  assert(!IsSimple(newick) && "There must a leaf to simplify");
  typedef std::vector<int>::const_iterator Iterator;
  const Iterator end = newick.end();
  for (Iterator from = newick.begin(); from!=end; ++from)
  {
    if (*from != Newick::bracket_open) continue;

    for (Iterator to = from + 1; to!=end; ++to)
    {
      if (*to > 0) continue;
      if (*to == Newick::bracket_open) break;
      if (*to == Newick::bracket_close)
      {
        //Found
        std::vector<int> new_newick(newick.begin(),from);
        new_newick.push_back(value);
        std::copy(to + 1,newick.end(),std::back_inserter(new_newick));
        assert(IsNewick(new_newick));
        return new_newick;
      }
    }
  }
  assert(!"Should not get here");
  throw std::logic_error("Should not get here");
}

std::vector<int> ribi::Newick::StringToNewick(const std::string& newick)
{
  assert(IsNewick(newick));
  assert(!newick.empty()
    && "s must not be empty");
  assert(newick[              0]=='('
    && "s must begin with a '('");
  assert(newick[newick.size()-1]==')'
    && "s must end with a ')'");

  std::vector<int> v;
  int value = 0;

  for(const char i: newick)
  {
    if (i == '(')
    {
      if (value!=0) v.push_back(value);
      value = 0;
      v.push_back(bracket_open);
      continue;
    }
    if (i == ')')
    {
      if (value!=0) v.push_back(value);
      value = 0;
      v.push_back(bracket_close);
      continue;
    }
    if (i == ',')
    {
      if (value!=0) v.push_back(value);
      value = 0;
      continue;
    }
    assert(i >= '0' && i <= '9'); //Should be a number
    value*=10;
    value+=boost::lexical_cast<int>(i);
  }
  assert(value == 0 && "Final bracket close must set value to zero");
  return v;
}

std::vector<int> ribi::Newick::Surround(const std::vector<int>& newick) noexcept
{
  std::vector<int> new_newick;
  new_newick.push_back(Newick::bracket_open);
  std::copy(newick.begin(),newick.end(),std::back_inserter(new_newick));
  new_newick.push_back(Newick::bracket_close);
  return new_newick;
}

#ifndef NDEBUG
///Test tests all Newick functions
void ribi::Newick::Test()
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    NewickCpp98();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);

  //#ifdef __GXX_EXPERIMENTAL_CXX0X__
  ///\note
  ///The tests below must be put back in again once
  #ifdef DEBUG_TEMP_REMOVE_2738236826438


  TRACE("Testing basic Newick functionality");
  //Check difference between C++98 and C++0x
  assert(Newick::CreateValidTrinaryNewicks() == NewickCpp98().CreateValidTrinaryNewicks());
  assert(Newick::GetKnownProbabilities() == NewickCpp98().GetKnownProbabilities());



  //Check conversions from std::string to std::vector #1
  {
    const std::vector<int> v = Newick::StringToNewick("(11,(22,33))");
    assert(v.size() == 7);
    assert(v[0]==Newick::bracket_open);
    assert(v[1]==11);
    assert(v[2]==Newick::bracket_open);
    assert(v[3]==22);
    assert(v[4]==33);
    assert(v[5]==Newick::bracket_close);
    assert(v[6]==Newick::bracket_close);
  }
  //Check if well-formed Newicks are accepted
  {
    const std::vector<std::string> v = Newick::CreateValidNewicks();
    for(const std::string& s: v)
    {
      #ifdef TRACE_REJECTED_NEWICKS
      const std::string debug = "I must be accepted: " + s;
      TRACE(debug);
      #endif
      assert(Newick::IsNewick(s));
      const std::vector<int> v = Newick::StringToNewick(s);
      assert(Newick::IsNewick(v));
    }
  }
  //Check if ill-formed Newicks are rejected
  {
    #ifndef NDEBUG
    const std::vector<std::string> v = Newick::CreateInvalidNewicks();
    for(const std::string& s: v)
    {
      #ifdef TRACE_REJECTED_NEWICKS
      const std::string debug = "I must be rejected: " + s;
      TRACE(debug);
      #endif
      assert(!Newick::IsNewick(s));
      //Cannot test if std::vector<int> versions are rejected,
      //because Newick::StringToNewick assumes a valid Newick
      //const std::vector<int> v = Newick::StringToNewick(s);
      //assert(!Newick::IsNewick(v));
    }
    #endif
  }
  //Check conversions from std::string to std::vector #2
  {
    const std::vector<int> v = Newick::StringToNewick("((11,22),33)");
    assert(v.size() == 7);
    assert(v[0]==Newick::bracket_open);
    assert(v[1]==Newick::bracket_open);
    assert(v[2]==11);
    assert(v[3]==22);
    assert(v[4]==Newick::bracket_close);
    assert(v[5]==33);
    assert(v[6]==Newick::bracket_close);
  }
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(1,(3,1))"))==0);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(3,(1,1))"))==1);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(1,((1,1),(1,1)))"))==3);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(1,((1,1),(2,2)))"))==2);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(1,(2,3))"))==0);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(99,99)"))==1);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(3,(2,2))"))==1);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(2,(2,2))"))==1);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("((3,3),(2,2))"))==2);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("((3,3),(3,3))"))==3);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("((3,3),(3,4))"))==1);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(((3,3),(4,4)),5)"))==2);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(((3,3),(5,5)),5)"))==2);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(((5,5),(5,5)),5)"))==3);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(((5,5),(5,5)),(4,4))"))==4);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(((5,5),(4,4)),(4,4))"))==3);
  assert(Newick::CalcNumOfSymmetriesBinary(StringToNewick("(((4,4),(4,4)),(4,4))"))==4);
  assert(Newick::CalcNumOfCombinationsBinary(StringToNewick("(3,(1,1))"))==10);
  assert(Newick::CalcNumOfCombinationsBinary(StringToNewick("(1,(3,1))"))==20);
  assert(Newick::CalcNumOfCombinationsBinary(StringToNewick("(1,(1,(1,(1,1))))"))==60);
  assert(Newick::CalcNumOfCombinationsBinary(StringToNewick("(1,((1,1),(1,1)))"))==15);
  assert(bigIntegerToString(Newick::FactorialBigInt(1))=="1");
  assert(bigIntegerToString(Newick::FactorialBigInt(2))=="2");
  assert(bigIntegerToString(Newick::FactorialBigInt(3))=="6");
  assert(bigIntegerToString(Newick::FactorialBigInt(4))=="24");
  assert(bigIntegerToString(Newick::FactorialBigInt(5))=="120");
  assert(bigIntegerToString(Newick::FactorialBigInt(6))=="720");
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(1)"))   == 1);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(12)"))  == 1);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(123)")) == 1);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(1,2)"))   == 2);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(12,2)"))  == 2);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(123,2)")) == 2);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(1,(1,2))"))   == 2);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(1,(12,2))"))  == 2);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(1,(123,2))")) == 2);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("((1,2),3)"))   == 2);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("((12,2),3)"))  == 2);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("((123,2),3)")) == 2);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(1,2,3)"))   == 3);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(12,2,3)"))  == 3);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(123,2,3)")) == 3);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(1,(1,2,3))"))   == 3);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(1,(12,2,3))"))  == 3);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("(1,(123,2,3))")) == 3);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("((1,2,3),4)"))   == 3);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("((12,2,3),4)"))  == 3);
  assert(Newick::GetLeafMaxArity(Newick::StringToNewick("((123,2,3),4)")) == 3);

  assert(fuzzy_equal_to()(  2.0,Newick::CalcDenominator(Newick::StringToNewick("(1,1)"),10.0)));
  assert(fuzzy_equal_to()(  6.0,Newick::CalcDenominator(Newick::StringToNewick("((1,1),1)"),10.0)));
  assert(fuzzy_equal_to()( 26.0,Newick::CalcDenominator(Newick::StringToNewick("(1,2)"),10.0)));
  assert(fuzzy_equal_to()( 32.0,Newick::CalcDenominator(Newick::StringToNewick("((1,1),2)"),10.0)));
  assert(fuzzy_equal_to()( 32.0,Newick::CalcDenominator(Newick::StringToNewick("(2,(1,1))"),10.0)));
  assert(fuzzy_equal_to()( 50.0,Newick::CalcDenominator(Newick::StringToNewick("((1,1),3)"),10.0)));
  assert(fuzzy_equal_to()( 80.0,Newick::CalcDenominator(Newick::StringToNewick("((1,2),3)"),10.0)));
  assert(fuzzy_equal_to()( 80.0,Newick::CalcDenominator(Newick::StringToNewick("((3,1),2)"),10.0)));
  assert(fuzzy_equal_to()( 80.0,Newick::CalcDenominator(Newick::StringToNewick("((2,3),1)"),10.0)));
  assert(fuzzy_equal_to()(102.0,Newick::CalcDenominator(Newick::StringToNewick("((2,1),4)"),10.0)));
  assert(fuzzy_equal_to()(152.0,Newick::CalcDenominator(Newick::StringToNewick("(2,(1,(3,3)))"),10.0)));
  assert(fuzzy_equal_to()(162.0,Newick::CalcDenominator(Newick::StringToNewick("((2,3),4)"),10.0)));
  assert(fuzzy_equal_to()(180.0,Newick::CalcDenominator(Newick::StringToNewick("((1,2),(3,4))"),10.0)));
  assert(fuzzy_equal_to()(180.0,Newick::CalcDenominator(Newick::StringToNewick("((4,1),(2,3))"),10.0)));
  assert(fuzzy_equal_to()(180.0,Newick::CalcDenominator(Newick::StringToNewick("((3,4),(1,2))"),10.0)));
  assert(fuzzy_equal_to()(180.0,Newick::CalcDenominator(Newick::StringToNewick("((2,3),(4,1))"),10.0)));
  {
    const std::vector<int> v = { 0,1,2,3,4,5,6 };
    assert(Newick::FindPosAfter(v,3,2)==3);
    assert(Newick::FindPosAfter(v,4,2)==4);
    assert(Newick::FindPosAfter(v,5,2)==5);
    assert(Newick::FindPosAfter(v,6,2)==6);
    assert(Newick::FindPosBefore(v,3,4)==3);
    assert(Newick::FindPosBefore(v,2,4)==2);
    assert(Newick::FindPosBefore(v,1,4)==1);
    assert(Newick::FindPosBefore(v,0,4)==0);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick::StringToNewick("(1,(2,2))"));
    const std::vector<int> w = Newick::GetDepth(Newick::StringToNewick("(9,(9,9))"));
    const std::vector<int> x = { 0,0,1,1,1,1,0 };
    assert(v == x);
    assert(w == x);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick::StringToNewick("((2,2),1)"));
    const std::vector<int> w = { 0,1,1,1,1,0,0 };
    assert(v == w);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick::StringToNewick("(1,(2,2),1)"));
    const std::vector<int> w = { 0,0,1,1,1,1,0,0 };
    assert(v == w);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick::StringToNewick("(1,(2,3),4,(5,6))"));
    const std::vector<int> w = { 0,0,1,1,1,1,0,1,1,1,1,0 };
    assert(v == w);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick::StringToNewick("(1,(2,3),(5,6))"));
    const std::vector<int> w = { 0,0,1,1,1,1,1,1,1,1,0 };
    assert(v == w);
  }
  {
    const std::vector<int> v = Newick::GetDepth(Newick::StringToNewick("(1,(2,(3,4)),((5,6),7))"));
    const std::vector<int> w = { 0,0,1,1,2,2,2,2,1,1,2,2,2,2,1,1,0 };
    assert(v == w);
  }
  //Test GetRootBranches
  {
    const std::vector<std::vector<int> > v = Newick::GetRootBranches(Newick::StringToNewick("(1,2)"));
    assert(v.size() == 2);
    assert(std::find(v.begin(),v.end(),
      Newick::StringToNewick("(1)")) != v.end());
    assert(std::find(v.begin(),v.end(),
      Newick::StringToNewick("(2)")) != v.end());
  }
  {
    const std::vector<std::vector<int> > v = Newick::GetRootBranches(Newick::StringToNewick("(1,(2,3))"));
    assert(v.size() == 2);
    assert(std::find(v.begin(),v.end(),
      Newick::StringToNewick("(1)")) != v.end());
    assert(std::find(v.begin(),v.end(),
      Newick::StringToNewick("(2,3)")) != v.end());
  }
  {
    const std::vector<std::vector<int> > v = Newick::GetRootBranches(Newick::StringToNewick("(1,2,(3,4))"));
    assert(v.size() == 3);
    assert(std::find(v.begin(),v.end(),
      Newick::StringToNewick("(1)")) != v.end());
    assert(std::find(v.begin(),v.end(),
      Newick::StringToNewick("(2)")) != v.end());
    assert(std::find(v.begin(),v.end(),
      Newick::StringToNewick("(3,4)")) != v.end());
  }
  //Compare C++98 and C++0x version
  {
    const std::vector<std::string> v = Newick::CreateValidBinaryNewicks();
    for(const std::string& s: v)
    {
      const std::vector<int> n = Newick::StringToNewick(s);
      assert(Newick::GetRootBranches(n) == NewickCpp98().GetRootBranches(n));
    }
  }

  //Check if binary and trinary Newicks are detected correctly
  {
    const std::vector<std::string> v = Newick::CreateValidBinaryNewicks();
    for(const std::string& s: v)
    {
      const std::vector<int> n = Newick::StringToNewick(s);
      assert(Newick::IsBinaryNewick(n));
    }
  }
  //Check if unary Newicks are detected correctly
  {
    const std::vector<std::string> v = Newick::CreateValidUnaryNewicks();
    for(const std::string& s: v)
    {
      const std::vector<int> n = Newick::StringToNewick(s);
      assert( Newick::GetLeafMaxArity(n)<=1);
      assert( Newick::IsUnaryNewick(n));
      assert(!Newick::IsBinaryNewick(n));
      assert(!Newick::IsTrinaryNewick(n));
    }
  }
  //Check if binary Newicks are detected correctly
  {
    const std::vector<std::string> v = Newick::CreateValidBinaryNewicks();
    for(const std::string& s: v)
    {
      const std::vector<int> n = Newick::StringToNewick(s);
      assert( Newick::GetLeafMaxArity(n)<=2);
      assert(!Newick::IsUnaryNewick(n));
      assert( Newick::IsBinaryNewick(n));
      assert(!Newick::IsTrinaryNewick(n));
    }
  }
  //Check if trinary Newicks are detected correctly
  {
    const std::vector<std::string> v = Newick::CreateValidTrinaryNewicks();
    for(const std::string& s: v)
    {
      //TRACE(s);
      const std::vector<int> n = Newick::StringToNewick(s);
      assert( Newick::GetLeafMaxArity(n)<=3);
      assert(!Newick::IsUnaryNewick(n));
      assert(!Newick::IsBinaryNewick(n));
      assert( Newick::IsTrinaryNewick(n));
    }
  }
  //Test binary Newick
  {
    const std::string s("(1,(2,3))");
    const std::vector<std::vector<int> > n = GetSimplerNewicks(Newick::StringToNewick(s));
    //#define DEBUG_1_BO_1_2_3_BC
    #ifdef  DEBUG_1_BO_1_2_3_BC
    for(const auto& t: n)
    {
      TRACE(Newick::NewickToString(t));
    }
    #endif
    assert(n.size() == 2);
    assert(std::find(n.begin(),n.end(),Newick::StringToNewick("(1,(1,3))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick::StringToNewick("(1,(2,2))"))
      != n.end());
  }
  {
    const std::string s("(1,(2,3,4))");
    const std::vector<std::vector<int> > n = GetSimplerNewicks(Newick::StringToNewick(s));
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),Newick::StringToNewick("(1,(1,3,4))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick::StringToNewick("(1,(2,2,4))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick::StringToNewick("(1,(2,3,3))"))
      != n.end());
  }
  {
    const std::string s("(1,(1,3,4))");
    const std::vector<std::vector<int> > n = GetSimplerNewicks(Newick::StringToNewick(s));
    //#define DEBUG_1_BO_1_3_4_BC
    #ifdef  DEBUG_1_BO_1_3_4_BC
    TRACE(boost::lexical_cast<std::string>(n.size()));
    for(const auto& t: n)
    {
      TRACE(Newick::NewickToString(t));
    }
    #endif
    assert(n.size() == 4);
    assert(std::find(n.begin(),n.end(),Newick::StringToNewick("(1,(4,4))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick::StringToNewick("(1,(3,5))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick::StringToNewick("(1,(1,2,4))"))
      != n.end());
    assert(std::find(n.begin(),n.end(),Newick::StringToNewick("(1,(1,3,3))"))
      != n.end());
  }
  {
    const std::string s("(1,(1,3,4))");
    const std::vector<std::pair<std::vector<int>,int> > n
      = GetSimplerNewicksFrequencyPairs(Newick::StringToNewick(s));
    typedef std::pair<std::vector<int>,int> Pair;
    #ifdef TRACE_GETSIMPLERNEWICKSFREQUENCYPAIRS_1_134
    for(const Pair& p: n)
    {
      std::cout << Newick::NewickToString(p.first) << '\n';
    }
    #endif
    assert(n.size() == 4);
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("(1,(4,4))"),1))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("(1,(3,5))"),1))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("(1,(1,2,4))"),3))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("(1,(1,3,3))"),4))
      != n.end());
  }
  {
    const std::string s("((1,1),2)");
    const std::vector<std::vector<int> > n = Newick::GetSimplerNewicks(
      Newick::StringToNewick(s));
    //#define DEBUG_BO_1_1_BC_2
    #ifdef  DEBUG_BO_1_1_BC_2
    for(const auto& t: n)
    {
      TRACE(Newick::NewickToString(t));
    }
    #endif
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      Newick::StringToNewick("(2,2)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick::StringToNewick("((1,1),1)"))
      != n.end());
  }
  {
    const std::string s("((1,1),2)");
    typedef std::pair<std::vector<int>,int> Pair;
    const std::vector<Pair> n
      = GetSimplerNewicksFrequencyPairs(Newick::StringToNewick(s));
    #ifdef TRACE_GETSIMPLERNEWICKSFREQUENCYPAIRS_11_2
    for(const Pair& p: n)
    {
      std::clog << Newick::NewickToString(p.first) << '\n';
    }
    #endif
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("(2,2)"),1))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("((1,1),1)"),2))
      != n.end());
  }
  {
    const std::string s("((2,1),4)");
    const std::vector<std::vector<int> > n = Newick::GetSimplerNewicks(
      Newick::StringToNewick(s));
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      Newick::StringToNewick("(3,4)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick::StringToNewick("((1,1),4)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick::StringToNewick("((2,1),3)"))
      != n.end());
  }
  {
    const std::string s("((2,1),4)");
    typedef std::pair<std::vector<int>,int> Pair;
    const std::vector<Pair> n
      = GetSimplerNewicksFrequencyPairs(Newick::StringToNewick(s));
    #ifdef TRACE_GETSIMPLERNEWICKSFREQUENCYPAIRS_21_2
    for(const Pair& p: n)
    {
      TRACE(Newick::NewickToString(p.first));
    }
    #endif
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("(3,4)"),1))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("((1,1),4)"),2))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("((2,1),3)"),4))
      != n.end());
  }
  {
    const std::string s("((2,3),4)");
    const std::vector<std::vector<int> > n = Newick::GetSimplerNewicks(
      Newick::StringToNewick(s));
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      Newick::StringToNewick("((1,3),4)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick::StringToNewick("((2,2),4)"))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      Newick::StringToNewick("((2,3),3)"))
      != n.end());
  }
  {
    const std::string s("((2,3),4)");
    typedef std::pair<std::vector<int>,int> Pair;
    const std::vector<Pair> n
      = GetSimplerNewicksFrequencyPairs(Newick::StringToNewick(s));
    #ifdef TRACE_GETSIMPLERNEWICKSFREQUENCYPAIRS_23_4
    for(const Pair& p: n)
    {
      std::cout << Newick::NewickToString(p.first) << '\n';
    }
    #endif
    assert(n.size() == 3);
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("((1,3),4)"),2))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("((2,2),4)"),3))
      != n.end());
    assert(std::find(n.begin(),n.end(),
      std::make_pair(Newick::StringToNewick("((2,3),3)"),4))
      != n.end());
  }
  //Compare GetSimplerNewicks and
  //GetSimplerNewicksFrequencyPairs
  {
    const std::vector<std::string> newicks
      = Newick::CreateValidNewicks();
    for(const std::string& newick_str: newicks)
    {
      const std::vector<int> newick
        = Newick::StringToNewick(newick_str);
      const std::vector<std::vector<int> > v1
        = Newick::GetSimplerNewicks(newick);
      const std::vector<std::pair<std::vector<int>,int> > v2
        = Newick::GetSimplerNewicksFrequencyPairs(newick);
      assert(v1.size() == v2.size());
      const int size = boost::numeric_cast<int>(v1.size());
      for (int i=0; i!=size; ++i)
      {
        #define DEBUG_COMPARE_GSN_VS_GSNFP
        #ifdef  DEBUG_COMPARE_GSN_VS_GSNFP
        if (v1[i] != v2[i].first)
        {
          TRACE("ERROR: DIFFERENT NEWICK SIMPLIFICATIONS");
          TRACE(Newick::NewickToString(newick));
          TRACE(Newick::NewickToString(v1[i]));
          TRACE(Newick::NewickToString(v2[i].first));
        }
        #endif
        assert(v1[i] == v2[i].first);
      }
      assert(Newick::GetSimplerNewicksFrequencyPairs(newick)
        == NewickCpp98().GetSimplerNewicksFrequencyPairs(newick));
    }
  }
  #endif
}
#endif
