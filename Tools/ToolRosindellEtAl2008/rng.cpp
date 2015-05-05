//---------------------------------------------------------------------------
/*
RosindellEtAl2008, refactoring an extension of Rosindel at al., 2008 [1]
Copyright (C) 2015 Richel Bilderbeek
Original version by James Rosindell

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRosindellEtAl2008.htm
//
//Article with original code:
//
// [1] Rosindell, James, Yan Wong, and Rampal S. Etienne.
//     "A coalescence approach to spatial neutral ecology."
//      Ecological Informatics 3.3 (2008): 259-271.
//---------------------------------------------------------------------------
#include "rng.h"

#include <cassert>
#include <stdexcept>

Rng::Rng(const int seed, const Type type) noexcept
  : m_seed{seed},
    m_type{type},
    m_mt(seed),
    m_nrrand(seed)
{
  #ifndef NDEBUG
  ///Must be called before Rng construction,
  ///due to Rosindell implementation calling std::srand
  Test();
  #endif
}

int Rng::GetRandomInt(const int max) noexcept
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomInt(max);
    case Type::bilderbeek:
    {
      std::uniform_int_distribution<int> d(0,max);
      const int x{d(m_mt)};
      return x;
    }
  }
  throw std::logic_error("Rng::GetRandomInt"); //Yes, the program will crash, due to noexcept
}

double Rng::GetRandomNormal() noexcept
{
  switch (m_type)
  {
    case Type::rosindell: return m_nrrand.GetRandomNormal();
    case Type::bilderbeek:
    {
      static const double mean{0.0};
      static const double sigma{1.0};
      static std::normal_distribution<double> d(mean,sigma);
      const double x{d(m_mt)};
      return x;
    }
  }
  throw std::logic_error("Rng::GetRandomNormal"); //Yes, the program will crash, due to noexcept
}
