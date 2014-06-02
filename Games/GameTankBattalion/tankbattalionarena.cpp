#include "tankbattalionarena.h"

#include <cassert>

ribi::taba::Arena::Arena(const int level)
  : m_arena(CreateArena(level))
{
  #ifndef NDEBUG
  //Test();
  #endif
}

std::array<std::array<int,ribi::taba::Arena::sm_n_columns>,ribi::taba::Arena::sm_n_rows> ribi::taba::Arena::CreateArena(const int level) noexcept
{
  std::array<std::array<int,sm_n_columns>,sm_n_rows> v;
  std::string s;
  switch (level)
  {
    case 0:
    s = "000000011000000000000"
        "000000011000000000000"
        "001110011001100111100"
        "001000000001100100000"
        "001000000001100100100"
        "001001111001100100100"
        "001001111000000000000"
        "000000000000000000000"
        "000000000001100000000"
        "111001111111100111111"
        "000000000001100000000"
        "000000000001100000000"
        "001001111001100110000"
        "111001111001100110011"
        "001001000000000000000"
        "000001000000000000000"
        "001001001111001100100"
        "001001000000001100100"
        "001001000000001100100"
        "001001001111001100100"
        "000000001221000000000"
        "000000001221000000000"
      ;
    break;
    default:
      assert(!"Not implemented this level");
  }

  int index = 0;
  for (int y=0; y!=GetRows(); ++y)
  {
    for (int x=0; x!=GetColumns(); ++x)
    {
      assert(y < static_cast<int>(v.size()));
      assert(x < static_cast<int>(v[y].size()));
      assert(index < static_cast<int>(s.size()));
      v[y][x] = static_cast<int>(s[index]);
      ++index;
    }
  }
  return v;
}

/*
QPixmap ribi::taba::Arena::CreatePixmap() const noexcept
{
  QPixmap p(GetColumns() * 8,GetRows() * 8);

}
*/

bool ribi::taba::Arena::Get(const int x, const int y) const noexcept
{
  assert(x >= 0);
  assert(x < sm_n_columns);
  assert(y >= 0);
  assert(y < sm_n_rows);
  assert(m_arena.at(y).at(x) >= 0);
  return m_arena[y][x];
}

