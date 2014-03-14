#ifndef COORDINAT_H
#define COORDINAT_H

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

#endif // COORDINAT_H
