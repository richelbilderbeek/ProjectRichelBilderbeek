//---------------------------------------------------------------------------

#ifndef UnitSpriteH
#define UnitSpriteH
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
enum EnumSprite
{
  spritePlayer,
  spriteMissile,
  spriteEnemySmall,
  spriteEnemyMedium
};
//---------------------------------------------------------------------------
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
  const int GetX() const { return mX; }
  const int GetY() const { return mY; }
  const int GetHealth() const { return mHealth; }
  const bool IsSpriteBodyRel(const int x, const int y) const;
  const bool IsSpriteBodyAbs(const int x, const int y) const;
  const std::vector<std::pair<int,int> > GetSpriteBodyAbs() const;

  void ChangeHealth(const int delta) { mHealth+=delta; }
  const bool IsDead() const { return mHealth <= 0; }
  void ChangeX(const int dx);
  void ChangeY(const int dy);
  const int GetWidth() const;
  const int GetHeight() const;

  void SetGraphic(const Graphic& g) { mGraphic = g; }

  virtual const EnumSprite GetSprite() const = 0;
  virtual void Move() = 0;
  virtual void Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites)  = 0;

  static int mMinx;
  static int mMiny;
  static int mMaxx;
  static int mMaxy;

  private:
  int mX;
  int mY;
  int mHealth;
  Graphic mGraphic;

};
//---------------------------------------------------------------------------
struct SpritePlayer : public Sprite
{
  SpritePlayer(const int x, const int y);

  const EnumSprite GetSprite() const { return spritePlayer; }
  void Move() {}
  void Move(const int dx, const int dy);
  void Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites);
  const int GetMaxHealth() const { return 100; }

  private:
  const Graphic GetPlayerGraphic() const;

};
//---------------------------------------------------------------------------
struct SpriteMissile : public Sprite
{
  SpriteMissile(const int x, const int y, const int dx, const int dy, const int size = 1);

  const EnumSprite GetSprite() const { return spriteMissile; }
  void Move();
  void Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites) { /* A rocket cannot shoot*/ }

  private:
  const Graphic GetMissileGraphic(const int size) const;
  const int mDx;
  const int mDy;

};
//---------------------------------------------------------------------------
struct SpriteEnemySmall : public Sprite
{
  SpriteEnemySmall(const int x, const int y);

  const EnumSprite GetSprite() const { return spriteEnemySmall; }
  void Move();
  void Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites);

  private:
  const Sprite::Graphic GetSpriteEnemySmallGraphic() const;
  int mTimer;
  int mDx;
  const int mTimeShoot;

};
//---------------------------------------------------------------------------
struct SpriteEnemyMedium : public Sprite
{
  enum EnumTurretDirection { turretDownLeft, turretDown, turretDownRight };
  SpriteEnemyMedium(const int x, const int y);

  const EnumSprite GetSprite() const { return spriteEnemyMedium; }
  void Move();
  void Shoot(std::vector<boost::shared_ptr<Sprite> >& newSprites);

  private:
  const Sprite::Graphic GetSpriteShootDown() const;
  const Sprite::Graphic GetSpriteShootDownLeft() const;
  const Sprite::Graphic GetSpriteShootDownRight() const;

  int mTimer;
  int mDx;
  const int mTimeShoot;
  EnumTurretDirection mTurretDirection;

};
//---------------------------------------------------------------------------
const bool IsCollision(
  const boost::shared_ptr<Sprite>& s1,
  const boost::shared_ptr<Sprite>& s2);


#endif
