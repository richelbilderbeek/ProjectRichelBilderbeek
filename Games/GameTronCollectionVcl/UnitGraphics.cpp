//---------------------------------------------------------------------------
/*
  The Tron Collection, three simple tron games
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
#include <algorithm>
#include <cassert>
#include <cmath>
#include <ExtCtrls.hpp>
#pragma hdrstop

#include "UnitGraphics.h"
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
void Rainbow(
  const double x,
  unsigned char& r,
  unsigned char& g,
  unsigned char& b)
{
  const int r0 = GetRed(x);
  const int g0 = GetGreen(x);
  const int b0 = GetBlue(x);
  const int max = std::max(r0, std::max(g0,b0));
  assert(max!=0);

  r = 255.0 * static_cast<double>(r0) / static_cast<double>(max);
  g = 255.0 * static_cast<double>(g0) / static_cast<double>(max);
  b = 255.0 * static_cast<double>(b0) / static_cast<double>(max);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
const unsigned char GetRed(const double x)
{
  assert( x >= 0.0 && x < 1.0);
  const double f = std::max(0.0,
    (x < 0.5
    ?  std::cos(x * 1.5 * M_PI)
    : -std::sin(x * 1.5 * M_PI)
    ) );
  assert( f >= 0.0);
  assert( f <= 1.0);
  const double y = 255.0 * f;
  assert( static_cast<int>(y) < 256 );
  return static_cast<unsigned char>(y);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
const unsigned char GetGreen(const double x)
{
  assert( x >= 0.0 && x < 1.0);

  const double f = std::max(0.0, std::sin( x * 1.5 * M_PI ) );
  assert( f >= 0.0);
  assert( f <= 1.0);
  const double y = 255.0 * f;
  assert( static_cast<int>(y) < 256 );
  return static_cast<unsigned char>(y);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
const unsigned char GetBlue(const double x)
{
  assert( x >= 0.0 && x < 1.0);

  const double f = std::max(0.0, -std::cos( x * 1.5 * M_PI ) );

  assert( f >= 0.0);
  assert( f <= 1.0);
  const double y = 255.0 * f;
  assert( static_cast<int>(y) < 256 );
  return static_cast<unsigned char>(y);
}
//---------------------------------------------------------------------------
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
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
const TColor GetPixelVcl(
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

  return static_cast<TColor>(RGB(
    line[x*3+2], //Red
    line[x*3+1], //Green
    line[x*3+0]  //Blue
    ));
}
//---------------------------------------------------------------------------
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
void SetPixel(
  TImage * const image,
  const int x,
  const int y,
  const TColor color)
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

  line[x*3+2] = GetRValue(color);
  line[x*3+1] = GetGValue(color);
  line[x*3+0] = GetBValue(color);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  )
{
  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      myLine[x*3+2] = red  ; //Red
      myLine[x*3+1] = green; //Green
      myLine[x*3+0] = blue ; //Blue
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl
void PaintVcl(TImage * const image, const TColor color)
{
  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  const unsigned char red   = GetRValue(color);
  const unsigned char green = GetGValue(color);
  const unsigned char blue  = GetBValue(color);

  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      myLine[x*3+2] = red  ; //Red
      myLine[x*3+1] = green; //Green
      myLine[x*3+0] = blue ; //Blue
    }
  }
}
//---------------------------------------------------------------------------

//From http://www.richelbilderbeek.nl
void RemoveColor(TImage * const image, const TColor color)
{
  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  const unsigned char red   = GetRValue(color);
  const unsigned char green = GetGValue(color);
  const unsigned char blue  = GetBValue(color);

  const unsigned char redBlack   = GetRValue(clBlack);
  const unsigned char greenBlack = GetGValue(clBlack);
  const unsigned char blueBlack  = GetBValue(clBlack);
  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      if ( myLine[x*3+2] == red    //Red
        && myLine[x*3+1] == green  //Green
        && myLine[x*3+0] == blue ) //Blue
      {
        myLine[x*3+2] = redBlack   ; //Red
        myLine[x*3+1] = greenBlack ; //Green
        myLine[x*3+0] = blueBlack  ; //Blue
      }
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl
void RemoveColor(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  )
{
  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      if ( myLine[x*3+2] == red    //Red
        && myLine[x*3+1] == green  //Green
        && myLine[x*3+0] == blue ) //Blue
      {
        myLine[x*3+2] = 0 ; //Red
        myLine[x*3+1] = 0 ; //Green
        myLine[x*3+0] = 0 ; //Blue
      }
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl
const TColor RgbToColor(
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  )
{
  return static_cast<TColor>(RGB(red,green,blue));
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl
void ColorToRgb(
  const TColor color,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue  )
{
  red   = GetRValue(color);
  green = GetGValue(color);
  blue  = GetBValue(color);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
void DrawGlobe(
  TImage * const image,
  const unsigned char rMax,
  const unsigned char gMax,
  const unsigned char bMax)
{
  assert(image!=0);
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  const double midX = static_cast<double>(width ) / 2.0;
  const double midY = static_cast<double>(height) / 2.0;
  const double maxDist = std::min(midX,midY);
  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    const double yD = static_cast<double>(y);
    for (int x=0; x!=width; ++x)
    {
      const double xD = static_cast<double>(x);
      const double dist = std::sqrt( ((xD - midX) * (xD - midX)) + ((yD - midY) * (yD - midY)) );
      if (dist <= maxDist)
      {
        const double relDist = dist / maxDist;
        const int r = relDist * static_cast<double>(rMax);
        const int g = relDist * static_cast<double>(gMax);
        const int b = relDist * static_cast<double>(bMax);
        assert( r >= 0);
        assert( r < 256);
        assert( g >= 0);
        assert( g < 256);
        assert( b >= 0);
        assert( b < 256);
        line[x*3+2] = (r == 0 ? 1 : r); //Never use a zero for red
        line[x*3+1] = (g == 0 ? 1 : g); //Never use a zero for green
        line[x*3+0] = (b == 0 ? 1 : b); //Never use a zero for blue
      }
      else
      {
        line[x*3+2] = 0;
        line[x*3+1] = 0;
        line[x*3+0] = 0;
      }
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDrawGlobeMinus.htm
void DrawGlobeMinus(TImage * const image,

  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  DrawGlobe(image,red,green,blue);
  const int height = image->Picture->Bitmap->Height;
  const int width  = image->Picture->Bitmap->Width;
  image->Canvas->Pen->Width = height / 10;
  image->Canvas->Pen->Color = static_cast<TColor>(RGB(red,green,blue));
  image->Canvas->MoveTo(1 * width / 4,height / 2);
  image->Canvas->LineTo(3 * width / 4,height / 2);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDrawGlobePlus.htm
void DrawGlobePlus(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  DrawGlobe(image,red,green,blue);
  const int height = image->Picture->Bitmap->Height;
  const int width  = image->Picture->Bitmap->Width;
  image->Canvas->Pen->Width = height / 10;
  image->Canvas->Pen->Color = static_cast<TColor>(RGB(red,green,blue));
  image->Canvas->MoveTo(1 * width / 4,height / 2);
  image->Canvas->LineTo(3 * width / 4,height / 2);
  image->Canvas->MoveTo(width / 2,1 * height / 4);
  image->Canvas->LineTo(width / 2,3 * height / 4);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
