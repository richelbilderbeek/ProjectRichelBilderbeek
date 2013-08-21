#include "gamexenonzerosprite.h"

#include <cassert>

namespace xnz {


int Sprite::mMinx = 1;
int Sprite::mMiny = 1;
int Sprite::mMaxx = 0;
int Sprite::mMaxy = 0;

Sprite::Sprite(
  const int x,
  const int y,
  const Graphic& graphic,
  const int health)
  : mX(x),
    mY(y),
    mGraphic(graphic),
    mHealth(health)
{
  assert( x >= mMinx);
  assert( x <  mMaxx);
  assert( y >= mMiny);
  assert( y <  mMaxy);
  assert(mGraphic.size() > 0);
  assert(mHealth > 0);

}

void Sprite::ChangeX(const int dx)
{
  //assert( x >= mMinx);
  //assert( x <  mMaxx);
  mX += dx;
}

void Sprite::ChangeY(const int dy)
{
  //assert( y >= mMiny);
  //assert( y <  mMaxy);
  mY += dy;
}

void SpritePlayer::Move(const int dx, const int dy)
{
  assert(mMaxx != 0);
  assert(mMaxy != 0);

  //Move in x direction
  {
    this->ChangeX(dx);
    while ( this->GetX() < mMinx)
    {
      this->ChangeX(1);
      this->ChangeHealth(-1);
    }
    while ( this->GetX() + this->GetWidth() > mMaxx)
    {
      this->ChangeX(-1);
      this->ChangeHealth(-1);
    }
  }

  {
    this->ChangeY(dy);
    while ( this->GetY() < mMiny)
    {
      this->ChangeY(1);
      this->ChangeHealth(-1);
    }
    while ( this->GetY() + this->GetHeight() > mMaxy)
    {
      this->ChangeY(-1);
      this->ChangeHealth(-1);
    }
  }
}

int Sprite::GetWidth() const
{
  assert(mGraphic.size() > 0);
  return mGraphic[0].size();
}

int Sprite::GetHeight() const
{
  return mGraphic.size();
}

bool Sprite::IsSpriteBodyAbs(const int x, const int y) const
{
  return this->IsSpriteBodyRel(x - GetX(), y - GetY() );
}

bool Sprite::IsSpriteBodyRel(const int x, const int y) const
{
  if ( x < 0
    || y < 0
    || x >= this->GetWidth()
    || y >= this->GetHeight()
    || mGraphic[y][x] == ' '
    )
    return false;
  return true;
}

const std::vector<std::pair<int,int> > Sprite::GetSpriteBodyAbs() const
{
  std::vector<std::pair<int,int> > v;
  const int maxx = GetX() + GetWidth();
  const int maxy = GetY() + GetHeight();
  for (int y=GetY(); y!=maxy; ++y)
  {
    for (int x=GetX(); x!=maxx; ++x)
    {
      if (IsSpriteBodyAbs(x,y)==true)
        v.push_back(std::make_pair(x,y) );
    }
  }
  return v;
}

SpritePlayer::SpritePlayer(const int x, const int y)
  : Sprite(
      x,
      y,
      this->GetPlayerGraphic(),
      this->GetMaxHealth())
{

}

const Sprite::Graphic SpritePlayer::GetPlayerGraphic() const
{
  Sprite::Graphic g(4);
  g[0] = " |  | ";
  g[1] = " |/\\| ";
  g[2] = " //\\\\ ";
  g[3] = "/_\\/_\\";
  return g;
}

void SpritePlayer::Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites)
{
  const int missileY  = GetY();
  const int missileX1 = GetX() + 1;
  const int missileX2 = GetX() + 4;
  const int dx = 0;
  const int dy = -1;
  boost::shared_ptr<Sprite> missile1(new SpriteMissile(missileX1,missileY,dx,dy));
  boost::shared_ptr<Sprite> missile2(new SpriteMissile(missileX2,missileY,dx,dy));
  newSprites.push_back(missile1);
  newSprites.push_back(missile2);
}

SpriteMissile::SpriteMissile(
  const int x,
  const int y,
  const int dx,
  const int dy,
  const int size)
  : Sprite(x,y,GetMissileGraphic(size),size*size),
    mDx(dx),
    mDy(dy)
{

}

const Sprite::Graphic SpriteMissile::GetMissileGraphic(const int size) const
{
  Sprite::Graphic g(size,std::string(size,'*'));
  return g;
}

void SpriteMissile::Move()
{
  ChangeX(mDx);
  ChangeY(mDy);
  const int x = GetX();
  const int y = GetY();
  if ( x < mMinx || x > mMaxx || y < mMiny || y > mMaxy)
  {
    ChangeHealth( -GetHealth() - 1 );
  }
}

SpriteEnemySmall::SpriteEnemySmall(const int x, const int y)
  : Sprite(x,y,GetSpriteEnemySmallGraphic(),1),
    mTimer(0),
    mTimeShoot(10),
    mDx(1)
{

}

