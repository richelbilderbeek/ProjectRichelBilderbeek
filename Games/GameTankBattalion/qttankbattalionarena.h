#ifndef QTTANKBATTALIONARENA_H
#define QTTANKBATTALIONARENA_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>

#include "tankbattalionfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace taba {

struct QtArena
{
  QtArena(const boost::shared_ptr<Arena>& arena);
  QPixmap Create();

  private:
  const boost::shared_ptr<Arena> m_arena;
};

} //~namespace taba
} //~namespace ribi

#endif // QTTANKBATTALIONARENA_H
