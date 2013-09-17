//---------------------------------------------------------------------------

#ifndef UnitCoordinatGetterH
#define UnitCoordinatGetterH
//---------------------------------------------------------------------------
#include "UnitEnumChessPieceColor.h"
//---------------------------------------------------------------------------
struct CoordinatGetter
{
  CoordinatGetter(const EnumChessPieceColor color)
    : mColor(color) {}
  const int GetX(const int x) const;
  const int GetY(const int y) const;
  const EnumChessPieceColor mColor;
};

#endif
 