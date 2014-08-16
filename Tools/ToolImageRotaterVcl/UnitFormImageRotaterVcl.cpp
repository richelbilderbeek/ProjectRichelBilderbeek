//---------------------------------------------------------------------------
/*
 *  The Image Rotater (VCL edition). Rotates 24-bit bitmaps
 *  Copyright (C) 2007  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
#include <algorithm>
#include <cmath>
#include <cassert>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormImageRotaterVcl.h"
#include "UnitFormAboutVcl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormImageRotaterVcl *FormImageRotaterVcl;
//---------------------------------------------------------------------------
__fastcall TFormImageRotaterVcl::TFormImageRotaterVcl(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormImageRotaterVcl::ButtonLoadClick(TObject *Sender)
{
  if (OpenDialog1->Execute() == false) return;

  ImageOriginal->Picture->LoadFromFile(OpenDialog1->FileName);
  const int max
    = std::max(
      ImageOriginal->Picture->Bitmap->Width,
      ImageOriginal->Picture->Bitmap->Height);
  ImageResult->Picture->Bitmap->Width  = 1.414 * max;
  ImageResult->Picture->Bitmap->Height = 1.414 * max;
  ImageResult->Width  = ImageResult->Picture->Bitmap->Height;
  ImageResult->Height = ImageResult->Picture->Bitmap->Height;

  TrackBar1->Enabled = true;
  TrackBar1->OnChange(0);

}
//---------------------------------------------------------------------------
//From www.richelbilderbeek.nl/CppGetAngle.htm
double GetAngle(const double dX, const double dY)
{
  //In which quadrant are we?
  if (dX > 0)
  {
    if (dY > 0)
    {
      //dX > 0 && dY > 0
      //Quadrant IV
      assert(dX > 0.0 && dY > 0.0);
      const double angle = (1.0 * M_PI) - std::atan(dX / dY);
      assert(angle > 0.5 * M_PI && angle < 1.0 * M_PI);
      return angle;
    }
    else if (dY < 0)
    {
      //dX > 0 && dY <= 0
      //Quadrant I
      assert(dX > 0.0 && dY < 0.0);
      const double angle = (0.0 * M_PI) - std::atan(dX / dY);
      assert(angle > 0.0 * M_PI && angle < 0.5 * M_PI);
      return angle;
    }
    else
    {
      //dX > 0.0 && dY == 0.0
      //On Y-axis, right side
      assert(dX > 0.0 && dY == 0.0);
      const double angle = (0.5 * M_PI);
      return angle;
    }
  }
  else if (dX < 0.0)
  {
    if (dY > 0.0)
    {
      //dX < 0 && dY > 0
      //Quadrant III
      assert(dX < 0.0 && dY > 0.0);
      const double angle = (1.0 * M_PI) - std::atan(dX / dY);
      assert(angle > 1.0 * M_PI && angle < 1.5 * M_PI);
      return angle;
    }
    else if (dY < 0.0)
    {
      //dX < 0 && dY < 0
      //Quadrant II
      assert(dX < 0.0 && dY < 0.0);
      const double angle = (2.0 * M_PI) - std::atan(dX / dY);
      assert(angle > 1.5 * M_PI && angle < 2.0 * M_PI);
      return angle;
    }
    else
    {
      //dX < 0 && dY == 0
      //On X-axis
      assert(dX < 0.0 && dY == 0.0);
      const double angle = (1.5 * M_PI);
      return angle;
    }
  }
  else
  {
    if (dY > 0.0)
    {
      //dX == 0 && dY > 0.0)
      //On Y-axis, right side of origin
      assert(dX==0.0 && dY > 0.0);
      const double angle = (1.0 * M_PI);
      return angle;
    }
    else if (dY < 0.0)
    {
      //dX == 0 && dY < 0.0)
      //On Y-axis, left side of origin
      assert(dX==0.0 && dY < 0.0);
      const double angle = (0.0 * M_PI);
      return angle;
    }
    else
    {
      //dX == 0 && dY == 0.0)
      //On origin
      assert(dX==0.0 && dY == 0.0);
      const double angle = (0.0 * M_PI);
      return angle;
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl
void SetPixelVcl(
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

  static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+2] = red;
  static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+1] = green;
  static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+0] = blue;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
TColor GetPixel(
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
  return static_cast<TColor>(RGB(
    (static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+2]), //Red
    (static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+1]), //Green
    (static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+0])  //Blue
    ));
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
  red   = (static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+2]);
  green = (static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+1]);
  blue  = (static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+0]);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRotate.htm
void Rotate(
  const TImage * const imageOriginal,
  TImage * const imageResult,
  const double angle)
{
  const int maxx = imageResult->Picture->Bitmap->Width;
  const int maxy = imageResult->Picture->Bitmap->Height;
  const double midx = static_cast<double>(maxx) / 2.0;
  const double midy = static_cast<double>(maxy) / 2.0;

  for (int y=0; y!=maxy; ++y)
  {
    for(int x=0; x!=maxx; ++x)
    {
      const double dx1 = static_cast<double>(x) - midx;
      const double dy1 = static_cast<double>(y) - midy;
      double dx2, dy2; //Coordinats in original
      Translate(dx1,dy1,angle,dx2,dy2);
      const double x2 =
      (static_cast<double>(imageOriginal->Picture->Bitmap->Width ) /
      2.0) + dx2;
      const double y2 =
      (static_cast<double>(imageOriginal->Picture->Bitmap->Height) /
      2.0) + dy2;
      if ( x2 < 1.0
        || y2 < 1.0
        || x2 >= imageOriginal->Picture->Bitmap->Width - 1.0
        || y2 >= imageOriginal->Picture->Bitmap->Height - 1.0
        )
      { //Out of range
        SetPixelVcl(imageResult,x,y,0,0,0);
        continue;
      }
      unsigned char r,g,b;
      GetPixel(imageOriginal,x2,y2,r,g,b);
      SetPixelVcl(imageResult,x,y,r,g,b);
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRotate.htm
void GetPixel(
  const TImage * const image,
  const double x,
  const double y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue)
{
  const double xRemainder = x - static_cast<int>(x);
  const double yRemainder = y - static_cast<int>(y);
  const int x_tl = ( xRemainder > 0.5 ? x : x-1);
  const int y_tl = ( yRemainder > 0.5 ? y : y-1);
  const double left = ( xRemainder > 0.5 ? 1.5 - xRemainder : 0.5 -
  xRemainder);
  const double top  = ( yRemainder > 0.5 ? 1.5 - yRemainder : 0.5 -
  yRemainder);
  return GetPixel(image,x_tl,y_tl,left,top,red,green,blue);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRotate.htm
void GetPixel(
  const TImage * const image,
  const int x_tl,
  const int y_tl,
  const double left,
  const double top,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue)
{
  const double right = 1.0 - left;
  const double bottom = 1.0 - top;
  assert(left   >= 0.0 && left   <=1.0);
  assert(top    >= 0.0 && top    <=1.0);
  assert(right  >= 0.0 && right  <=1.0);
  assert(bottom >= 0.0 && bottom <=1.0);

  unsigned char r_tl, g_tl, b_tl;
  unsigned char r_tr, g_tr, b_tr;
  unsigned char r_bl, g_bl, b_bl;
  unsigned char r_br, g_br, b_br;

  GetPixel(image,x_tl+0,y_tl+0,r_tl,g_tl,b_tl);
  GetPixel(image,x_tl+1,y_tl+0,r_tr,g_tr,b_tr);
  GetPixel(image,x_tl+0,y_tl+1,r_bl,g_bl,b_bl);
  GetPixel(image,x_tl+1,y_tl+1,r_br,g_br,b_br);

  const double rTotal
    = (top    * left  * static_cast<double>(r_tl))
    + (top    * right * static_cast<double>(r_tr))
    + (bottom * left  * static_cast<double>(r_bl))
    + (bottom * right * static_cast<double>(r_br));
  const double gTotal
    = (top    * left  * static_cast<double>(g_tl))
    + (top    * right * static_cast<double>(g_tr))
    + (bottom * left  * static_cast<double>(g_bl))
    + (bottom * right * static_cast<double>(g_br));
  const double bTotal
    = (top    * left  * static_cast<double>(b_tl))
    + (top    * right * static_cast<double>(b_tr))
    + (bottom * left  * static_cast<double>(b_bl))
    + (bottom * right * static_cast<double>(b_br));
  assert(rTotal >= 0.0 && rTotal < 256.0);
  assert(gTotal >= 0.0 && gTotal < 256.0);
  assert(bTotal >= 0.0 && bTotal < 256.0);
  red   = static_cast<unsigned char>(rTotal);
  green = static_cast<unsigned char>(gTotal);
  blue  = static_cast<unsigned char>(bTotal);

}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRotate.htm
void Translate(
  const double dx1,
  const double dy1,
  const double dAngle,
  double& dx2,
  double& dy2)
{
  const double oldAngle = GetAngle(dx1,dy1);
  const double newAngle = oldAngle - dAngle; //NEW: Must be a minus to rotate clockwise
  const double ray = std::sqrt((dx1 * dx1) + (dy1 * dy1)); //Pythagoras
  dx2 = std::sin(newAngle) * ray;
  dy2 = -std::cos(newAngle) * ray;
}
//---------------------------------------------------------------------------
void __fastcall TFormImageRotaterVcl::TrackBar1Change(TObject *Sender)
{
  ImageResult->Visible = true;
  const double angle
    = static_cast<double>(TrackBar1->Position)
    / static_cast<double>(TrackBar1->Max)
    * (2.0 * M_PI);
  Rotate(ImageOriginal,ImageResult,angle);
  ImageResult->Refresh();
  ButtonSave->Enabled = true;
  TrackBar1->Hint = "Angle: " + FloatToStr(angle);
}
//---------------------------------------------------------------------------
void __fastcall TFormImageRotaterVcl::ButtonSaveClick(TObject *Sender)
{
  if (SaveDialog1->Execute() == false) return;
  ImageResult->Picture->SaveToFile(SaveDialog1->FileName);
  ShowMessage( "Image saved to file '" + (SaveDialog1->FileName) + "' succesfully.");
}
//---------------------------------------------------------------------------
void __fastcall TFormImageRotaterVcl::ButtonAboutClick(TObject *Sender)
{
  TFormAboutVcl * f = new TFormAboutVcl(this);
  f->ShowModal();
}
//---------------------------------------------------------------------------

