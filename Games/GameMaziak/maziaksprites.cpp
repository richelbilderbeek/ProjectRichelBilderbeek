#include "maziaksprites.h"

#include <cassert>
#include <stdexcept>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QPixmap>

#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::maziak::Sprites::Sprites()
  : m_sprites(CreateSprites())
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::maziak::Sprites::CamelCasify(const std::string& s) noexcept
{
  std::string t;
  const std::size_t sz = s.size();
  for(std::size_t i = 0;i!=sz;++i)
  {
    const char c = s[i];
    if (s[i] == '_')
    {
      assert(i + 1 < s.size());
      ++i;
      const char d = std::toupper(s[i]);
      t += d;
    }
    else
    {
      t += c;
    }
  }
  return t;
}

const std::map<ribi::maziak::Sprite,boost::shared_ptr<const QPixmap>> ribi::maziak::Sprites::CreateSprites()
{
  std::map<ribi::maziak::Sprite,boost::shared_ptr<const QPixmap>> m;
  const std::vector<Sprite> v { GetAllSprites() };
  for (const Sprite sprite: v)
  {
    std::string spritename { ToStr(sprite) };
    spritename[0] = std::toupper(spritename[0]);
    spritename = CamelCasify(spritename);

    const std::string filename {
      ":/images/" + spritename + ".png"
    };

    const boost::shared_ptr<const QPixmap> pixmap {
      new QPixmap(filename.c_str())
    };
    if (pixmap->width() == 0)
    {
      TRACE("Pixmap not found");
      TRACE(filename);
    }
    assert(pixmap);
    assert(pixmap->width() > 0);
    assert(pixmap->height() > 0);
    m.insert(std::make_pair(sprite,pixmap));
  }
  return m;
}

const boost::shared_ptr<const QPixmap> ribi::maziak::Sprites::Get(const Sprite sprite) const noexcept
{
  assert(m_sprites.find(sprite) != m_sprites.end());
  const boost::shared_ptr<const QPixmap> pixmap {
    m_sprites.find(sprite)->second
  };
  assert(pixmap);
  return pixmap;
}

const std::vector<ribi::maziak::Sprite> ribi::maziak::Sprites::GetAllSprites() noexcept
{
  const std::vector<Sprite> v {
    Sprite::empty,
    Sprite::wall,
    Sprite::path,
    Sprite::transparent,
    Sprite::player_look_down,
    Sprite::player_look_down_sword,
    Sprite::player_look_left,
    Sprite::player_look_left_sword,
    Sprite::player_look_right,
    Sprite::player_look_right_sword,
    Sprite::player_look_up,
    Sprite::player_look_up_sword,
    Sprite::player_walk_left1,
    Sprite::player_walk_left2,
    Sprite::player_walk_left_sword1,
    Sprite::player_walk_left_sword2,
    Sprite::player_walk_right1,
    Sprite::player_walk_right2,
    Sprite::player_walk_right_sword1,
    Sprite::player_walk_right_sword2,
    Sprite::player_walk_down1,
    Sprite::player_walk_down2,
    Sprite::player_walk_down_sword1,
    Sprite::player_walk_down_sword2,
    Sprite::player_walk_up1,
    Sprite::player_walk_up2,
    Sprite::player_walk_up_sword1,
    Sprite::player_walk_up_sword2,
    Sprite::player_won1,
    Sprite::player_won2,
    Sprite::fight_sword1,
    Sprite::fight_no_sword1,
    Sprite::fight2,
    Sprite::fight3,
    Sprite::fight4,
    Sprite::fight_won1,
    Sprite::fight_won2,
    Sprite::fight_lost1,
    Sprite::fight_lost2,
    Sprite::enemy1,
    Sprite::enemy2,
    Sprite::prisoner1,
    Sprite::prisoner2,
    Sprite::sword,
    Sprite::exit
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(Sprite::n_sprites)
    && "All Sprite values (except Sprite::n_sprites) must be in");

  return v;
}

#ifndef NDEBUG
void ribi::maziak::Sprites::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  assert(CamelCasify("player_look_down_sword") == "playerLookDownSword");
}
#endif

