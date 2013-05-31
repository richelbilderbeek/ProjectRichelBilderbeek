//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitSpriteIndexChanger.h"
//---------------------------------------------------------------------------
#include "UnitConstants.h"
//---------------------------------------------------------------------------
int SpriteIndexChanger::Move(const EnumKey& key, const int& index) const
{
  switch(key)
  {
    case keyUp   : return MoveUp(index);
    case keyRight: return MoveRight(index);
    case keyDown : return MoveDown(index);
    case keyLeft : return MoveLeft(index);
  }
  return index;
}
//---------------------------------------------------------------------------
int SpriteIndexChanger::MoveUp(const int& index) const
{
  switch(index)
  {
    //Looking right, gun pointing down-right
    case TPS::mainCharRocketDownRight1: return TPS::mainCharRocketRight1;
    case TPS::mainCharRocketDownRight2: return TPS::mainCharRocketRight2;
    //Looking right, normal gun position
    case TPS::mainCharRocketRight1: return TPS::mainCharRocketUpRight1;
    case TPS::mainCharRocketRight2: return TPS::mainCharRocketUpRight2;
    //Looking right, gun pointing up-right
    case TPS::mainCharRocketUpRight1: return TPS::mainCharRocketUp1;
    case TPS::mainCharRocketUpRight2: return TPS::mainCharRocketUp2;
    //Looking down
    case TPS::mainCharRocketDown1: return TPS::mainCharRocketUp1;
    case TPS::mainCharRocketDown2: return TPS::mainCharRocketUp2;
    //Looking left, gun pointing down-left
    case TPS::mainCharRocketDownLeft1: return TPS::mainCharRocketLeft1;
    case TPS::mainCharRocketDownLeft2: return TPS::mainCharRocketLeft2;
    //Looking left, normal gun position
    case TPS::mainCharRocketLeft1: return TPS::mainCharRocketUpLeft1;
    case TPS::mainCharRocketLeft2: return TPS::mainCharRocketUpLeft2;
    //Looking left, gun pointing up-left
    case TPS::mainCharRocketUpLeft1: return TPS::mainCharRocketUp1;
    case TPS::mainCharRocketUpLeft2: return TPS::mainCharRocketUp2;
  }
  return index;
}
//---------------------------------------------------------------------------
int SpriteIndexChanger::MoveRight(const int& index) const
{
  switch(index)
  {
    //Accelerate right, normal gun position
    case TPS::mainCharRocketRight1: return TPS::mainCharRocketRight2;
    case TPS::mainCharRocketRight2: return TPS::mainCharRocketRight1;
    //Accelate right, gun pointing up-right
    case TPS::mainCharRocketUpRight1: return TPS::mainCharRocketUpRight2;
    case TPS::mainCharRocketUpRight2: return TPS::mainCharRocketUpRight1;
    //Accelate right, gun pointing down-right
    case TPS::mainCharRocketDownRight1: return TPS::mainCharRocketDownRight2;
    case TPS::mainCharRocketDownRight2: return TPS::mainCharRocketDownRight1;
    //Looking down
    case TPS::mainCharRocketDown1: return TPS::mainCharRocketRight1;
    case TPS::mainCharRocketDown2: return TPS::mainCharRocketRight2;
    //Looking up
    case TPS::mainCharRocketUp1: return TPS::mainCharRocketRight1;
    case TPS::mainCharRocketUp2: return TPS::mainCharRocketRight2;
    //Turn right, gun position up-right
    case TPS::mainCharRocketUpLeft1: return TPS::mainCharRocketUpRight1;
    case TPS::mainCharRocketUpLeft2: return TPS::mainCharRocketUpRight2;
    //Turn right, gun position horizontal
    case TPS::mainCharRocketLeft1: return TPS::mainCharRocketRight1;
    case TPS::mainCharRocketLeft2: return TPS::mainCharRocketRight2;
    //Turn right, gun position down-right
    case TPS::mainCharRocketDownLeft1: return TPS::mainCharRocketDownRight1;
    case TPS::mainCharRocketDownLeft2: return TPS::mainCharRocketDownRight2;
  }
  return index;
}
//---------------------------------------------------------------------------
int SpriteIndexChanger::MoveDown(const int& index) const
{
  switch(index)
  {
    //Looking right, gun pointing down-right
    case TPS::mainCharRocketDownRight1: return TPS::mainCharRocketDown1;
    case TPS::mainCharRocketDownRight2: return TPS::mainCharRocketDown2;
    //Looking right, normal gun position
    case TPS::mainCharRocketRight1: return TPS::mainCharRocketDownRight1;
    case TPS::mainCharRocketRight2: return TPS::mainCharRocketDownRight2;
    //Looking right, gun pointing up-right
    case TPS::mainCharRocketUpRight1: return TPS::mainCharRocketRight1;
    case TPS::mainCharRocketUpRight2: return TPS::mainCharRocketRight2;
    //Looking up
    case TPS::mainCharRocketUp1: return TPS::mainCharRocketDown1;
    case TPS::mainCharRocketUp2: return TPS::mainCharRocketDown2;
    //Looking left, gun pointing down-left
    case TPS::mainCharRocketDownLeft1: return TPS::mainCharRocketDown1;
    case TPS::mainCharRocketDownLeft2: return TPS::mainCharRocketDown2;
    //Looking left, normal gun position
    case TPS::mainCharRocketLeft1: return TPS::mainCharRocketDownLeft1;
    case TPS::mainCharRocketLeft2: return TPS::mainCharRocketDownLeft2;
    //Looking left, gun pointing up-left
    case TPS::mainCharRocketUpLeft1: return TPS::mainCharRocketLeft1;
    case TPS::mainCharRocketUpLeft2: return TPS::mainCharRocketLeft2;
  }
  return index;
}
//---------------------------------------------------------------------------
int SpriteIndexChanger::MoveLeft(const int& index) const
{
  switch(index)
  {
    //Accelerate left, normal gun position
    case TPS::mainCharRocketLeft1: return TPS::mainCharRocketLeft2;
    case TPS::mainCharRocketLeft2: return TPS::mainCharRocketLeft1;
    //Accelate left, gun pointing up-left
    case TPS::mainCharRocketUpLeft1: return TPS::mainCharRocketUpLeft2;
    case TPS::mainCharRocketUpLeft2: return TPS::mainCharRocketUpLeft1;
    //Accelate left, gun pointing down-left
    case TPS::mainCharRocketDownLeft1: return TPS::mainCharRocketDownLeft2;
    case TPS::mainCharRocketDownLeft2: return TPS::mainCharRocketDownLeft1;
    //Looking down
    case TPS::mainCharRocketDown1: return TPS::mainCharRocketLeft1;
    case TPS::mainCharRocketDown2: return TPS::mainCharRocketLeft2;
    //Looking up
    case TPS::mainCharRocketUp1: return TPS::mainCharRocketLeft1;
    case TPS::mainCharRocketUp2: return TPS::mainCharRocketLeft2;
    //Turn left, gun position up-right
    case TPS::mainCharRocketUpRight1: return TPS::mainCharRocketUpLeft1;
    case TPS::mainCharRocketUpRight2: return TPS::mainCharRocketUpLeft2;
    //Turn left, gun position horizontal
    case TPS::mainCharRocketRight1: return TPS::mainCharRocketLeft1;
    case TPS::mainCharRocketRight2: return TPS::mainCharRocketLeft2;
    //Turn left, gun position down-right
    case TPS::mainCharRocketDownRight1: return TPS::mainCharRocketDownLeft1;
    case TPS::mainCharRocketDownRight2: return TPS::mainCharRocketDownLeft2;
  }
  return index;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
