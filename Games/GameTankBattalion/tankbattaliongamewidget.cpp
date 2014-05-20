#include "tankbattaliongamewidget.h"

#include <cassert>

ribi::taba::GameWidget::GameWidget()
  : m_arena(CreateArena())
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::array<std::array<int,ribi::taba::GameWidget::sm_n_columns>,ribi::taba::GameWidget::sm_n_rows> ribi::taba::GameWidget::CreateArena() noexcept
{
  std::array<std::array<int,sm_n_columns>,sm_n_rows> v;
  return v;
}

bool ribi::taba::GameWidget::GetIsBrick(const int x, const int y) const noexcept
{
  assert(x >= 0);
  assert(x < sm_n_columns);
  assert(y >= 0);
  assert(y < sm_n_rows);
  assert(m_arena.at(y).at(x) >= 0);
  return m_arena[y][x];
}
