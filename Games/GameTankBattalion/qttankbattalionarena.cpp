#include "qttankbattalionarena.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QImage>
#include <QPixmap>
#include "qttankbattalionsprite.h"
#include "tankbattalionarena.h"
#include "tankbattalionhelper.h"
#pragma GCC diagnostic pop

QImage ribi::taba::QtArena::Create(
  const int player_x,
  const int player_y,
  const Direction player_direction
) const
{
  QImage image;
  const int block_width  = 8;
  const int block_height = 8;
  const auto n_rows = Arena::GetRows();
  const auto n_cols = Arena::GetColumns();

  for (int row=0; row!=n_rows; ++row)
  {
    const int top{row * block_height};
    for (int col=0; col!=n_cols; ++col)
    {
      const int left{col * block_width};
      const auto type = m_arena->Get(col,row);
      const auto sprite = QtSprite().GetImage(type);
      for (int x=0;x!=block_width; ++x)
      {
        for (int y=0;y!=block_height; ++y)
        {
          image.setPixel(left + x,top + y,
            sprite.pixel(x,y)
          );
        }
      }
    }
  }

  //Player
  {
    const auto sprite = QtSprite().GetImage(Helper().ToPlayerSpriteType(player_direction));
    assert(sprite.height() > 0);
    assert(sprite.width() > 0);
    for (int x=0;x!=block_width*2; ++x)
    {
      for (int y=0;y!=block_height*2; ++y)
      {
        image.setPixel(player_x + x,player_y + y,
          sprite.pixel(x,y)
        );
      }
    }
  }

  //Flag
  {
    const int left{9 * block_width};
    const int top{20 * block_width};
    const auto sprite = QtSprite().GetImage(SpriteType::flag);
    assert(sprite.height() > 0);
    assert(sprite.width() > 0);
    for (int x=0;x!=block_width*2; ++x)
    {
      for (int y=0;y!=block_height*2; ++y)
      {
        image.setPixel(left + x,top + y,
          sprite.pixel(x,y)
        );
      }
    }
  }
  return image;
}
