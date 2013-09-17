//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitCoordinatGetter.h"
//---------------------------------------------------------------------------
const int CoordinatGetter::GetX(const int x) const
{
  if (mColor == white)
  {
    return x;
  }
  else
  {
    return 7 - x;
  }
}
//---------------------------------------------------------------------------
const int CoordinatGetter::GetY(const int y) const
{
  if (mColor == white)
  {
    return 7 - y;
  }
  else
  {
    return y;
  }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
