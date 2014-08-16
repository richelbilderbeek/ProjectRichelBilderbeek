//---------------------------------------------------------------------------
/*
  DotMatrix, tool to demonstrate dot-matrix text drawing
  Copyright (C) 2009  Richel Bilderbeek

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

#include <boost/shared_ptr.hpp>
#include "UnitFormDotMatrix.h"
#include "UnitDotMatrix.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDotMatrix *FormDotMatrix;
//---------------------------------------------------------------------------
__fastcall TFormDotMatrix::TFormDotMatrix(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFormDotMatrix::RichEditChange(TObject *Sender)
{
  //Paint Image to white
  SetPixel(Image,
    0,0,Image->Picture->Graphic->Width,Image->Picture->Graphic->Height,
    255,255,255);
  
  const std::vector<std::string> v = StringsToVector(RichEdit->Lines);
  const int max_length = FindLongestStringLength(v);
  Image->Picture->Graphic->Width  = 6 * max_length;
  Image->Picture->Graphic->Height = 8 * v.size();

  DotMatrix(Image,0,0,v);
  Image->Refresh();

}
//---------------------------------------------------------------------------
void __fastcall TFormDotMatrix::ButtonSaveClick(TObject *Sender)
{
  if (!SaveDialog->Execute()) return;
  Image->Picture->SaveToFile(SaveDialog->FileName);
}
//---------------------------------------------------------------------------
const std::vector<std::string> StringsToVector(const TStrings * const strings)
{
  //const_cast because the VCL is not const-correct. Grumble, grumble...
  TStrings* const s = const_cast<TStrings*>(strings);

  const int sz = s->Count;
  std::vector<std::string> v(sz);

  for (int i=0; i!=sz; ++i)
  {
    v[i]=s->operator[](i).c_str();
  }
  return v;
}
//---------------------------------------------------------------------------
const int FindLongestStringLength(const std::vector<std::string>& v)
{
  if (v.empty()) return 0;
  int length = v[0].size();

  const int sz = v.size();
  for (int i=1; i!=sz; ++i) //1 as 0 has already been read
  {
    const int this_length = v[i].size();
    if (this_length > length) length = this_length;
  }
  return length;
}
//---------------------------------------------------------------------------

void __fastcall TFormDotMatrix::Button1Click(TObject *Sender)
{
  boost::shared_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

