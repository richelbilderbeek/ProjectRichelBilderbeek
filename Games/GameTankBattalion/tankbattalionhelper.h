#ifndef TANKBATTALIONHELPER_H
#define TANKBATTALIONHELPER_H

#include "tankbattaliondirection.h"
#include "tankbattalionkey.h"
#include "tankbattalionspritetype.h"

namespace ribi {
namespace taba {

struct Helper
{
  Helper();
  Direction KeyToDirection(const Key k);
  SpriteType ToPlayerSpriteType(const Direction d) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace taba
} //~namespace ribi

#endif // TANKBATTALIONHELPER_H
