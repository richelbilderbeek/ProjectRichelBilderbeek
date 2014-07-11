//---------------------------------------------------------------------------
/*
  The Refrigerator Puzzle Solver, program to solve a refrigerator puzzle
  Copyright (C) 2008  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <cassert>
#include <stdexcept>
#include <string>
#include "UnitPuzzlePiece.h"

//---------------------------------------------------------------------------
const std::string ToStr(const EnumPicture p)
{
  switch (p)
  {
    case greenBeetleHead: return "GH";
    case greenBeetleTail: return "GT";
    case brownBeetleHead: return "BH";
    case brownBeetleTail: return "BT";
    case wormShort:       return "WS";
    case wormLong:        return "WL";
    case hairyWormHead:   return "HH";
    case hairyWormTail:   return "HT";
  }
  assert(!"Should not get here");
  throw std::logic_error("Unkown picture in function ToStr");
}
//---------------------------------------------------------------------------
PuzzlePiece::PuzzlePiece(
  const EnumPicture top,
  const EnumPicture right,
  const EnumPicture bottom,
  const EnumPicture left)
: mTop(top),
  mRight(right),
  mBottom(bottom),
  mLeft(left),
  mValue(ConvertToInt(*this)),
  mNrotations(0)

{

}
//---------------------------------------------------------------------------
void PuzzlePiece::Rotate()
{
  const EnumPicture oldTop = mTop;
  mTop = mRight;
  mRight = mBottom;
  mBottom = mLeft;
  mLeft = oldTop;
  mValue = ConvertToInt(*this);
  mNrotations = (mNrotations + 1) % 4; 
}
//---------------------------------------------------------------------------
const bool DoesFit(const EnumPicture a, const EnumPicture b)
{
  switch (a)
  {
    case greenBeetleHead: return (b == greenBeetleTail);
    case greenBeetleTail: return (b == greenBeetleHead);
    case brownBeetleHead: return (b == brownBeetleTail);
    case brownBeetleTail: return (b == brownBeetleHead);
    case wormShort: return (b == wormLong);
    case wormLong: return (b == wormShort);
    case hairyWormHead: return (b == hairyWormTail);
    case hairyWormTail: return (b == hairyWormHead);
  }
  assert(!"Should not get here");
  throw std::logic_error("Unkown picture in function DoesFit");
}
//---------------------------------------------------------------------------
// Y-X ordered vector
const bool DoesFit(const std::vector<std::vector<PuzzlePiece> >& v)
{
  assert(v.size() == 3);
  assert(v[0].size() == 3);
  return (
       DoesFit(v[0][0].mBottom,v[1][0].mTop)
    && DoesFit(v[1][0].mBottom,v[2][0].mTop)
    && DoesFit(v[0][1].mBottom,v[1][1].mTop)
    && DoesFit(v[1][1].mBottom,v[2][1].mTop)
    && DoesFit(v[0][2].mBottom,v[1][2].mTop)
    && DoesFit(v[1][2].mBottom,v[2][2].mTop)
    && DoesFit(v[0][0].mRight ,v[0][1].mLeft)
    && DoesFit(v[0][1].mRight ,v[0][2].mLeft)
    && DoesFit(v[1][0].mRight ,v[1][1].mLeft)
    && DoesFit(v[1][1].mRight ,v[1][2].mLeft)
    && DoesFit(v[2][0].mRight ,v[2][1].mLeft)
    && DoesFit(v[2][1].mRight ,v[2][2].mLeft)
  );
}
//---------------------------------------------------------------------------
const bool DoesFit(const std::vector<PuzzlePiece>& v)
{
  assert(v.size() == 9);
  return (
       DoesFit(v[0].mBottom,v[3].mTop)
    && DoesFit(v[1].mBottom,v[4].mTop)
    && DoesFit(v[2].mBottom,v[5].mTop)
    && DoesFit(v[3].mBottom,v[6].mTop)
    && DoesFit(v[4].mBottom,v[7].mTop)
    && DoesFit(v[5].mBottom,v[8].mTop)
    && DoesFit(v[0].mRight ,v[1].mLeft)
    && DoesFit(v[1].mRight ,v[2].mLeft)
    && DoesFit(v[3].mRight ,v[4].mLeft)
    && DoesFit(v[4].mRight ,v[5].mLeft)
    && DoesFit(v[6].mRight ,v[7].mLeft)
    && DoesFit(v[7].mRight ,v[8].mLeft)
  );
}
//---------------------------------------------------------------------------
const std::vector<PuzzlePiece> GetPieces()
{
  std::vector<PuzzlePiece> v;
  v.push_back(PuzzlePiece(hairyWormTail,wormLong,greenBeetleTail,hairyWormTail));
  v.push_back(PuzzlePiece(hairyWormHead,greenBeetleTail,wormLong,wormLong));
  v.push_back(PuzzlePiece(greenBeetleTail,wormLong,hairyWormHead,greenBeetleHead));
  v.push_back(PuzzlePiece(greenBeetleHead,brownBeetleHead,greenBeetleTail,hairyWormHead));
  v.push_back(PuzzlePiece(greenBeetleTail,brownBeetleTail,wormShort,brownBeetleTail));
  v.push_back(PuzzlePiece(brownBeetleTail,brownBeetleHead,hairyWormTail,wormLong));
  v.push_back(PuzzlePiece(greenBeetleHead,hairyWormTail,wormShort,brownBeetleTail));
  v.push_back(PuzzlePiece(brownBeetleHead,wormShort,wormShort,greenBeetleHead));
  v.push_back(PuzzlePiece(wormShort,greenBeetleHead,brownBeetleHead,greenBeetleHead));
  assert(v.size() == 9);
  return v;
}
//---------------------------------------------------------------------------
const int ConvertToInt(const PuzzlePiece& p)
{
  return (
      ( 1 * static_cast<int>(p.mTop))
    + ( 4 * static_cast<int>(p.mRight))
    + (16 * static_cast<int>(p.mBottom))
    + (64 * static_cast<int>(p.mLeft))
  );

}
//---------------------------------------------------------------------------
const bool operator==(const PuzzlePiece& p1, const PuzzlePiece& p2)
{
  return (p1.mValue == p2.mValue);
}
//---------------------------------------------------------------------------
const bool operator!=(const PuzzlePiece& p1, const PuzzlePiece& p2)
{
  return !(p1.mValue == p2.mValue);
}
//---------------------------------------------------------------------------
const bool operator<(const PuzzlePiece& p1, const PuzzlePiece& p2)
{
  assert(p1.mValue != p2.mValue);
  return (p1.mValue < p2.mValue);
  //return (ConvertToInt(p1) < ConvertToInt(p2));
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
