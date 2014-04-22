#ifndef MAZIAKSPRITES_H
#define MAZIAKSPRITES_H

#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>

#include "maziaksprite.h"
#pragma GCC diagnostic pop

struct QPixmap;

namespace ribi {
namespace maziak {

struct Sprites
{
  Sprites();
  const boost::shared_ptr<const QPixmap> Get(const Sprite sprite) const noexcept;

  ///ASCII art
  static char ToChar(const Sprite) noexcept;

  private:
  const std::map<Sprite,boost::shared_ptr<const QPixmap>> m_sprites;

  static std::string CamelCasify(const std::string& s) noexcept;
  const std::map<Sprite,boost::shared_ptr<const QPixmap>> CreateSprites();
  static const std::vector<Sprite> GetAllSprites() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  static std::string ToStr(const Sprite) noexcept;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSPRITES_H
