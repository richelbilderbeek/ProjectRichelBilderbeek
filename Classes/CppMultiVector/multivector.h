//---------------------------------------------------------------------------
/*
MultiVector, any-dimensional std::vector class
Copyright (C) 2011-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS  A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppMultiVector.htm
//---------------------------------------------------------------------------
#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

namespace ribi {

template <class T>
struct MultiVector
{
  MultiVector() : m_indices{}, m_multivectors{} {}

  ///CanRetrieve returns if an index/coordinat can be retrieved
  bool CanRetrieve(const std::vector<int>& indices) const
  {
    assert(!indices.empty());
    if (indices.size() == 1)
    {
      return (indices[0] < boost::numeric_cast<int>(m_indices.size()));
    }
    else
    {
      std::vector<int> copy_indices;
      std::copy(indices.begin() + 1,indices.end(),std::back_inserter(copy_indices));
      if (!(indices[0] < boost::numeric_cast<int>(m_multivectors.size())))
      {
        return false;
      }
      return m_multivectors[ indices[0] ].CanRetrieve(copy_indices);
    }
  }

  ///CreateTable creates a non-recursive table
  const std::vector<std::pair<std::vector<T>,T> > CreateTable() const
  {
    assert(!"TODO");
    std::vector<std::pair<std::vector<T>,T> > v;
    return v;
  }

  const std::vector<T>& PeekIndices() const { return m_indices; }

  const std::vector<MultiVector>& PeekMultiVectors() const { return m_multivectors; }

  ///Retrieve retrieves a stored value at a certain, any-dimensional index/coordinat
  const T& Retrieve(const std::vector<int>& indices) const
  {
    assert(!indices.empty());
    if (!CanRetrieve(indices))
    {
      std::clog << "Breakpoint\n";
    }
    assert(CanRetrieve(indices));
    if (indices.size() == 1)
    {
      assert(indices[0] < boost::numeric_cast<int>(m_indices.size()));
      return m_indices[indices[0] ];
    }
    else
    {
      std::vector<int> copy_indices;
      std::copy(indices.begin() + 1,indices.end(),std::back_inserter(copy_indices));
      assert(indices[0] < boost::numeric_cast<int>(m_multivectors.size()));
      return m_multivectors[ indices[0] ].Retrieve(copy_indices);
    }
  }

  ///Store stores a value at a certain, any-dimensional index/coordinat
  void Store(const std::vector<int>& indices, const T& value)
  {
    assert(!indices.empty());
    const int index = indices[0];
    if (indices.size() == 1)
    {
      if (index + 1 > boost::numeric_cast<int>(m_indices.size()))
      {
        m_indices.resize(index + 1);
      }
      assert(index < boost::numeric_cast<int>(m_indices.size()));
      m_indices[index] = value;
    }
    else
    {
      std::vector<int> copy_indices;
      std::copy(indices.begin() + 1,indices.end(),std::back_inserter(copy_indices));
      if (index + 1 > boost::numeric_cast<int>(m_multivectors.size()))
      {
        m_multivectors.resize(index + 1);
      }
      assert(indices[0] < boost::numeric_cast<int>(m_multivectors.size()));
      m_multivectors[ indices[0] ].Store(copy_indices,value);
    }
  }

  private:
  std::vector<T> m_indices;
  std::vector<MultiVector> m_multivectors;

  public:

  static std::string GetVersion()
  {
    return "1.1";
  }

  std::vector<std::string> GetVersionHistory()
  {
    return {
      "2011-03-02: version 1.0: initial version",
      "2011-03-02: version 1.1: added CanRetrieve and Peek methods"
    };
  }
};

} //~namespace ribi

#endif // MULTIVECTOR_H
