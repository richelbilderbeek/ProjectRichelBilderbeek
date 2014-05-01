//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitMissile.h"

//---------------------------------------------------------------------------
void Missile::Move()
{
  mX += mDx;
  mY += mDy;
  mSpriteIndex = (mSpriteIndex == mSpriteIndex1 ? mSpriteIndex2 : mSpriteIndex1);

  if ( mX > mMaxX
    || mY > mMaxY
    || mX < mMinX
    || mY < mMinY) mDeleteMe = true;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

