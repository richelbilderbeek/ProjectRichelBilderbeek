#ifndef COORDINAT_H
#define COORDINAT_H

///A normal (x,y) coordinat
template <class Length>
struct Coordinat
{
  explicit Coordinat(const Length& x, const Length& y);

  const Length& GetX() const { return m_x; }
  const Length& GetY() const { return m_y; }

  ///Test this class
  static void Test();

  void Translate(const Length& dx, const Length& dy);
  void Translate(const Coordinat& delta);

  private:
  Length m_x;
  Length m_y;
};



template <class Length>
Coordinat<Length>::Coordinat(const Length& x, const Length& y)
  : m_x { x },
    m_y { y }
{
  #ifndef NDEBUG
  Test();
  #endif
}

template <class Length>
void Coordinat<Length>::Test()
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
}

template <class Length>
void Coordinat<Length>::Translate(const Coordinat& delta)
{
  Translate(delta.GetX(),delta.GetY());
}

template <class Length>
void Coordinat<Length>::Translate(const Length& dx, const Length& dy)
{
  m_x += dx;
  m_y += dy;
}

#endif // COORDINAT_H
