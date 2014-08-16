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
#ifndef UnitPuzzlePieceH
#define UnitPuzzlePieceH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
enum EnumPicture
{
  greenBeetleHead,
  greenBeetleTail,
  brownBeetleHead,
  brownBeetleTail,
  wormShort,
  wormLong,
  hairyWormHead,
  hairyWormTail
};
//---------------------------------------------------------------------------
const std::string ToStr(const EnumPicture p);
//---------------------------------------------------------------------------
struct PuzzlePiece
{
  PuzzlePiece(
    const EnumPicture top,
    const EnumPicture right,
    const EnumPicture bottom,
    const EnumPicture left);
  EnumPicture mLeft;
  EnumPicture mRight;
  EnumPicture mTop;
  EnumPicture mBottom;
  void Rotate();
  int mNrotations;
  private:
  int mValue;
  friend const bool operator<(const PuzzlePiece& p1, const PuzzlePiece& p2);
  friend const bool operator!=(const PuzzlePiece& p1, const PuzzlePiece& p2);
  friend const bool operator==(const PuzzlePiece& p1, const PuzzlePiece& p2);

};
//---------------------------------------------------------------------------
const bool operator<(const PuzzlePiece& p1, const PuzzlePiece& p2);
const bool operator!=(const PuzzlePiece& p1, const PuzzlePiece& p2);
const bool operator==(const PuzzlePiece& p1, const PuzzlePiece& p2);
//---------------------------------------------------------------------------
const bool DoesFit(const EnumPicture a, const EnumPicture b);
//---------------------------------------------------------------------------
// Y-X ordered vector
const bool DoesFit(const std::vector<std::vector<PuzzlePiece> >& v);
const bool DoesFit(const std::vector<PuzzlePiece>& v);
//---------------------------------------------------------------------------
const std::vector<PuzzlePiece> GetPieces();
//---------------------------------------------------------------------------
const int ConvertToInt(const PuzzlePiece& p);
//---------------------------------------------------------------------------

#endif
