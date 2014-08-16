//---------------------------------------------------------------------------
/*
  AsciiArter, tool to convert images to ASCII art
  Copyright (C) 2006  Richel Bilderbeek

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
#include <cassert>
#include <algorithm>
#include <boost/scoped_ptr.hpp>
#include <vcl.h>
#pragma hdrstop

#pragma warn -8041
  #include <boost/lexical_cast.hpp>
#pragma warn +8041


#include "UnitFormAsciiArter.h"
#include "UnitFormAsciiArterAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAsciiArter *FormAsciiArter;
//---------------------------------------------------------------------------
__fastcall TFormAsciiArter::TFormAsciiArter(TComponent* Owner)
        : TForm(Owner), mImageLoaded(false)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormAsciiArter::ButtonLoadClick(TObject *Sender)
{
  if (!OpenDialog1->Execute()) return;
  ImageOriginal->Picture->LoadFromFile(OpenDialog1->FileName);

  if (ImageOriginal->Picture->Bitmap->PixelFormat != pf24bit)
  {
    ShowMessage("You've selected a non-24-bit bitmap. Please select a 24-bit bitmap.");
    return;
  }

  ImageOriginal->Visible = true;
  mImageLoaded = true;
  if (this->CanConvert() == true) Convert();
  ++PageControlMain->ActivePageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFormAsciiArter::EditWidthChange(TObject *Sender)
{
  if (this->CanConvert() == true) Convert();
}
//---------------------------------------------------------------------------
const bool TFormAsciiArter::CanConvert() const
{
  return (mImageLoaded == true
    && IsInt( std::string(EditWidth->Text.c_str() ) ) == true
    && boost::lexical_cast<double>( std::string(EditWidth->Text.c_str() ) ) >= 5
  );
}
//---------------------------------------------------------------------------
void TFormAsciiArter::Convert()
{
  assert(this->CanConvert() == true);
  const int width = boost::lexical_cast<int>(std::string(EditWidth->Text.c_str() ) );
  const std::vector<std::string> ascii = ImageToAscii(ImageOriginal,width);

  RichEditAscii->Clear();

  const int nLines = ascii.size();
  for (int i=0; i!=nLines; ++i)
  {
    RichEditAscii->Lines->Add( ascii[i].c_str() );
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormAsciiArter::ButtonAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormAsciiArterAbout> form(new TFormAsciiArterAbout(0));
  form->ShowModal();
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetAsciiArtGradient.htm
const std::vector<char> GetAsciiArtGradient()
{
  std::vector<char> chars;
  chars.push_back('M');
  chars.push_back('N');
  chars.push_back('m');
  chars.push_back('d');
  chars.push_back('h');
  chars.push_back('y');
  chars.push_back('s');
  chars.push_back('o');
  chars.push_back('+');
  chars.push_back('/');
  chars.push_back(':');
  chars.push_back('-');
  chars.push_back('.');
  chars.push_back('`');
  chars.push_back(' ');
  return chars;
}
//---------------------------------------------------------------------------
//Get a pixel's greyness
//From http://www.richelbilderbeek.nl/CppGetGreyness.htm
const unsigned char GetGreyness(
  const TImage * const image,
  const int x,
  const int y)
{
  assert(image!=0 && "Image is NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert( x >= 0 && "x coordinat is below zero");
  assert( y >= 0 && "y coordinat is below zero");
  assert( x < image->Picture->Bitmap->Width  && "x coordinat is beyond image width");
  assert( y < image->Picture->Bitmap->Height && "y coordinat is beyond image height");

  const unsigned char * const line
    = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);

  const unsigned char red   = line[x*3+2];
  const unsigned char green = line[x*3+1];
  const unsigned char blue  = line[x*3+0];
  const int grey = (red + green + blue) / 3;
  assert(grey >= 0 && grey < 256);
  return grey;
}
//---------------------------------------------------------------------------
//Get a line of pixel's average greyness
//From http://www.richelbilderbeek.nl/CppGetGreyness.htm
const unsigned char GetGreyness(
  const TImage * const image,
  const int x1,
  const int x2,
  const int y)
{
  assert(image!=0 && "Image is NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert( x1 >= 0 && "x1 coordinat is below zero");
  assert( x2 >= 0 && "x2 coordinat is below zero");
  assert( y >= 0 && "y coordinat is below zero");
  assert( x1 < image->Picture->Bitmap->Width  && "x1 coordinat is beyond image width");
  assert( x2 < image->Picture->Bitmap->Width  && "x2 coordinat is beyond image width");
  assert( y < image->Picture->Bitmap->Height && "y coordinat is beyond image height");
  assert( x1 < x2);

  const unsigned char * const line
    = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);

  const int nPixels = x2 - x1;
  int sum = 0;

  for (int x=x1; x!=x2; ++x)
  {
    const unsigned char red   = line[x*3+2];
    const unsigned char green = line[x*3+1];
    const unsigned char blue  = line[x*3+0];
    const int grey = (red + green + blue) / 3;
    assert(grey >= 0 && grey < 256);
    sum+=grey;
  }
  const int averageGrey = sum / nPixels;
  assert(averageGrey >= 0 && averageGrey < 256);
  return averageGrey;
}
//---------------------------------------------------------------------------
//Get a square of pixels' average greyness
//From http://www.richelbilderbeek.nl/CppGetGreyness.htm
const unsigned char GetGreyness(
  const TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2)
{
  assert(x1 < x2 );
  assert(y1 < y2 );
  const int nPixelsVertical = y2 - y1;
  int sum = 0;

  for (int y=y1; y!=y2; ++y)
  {
    const int grey = GetGreyness(image,x1,x2,y);
    assert(grey >= 0 && grey < 256);
    sum+=grey;
  }
  const int grey = sum / nPixelsVertical;
  assert(grey >=0 && grey < 256);
  return grey;
}
//---------------------------------------------------------------------------
//Generalizes a pixel, line or rectangle to one average greyness
//From http://www.richelbilderbeek.nl/CppImageToAscii.htm
const double GetFractionGrey(
  const TImage* const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2)
{
  if (x1 == x2 && y1 == y2) return ( static_cast<double>(GetGreyness(image, x1,y1)) / 255.0);
  if (y1 == y2) return ( static_cast<double>(GetGreyness(image, x1,x2,y1)) / 255.0);
  if (x1 == x2)
  {
    int sum = 0;
    for (int y=y1; y!=y2; ++y)
    {
      sum+=static_cast<int>(GetGreyness(image,x1,y));
    }
    return ( static_cast<double>(sum) / 255.0);
  }
  return ( static_cast<double>(GetGreyness(image,x1,y1,x2,y2)) / 255.0);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppImageToAscii.htm
const std::vector<std::string> ImageToAscii(
  const TImage* const image,
  const int charWidth) //How many chars the ASCII image will be wide
{
  static const std::vector<char> chars(GetAsciiArtGradient());

  //If the number of chars is below 5,
  //the calculation would be more complicated due to a too trivial value of charWidth
  assert(charWidth >= 5);

  //Check the bitmap
  assert(image!=0 && "Image must not be NULL");
  assert(image->Picture->Bitmap != 0 && "Image bitmap must not be NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Image format must be 24-bit");


  //Maxy is in proportion with the bitmap
  const int maxy =
    (static_cast<double>(charWidth)
    / static_cast<double>(image->Picture->Bitmap->Width))
    * static_cast<double>(image->Picture->Bitmap->Height);
  assert(charWidth > 0);
  assert(maxy > 0);
  const double dX = static_cast<double>(image->Picture->Bitmap->Width)
    / static_cast<double>(charWidth);
  const double dY = static_cast<double>(image->Picture->Bitmap->Height)
    / static_cast<double>(maxy);
  assert(dX > 0.0);
  assert(dY > 0.0);

  std::vector<std::string> v;

  for (int y=0; y!=maxy; ++y)
  {
    std::string myLine;
    for (int x=0; x!=charWidth; ++x)
    {
      const int x1 = std::min(
        static_cast<double>(x) * dX,
        image->Picture->Bitmap->Width  - 1.0) + 0.5;
      const int y1 = std::min(
        static_cast<double>(y) * dY,
        image->Picture->Bitmap->Height - 1.0) + 0.5;
      const int x2 = std::min(
        (static_cast<double>(x) * dX) + dX,
        image->Picture->Bitmap->Width  - 1.0) + 0.5;
      const int y2 = std::min(
        (static_cast<double>(y) * dY) + dY,
        image->Picture->Bitmap->Height - 1.0) + 0.5;
      assert(x1 >= 0);
      assert(x2 >= 0);
      assert(y1 >= 0);
      assert(y2 >= 0);
      assert(x1 < image->Picture->Bitmap->Width);
      assert(x2 < image->Picture->Bitmap->Width);
      assert(y1 < image->Picture->Bitmap->Height);
      assert(y2 < image->Picture->Bitmap->Height);

      const double fGrey = std::min(
        std::max(0.0, GetFractionGrey(image,x1,y1,x2,y2)),1.0);
      assert(fGrey >= 0.0 && fGrey <= 1.0);
      const double charIndex
        = fGrey * static_cast<double>(chars.size() - 1);
      assert(charIndex >= 0);
      assert(charIndex < static_cast<int>(chars.size()));
      const char thisChar = chars[charIndex];
      myLine+=thisChar;
    }
    v.push_back(myLine);
  }
  return v;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppIsInt.htm
const bool IsInt(const std::string& s)
{
  std::istringstream i(s);
  int temp;
  return ( (i >> temp) ? true : false );
}
//---------------------------------------------------------------------------