const Sprite::Graphic SpriteEnemySmall::GetSpriteEnemySmallGraphic() const
{
  Sprite::Graphic g(2);
  g[0] = "/*\\/*\\";
  g[1] = "[]  []";

  return g;

}

void SpriteEnemySmall::Move()
{
  this->ChangeX(mDx);
  if (this->GetX() + this->GetWidth() >= this->mMaxx)
  {
    mDx = -mDx;
    this->ChangeX(mDx);
    assert(! (this->GetX() + this->GetWidth() >= this->mMaxx) );
  }
  else if (this->GetX() <= this->mMinx)
  {
    mDx = -mDx;
    this->ChangeX(mDx);
    assert(!(this->GetX() <= this->mMinx));
  }
}

void SpriteEnemySmall::Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites)
{
  ++mTimer;
  if (mTimer % mTimeShoot == 0)
  {
    const int missileY  = GetY() + 2;
    const int missileX1 = GetX() + 0;
    const int missileX2 = GetX() + 5;
    const int dx = 0;
    const int dy = 1;
    boost::shared_ptr<Sprite> missile1(new SpriteMissile(missileX1,missileY,dx,dy));
    boost::shared_ptr<Sprite> missile2(new SpriteMissile(missileX2,missileY,dx,dy));
    newSprites.push_back(missile1);
    newSprites.push_back(missile2);
  }
}

SpriteEnemyMedium::SpriteEnemyMedium(const int x, const int y)
  : Sprite(x,y,GetSpriteShootDown(),10),
    mTimeShoot(2)
{

}

const Sprite::Graphic SpriteEnemyMedium::GetSpriteShootDownLeft() const
{
  Sprite::Graphic g(7);
  g[0] = "  /----\\  ";
  g[1] = " //xxxx\\\\ ";
  g[2] = "//xx/\\xx\\\\";
  g[3] = "\\\\xx\\/xx//";
  g[4] = "  x[[]]x  ";
  g[5] = "  [[]]    ";
  g[6] = " [[]]     ";
  return g;

}

const Sprite::Graphic SpriteEnemyMedium::GetSpriteShootDown() const
{
  Sprite::Graphic g(7);
  g[0] = "  /----\\  ";
  g[1] = " //xxxx\\\\ ";
  g[2] = "//xx/\\xx\\\\";
  g[3] = "\\\\xx\\/xx//";
  g[4] = "  x[[]]x  ";
  g[5] = "   [[]]   ";
  g[6] = "   [[]]   ";

  return g;

}

const Sprite::Graphic SpriteEnemyMedium::GetSpriteShootDownRight() const
{
  Sprite::Graphic g(7);
  g[0] = "  /----\\  ";
  g[1] = " //xxxx\\\\ ";
  g[2] = "//xx/\\xx\\\\";
  g[3] = "\\\\xx\\/xx//";
  g[4] = "  x[[]]x  ";
  g[5] = "    [[]]  ";
  g[6] = "     [[]] ";
  return g;

}

void SpriteEnemyMedium::Move()
{

}

void SpriteEnemyMedium::Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites)
{
  ++mTimer;
  if (mTimer % mTimeShoot == 0)
  {
    const int missileY = GetY() + GetHeight();
    const int missileX = GetX()
      + (GetWidth() / 2)
      + (mTurretDirection == turretDownLeft  ? -2 : 0)
      + (mTurretDirection == turretDownRight ?  2 : 0);
    const int dx = 0
      + (mTurretDirection == turretDownLeft  ? -1 : 0)
      + (mTurretDirection == turretDownRight ?  1 : 0);
    const int dy = 1;
    boost::shared_ptr<Sprite> missile(new SpriteMissile(missileX,missileY,dx,dy,2));
    newSprites.push_back(missile);

  }
  else
  {
    mTurretDirection = static_cast<EnumTurretDirection>(std::rand() % 3);
    switch(mTurretDirection)
    {
      case turretDownLeft:  SetGraphic(GetSpriteShootDownLeft()); break;
      case turretDown:      SetGraphic(GetSpriteShootDown()); break;
      case turretDownRight: SetGraphic(GetSpriteShootDownRight()); break;
      default: assert(!"Should not get here");
    }
  }
}

bool IsCollision(
  const boost::shared_ptr<Sprite>& s1,
  const boost::shared_ptr<Sprite>& s2)
{
  const std::vector<std::pair<int,int> > body1 = s1->GetSpriteBodyAbs();
  const std::vector<std::pair<int,int> > body2 = s2->GetSpriteBodyAbs();
  const std::vector<std::pair<int,int> >::const_iterator j = body1.end();
  for (std::vector<std::pair<int,int> >::const_iterator i = body1.begin(); i!=j; ++i)
  {
    if ( std::find(body2.begin(),body2.end(), *i) != body2.end() ) return true;
  }
  return false;
}

} //~namespace xnz
