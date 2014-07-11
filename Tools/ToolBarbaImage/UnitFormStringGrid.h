//---------------------------------------------------------------------------
/*
  BarbaImage, tool to perform image manipulations
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
#ifndef UnitFormStringGridH
#define UnitFormStringGridH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include <iosfwd>
#include <vector>
struct TFormImage;
//---------------------------------------------------------------------------
class TFormStringGrid : public TForm
{
__published:	// IDE-managed Components
  TStringGrid *StringGrid;
  TPopupMenu *PopupMenuFilter;
  TMenuItem *ItemAddCol;
  TMenuItem *ItemAddRow;
  TMenuItem *N1;
  TMenuItem *ItemRemoveCol;
  TMenuItem *ItemRemoveRow;
  void __fastcall StringGridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
  void __fastcall ItemAddColClick(TObject *Sender);
  void __fastcall ItemAddRowClick(TObject *Sender);
  void __fastcall ItemRemoveColClick(TObject *Sender);
  void __fastcall ItemRemoveRowClick(TObject *Sender);
private:	// User declarations
  const TImage * const mSource;
  TFormImage * const mTarget;
  void(* const mFunction)(
    const TImage * const,                     //Input image
    const std::vector<std::vector<double> >&, //2D vector
    TImage * const);                          //Output image

public:		// User declarations
  __fastcall TFormStringGrid(TComponent* Owner,
    const TImage * const source,
    TFormImage * const target,
      void(* const anyFunction)(
        const TImage * const,const
        std::vector<std::vector<double> >&,
        TImage * const)
      );


};
//---------------------------------------------------------------------------
extern PACKAGE TFormStringGrid *FormStringGrid;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CanStringGridToVector.htm
export template <class T>
const bool CanStringGridToVector(const TStringGrid * const stringGrid);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppStringGridToVector.htm
export template <class T>
const std::vector<std::vector<T> > StringGridToVector(const TStringGrid * const stringGrid);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCanCast.htm
export template <class TargetType> const bool CanCast(const std::string& from);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
template <typename TargetType>
const TargetType LexicalCast(const std::string& s);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
export template <>
const double LexicalCast<double>(const std::string& s);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
export template <>
const int LexicalCast<int>(const std::string& s);
//---------------------------------------------------------------------------
#endif
