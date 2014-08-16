/*
  The Pixelator, a tool to 'pixelate' images
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
#include <vcl.h>
#pragma hdrstop

#include "UnitFormPixelatorMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPixelatorMain *FormPixelatorMain;
//---------------------------------------------------------------------------
__fastcall TFormPixelatorMain::TFormPixelatorMain(TComponent* Owner)
        : TForm(Owner)
{
  TrackBarPixelSizeRgb->OnChange(0);
  TrackBarPixelSizeGrey->OnChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormPixelatorMain::ButtonLoadClick(TObject *Sender)
{
  if (OpenDialog1->Execute() == false) return;
  ImageOriginal->Picture->LoadFromFile(OpenDialog1->FileName);
  TrackBarPixelSizeRgb->OnChange(0);
  TrackBarPixelSizeGrey->OnChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormPixelatorMain::TrackBarPixelSizeRgbChange(
      TObject *Sender)
{
  DoPixelateRgb(ImageOriginal, ImagePixelateRgb, TrackBarPixelSizeRgb->Position);
}
//---------------------------------------------------------------------------
void __fastcall TFormPixelatorMain::TrackBarPixelSizeGreyChange(
      TObject *Sender)
{
  DoPixelateGrey(ImageOriginal, ImagePixelateGrey, TrackBarPixelSizeGrey->Position);
}
//---------------------------------------------------------------------------
void __fastcall TFormPixelatorMain::ButtonSavePixelateRgbClick(
      TObject *Sender)
{
  if (SaveDialog1->Execute() == false) return;
  ImagePixelateRgb->Picture->SaveToFile(SaveDialog1->FileName);
  ShowMessage("File has been saved");

}
//---------------------------------------------------------------------------
void DoPixelateRgb(
  const TImage * const imageOriginal,
  TImage * const imageResult,
  const int pixelSize)
{
  assert(imageOriginal!=0);
  assert(imageResult!=0);

  imageResult->Picture->Graphic = imageOriginal->Picture->Graphic;

  assert(imageOriginal->Picture->Bitmap->Width  == imageResult->Picture->Bitmap->Width );
  assert(imageOriginal->Picture->Bitmap->Height == imageResult->Picture->Bitmap->Height);

  const int width  = imageOriginal->Picture->Bitmap->Width;
  const int height = imageOriginal->Picture->Bitmap->Height;
  const int maxx = 1 + (width  / pixelSize);
  const int maxy = 1 + (height / pixelSize);

  for (int y=0; y!=maxy; ++y)
  {
    const int y1 = (y * pixelSize);
    if (y1 >= height) continue;
    const int y2 = std::min( y1 + pixelSize, height);
    assert(y1 <= height);
    assert(y2 <= height);
    assert(y1!=y2);

    for (int x=0; x!=maxx; ++x)
    {
      const int x1 = (x * pixelSize);
      if (x1 >= width) continue;
      const int x2 = std::min( x1 + pixelSize, width);
      assert(x1 <= width);
      assert(x2 <= width);
      assert(x1!=x2);


      unsigned char r,g,b;
      GetPixel(imageOriginal,
        x1,
        y1,
        x2,
        y2,
        r,g,b);
      SetPixel(
        imageResult,
        x1,
        y1,
        x2,
        y2,
        r,g,b);
    }
  }
}
//---------------------------------------------------------------------------
void DoPixelateGrey(
  const TImage * const imageOriginal,
  TImage * const imageResult,
  const int pixelSize)
{
  assert(imageOriginal!=0);
  assert(imageResult!=0);

  imageResult->Picture->Graphic = imageOriginal->Picture->Graphic;

  assert(imageOriginal->Picture->Bitmap->Width  == imageResult->Picture->Bitmap->Width );
  assert(imageOriginal->Picture->Bitmap->Height == imageResult->Picture->Bitmap->Height);

  const int width  = imageOriginal->Picture->Bitmap->Width;
  const int height = imageOriginal->Picture->Bitmap->Height;
  const int maxx = 1 + (width  / pixelSize);
  const int maxy = 1 + (height / pixelSize);

  for (int y=0; y!=maxy; ++y)
  {
    const int y1 = (y * pixelSize);
    if (y1 >= height) continue;
    const int y2 = std::min( y1 + pixelSize, height );
    assert(y1 <= height);
    assert(y2 <= height);
    assert(y1!=y2);

    for (int x=0; x!=maxx; ++x)
    {
      const int x1 = (x * pixelSize);
      if (x1 >= width) continue;
      const int x2 = std::min( x1 + pixelSize, width );
      assert(x1 <= width);
      assert(x2 <= width);
      assert(x1!=x2);
      const int grey = GetGreyness(imageOriginal,x1,y1,x2,y2);
      SetGreyness(imageResult,x1,y1,x2,y2,grey);
    }
  }
}
//---------------------------------------------------------------------------
void ThresholdFilter(
  const TImage * const imageOriginal,
  TImage * const imageThreshold,
  const unsigned char threshold)
{
  assert(imageOriginal!=0);
  assert(imageThreshold!=0);

  imageThreshold->Picture->Graphic = imageOriginal->Picture->Graphic;

  assert(imageOriginal->Picture->Bitmap->Width  == imageThreshold->Picture->Bitmap->Width );
  assert(imageOriginal->Picture->Bitmap->Height == imageThreshold->Picture->Bitmap->Height);

  const int width  = imageOriginal->Picture->Bitmap->Width;
  const int height = imageOriginal->Picture->Bitmap->Height;

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * const lineOriginal
      = static_cast<unsigned char *>(imageOriginal->Picture->Bitmap->ScanLine[y]);
    unsigned char * const lineThreshold
      = static_cast<unsigned char *>(imageThreshold->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const int grey = (lineOriginal[x*3+0] + lineOriginal[x*3+1] + lineOriginal[x*3+2]) / 3;
      if (grey > threshold)
      {
        lineThreshold[x*3+2] = 255; //Red
        lineThreshold[x*3+1] = 255; //Green
        lineThreshold[x*3+0] = 255; //Blue
      }
      else
      {
        lineThreshold[x*3+2] = 0; //Red
        lineThreshold[x*3+1] = 0; //Green
        lineThreshold[x*3+0] = 0; //Blue
      }
    }
  }
}
//---------------------------------------------------------------------------
//Get a pixel's greyness
//From http://www.richelbilderbeek.nl
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
//Get a line of pixel's average greyness
//From http://www.richelbilderbeek.nl
void GetPixel(
  const TImage * const image,
  const int x1,
  const int x2,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue)
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
  assert( x1 < x2);

  const unsigned char * const line
    = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);

  const int nPixels = x2 - x1;
  int sumRed   = 0;
  int sumGreen = 0;
  int sumBlue  = 0;

  for (int x=x1; x!=x2; ++x)
  {
    const unsigned char r = line[x*3+2];
    const unsigned char g = line[x*3+1];
    const unsigned char b = line[x*3+0];
    sumRed+=r;
    sumGreen+=g;
    sumBlue+=b;
  }
  const int averageRed   = sumRed   / nPixels;
  const int averageGreen = sumGreen / nPixels;
  const int averageBlue  = sumBlue  / nPixels;
  assert(averageRed   >= 0 && averageRed   < 256);
  assert(averageGreen >= 0 && averageGreen < 256);
  assert(averageBlue  >= 0 && averageBlue  < 256);
  red   = averageRed;
  green = averageGreen;
  blue  = averageBlue;

}
//---------------------------------------------------------------------------
//Get a square of pixels' average greyness
//From http://www.richelbilderbeek.nl
void GetPixel(
  const TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue)

{
  assert(x1 < x2 );
  assert(y1 < y2 );
  const int nPixelsVertical = y2 - y1;
  int sumRed   = 0;
  int sumGreen = 0;
  int sumBlue  = 0;

  for (int y=y1; y!=y2; ++y)
  {
    unsigned char r,g,b;
    GetPixel(image,x1,x2,y,r,g,b);
    sumRed+=r;
    sumGreen+=g;
    sumBlue+=b;
  }
  const int averageRed   = sumRed   / nPixelsVertical;
  const int averageGreen = sumGreen / nPixelsVertical;
  const int averageBlue  = sumBlue  / nPixelsVertical;
  assert(averageRed   >= 0 && averageRed   < 256);
  assert(averageGreen >= 0 && averageGreen < 256);
  assert(averageBlue  >= 0 && averageBlue  < 256);
  red   = averageRed;
  green = averageGreen;
  blue  = averageBlue;
}
//---------------------------------------------------------------------------











//Set a pixel's color
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

  unsigned char * const myLine
    = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);

  myLine[x*3+2] = red;
  myLine[x*3+1] = green;
  myLine[x*3+0] = blue;
}
//---------------------------------------------------------------------------
//Set a line of pixel's color
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
//Set a square of pixels' color
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




















//Get a pixel's greyness
//From http://www.richelbilderbeek.nl
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
//From http://www.richelbilderbeek.nl
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
  assert( x2 <= image->Picture->Bitmap->Width  && "x2 coordinat is beyond image width");
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
//From http://www.richelbilderbeek.nl
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
//Set a pixel's greyness
//From http://www.richelbilderbeek.nl
void SetGreyness(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char grey)
{
  assert(image!=0 && "Image is NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert( x >= 0 && "x coordinat is below zero");
  assert( y >= 0 && "y coordinat is below zero");
  assert( x < image->Picture->Bitmap->Width  && "x coordinat is beyond image width");
  assert( y < image->Picture->Bitmap->Height && "y coordinat is beyond image height");

  unsigned char * const myLine
    = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);

  myLine[x*3+2] = grey;
  myLine[x*3+1] = grey;
  myLine[x*3+0] = grey;
}
//---------------------------------------------------------------------------
//Set a line of pixel's greyness
//From http://www.richelbilderbeek.nl
void SetGreyness(
  TImage * const image,
  const int x1,
  const int x2,
  const int y,
  const unsigned char grey)
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
    myLine[x*3+2] = grey;
    myLine[x*3+1] = grey;
    myLine[x*3+0] = grey;
  }
}
//---------------------------------------------------------------------------
//Set a square of pixels' greyness
//From http://www.richelbilderbeek.nl
void SetGreyness(
  TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  const unsigned char grey)
{
  for (int y=y1; y!=y2; ++y)
  {
    SetGreyness(image,x1,x2,y,grey);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPixelatorMain::ButtonSavePixelateGreyClick(
      TObject *Sender)
{
  if (SaveDialog1->Execute() == false) return;
  ImagePixelateGrey->Picture->SaveToFile(SaveDialog1->FileName);
  ShowMessage("File has been saved");

}
//---------------------------------------------------------------------------

