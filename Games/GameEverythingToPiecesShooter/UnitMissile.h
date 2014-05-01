//---------------------------------------------------------------------------

#ifndef UnitMissileH
#define UnitMissileH
//---------------------------------------------------------------------------
struct Missile
{
  Missile(
    const double& x, const double& y,
    const double& dX, const double& dY,
    const int& spriteIndex1, const int& spriteIndex2)
  : mX(x), mY(y),
    mDx(dX), mDy(dY),
    mSpriteIndex1(spriteIndex1),
    mSpriteIndex2(spriteIndex2),
    mSpriteIndex(spriteIndex1),
    mDeleteMe(false)
  {

  }
  const int mDx;
  const int mDy;
  const int mSpriteIndex1;
  const int mSpriteIndex2;

  void Move();
  bool DeleteMe() const { return mDeleteMe; }

  private:
  double mX;
  double mY;
  bool mDeleteMe;

  static double mMinX;
  static double mMinY;
  static double mMaxX;
  static double mMaxY;

  int mSpriteIndex;
};
//---------------------------------------------------------------------------
#endif
