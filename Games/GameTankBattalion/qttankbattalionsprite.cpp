#include "qttankbattalionsprite.h"

#include <cassert>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QImage>
#include "tankbattalionspritetypes.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::taba::QtSprite::QtSprite()
  : m_sprites{CreateSprites()}
{

}

ribi::taba::QtSprite::Map ribi::taba::QtSprite::CreateSprites() const
{
  Map m;
  m[SpriteType::bricks      ] = QImage(":/GameTankBattalion/images/GameTankBattalionBricks.png"     );
  m[SpriteType::flag        ] = QImage(":/GameTankBattalion/images/GameTankBattalionFlag.png"     );
  m[SpriteType::no_bricks   ] = QImage(":/GameTankBattalion/images/GameTankBattalionNoBricks.png"   );
  m[SpriteType::player_down ] = QImage(":/GameTankBattalion/images/GameTankBattalionPlayerDown.png" );
  m[SpriteType::player_left ] = QImage(":/GameTankBattalion/images/GameTankBattalionPlayerLeft.png" );
  m[SpriteType::player_right] = QImage(":/GameTankBattalion/images/GameTankBattalionPlayerRight.png");
  m[SpriteType::player_up   ] = QImage(":/GameTankBattalion/images/GameTankBattalionPlayerUp.png"   );
  assert(static_cast<int>(m.size()) == static_cast<int>(SpriteType::n_types));
  #ifndef NDEBUG
  for (auto p:m) { assert(p.second.width() > 0 && "Picture must exist"); }
  #endif
  return m;
}

QImage ribi::taba::QtSprite::GetImage(const SpriteType& s) const
{
  const Map::const_iterator i
    = m_sprites.find(s);
  assert(i!=m_sprites.end());
  return i->second;
}

#ifndef NDEBUG
void ribi::taba::QtSprite::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    SpriteTypes();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtSprite s;
}
#endif
