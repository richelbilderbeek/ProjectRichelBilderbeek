//---------------------------------------------------------------------------
/*
  Secret Message, tool to add secret messages to images
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
#pragma hdrstop

#include <cassert>
#include <algorithm>
#include "UnitFunctions.h"

//---------------------------------------------------------------------------
//Makes all red pixels even, except when there's a message pixel
//From http://www.richelbilderbeek.nl/CppAddMessageRed.htm
void AddMessageRed(
  const TImage * const original,
  const TImage * const message,
  TImage * const result)
{
  assert(original!=0 && "Image is NULL");
  assert(message!=0 && "Image is NULL");
  assert(result!=0 && "Image is NULL");
  assert(original->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(message->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(result->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(original->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert(message->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert(result->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");

  //Get sizes and set size
  const int widthOriginal = original->Picture->Bitmap->Width;
  const int widthMessage  = message->Picture->Bitmap->Width;
  const int width = std::min(widthOriginal, widthMessage);
  result->Picture->Bitmap->Width = width;
  const int heightOriginal = original->Picture->Bitmap->Height;
  const int heightMessage  = message->Picture->Bitmap->Height;
  const int height = std::min(heightOriginal, heightMessage);
  result->Picture->Bitmap->Height = height;

  //Get the pixel offsets
  const int dx1 = (widthOriginal  - width ) / 2;
  const int dx2 = (widthMessage   - width ) / 2;
  const int dy1 = (heightOriginal - height) / 2;
  const int dy2 = (heightMessage  - height) / 2;
  assert(dx1 >= 0);
  assert(dx2 >= 0);
  assert(dy1 >= 0);
  assert(dy2 >= 0);

  for (int y=0; y!=height; ++y)
  {
    for(int x=0; x!=width; ++x)
    {
      const int x1 = dx1 + x;
      const int x2 = dx2 + x;
      const int x3 = x;
      assert(x1 >= 0);
      assert(x2 >= 0);
      assert(x3 >= 0);
      assert(x1 < original->Picture->Width);
      assert(x2 < message->Picture->Width );
      assert(x3 < result->Picture->Width  );
      const int y1 = dy1 + y;
      const int y2 = dy2 + y;
      const int y3 = y;
      assert(y1 >= 0);
      assert(y2 >= 0);
      assert(y3 >= 0);
      assert(y1 < original->Picture->Height);
      assert(y2 < message->Picture->Height);
      assert(y3 < result->Picture->Height);
      unsigned char r = 0;
      unsigned char g = 0;
      unsigned char b = 0;
      //Get original's pixel
      GetPixel(original,x1,y1,r,g,b);
      //Make colors even by increment, watch out for 256
      if (r%2 != 0)
      {
        if (r == 255) {--r;}
        else { ++r; }
      }
      assert(r%2 == 0);
      assert(r <= 254);
      //Add message
      const bool isWhite = IsWhite(message,x2,y2);
      if (isWhite == true) ++r;
      //Write to result image
      SetPixel(result,x3,y3,r,g,b);
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppExtractMessageRed.htm
void ExtractMessageRed(
  const TImage * const original,
  TImage * const result)
{
  assert(original!=0 && "Image is NULL");
  assert(result!=0 && "Image is NULL");
  assert(original->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(result->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(original->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert(result->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");

  //Get sizes and set size
  const int width = original->Picture->Bitmap->Width;
  result->Picture->Bitmap->Width = width;
  const int height = original->Picture->Bitmap->Height;
  result->Picture->Bitmap->Height = height;

  for (int y=0; y!=height; ++y)
  {
    for(int x=0; x!=width; ++x)
    {
      unsigned char r = 0;
      unsigned char g = 0;
      unsigned char b = 0;
      //Get original's pixel
      GetPixel(original,x,y,r,g,b);
      //Make colors even by increment, watch out for 256
      if (r%2 == 0)
      {
        //No message pixel
        SetPixel(result,x,y,0,0,0);
      }
      else
      {
        //Message pixel
        SetPixel(result,x,y,255,255,255);
      }
    }
  }

}
//---------------------------------------------------------------------------
//Get a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
void GetPixel(
  const TImage * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue)
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

  red   = line[x*3+2];
  green = line[x*3+1];
  blue  = line[x*3+0];
}
//---------------------------------------------------------------------------
//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppSetPixel.htm
void SetPixel(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  assert(image!=0 && "Image is NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert( x >= 0 && "x coordinat is below zero");
  assert( y >= 0 && "y coordinat is below zero");
  assert( x < image->Picture->Bitmap->Width  && "x coordinat is beyond image width");
  assert( y < image->Picture->Bitmap->Height && "y coordinat is beyond image height");

  unsigned char * const line
    = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);

  line[x*3+2] = red;
  line[x*3+1] = green;
  line[x*3+0] = blue;
}
//---------------------------------------------------------------------------
const bool IsWhite(const TImage * const image, const int x, const int y)
{
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
  GetPixel(image,x,y,r,g,b);
  const int sum = static_cast<int>(r)
    + static_cast<int>(g)
    + static_cast<int>(b);
  return (sum / 3 > 127);

}
//---------------------------------------------------------------------------

#pragma package(smart_init)
