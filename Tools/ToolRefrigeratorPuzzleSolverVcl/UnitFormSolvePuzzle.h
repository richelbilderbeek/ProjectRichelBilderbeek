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
#ifndef UnitFormSolvePuzzleH
#define UnitFormSolvePuzzleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include "UnitPuzzlePiece.h"
//---------------------------------------------------------------------------
class TFormSolvePuzzle : public TForm
{
__published:	// IDE-managed Components
        TProgressBar *ProgressBar;
  TButton *ButtonQuit;
  TStringGrid *StringGrid;
  TCheckBox *CheckBoxDisplay;
        TButton *ButtonSolve;
        TButton *ButtonAbout;
  void __fastcall ButtonQuitClick(TObject *Sender);
  void __fastcall ButtonSolveClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
  bool mQuit;
  void ShowSolution(const std::vector<PuzzlePiece>& v);
  const std::vector<PuzzlePiece> SolvePuzzle(
    const std::vector<PuzzlePiece>& piecesUsed,
    const std::vector<PuzzlePiece>& piecesLeft);
public:		// User declarations
  __fastcall TFormSolvePuzzle(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSolvePuzzle *FormSolvePuzzle;
//---------------------------------------------------------------------------
const int IntPower(const int base, const int exponent);
const int Factorial(const int n);
//---------------------------------------------------------------------------
#endif
