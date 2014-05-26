#ifndef TANKBATTALIONKEYS_H
#define TANKBATTALIONKEYS_H

#include "tankbattalionkey.h"

namespace ribi {
namespace taba {

struct Keys
{
  Keys() noexcept;

  Key GetOpposite(const Key k) const noexcept;
  bool IsOpposite(const Key a, const Key b) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace taba
} //~namespace ribi


#endif // TANKBATTALIONKEYS_H
