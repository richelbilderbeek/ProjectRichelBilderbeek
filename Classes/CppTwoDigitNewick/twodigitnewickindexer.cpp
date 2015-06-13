//---------------------------------------------------------------------------
/*
TestTwoDigitNewick, tool to test the two-digit-Newick architecture
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
//From http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "twodigitnewickindexer.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>


#include <boost/numeric/conversion/cast.hpp>

#include "newick.h"
#include "binarynewickvector.h"

#pragma GCC diagnostic pop

//TwoDigitNewickIndexer constructor does all the work
ribi::TwoDigitNewickIndexer::TwoDigitNewickIndexer(
  const BinaryNewickVector& n,
  const double theta)
  : m_calculated_to_index{CalculateReserved(n)},
    m_current_index{CalculateReserved(n)},
    m_index_table{},
    m_newicks{CalculateReserved(n),theta},
    m_probability{-1.0},
    m_reserved{CalculateReserved(n)},
    m_theta{theta}
{
  assert(m_reserved == m_newicks.Size());
  assert(m_current_index == m_newicks.Size());

  //If the Newick is simple
  if (Newick().IsSimple(n.Peek()))
  {
    //Calculate the Ewens probability only
    m_probability = Newick().CalcProbabilitySimpleNewick(n.Peek(),theta);
    return;
  }

  //Assume all reserved Newicks from index 2 are complete
  #ifndef NDEBUG
  {
    const int sz = m_newicks.Size();
    for (int i=2; i!=sz; ++i)
    {
      assert(GetNewick(i).IsComplete());
    }
  }
  #endif

  //Create all Newicks and derivatives, but do not calculate their
  //probabilities yet
  std::vector<int> v = n.Peek();
  while(v.size()>2) //Find a leaf and cut it until the string is empty
  {
    //Find a leaf
    //Find index i (starting opening bracket) and j (closing bracket)
    const std::size_t sz = v.size();
    std::size_t i = 0;
    std::size_t j = 0;
    for (i=0 ; i!=sz; ++i) //Index of opening bracket
    {
      if (v[i]!=Newick::bracket_open) continue;
      for (j=i+1; j!=sz; ++j)
      {
        if (v[j]==Newick::bracket_open) { j = 0; break; }
        if (v[j]!=Newick::bracket_close) continue;
        break;
      }
      if (j ==  0) continue; //j cannot be 0 after previous for loop
      break;
    }
    //Find simplest leaf
    assert(v[i]==Newick::bracket_open);
    assert(v[j]==Newick::bracket_close);
    std::vector<int> v_new(v.begin(),v.begin() + i);
    const int x = v[i+1];
    const int y = v[i+2];
    //Feed it and obtain simpler index
    //Indices 0 and 1 cannot be complete, because
    //they don't have sensible derivates to point to
    assert(x < 2 || this->GetNewick(x).IsComplete());
    assert(y < 2 || this->GetNewick(y).IsComplete());
    const int saz
      = this->GetNewick(x).GetSumTermsAboveZero()
      + this->GetNewick(y).GetSumTermsAboveZero();
    const int sao
      = this->GetNewick(x).GetSumTermsAboveOne()
      + this->GetNewick(y).GetSumTermsAboveOne();

    assert(saz >  0);
    assert(sao >= 0);

    v_new.push_back(SummarizeNewick(x,y,saz,sao));
    //Replace leaf with simpler index
    std::copy(v.begin() + j + 1, v.end(),std::back_inserter(v_new));
    v = v_new;
  }

  //Now all Newicks are created, but do not have their probabilities calculated
  const int sz = m_newicks.Size();
  //m_calculated_to_index == sz denotes that all Newicks'
  //probabilities are calculated
  while (m_calculated_to_index != sz)
  {
    //Try to calculate if new Newicks can be solved
    this->TryToCalculateNewNewicks();
    //If all is well, there will be new Newicks known
    this->UpdateCalculatedFromIndex();
    //When no new probabilities are calculated,
    //all Newicks are solved
  }
}

int ribi::TwoDigitNewickIndexer::CalculateReserved(const BinaryNewickVector& n) const
{
  const std::vector<int>& v = n.Peek();
  //Count the number of elements
  const int n_elements
    = std::count_if(v.begin(),v.end(),
      std::bind2nd(std::greater<int>(),0));
  const int max_element = *std::max_element(std::begin(v),std::end(v));
  //\todo: +1 needed?
  return n_elements + max_element + 1;
}

///ConstructNewick constructs a full BinaryNewickVector from
///the TwoDigitNewick at index i.
///ConstructNewick is for debugging purposes only,
///as it's the idea to work with non-full determined
///(that is: two-digit) Newicks
const ribi::BinaryNewickVector ribi::TwoDigitNewickIndexer::ConstructNewick(const int i) const
{
  std::vector<int> v;

  if (i < m_reserved)
  {
    v.push_back(Newick::bracket_open);
    //Newick '(0)' is not valid, so fake it as '(1)'
    v.push_back(i == 0 ? 1 : i);
    v.push_back(Newick::bracket_close);
    BinaryNewickVector n(v);
    return n;
  }

  //Search for index i in Indextable to get two digits
  {
    const std::pair<int,int> p = m_index_table.Find(i);
    v.push_back(Newick::bracket_open);
    v.push_back(p.first);
    v.push_back(p.second);
    v.push_back(Newick::bracket_close);
  }
  assert(Newick().IsNewick(v));

  //As long as there are not only reserved (that is: simple)
  //values in v, replace those by their simplers
  while (1)
  {
    const std::vector<int>::iterator i
      = std::find_if(v.begin(),v.end(),
          std::bind2nd(std::greater_equal<int>(),m_reserved));
    if (i== v.end()) break;
    assert(*i >= m_reserved);
    //Create a new std::vector from the v's begin to i
    std::vector<int> v_new( v.begin(),i);
    v_new.push_back(Newick::bracket_open);
    const std::pair<int,int> p = m_index_table.Find(*i);
    v_new.push_back(p.first);
    v_new.push_back(p.second);
    v_new.push_back(Newick::bracket_close);
    //Copy the remainder of v (from after i) to v_new
    std::copy(i+1,v.end(),std::back_inserter(v_new));
    std::swap(v,v_new);
    assert(Newick().IsNewick(v));
  }
  BinaryNewickVector n(v);
  return n;
}

const ribi::TwoDigitNewick ribi::TwoDigitNewickIndexer::CreateTwoDigitNewickDerivatives(
  const int x, const int y,
  const int sum_above_zero,
  const int sum_above_one)
{
  //std::clog << "Sum_above_one: " << sum_above_one << '\n';
  assert(sum_above_zero >= 0);
  assert(sum_above_one >= 0);
  if (IsSimple(x))
  {
    if (IsSimple(y))
    {
      return
        CreateTwoDigitNewickDerivativesSimpleSimple(x,y);
    }
    return
      CreateTwoDigitNewickDerivativesSimpleComplex(
        x,y,sum_above_zero,sum_above_one);
  }
  if (IsSimple(y))
  {
    return
      CreateTwoDigitNewickDerivativesSimpleComplex(
        y,x,sum_above_zero,sum_above_one);
  }
  return
    CreateTwoDigitNewickDerivativesComplexComplex(
      x,y,sum_above_zero,sum_above_one);
}

const ribi::TwoDigitNewick
  ribi::TwoDigitNewickIndexer::CreateTwoDigitNewickDerivativesSimpleSimple(
  const int x, const int y)
{
  assert(x <= y);
  assert(x <= m_reserved && y <= m_reserved);
  assert(IsSimple(x) && IsSimple(y));


  if (x==1 && y==1)
  {
    //(1,1) -> 2
    //'2' has reserved index 2
    std::vector<TwoDigitNewickDerivative> v;
    const int derived_index = 2;
    const int value_changed = 1;
    const int other_value_changed = 1;
    //Add this derivative twice, because there are two ways
    //to change (1,1) -> 2
    v.push_back(
      TwoDigitNewickDerivative(
        derived_index,value_changed,other_value_changed));
    v.push_back(
      TwoDigitNewickDerivative(
        derived_index,value_changed,other_value_changed));
    //saz = sum above zero
    const int saz = 2;
    //sao = sum above one
    const int sao = 0;
    TwoDigitNewick n(v,saz,sao);
    return n;
  }
  else if (x==1)
  {
    //(1,y) -> { (1,y-1), (y+1) }
    //'1','y' and 'y-1' are reserved indices
    assert(x == 1);
    assert(y > 1 && y < m_reserved);
    std::vector<TwoDigitNewickDerivative> v;
    //Create (1,y-1)
    {
      //saz = sum above zero
      const int saz = x + y - 1;
      //sao = sum above one
      const int sao = (y - 1 == 1 ? 0 : y - 1);
      assert(saz >  0);
      assert(sao >= 0);
      const int d_i = SummarizeNewick(x,y-1,saz,sao);
      const int value_changed = y;
      const int other_value_changed = 0; //<Only y changed
      v.push_back(TwoDigitNewickDerivative(d_i,value_changed,other_value_changed));
    }
    //Create (y+1)
    {
      ///\todo: this
      const int d_i = y + 1;
      const int value_changed = 1;       //Note the reversal of 1 and y
      const int other_value_changed = y; //Note the reversal of 1 and y
      v.push_back(TwoDigitNewickDerivative(d_i,value_changed,other_value_changed));
    }
    TwoDigitNewick n( v,x+y,y);
    return n;
  }
  else
  {
    //(x,y) -> { (x-1,y), (x,y-1) }
    //'y','y-1','x' and 'x-1' are reserved indices
    assert(x > 1 && x < m_reserved);
    assert(y > 1 && y < m_reserved);

    std::vector<TwoDigitNewickDerivative> v;

    //saz = sum above zero
    const int saz = x + y - 1;
    //sao = sum above one
    const int sao_left  = (x - 1 == 1 ? x + y - 2 : x + y - 1);
    const int sao_right = (y - 1 == 1 ? x + y - 2 : x + y - 1);

    assert(saz       >  0);
    assert(sao_left  >= 0);
    assert(sao_right >= 0);
    //Derive (x-1,y)
    {
      const int d_i_left  = SummarizeNewick(x-1,y,saz,sao_left );
      const int value_changed_left = x;
      const int other_value_changed_left = 0; //<Only x changed
      v.push_back(
        TwoDigitNewickDerivative(
          d_i_left,value_changed_left,other_value_changed_left));
    }
    //Derive (x,y-1)
    {
      const int d_i_right = SummarizeNewick(x,y-1,saz,sao_right);
      const int value_changed_right = y;
      const int other_value_changed_right = 0; //<Only y changed
      v.push_back(
        TwoDigitNewickDerivative(
          d_i_right,value_changed_right,other_value_changed_right));
      TwoDigitNewick n(v,x+y,x+y);
      return n;
    }
  }
}

const ribi::TwoDigitNewick ribi::TwoDigitNewickIndexer::CreateTwoDigitNewickDerivativesSimpleComplex(
  const int x, const int y,
  const int sum_above_zero,
  const int sum_above_one)
{
  assert(IsSimple(x) && !IsSimple(y));

  std::vector<TwoDigitNewickDerivative> v;
  assert(x>=0);
  if (x>1)
  {
    assert(x > 1);
    assert(y >= m_reserved && "So cannot work with y-1");
    //saz = sum above zero
    const int saz = sum_above_zero - 1;
    assert(saz >= 0);
    //sao = sum above one
    const int sao = (x - 1 == 1 ? sum_above_one - 2 : sum_above_one - 1);

    assert(saz >  0);
    assert(sao >= 0);

    const int i = SummarizeNewick(x-1,y,saz,sao);
    assert(i < m_newicks.Size());

    const int value_changed = x;
    const int other_value_changed = 0; //<Only x changed
    v.push_back(TwoDigitNewickDerivative(i,value_changed,other_value_changed));
  }
  assert(y < m_newicks.Size());
  assert(!m_newicks.Empty(y));
  //\todo: Find out why 'const TwoDigitNewickDerivativesData&' does not work
  const TwoDigitNewick v_derived = m_newicks.GetNewick(y);
  for(const TwoDigitNewickDerivative& i: v_derived.GetDerivatives())
  {
    assert(i.m_derived_index < m_newicks.Size()
      && "TwoDigitNewickDerivative index must be smaller than the number of derivatives");

    //dsaz = delta sum above zero
    const int dsaz = GetDeltaSumAboveZero(i.m_value_changed);
    //dsao = delta sum above one
    const int dsao = GetDeltaSumAboveOne(i);
    //saz = sum above zero
    const int saz = sum_above_zero + dsaz;
    //sao = sum above one
    const int sao = sum_above_one + dsao;

    assert(saz >  0);
    assert(sao >= 0);

    const int d_i = SummarizeNewick( x,i.m_derived_index,saz,sao);

    const int value_changed = i.m_value_changed;
    ///\todo: check that guess is right, that using
    ///i.m_other_value_changed is better than '0'
    const int other_value_changed = i.m_other_value_changed;
    v.push_back(TwoDigitNewickDerivative(d_i,value_changed,other_value_changed));
  }
  TwoDigitNewick n( v,sum_above_zero,sum_above_one);
  return n;
}

const ribi::TwoDigitNewick
  ribi::TwoDigitNewickIndexer::CreateTwoDigitNewickDerivativesComplexComplex(
  const int x, const int y,
  const int sum_above_zero,
  const int sum_above_one)
{
  assert(!IsSimple(x) && !IsSimple(y));
  std::vector<TwoDigitNewickDerivative> v;

  //Get (X',Y)
  {
    assert(x < boost::numeric_cast<int>(m_newicks.Size()));
    assert(!m_newicks.Empty(x));
    //\todo: Find out why 'const TwoDigitNewickDerivativesData&' does not work
    const TwoDigitNewick v_derived = m_newicks.GetNewick(x);
    for(const TwoDigitNewickDerivative& i: v_derived.GetDerivatives())
    {
      //dsaz = delta sum above zero
      const int dsaz = GetDeltaSumAboveZero(i.m_value_changed);
      //dsao = delta sum above one
      const int dsao = GetDeltaSumAboveOne(i);
      //saz = sum above zero
      const int saz = sum_above_zero + dsaz;
      //sao = sum above one
      const int sao = sum_above_one + dsao;

      assert(saz >  0);
      assert(sao >= 0);

      const int d_i = SummarizeNewick(y,i.m_derived_index,saz,sao);

      const int value_changed = i.m_value_changed;
      ///\todo: check that guess is right, that using
      ///i.m_other_value_changed is better than '0'
      const int other_value_changed = i.m_other_value_changed;

      v.push_back(TwoDigitNewickDerivative(d_i,value_changed,other_value_changed));
    }
  }
  //Get (X,Y')
  {
    assert(y < boost::numeric_cast<int>(m_newicks.Size()));
    assert(!m_newicks.Empty(y));
    //\todo: Find out why 'const TwoDigitNewickDerivativesData&' does not work
    const TwoDigitNewick v_derived = m_newicks.GetNewick(y);
    for(const TwoDigitNewickDerivative& i: v_derived.GetDerivatives())
    {
      //dsaz = delta sum above zero
      const int dsaz = GetDeltaSumAboveZero(i.m_value_changed);
      //dsao = delta sum above one
      const int dsao = GetDeltaSumAboveOne(i);
      //saz = sum above zero
      const int saz = sum_above_zero + dsaz;
      //sao = sum above one
      const int sao = sum_above_one + dsao;

      assert(saz >  0);
      assert(sao >= 0);

      const int d_i = SummarizeNewick(x,i.m_derived_index,saz,sao);
      const int value_changed = i.m_value_changed;
      ///\todo: check that guess is right, that using
      ///i.m_other_value_changed is better than '0'
      const int other_value_changed = i.m_other_value_changed;

      v.push_back(TwoDigitNewickDerivative(d_i,value_changed,other_value_changed));
    }
  }
  TwoDigitNewick n(v,sum_above_zero,sum_above_one);
  return n;
}

///GetDeltaSumAboveZero calculates the delta in the
///TwoDigitNewick::m_sum_above_zero of a new Newick
///when an old_value is changed.
int ribi::TwoDigitNewickIndexer::GetDeltaSumAboveZero(const int old_value) const
{
  assert(old_value > 0);
  return (old_value == 1 ? 0 : -1);
}

///GetDeltaSumAboveOne calculates the delta in the
///TwoDigitNewick::m_sum_above_one of a new Newick
///when an old_value is changed.
int ribi::TwoDigitNewickIndexer::GetDeltaSumAboveOne(const TwoDigitNewickDerivative& d) const
{
  const int x = d.m_value_changed;
  //std::clog << "GetDeltaSumAboveOne for x " << x << '\n';
  assert(x > 0);
  if (x  > 2) return -1;
  if (x == 2) return -2;
  assert(x == 1);
  return (d.m_other_value_changed == 1 ? 2 : 1);
}

///GetProbability returns the probability of the BinaryNewickVector
///given at the constructor
double ribi::TwoDigitNewickIndexer::GetProbability() const
{
  assert(m_probability >= 0.0);
  assert(m_probability <= 1.00001);
  assert(m_calculated_to_index == m_newicks.Size()
    && "Assume calculation is completed");

  return m_probability;
}

///IsSimple determines if an index is the index of
///a simple Newick
bool ribi::TwoDigitNewickIndexer::IsSimple(const int i) const
{
  return i < m_reserved;
}

///Allow for recursion
int ribi::TwoDigitNewickIndexer::SummarizeNewick(
  const int x, const int y,
  const int sum_above_zero,
  const int sum_above_one)
{
  assert(sum_above_zero >  0);
  assert(sum_above_one  >= 0);

  assert(x > 0 && y > 0);
  //Ensure proper ordering
  if (x > y)
  {
    return SummarizeNewick(
      y,x,sum_above_zero,sum_above_one);
  }
  assert(x <= y);

  //If index is known, return the index
  if (m_index_table.CanGetIndex(x,y))
  {
    const int i = m_index_table.GetIndex(x,y);
    if (i) return i;
  }

  //A new (x,y) pair is fed
  assert(x <= y);
  const int i = m_current_index;
  m_index_table.SetIndex(x,y,i);

  ++m_current_index;

  assert(sum_above_zero >= 0);
  assert(sum_above_one  >= 0);

  TwoDigitNewick n = CreateTwoDigitNewickDerivatives(
    x,y,sum_above_zero,sum_above_one);

  //Check if the Newick is simple
  //and its probability can be calculated with
  //the Ewens formula
  if (x < m_reserved && y < m_reserved)
  {
    std::vector<int> v;
    v.push_back(Newick::bracket_open);
    v.push_back(x);
    v.push_back(y);
    v.push_back(Newick::bracket_close);
    n.SetProbability(Newick().CalcProbabilitySimpleNewick(v,m_theta));
    //If the user requests simple Newicks to be solved,
    //perhaps the requested probability has just been calculated
    m_probability = n.GetProbability();
  }
  m_newicks.SetNewick(i,n);
  return i;
}

///TryToCalculateNewNewick tries to calculate the probability
///of Newick with index i
void ribi::TwoDigitNewickIndexer::TryToCalculateNewNewick(const int i)
{
  assert(i >= m_calculated_to_index);
  assert(i  < m_newicks.Size());
  ///\todo: why cannot use 'const TwoDigitNewick&'?
  ///\bug: this seems to give memory problems (and funny output)
  const TwoDigitNewick n = this->GetNewick(i);
  //Remember: m_calculated_to_index is not increased
  if (n.IsProbabilityKnown())
  {
    //Already know the probability
    return;
  }
  const std::vector<TwoDigitNewickDerivative> derivatives = n.GetDerivatives();
  //Check if of all derivates the probability is known
  for(const TwoDigitNewickDerivative& derivative: derivatives)
  {
    if (!GetNewick(derivative.m_derived_index).IsProbabilityKnown())
    {
      //Too bad, derived Newick's probability is unknown
      return;
    }
  }
  ///Calculate constants and probability
  double p = 0.0;
  //The denominator is that of the focal Newick,
  //and not its derivative(s)
  const double denominator = GetNewick(i).GetDenominator();
  for(const TwoDigitNewickDerivative& derivative: derivatives)
  {
    assert(GetNewick(derivative.m_derived_index).IsProbabilityKnown());

    const double c
      = (derivative.m_value_changed == 1
      ? m_theta
      : boost::numeric_cast<double>(derivative.m_value_changed) * boost::numeric_cast<double>(derivative.m_value_changed - 1))
      / denominator;
    const double p_this
      = c * GetNewick(derivative.m_derived_index).GetProbability();
    p+=p_this;
  }
  //std::clog << "Index " << i
  //  << " has been calculated to have the probability of "
  //  << p << '\n';
  m_probability = p;
  this->m_newicks.SetNewickProbability(i,p);
}

///TryToCalculateNewNewicks tries to calculate new Newick probabilities
///\warning: m_calculated_to_index is not increased
void ribi::TwoDigitNewickIndexer::TryToCalculateNewNewicks()
{
  const int sz = m_newicks.Size();
  //m_calculated_to_index == sz denotes that all Newicks'
  //probabilities are calculated
  assert(m_calculated_to_index <= sz);
  for (int i = m_calculated_to_index; i!=sz; ++i)
  {
    TryToCalculateNewNewick(i);
  }
}

void ribi::TwoDigitNewickIndexer::UpdateCalculatedFromIndex()
{
  const int sz = m_newicks.Size();
  while (m_calculated_to_index < sz)
  {
    assert(m_calculated_to_index < m_newicks.Size());
    ///\todo: find out why 'const TwoDigitNewick&' does not work
    const TwoDigitNewick n
      = m_newicks.GetNewick(m_calculated_to_index);
    if (n.IsProbabilityKnown())
    {
      //std::clog << "At index " << m_calculated_to_index
      //  << " the probability is known\n";
      ++m_calculated_to_index;
    }
    else
    {
      break;
    }
  }
}
