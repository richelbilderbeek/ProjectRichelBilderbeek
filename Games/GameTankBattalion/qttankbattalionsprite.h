#ifndef QTTANKBATTALIONSPRITE_H
#define QTTANKBATTALIONSPRITE_H

#include <map>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "tankbattalionspritetype.h"
#include "tankbattalionfwd.h"

struct QImage;

#pragma GCC diagnostic pop

namespace ribi {
namespace taba {

///Get a Sprite
struct QtSprite
{
  typedef std::map<SpriteType,QImage> Map;
  QtSprite();
  QImage GetImage(const SpriteType& s) const;

  private:
  const Map m_sprites;
  Map CreateSprites() const;
  QImage Create() const;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace taba
} //~namespace ribi

#endif // QTTANKBATTALIONSPRITE_H
