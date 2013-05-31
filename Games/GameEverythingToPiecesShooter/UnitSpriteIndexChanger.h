//---------------------------------------------------------------------------

#ifndef UnitSpriteIndexChangerH
#define UnitSpriteIndexChangerH
//---------------------------------------------------------------------------
#include "UnitEnums.h"
//---------------------------------------------------------------------------
//Given a certain sprite index
//and given a certain action
//SpriteIndexChanger possibly returns a next sprite index
struct SpriteIndexChanger
{
  int Move(const EnumKey& key, const int& index) const;
  int MoveUp(const int& index) const;
  int MoveRight(const int& index) const;
  int MoveDown(const int& index) const;
  int MoveLeft(const int& index) const;
};

#endif
