#ifndef GAMEXENONZEROSPRITE_H
#define GAMEXENONZEROSPRITE_H

#include <vector>
#include <string>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "xenonzerospritetype.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace xnz {

struct Sprite
{
  typedef std::vector<std::string> Graphic;

  Sprite(
    const int x,
    const int y,
    const Graphic& graphic,
    const int health);
  virtual ~Sprite() {}

  const Graphic& GetGraphic() const { return mGraphic; }
  int GetX() const { return mX; }
  int GetY() const { return mY; }
  int GetHealth() const { return mHealth; }
  bool IsSpriteBodyRel(const int x, const int y) const;
  bool IsSpriteBodyAbs(const int x, const int y) const;
  const std::vector<std::pair<int,int> > GetSpriteBodyAbs() const;

  void ChangeHealth(const int delta) { mHealth+=delta; }
  bool IsDead() const { return mHealth <= 0; }
  void ChangeX(const int dx);
  void ChangeY(const int dy);
  int GetWidth() const;
  int GetHeight() const;

  void SetGraphic(const Graphic& g) { mGraphic = g; }

  virtual EnumSprite GetSprite() const = 0;
  virtual void Move() = 0;
  virtual void Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites)  = 0;

  static int mMinx;
  static int mMiny;
  static int mMaxx;
  static int mMaxy;

  private:
  int mX;
  int mY;
  Graphic mGraphic;
  int mHealth;

};

struct SpritePlayer : public Sprite
{
  SpritePlayer(const int x, const int y);

  EnumSprite GetSprite() const { return EnumSprite::spritePlayer; }
  void Move() {}
  void Move(const int dx, const int dy);
  void Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites);
  int GetMaxHealth() const { return 100; }

  private:
  const Graphic GetPlayerGraphic() const;

};

struct SpriteMissile : public Sprite
{
  SpriteMissile(const int x, const int y, const int dx, const int dy, const int size = 1);

  EnumSprite GetSprite() const { return EnumSprite::spriteMissile; }
  void Move();
  void Shoot(std::vector<boost::shared_ptr<Sprite> >& /* newSprites */) { /* A rocket cannot shoot*/ }

  private:
  const Graphic GetMissileGraphic(const int size) const;
  const int mDx;
  const int mDy;

};

struct SpriteEnemySmall : public Sprite
{
  SpriteEnemySmall(const int x, const int y);

  EnumSprite GetSprite() const { return EnumSprite::spriteEnemySmall; }
  void Move();
  void Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites);

  private:
  const Sprite::Graphic GetSpriteEnemySmallGraphic() const;
  int mDx;
  int mTimer;
  const int mTimeShoot;

};

struct SpriteEnemyMedium : public Sprite
{
  enum EnumTurretDirection { turretDownLeft, turretDown, turretDownRight };
  SpriteEnemyMedium(const int x, const int y);

  EnumSprite GetSprite() const { return EnumSprite::spriteEnemyMedium; }
  void Move();
  void Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites);

  private:
  const Sprite::Graphic GetSpriteShootDown() const;
  const Sprite::Graphic GetSpriteShootDownLeft() const;
  const Sprite::Graphic GetSpriteShootDownRight() const;

  int mDx;
  int mTimer;
  const int mTimeShoot;
  EnumTurretDirection mTurretDirection;

};

bool IsCollision(
  const boost::shared_ptr<Sprite>& s1,
  const boost::shared_ptr<Sprite>& s2);

} //~namespace xnz

} //~namespace ribi

#endif