char ribi::maziak::Sprites::ToChar(const ribi::maziak::Sprite sprite) noexcept
{
  switch (sprite)
  {
    case Sprite::empty: return ' ';
    case Sprite::wall: return 'X';
    case Sprite::path: return '.';
    case Sprite::transparent: return ' ';
    case Sprite::player_look_down: return 'v';
    case Sprite::player_look_down_sword: return 'w';
    case Sprite::player_look_left: return '<';
    case Sprite::player_look_left_sword: return 'E';
    case Sprite::player_look_right: return '>';
    case Sprite::player_look_right_sword: return '3';
    case Sprite::player_look_up: return 'A';
    case Sprite::player_look_up_sword: return 'M';
    case Sprite::player_walk_left1: return '\\';
    case Sprite::player_walk_left2: return '/';
    case Sprite::player_walk_left_sword1: return '=';
    case Sprite::player_walk_left_sword2: return 'E';
    case Sprite::player_walk_right1: return '\\';
    case Sprite::player_walk_right2: return '/';
    case Sprite::player_walk_right_sword1: return '=';
    case Sprite::player_walk_right_sword2: return '3';
    case Sprite::player_walk_down1: return '\\';
    case Sprite::player_walk_down2: return '/';
    case Sprite::player_walk_down_sword1: return 'W';
    case Sprite::player_walk_down_sword2: return 'w';
    case Sprite::player_walk_up1: return '/';
    case Sprite::player_walk_up2: return '\\';
    case Sprite::player_walk_up_sword1: return 'm';
    case Sprite::player_walk_up_sword2: return 'M';
    case Sprite::player_won1: return '!';
    case Sprite::player_won2: return '!';
    case Sprite::fight_sword1: return '#';
    case Sprite::fight_no_sword1: return '+';
    case Sprite::fight2: return '*';
    case Sprite::fight3: return '%';
    case Sprite::fight4: return '@';
    case Sprite::fight_won1: return 'W';
    case Sprite::fight_won2: return 'w';
    case Sprite::fight_lost1: return 'Z';
    case Sprite::fight_lost2: return 'z';
    case Sprite::enemy1: return 'Z';
    case Sprite::enemy2: return 'z';
    case Sprite::prisoner1: return ':';
    case Sprite::prisoner2: return ';';
    case Sprite::sword: return '+';
    case Sprite::exit: return '!';
    case Sprite::n_sprites:
      assert(!"Should never use Sprite::n_sprites");
      throw std::logic_error("Never use Sprite::n_sprites");
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown Sprite");
}

std::string ribi::maziak::Sprites::ToStr(const ribi::maziak::Sprite sprite) noexcept
{
  switch (sprite)
  {
    case Sprite::empty: return "empty";
    case Sprite::wall: return "wall";
    case Sprite::path: return "path";
    case Sprite::transparent: return "transparent";
    case Sprite::player_look_down: return "player_look_down";
    case Sprite::player_look_down_sword: return "player_look_down_sword";
    case Sprite::player_look_left: return "player_look_left";
    case Sprite::player_look_left_sword: return "player_look_left_sword";
    case Sprite::player_look_right: return "player_look_right";
    case Sprite::player_look_right_sword: return "player_look_right_sword";
    case Sprite::player_look_up: return "player_look_up";
    case Sprite::player_look_up_sword: return "player_look_up_sword";
    case Sprite::player_walk_left1: return "player_walk_left1";
    case Sprite::player_walk_left2: return "player_walk_left2";
    case Sprite::player_walk_left_sword1: return "player_walk_left_sword1";
    case Sprite::player_walk_left_sword2: return "player_walk_left_sword2";
    case Sprite::player_walk_right1: return "player_walk_right1";
    case Sprite::player_walk_right2: return "player_walk_right2";
    case Sprite::player_walk_right_sword1: return "player_walk_right_sword1";
    case Sprite::player_walk_right_sword2: return "player_walk_right_sword2";
    case Sprite::player_walk_down1: return "player_walk_down1";
    case Sprite::player_walk_down2: return "player_walk_down2";
    case Sprite::player_walk_down_sword1: return "player_walk_down_sword1";
    case Sprite::player_walk_down_sword2: return "player_walk_down_sword2";
    case Sprite::player_walk_up1: return "player_walk_up1";
    case Sprite::player_walk_up2: return "player_walk_up2";
    case Sprite::player_walk_up_sword1: return "player_walk_up_sword1";
    case Sprite::player_walk_up_sword2: return "player_walk_up_sword2";
    case Sprite::player_won1: return "player_won1";
    case Sprite::player_won2: return "player_won2";
    case Sprite::fight_sword1: return "fight_sword1";
    case Sprite::fight_no_sword1: return "fight_no_sword1";
    case Sprite::fight2: return "fight2";
    case Sprite::fight3: return "fight3";
    case Sprite::fight4: return "fight4";
    case Sprite::fight_won1: return "fight_won1";
    case Sprite::fight_won2: return "fight_won2";
    case Sprite::fight_lost1: return "fight_lost1";
    case Sprite::fight_lost2: return "fight_lost2";
    case Sprite::enemy1: return "enemy1";
    case Sprite::enemy2: return "enemy2";
    case Sprite::prisoner1: return "prisoner1";
    case Sprite::prisoner2: return "prisoner2";
    case Sprite::sword: return "sword";
    case Sprite::exit: return "exit";
    case Sprite::n_sprites:
      assert(!"Should never use Sprite::n_sprites");
      throw std::logic_error("Never use Sprite::n_sprites");
  }
  assert(!"Should not get here");
  throw std::logic_error("Unknown Sprite");
}
