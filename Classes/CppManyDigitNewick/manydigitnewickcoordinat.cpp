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
#include "manydigitnewickcoordinat.h"

#include <algorithm>
#include <cassert>
#include <functional>

#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

ribi::ManyDigitNewickCoordinat::ManyDigitNewickCoordinat(
  const std::vector<int>& v)
  : m_v(Sort(v))
{
  assert(IsValid()  && "Assume all indices in a ManyDigitCoordinat are positive");
  assert(IsSorted() && "Assume that all indices are sorted");
}

///AllSimple returns whether it contains simple indices only.
///ManyDigitNewickIndexer::m_reserved determines this:
///a value of '7' might be the Newick frequency of '7' if
///threshold_index equals '9'. If the threshold_index equals '5', however,
///'7' might be a summarization of '(2,2)'.
bool ribi::ManyDigitNewickCoordinat::AllSimple(const int threshold_index) const
{
  return
    std::count_if(
      m_v.begin(),
      m_v.end(),
      std::bind2nd(std::less<int>(),threshold_index))
    == boost::numeric_cast<int>(m_v.size());

}

///IsSorted checks if a std::vector is sorted.
///From http://www.richelbilderbeek.nl/CppIsSorted.htm
bool ribi::ManyDigitNewickCoordinat::IsSorted() const
{
  return std::adjacent_find(
    m_v.begin(),
    m_v.end(),
    std::greater<int>()) == m_v.end();
}

///IsValid returns if all indices are valid, that is, positive and
///non-zero.
bool ribi::ManyDigitNewickCoordinat::IsValid() const
{
  return
    std::count_if(
      m_v.begin(),
      m_v.begin(),
      std::bind2nd(std::less_equal<int>(),0))
    == 0;

}

const std::vector<int> ribi::ManyDigitNewickCoordinat::Sort(std::vector<int> v)
{
  std::sort(std::begin(v),std::end(v));
  return v;
}


