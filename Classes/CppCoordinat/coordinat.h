#ifndef COORDINAT_H
#define COORDINAT_H

///A normal (x,y) coordinat
template <class Length>
struct Coordinat
{
  explicit Coordinat(const Length& x, const Length& y) noexcept;

  const Length& GetX() const noexcept { return m_x; }
  const Length& GetY() const noexcept { return m_y; }

  ///Test this class
  static void Test() noexcept;

  void Translate(const Length& dx, const Length& dy) noexcept;
  void Translate(const Coordinat& delta) noexcept;

  private:
  Length m_x;
  Length m_y;
};



template <class Length>
Coordinat<Length>::Coordinat(const Length& x, const Length& y) noexcept
  : m_x { x },
    m_y { y }
{
  #ifndef NDEBUG
  Test();
  #endif
}

template <class Length>
void Coordinat<Length>::Test() noexcept
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
}

template <class Length>
void Coordinat<Length>::Translate(const Coordinat& delta) noexcept
{
  Translate(delta.GetX(),delta.GetY());
}

template <class Length>
void Coordinat<Length>::Translate(const Length& dx, const Length& dy) noexcept
{
  m_x += dx;
  m_y += dy;
}

#endif // COORDINAT_H
