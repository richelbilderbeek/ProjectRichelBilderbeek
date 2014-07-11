/*
  SimBrainiac, a simulation of Brainiacs interacting
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
#include <cassert>   //For assert
#include <cmath>     //For std::sqrt
#include <algorithm> //For std::min
#include <vector>
#include "UnitBrainiac.h"
#include <ExtCtrls.hpp>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSimBrainiacMain.h"
#include "UnitFormSimBrainiacGraph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSimBrainiacMain *FormSimBrainiacMain;
//---------------------------------------------------------------------------
__fastcall TFormSimBrainiacMain::TFormSimBrainiacMain(
    TComponent* Owner,
    const int nBrainiacs,
    const int nCorrectAnswerLevels,
    const int nHasQuestionLevels)
    : TForm(Owner),
      mSim(SimBrainiac(GetBrainiacs(nBrainiacs,nCorrectAnswerLevels,nHasQuestionLevels))),
      mUseGrey(true),
      mDrawBrainiacs(true),
      mFormGraph(new TFormSimBrainiacGraph(0)),
      mNrows(static_cast<int>(std::sqrt( static_cast<double>(nBrainiacs))) + 1),
      mNcols(static_cast<int>(std::sqrt( static_cast<double>(nBrainiacs))) + 1)
{
  OnResize(0);
  TimerMainTimer(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimBrainiacMain::TimerMainTimer(TObject *Sender)
{
  if (mDrawBrainiacs == false)
  {
    TimerMain->Enabled = false;
    while (mDrawBrainiacs==false)
    {
      mSim.Tick();
      mFormGraph->Plot(mSim.GetBrainiacs());
      Application->ProcessMessages();
    }
  }


  mSim.Tick();
  mFormGraph->Plot(mSim.GetBrainiacs());

  const std::vector<Brainiac>& v = mSim.GetBrainiacs();
  const int size = v.size();
  if (size==0) return;
  const int dX = ImageBrainiac->Picture->Graphic->Width;
  const int dY = ImageBrainiac->Picture->Graphic->Height;

  for (int i=0; i!=size; ++i)
  {
    const int indexX = i % mNcols;
    const int indexY = i / mNcols;
    assert(indexX < mNcols);
    assert(indexY < mNrows);
    const int x = dX * indexX;
    const int y = dY * indexY;
    DrawBrainiac(v[i]);
    ImageBuffer->Canvas->Draw(
      x,y,
      ImageBrainiac->Picture->Graphic);
  }
  this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimBrainiacMain::FormResize(TObject *Sender)
{
  const int width  = ClientWidth  / mNrows;
  const int height = ClientHeight / mNcols;
  ImageBrainiac->Picture->Bitmap->Width  = width;
  ImageBrainiac->Picture->Bitmap->Height = height;
  ImageBuffer->Picture->Bitmap->Width  = ClientWidth;
  ImageBuffer->Picture->Bitmap->Height = ClientHeight;

  PaintVcl(ImageBuffer,255,255,255);
  PaintVcl(ImageBrainiac,255,255,255);

  DrawGlobe(ImageBrainiac,255,255,255);
}
//---------------------------------------------------------------------------
void TFormSimBrainiacMain::DrawBrainiac(
  const Brainiac& brainiac) const
{
  assert(brainiac.pCorrectAnswer >= 0.0 && brainiac.pCorrectAnswer < 1.0);
  assert(brainiac.pHasQuestion >= 0.0 && brainiac.pHasQuestion < 1.0);

  //Assumes that 'image' already contains a globe!
  const int width  = ImageBrainiac->Picture->Bitmap->Width;
  const int height = ImageBrainiac->Picture->Bitmap->Height;
  const int midX = width  / 2;
  const int midY = height / 2;
  const int midX2 = midX / 2;
  const int midY2 = midY / 2;
  const unsigned char greyCorrectAnswer
    = static_cast<unsigned char>(
      1.0 + (brainiac.pCorrectAnswer * 254.0)
      );
  const unsigned char greyHasQuestion
    = static_cast<unsigned char>(
      1.0 + (brainiac.pHasQuestion * 254.0)
      );
  const int x1 = midX-midX2;
  const int y1 = midY-midY2;
  const int x2 = midX+midX2;
  const int y2 = midY+midY2;
  
  assert(x1 >= 0);
  assert(x1 < width);
  assert(y1 >= 0);
  assert(y1 < height);
  assert(x2 >= 0);
  assert(x2 < width);
  assert(y2 >= 0);
  assert(y2 < height);

  if (mUseGrey==true)
  {
    //Grey
    SetPixel(ImageBrainiac,
      x1,
      y1,
      midX,
      midY,
      greyCorrectAnswer,greyCorrectAnswer,greyCorrectAnswer);
    //Rainbow(brainiac.pHasQuestion,r,g,b);
    SetPixel(ImageBrainiac,
      midX,
      midY,
      x2,
      y2,
      greyHasQuestion,greyHasQuestion,greyHasQuestion);
  }
  else
  {
    //Rainbow
    unsigned char r,g,b;
    Rainbow(brainiac.pCorrectAnswer,r,g,b);
    SetPixel(ImageBrainiac,
      x1,
      y1,
      midX,
      midY,
      r,g,b);
    Rainbow(brainiac.pHasQuestion,r,g,b);
    SetPixel(ImageBrainiac,
      midX,
      midY,
      x2,
      y2,
      r,g,b);
  }
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
//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl
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
//Set a line of pixels' RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  TImage * const image,
  const int x1,
  const int x2,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  assert(image!=0 && "Image is NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert( x1 >= 0 && "x1 coordinat is below zero");
  assert( x2 >= 0 && "x2 coordinat is below zero");
  assert( y >= 0 && "y coordinat is below zero");
  assert( x1 < image->Picture->Bitmap->Width  && "x1 coordinat is beyond image width");
  assert( x2 <= image->Picture->Bitmap->Width  && "x2 coordinat is beyond image width");
  assert( y < image->Picture->Bitmap->Height && "y coordinat is beyond image height");

  unsigned char * const myLine
    = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
  for (int x=x1; x!=x2; ++x)
  {
    myLine[x*3+2] = red;
    myLine[x*3+1] = green;
    myLine[x*3+0] = blue;
  }
}
//---------------------------------------------------------------------------
//Set a square of pixels' RGB values
//From http://www.richelbilderbeek.nl
void SetPixel(
  TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  for (int y=y1; y!=y2; ++y)
  {
    SetPixel(image,x1,x2,y,red,green,blue);
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <cassert>
#include <cmath>
#include <algorithm>
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

void __fastcall TFormSimBrainiacMain::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if (Key == VK_F1 || Key == 'c' || Key == 'C') mUseGrey = !mUseGrey;
  if (Key == VK_F2 || Key == 'g' || Key == 'G') mFormGraph->Visible = !mFormGraph->Visible;
  if (Key == VK_F3 || Key == 'd' || Key == 'D')
  {
    mDrawBrainiacs = !mDrawBrainiacs;
    //TimerMain->Enabled = mDrawBrainiacs;
  }
  if (Key == VK_ADD || Key == VK_F12)
  {
    TimerMain->Enabled = false;
    TimerMain->Interval -= 100;
    if (TimerMain->Interval < 1) TimerMain->Interval = 1;
    TimerMain->Enabled = true;
  }

  if (Key == VK_SUBTRACT || Key == VK_F11)
  {
    TimerMain->Enabled = false;
    TimerMain->Interval += 100;
    TimerMain->Enabled = true;
  }
}
//---------------------------------------------------------------------------


