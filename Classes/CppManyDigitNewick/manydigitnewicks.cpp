//---------------------------------------------------------------------------
/*
ManyDigitNewick, Newick class
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppManyDigitNewick.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "manydigitnewicks.h"

#include <cassert>


#include <boost/numeric/conversion/cast.hpp>

#include "newick.h"
#include "manydigitnewickderivative.h"
#include "newickvector.h"

#pragma GCC diagnostic pop

ribi::ManyDigitNewicks::ManyDigitNewicks(const int n_reserved, const double theta)
  : m_v{}
{
  //Create derivatives of simplest and reserved ManyDigitNewicks

  //Create the Newick at index 0
  //this->SetNewick(0,ManyDigitNewick(std::vector<ManyDigitDerivative>(ManyDigitDerivative(),0,0));
  //Create the Newick at index 1
  this->SetNewick(1,ManyDigitNewick(std::vector<Derivative>(),1,0));

  //Let i start at 1, because '(0)' is no valid Newick
  for (int i=2; i!=n_reserved; ++i)
  {
    std::vector<Derivative> v;
    const int value_changed = i;
    const int other_value_changed = 0; //<There is no other value
    v.push_back(Derivative(i-1,value_changed,other_value_changed));

    //saz = sum above zero
    const int saz = i;
    //sao = sum above one
    const int sao = (i > 1 ? i : 0);

    ManyDigitNewick n(v,saz,sao);

    n.SetProbability(Newick().CalcProbabilitySimpleNewick(
      {
        static_cast<int>(Newick::bracket_open),
        i,
        static_cast<int>(Newick::bracket_close)
      },
      theta)
    );
    this->SetNewick(i,n);

    assert( (i < 2 || this->GetNewick(i).IsComplete())
     && "All newick with index >= 2 must be complete");
  }

  assert(Empty(1));
}

///Empty returns if an index is empty
bool ribi::ManyDigitNewicks::Empty(const int i) const
{
  assert(i >= 0);
  assert(i < this->Size());
  return m_v[i].Empty();
}

const ribi::ManyDigitNewick& ribi::ManyDigitNewicks::GetNewick(
    const int i) const
{
  //Check if i is in range
  assert(i>=0);
  assert(i < this->Size());
  //Check if returned indices are okay
  #ifndef NDEBUG
  const ManyDigitNewick& v = m_v[i];
  for(const Derivative& j: v.GetDerivatives())
  {
    assert(j.m_derived_index >= 0);
    assert(j.m_derived_index < this->Size() );
  }
  #endif
  return m_v[i];
}

void ribi::ManyDigitNewicks::SetNewick(const int i, const ManyDigitNewick& v)
{
  //Allocate storage
  //TODO: replace by push_back
  if (i >= boost::numeric_cast<int>(m_v.size()))
  {
    m_v.resize(i + 1);
    assert(m_v[m_v.size()-1].Empty());
  }
  //
  //std::clog << "Adding a Newick at index " << i << '\n';
  assert(m_v[i].Empty());

  #ifndef NDEBUG
  for(const Derivative& j: v.GetDerivatives())
  {
    assert(j.m_derived_index > 0);
    assert(j.m_derived_index < boost::numeric_cast<int>(m_v.size())
      && "Cannot set a derivative index "
         "bigger than the number of derivatives");
  }
  #endif

  m_v[i] = v;
}

void ribi::ManyDigitNewicks::SetNewickProbability(
  const int i,const double p)
{
  assert(i >= 0);
  assert(i  < Size());
  assert(p >= 0.0);
  assert(p <= 1.0);
  m_v[i].SetProbability(p);
}

int ribi::ManyDigitNewicks::Size() const
{
  return boost::numeric_cast<int>(m_v.size());
}

