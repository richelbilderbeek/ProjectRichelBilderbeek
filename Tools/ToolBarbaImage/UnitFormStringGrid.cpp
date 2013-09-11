//---------------------------------------------------------------------------
/*
  BarbaImage, tool to perform image manipulations
  Copyright (C) 2008  Richèl Bilderbeek

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

#include <cassert>
#include <sstream>
#include <string>
#include "UnitFormStringGrid.h"
#include "UnitFormImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormStringGrid *FormStringGrid;
//---------------------------------------------------------------------------
__fastcall TFormStringGrid::TFormStringGrid(
  TComponent* Owner,
  const TImage * const source,
  TFormImage * const target,
  void(* const anyFunction)(
    const TImage * const,const
    std::vector<std::vector<double> >&,
    TImage * const)
  )
  : TForm(Owner),
    mSource(source),
    mTarget(target),
    mFunction(anyFunction)
{
  assert(mSource!=0 && "Source must not be NULL");
  assert(mTarget!=0 && "Target must not be NULL");
  assert(anyFunction!=0 && "Function pointer must not be NULL");

  StringGrid->Cells[0][0] = -1.0;
  StringGrid->Cells[1][0] =  0.0;
  StringGrid->Cells[2][0] =  1.0;
  StringGrid->Cells[0][1] = -1.0;
  StringGrid->Cells[1][1] =  0.0;
  StringGrid->Cells[2][1] =  1.0;
  StringGrid->Cells[0][2] = -1.0;
  StringGrid->Cells[1][2] =  0.0;
  StringGrid->Cells[2][2] =  1.0;

}
//---------------------------------------------------------------------------
void __fastcall TFormStringGrid::StringGridSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
  if (CanStringGridToVector<double>(StringGrid)==false) return;

  mFunction(mSource,StringGridToVector<double>(StringGrid),mTarget->Image);
  //Redraw the image
  //mTarget->Canvas->Draw(0,0,mTarget->Image->Picture->Graphic);
  mTarget->Canvas->StretchDraw(
    mTarget->Image->ClientRect,
    mTarget->Image->Picture->Graphic);

}
//---------------------------------------------------------------------------
//VCL dependent
//From http://www.richelbilderbeek.nl/CppStringGridToVector.htm
template <class T>
const std::vector<std::vector<T> > StringGridToVector(const TStringGrid * const stringGrid)
{
  assert(CanStringGridToVector<T>(stringGrid)==true);
  assert(stringGrid!=0 && "StringGrid must not be NULL");
  const int height = stringGrid->RowCount;
  const int width  = stringGrid->ColCount;
  std::vector<std::vector<T> > v(height,std::vector<T>(width));
  for (int y=0; y!=height; ++y)
  {
    assert(y >=0);
    assert(y < static_cast<int>(v.size()) );
    std::vector<T>& line = v[y];
    //Don't have the guts to do a line-access on a TStringGrid...

    for (int x=0; x!=width; ++x)
    {
      assert(x >=0);
      assert(x < static_cast<int>(line.size()) );
      //const_cast because the VCL is not const-correct. Grumble, grumble...
      const std::string s = (const_cast<TStringGrid*>(stringGrid)->Cells[x][y]).c_str();
      const T t = LexicalCast<T>(s);
      line[x] = t;
    }
  }
  return v;
}
//---------------------------------------------------------------------------
//VCL dependent
//From http://www.richelbilderbeek.nl/CanStringGridToVector.htm
template <class T>
const bool CanStringGridToVector(const TStringGrid * const stringGrid)
{
  if (stringGrid==0) return false;

  const int height = stringGrid->RowCount;
  const int width  = stringGrid->ColCount;

  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      //const_cast because the VCL is not const-correct. Grumble, grumble...
      const std::string s = (const_cast<TStringGrid*>(stringGrid)->Cells[x][y]).c_str();
      if (CanCast<T>(s) == false) return false;
    }
  }
  return true;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCanCast.htm
template <class TargetType> const bool CanCast(const std::string& from)
{
  std::istringstream i(from);
  TargetType temp;
  return ( (i >> temp) ? true : false );
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
template <>
const int LexicalCast<int>(const std::string& s)
{
  assert(CanCast<int>(s) == true);
  return std::atoi(s.c_str());
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
template <>
const double LexicalCast<double>(const std::string& s)
{
  assert(CanCast<double>(s) == true);
  return std::atof(s.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TFormStringGrid::ItemAddColClick(TObject *Sender)
{
  ++StringGrid->ColCount;
}
//---------------------------------------------------------------------------

void __fastcall TFormStringGrid::ItemAddRowClick(TObject *Sender)
{
  ++StringGrid->RowCount;
}
//---------------------------------------------------------------------------

void __fastcall TFormStringGrid::ItemRemoveColClick(TObject *Sender)
{
  if (StringGrid->ColCount > 1) --StringGrid->ColCount;
}
//---------------------------------------------------------------------------

void __fastcall TFormStringGrid::ItemRemoveRowClick(TObject *Sender)
{
  if (StringGrid->RowCount > 1) --StringGrid->RowCount;
}
//---------------------------------------------------------------------------

