#ifndef TANKBATTALIONARENA_H
#define TANKBATTALIONARENA_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <array>
#include <QPixmap>
#include "tankbattalionspritetype.h"
#pragma GCC diagnostic pop

struct QPixmap;

namespace ribi {
namespace taba {

struct Arena
{
  Arena(const int level = 0);
  static int GetColumns() noexcept { return sm_n_columns; }
  static int GetRows() noexcept { return sm_n_rows; }
  SpriteType Get(const int x, const int y) const noexcept;
  //QPixmap CreatePixmap() const noexcept;

  private:
  static const int sm_n_columns = 21; //blocks
  static const int sm_n_rows    = 22; //blocks
  std::array<std::array<SpriteType,sm_n_columns>,sm_n_rows> m_arena;

  static std::array<std::array<SpriteType,sm_n_columns>,sm_n_rows> CreateArena(const int level) noexcept;

};

} //~namespace taba
} //~namespace ribi

#endif // TANKBATTALIONARENA_H
