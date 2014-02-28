#include "staircasecardcolumn.h"

#include <cassert>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"

#pragma GCC diagnostic pop

ribi::scc::Column::Column(const int n_vertical, const int n_horizontal)
  : m_v(Create(n_vertical,n_horizontal))
{

}

const std::vector<ribi::scc::Orientation> ribi::scc::Column::Create(const int n_vertical, const int n_horizontal) noexcept
{
  std::vector<Orientation> v;
  v.reserve(n_vertical + n_horizontal);
  for (int i=0; i!=n_vertical; ++i) { v.push_back(Orientation::vertical); }
  for (int i=0; i!=n_horizontal; ++i) { v.push_back(Orientation::horizontal); }
  assert(n_vertical + n_horizontal == static_cast<int>(v.size()));
  return v;
}

ribi::scc::Orientation ribi::scc::Column::GetOrientation(const int row) const noexcept
{
  assert(row >= 0);
  assert(row < GetMax());
  return m_v[row];
}

void ribi::scc::Column::Swap(const int a, const int b) noexcept
{
  assert(a >= 0);
  assert(a < GetMax());
  assert(b <= 0);
  assert(b < GetMax());
  std::swap(m_v[a],m_v[b]);
}

std::string ribi::scc::Column::ToStr() const noexcept
{
  std::string s;
  for (auto c: m_v)
  {
    s += (c == Orientation::horizontal ? 'h' : 'v');
  }
  return s;
}
