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
#include <vcl.h>
#pragma hdrstop

#include <cmath>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/scoped_ptr.hpp>
#include "UnitPuzzlePiece.h"

#include "UnitFormSolvePuzzle.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSolvePuzzle *FormSolvePuzzle;
//---------------------------------------------------------------------------
__fastcall TFormSolvePuzzle::TFormSolvePuzzle(TComponent* Owner)
  : TForm(Owner), mQuit(false)
{
  //Tests
  assert(IntPower(2,2)== 4);
  assert(IntPower(2,3)== 8);
  assert(IntPower(2,4)==16);
  assert(IntPower(3,2)== 9);
  assert(IntPower(3,3)==27);
  assert(IntPower(3,4)==81);
  //More tests
  PuzzlePiece p0(
    greenBeetleHead,
    greenBeetleTail,
    brownBeetleHead,
    brownBeetleTail);
  PuzzlePiece p1 = p0;
  assert(p0 == p1);
  p1.Rotate();
  assert(p0 != p1);
  PuzzlePiece p2 = p1;
  assert(p1 == p2);
  p2.Rotate();
  assert(p1 != p2);
  PuzzlePiece p3 = p2;
  assert(p2 == p3);
  p3.Rotate();
  assert(p2 != p3);
  PuzzlePiece p4 = p3;
  assert(p3 == p4);
  p4.Rotate();
  assert(p3 != p4);
  assert(p0 == p4);
}
//---------------------------------------------------------------------------
const int IntPower(const int base, const int exponent)
{
  assert(exponent >= 0);
  int result = 1;
  for (int i=0; i!=exponent; ++i)
  {
    result *= base;
  }
  return result;
}
//---------------------------------------------------------------------------
const int Factorial(const int n)
{
  assert(n>=0);
  int result = 1;
  for (int i=1; i<=n; ++i)
  {
    result*=i;
  }
  return result;
}
//---------------------------------------------------------------------------
void __fastcall TFormSolvePuzzle::ButtonQuitClick(TObject *Sender)
{
  mQuit = true;
  Close();
}
//---------------------------------------------------------------------------
void TFormSolvePuzzle::ShowSolution(const std::vector<PuzzlePiece>& v)
{
  const int n = static_cast<int>(v.size());
  for (int i=0; i!=n; ++i)
  {
    const int x = (i % 3) * 3;
    const int y = (i / 3) * 3;
    StringGrid->Cells[x+1][y  ] = ToStr(v[i].mTop).c_str();
    StringGrid->Cells[x+2][y+1] = ToStr(v[i].mRight).c_str();
    StringGrid->Cells[x+1][y+2] = ToStr(v[i].mBottom).c_str();
    StringGrid->Cells[x  ][y+1] = ToStr(v[i].mLeft).c_str();
  }
  for (int i=n; i!=9; ++i)
  {
    const int x = (i % 3) * 3;
    const int y = (i / 3) * 3;
    StringGrid->Cells[x+1][y  ] = "";
    StringGrid->Cells[x+2][y+1] = "";
    StringGrid->Cells[x+1][y+2] = "";
    StringGrid->Cells[x  ][y+1] = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormSolvePuzzle::ButtonSolveClick(TObject *Sender)
{
  const std::vector<PuzzlePiece> piecesOriginal = GetPieces();
  std::vector<PuzzlePiece> pieces1d = piecesOriginal;
  std::sort(pieces1d.begin(),pieces1d.end());

  ProgressBar->Max = IntPower(4,9);
  ProgressBar->Hint = ProgressBar->Max;

  const int maxI = IntPower(4,9);
  for (int i = 1; i!=maxI; ++i)
  {
    const std::vector<PuzzlePiece> solution = SolvePuzzle(std::vector<PuzzlePiece>(),pieces1d);
    if (solution.empty() == false)
    {
      ShowSolution(solution);
      ShowMessage("Solved!");
      return;
    }

    Application->ProcessMessages();
    if (mQuit == true) return;
    ProgressBar->Position = i;

    //Rotate a piece or more pieces
    for (int index = 0; index != 9; ++index)
    {
      pieces1d[index].Rotate();
      if (pieces1d[index].mNrotations != 0) break;
    }
  }

  ShowMessage("Not solved...");
}
//---------------------------------------------------------------------------
const std::vector<PuzzlePiece> TFormSolvePuzzle::SolvePuzzle(
  const std::vector<PuzzlePiece>& piecesUsed,
  const std::vector<PuzzlePiece>& piecesLeft)
{
  if (CheckBoxDisplay->Checked == true)
  {
    ShowSolution(piecesUsed);
    Application->ProcessMessages();
    this->Refresh();
    Sleep(100);
  }
  if (piecesLeft.empty() == true) return piecesUsed;
  assert(piecesUsed.size() + piecesLeft.size() == 9);
  const int nUsed = static_cast<int>(piecesUsed.size());
  const int nLeft = static_cast<int>(piecesLeft.size());
  const int newIndex = nUsed;
  for (int i=0; i!=nLeft; ++i)
  {
    //Check if the newcomer will fit
    if (newIndex > 2
      && DoesFit(piecesUsed[newIndex-3].mBottom,piecesLeft[i].mTop)==false)
    {
      continue;
    }
    if (newIndex % 3 != 0
      && DoesFit(piecesUsed[newIndex-1].mRight,piecesLeft[i].mLeft)==false)
    {
      continue;
    }
    //Newcomer fits!
    std::vector<PuzzlePiece> newPiecesUsed = piecesUsed;
    std::vector<PuzzlePiece> newPiecesLeft = piecesLeft;
    newPiecesUsed.push_back(newPiecesLeft[i]);
    std::swap(newPiecesLeft[i],newPiecesLeft.back());
    newPiecesLeft.pop_back();
    const std::vector<PuzzlePiece> solution = SolvePuzzle(newPiecesUsed,newPiecesLeft);
    if (solution.empty() == false) return solution;
  }
  return std::vector<PuzzlePiece>();
}
//---------------------------------------------------------------------------
void __fastcall TFormSolvePuzzle::ButtonAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

