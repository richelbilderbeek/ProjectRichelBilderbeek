#ifndef TANKBATTALIONGAMEWIDGET_H
#define TANKBATTALIONGAMEWIDGET_H

#include <array>
#include <vector>
#include "tankbattaliondirection.h"
#include "tankbattalionkey.h"

namespace ribi {
namespace taba {

struct GameWidget
{
  GameWidget();
  int GetColumns() const noexcept { return sm_n_columns; }
  Direction GetDirection() const noexcept { return m_direction; }

  bool GetIsBrick(const int x, const int y) const noexcept;
  int GetRows() const noexcept { return sm_n_rows; }
  int GetPlayerX() const noexcept { return m_x; }
  int GetPlayerY() const noexcept { return m_y; }

  void OnTimer() noexcept;

  ///Responds to a key press
  void PressKey(const Key key);

  ///Responds to a key release
  void ReleaseKey(const Key key);

  private:
  static const int sm_n_columns = 21; //blocks
  static const int sm_n_rows    = 22; //blocks

  std::array<std::array<int,sm_n_columns>,sm_n_rows> m_arena;
  Direction m_direction;

  ///The primary key, if any, is at index 0
  ///The secondary key, if any, is at index 1
  std::vector<Key> m_keys;
  int m_x;
  int m_y;

  static std::array<std::array<int,sm_n_columns>,sm_n_rows> CreateArena() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace taba
} //~namespace ribi

#endif // TANKBATTALIONGAMEWIDGET_H
