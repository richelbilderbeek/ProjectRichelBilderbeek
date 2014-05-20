#ifndef TANKBATTALIONGAMEWIDGET_H
#define TANKBATTALIONGAMEWIDGET_H

#include <array>

namespace ribi {
namespace taba {

struct GameWidget
{
  GameWidget();
  int GetColumns() const noexcept { return sm_n_columns; }
  bool GetIsBrick(const int x, const int y) const noexcept;
  int GetRows() const noexcept { return sm_n_rows; }

  private:
  static const int sm_n_columns  = 21; //blocks
  static const int sm_n_rows = 22; //blocks
  std::array<std::array<int,sm_n_columns>,sm_n_rows> m_arena;

  static std::array<std::array<int,sm_n_columns>,sm_n_rows> CreateArena() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace taba
} //~namespace ribi

#endif // TANKBATTALIONGAMEWIDGET_H
