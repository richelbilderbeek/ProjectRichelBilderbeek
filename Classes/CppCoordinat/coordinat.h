//---------------------------------------------------------------------------
/*
Coordinat, coordinat classes
Copyright (C) 2013-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppCoordinat.htm
//---------------------------------------------------------------------------
#ifndef RIBI_COORDINAT_H
#define RIBI_COORDINAT_H

#ifdef USE_CUSTOM_RIBI_COORDINAT

#include <cassert>
#include "trace.h"

///A normal (x,y) coordinat
template <class Length>
struct Coordinat
{
  explicit Coordinat(const Length& x, const Length& y) noexcept;

  const Length& GetX() const noexcept { return m_x; }
  const Length& GetY() const noexcept { return m_y; }

  void Translate(const Length& dx, const Length& dy) noexcept;
  void Translate(const Coordinat& delta) noexcept;

  private:
  Length m_x;
  Length m_y;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};



template <class Length>
Coordinat::Coordinat(const Length& x, const Length& y) noexcept
  : m_x { x },
    m_y { y }
{
  #ifndef NDEBUG
  Test();
  #endif
}

template <class Length>
void Coordinat::Translate(const Coordinat& delta) noexcept
{
  Translate(delta.GetX(),delta.GetY());
}

template <class Length>
void Coordinat::Translate(const Length& dx, const Length& dy) noexcept
{
  m_x += dx;
  m_y += dy;
}

template <class Length>
Coordinat operator+(const Coordinat& lhs, const Coordinat& rhs) noexcept
{
  return Coordinat(
    lhs.GetX() + rhs.GetX(),
    lhs.GetY() + rhs.GetY()
  );
}

template <class Length>
bool operator==(const Coordinat& lhs, const Coordinat& rhs) noexcept
{
  return lhs.GetX() == rhs.GetX()
      && lhs.GetY() == rhs.GetY();
}


#ifndef NDEBUG
template <class Length>
void Coordinat::Test() noexcept
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Coordinat::Test");
  {
    const Coordinat<double> a(0.0,0.0);
    const Coordinat<double> b(0.0,0.0);
    assert(a == b);
    const Coordinat<double> c(a);
  }
  TRACE("Finished ribi::Coordinat::Test successfully");
}
#endif

#endif // USE_CUSTOM_RIBI_COORDINAT

#endif // RIBI_COORDINAT_H
