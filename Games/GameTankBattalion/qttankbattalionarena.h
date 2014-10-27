#ifndef QTTANKBATTALIONARENA_H
#define QTTANKBATTALIONARENA_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "tankbattalionfwd.h"
#include "tankbattaliondirection.h"
struct QImage;

#pragma GCC diagnostic pop

namespace ribi {
namespace taba {

//Displays an Arena
struct QtArena
{
  QtArena(const boost::shared_ptr<const Arena>& arena);
  QImage Create(
    const int player_x,
    const int player_y,
    const Direction player_direction
  ) const;

  private:
  const boost::shared_ptr<const Arena> m_arena;
};

} //~namespace taba
} //~namespace ribi

#endif // QTTANKBATTALIONARENA_H
