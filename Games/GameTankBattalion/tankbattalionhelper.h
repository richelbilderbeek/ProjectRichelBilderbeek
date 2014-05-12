#ifndef TANKBATTALIONHELPER_H
#define TANKBATTALIONHELPER_H

#include "tankbattaliondirection.h"
#include "tankbattalionspritetype.h"

namespace ribi {
namespace taba {

struct Helper
{
  SpriteType ToPlayerSpriteType(const Direction d) const noexcept;
};

} //~namespace taba
} //~namespace ribi

#endif // TANKBATTALIONHELPER_H
