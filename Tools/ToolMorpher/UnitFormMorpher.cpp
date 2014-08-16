//---------------------------------------------------------------------------
/*
    Morpher, a tool to generate a series of morphed images
    Copyright (C) 2007  Richel Bilderbeek

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
#define NDEBUG
#include <memory>
#include <cassert>
#include <algorithm>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormMorpher.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMorpher *FormMorpher;
//---------------------------------------------------------------------------
__fastcall TFormMorpher::TFormMorpher(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMorpher::ButtonLoad1Click(TObject *Sender)
{
  if (OpenDialog1->Execute() == false) return;
  Image1->Picture->LoadFromFile(OpenDialog1->FileName);
  PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormMorpher::ButtonLoad2Click(TObject *Sender)
{
  if (OpenDialog2->Execute() == false) return;
  Image2->Picture->LoadFromFile(OpenDialog2->FileName);
  PageControl1->ActivePageIndex = 1;
}
//---------------------------------------------------------------------------
void __fastcall TFormMorpher::ButtonMorphClick(TObject *Sender)
{
  const int n = EditNumber->Text.ToIntDef(-1);
  const String fileStart = EditFileStart->Text;
  if (n < 1)    { ShowMessage("Number must be at least 1");   return; }
  if (n > 1000) { ShowMessage("Number must not exceed 1000"); return; }
  const int maxx = std::min(Image1->Picture->Bitmap->Width,Image2->Picture->Bitmap->Width);
  const int maxy = std::min(Image1->Picture->Bitmap->Height,Image2->Picture->Bitmap->Height);
  Image3->Picture->Bitmap->Width  = maxx;
  Image3->Picture->Bitmap->Height = maxy;

  PageControl1->ActivePageIndex = 2;
  PageControl1->Refresh();

  for (int i=0; i!=n; ++i)
  {
    const double fraction = static_cast<double>(i) / static_cast<double>(n+1);
    for (int y=0; y!=maxy; ++y)
    {
      const unsigned char * const line1
        = static_cast<unsigned char *>(Image1->Picture->Bitmap->ScanLine[y]);
      const unsigned char * const line2
        = static_cast<unsigned char *>(Image2->Picture->Bitmap->ScanLine[y]);
      unsigned char * const line3
        = static_cast<unsigned char *>(Image3->Picture->Bitmap->ScanLine[y]);
      for (int x=0; x!=maxx; ++x)
      {
        const short r1 = line1[x*3+2];
        const short g1 = line1[x*3+1];
        const short b1 = line1[x*3+0];
        const short r2 = line2[x*3+2];
        const short g2 = line2[x*3+1];
        const short b2 = line2[x*3+0];
        const short dr = r2 - r1; //Delta red
        const short dg = g2 - g1; //Delta green
        const short db = b2 - b1; //Delta blue
        const short r3 = r1 + static_cast<short>(fraction * static_cast<double>(dr));
        const short g3 = g1 + static_cast<short>(fraction * static_cast<double>(dg));
        const short b3 = b1 + static_cast<short>(fraction * static_cast<double>(db));
        assert( r3 >= 0);
        assert( r3 <= 255);
        assert( g3 >= 0);
        assert( g3 <= 255);
        assert( b3 >= 0);
        assert( b3 <= 255);
        line3[x*3+2] = r3;
        line3[x*3+1] = g3;
        line3[x*3+0] = b3;
      }
    }
    Image3->Refresh();
    const String fileName = fileStart + IntToStr(i) + ".bmp";
    Image3->Picture->SaveToFile(fileName);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMorpher::ButtonAboutClick(TObject *Sender)
{
  std::auto_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
