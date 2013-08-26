//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <algorithm>
#include <cassert>
#include <cmath>
#include "UnitFunctions.h"

#include "UnitVcl.h"
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
void Blacken(Extctrls::TImage * const image, const double intensity)
{
  assert(image != 0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;

  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      const int r = static_cast<int>( static_cast<double>(
        line[(x*3)+2] ) * (1.0 - intensity) );
      const int g = static_cast<int>( static_cast<double>(
        line[(x*3)+1] ) * (1.0 - intensity) );
      const int b = static_cast<int>( static_cast<double>(
        line[(x*3)+0] ) * (1.0 - intensity) );
      assert( r >= 0); assert( r < 256);
      assert( g >= 0); assert( g < 256);
      assert( b >= 0); assert( b < 256);
      line[(x*3)+2] = r; //Red
      line[(x*3)+1] = g; //Green
      line[(x*3)+0] = b; //Blue
    }
  }
}
//---------------------------------------------------------------------------
void CreateWatermark(
  const Extctrls::TImage * const original,
  Extctrls::TImage * const image)
{
  assert(original != 0);
  assert(original->Picture->Bitmap != 0);
  assert(original->Picture->Bitmap->PixelFormat == pf24bit);
  assert(image != 0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = original->Picture->Bitmap->Width;
  const int maxy = original->Picture->Bitmap->Height;
  image->Picture->Bitmap->Width  = maxx;
  image->Picture->Bitmap->Height = maxy;

  for (int y = 0; y != maxy; ++y)
  {
    const unsigned char * const lineRead
      = static_cast<unsigned char*>(original->Picture->Bitmap->ScanLine[y]);
    unsigned char * const lineWrite
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      const int grey = ( lineRead[(x*3)+0] + lineRead[(x*3)+2]
        + lineRead[(x*3)+2] ) / 3;
      lineWrite[(x*3)+2] = (grey + 256) / 2 ; //Red
      lineWrite[(x*3)+1] = (grey + 256) / 2; //Green
      lineWrite[(x*3)+0] = (grey + 256) / 2; //Blue
    }
  }

}
//---------------------------------------------------------------------------
void DrawAudioSignal(Extctrls::TImage * const image, const double intensity)
{
  assert(image!=0);
  const int height = image->Picture->Bitmap->Height;
  const int width  = image->Picture->Bitmap->Width;
  const int dy = height / 10;

  image->Canvas->Pen->Color = clBlack;
  image->Canvas->Pen->Width = 1;

  //1x red on top
  image->Canvas->Brush->Color = (intensity > 1.500 ? clRed : clWhite);
  image->Canvas->Rectangle(0,0*dy,width, 1*dy);
  //3x orange
  TColor clOrange = static_cast<TColor>(RGB(255,127,0));
  image->Canvas->Brush->Color = (intensity > 1.333 ? clOrange : clWhite);
  image->Canvas->Rectangle(0,1*dy,width, 2*dy);
  image->Canvas->Brush->Color = (intensity > 1.167 ? clOrange : clWhite);
  image->Canvas->Rectangle(0,2*dy,width, 3*dy);
  image->Canvas->Brush->Color = (intensity > 1.000 ? clOrange : clWhite);
  image->Canvas->Rectangle(0,3*dy,width, 4*dy);
  //6x green
  image->Canvas->Brush->Color = (intensity > 0.833 ? clLime : clWhite);
  image->Canvas->Rectangle(0,4*dy,width, 5*dy);
  image->Canvas->Brush->Color = (intensity > 0.667 ? clLime : clWhite);
  image->Canvas->Rectangle(0,5*dy,width, 6*dy);
  image->Canvas->Brush->Color = (intensity > 0.500 ? clLime : clWhite);
  image->Canvas->Rectangle(0,6*dy,width, 7*dy);
  image->Canvas->Brush->Color = (intensity > 0.333 ? clLime : clWhite);
  image->Canvas->Rectangle(0,7*dy,width, 8*dy);
  image->Canvas->Brush->Color = (intensity > 0.167 ? clLime : clWhite);
  image->Canvas->Rectangle(0,8*dy,width, 9*dy);
  image->Canvas->Brush->Color = (intensity > 0.000 ? clLime : clWhite);
  image->Canvas->Rectangle(0,9*dy,width,10*dy);


}
//---------------------------------------------------------------------------
void DrawDial(Extctrls::TImage * const image, const int x, const int y,
  const Graphics::TColor color)
{
  assert(image!=0);
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;

  //Clear image
  image->Picture->Bitmap->TransparentColor = clLime;
  PaintVcl(image,clLime);

  //Draw knob
  image->Canvas->Pen->Width = 1;
  image->Canvas->Pen->Color = clBlack;
  image->Canvas->Brush->Color = color;
  image->Canvas->Ellipse(0,0,width,height);

  //Draw pointer
  const int midX = width / 2;
  const int midY = height / 2;
  const double ray = static_cast<double>(std::min( midX, midY ));
  const double angle
    = GetAngle( static_cast<double>(x - midX),
        static_cast<double>(y - midY));
  const int pointerX
    = static_cast<int>( static_cast<double>(midX) + (std::sin(angle) * ray) );
  const int pointerY
    = static_cast<int>( static_cast<double>(midY) - (std::cos(angle) * ray) );
  image->Canvas->Pen->Width = 4;
  image->Canvas->MoveTo(midX,midY);
  image->Canvas->LineTo(pointerX,pointerY);
}
//---------------------------------------------------------------------------
void DrawFader(Extctrls::TImage * const image, const int faderY)
{
  assert(image!=0);
  assert(faderY >= 0);
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  assert(faderY < height);
  const int trenchWidth = 4;
  const int trenchMidX = width / 2;
  const int faderHeight = width / 2;
  const int faderMidY = (faderY < (faderHeight / 2) ? (faderHeight / 2) :
    (faderY + (faderHeight / 2) > height ? height - (faderHeight / 2)   :
    faderY));

  //Clear image
  image->Picture->Bitmap->TransparentColor = clLime;
  PaintVcl(image,clLime);

  //Draw vertical trench
  image->Canvas->Pen->Width = trenchWidth;
  image->Canvas->Pen->Color = clBlack;
  image->Canvas->Brush->Color = clGray;
  image->Canvas->MoveTo(trenchMidX, 0);
  image->Canvas->LineTo(trenchMidX, height);
  //Draw fader
  image->Canvas->Pen->Width = 1;
  image->Canvas->Rectangle(
    0,
    faderMidY  - (faderHeight / 2),
    width - 1,
    faderMidY  + (faderHeight / 2));
}
//---------------------------------------------------------------------------
void DrawLamp(Extctrls::TImage * const image,
  const double brightness,
  const int red, const int green, const int blue)
{
  assert(image!=0);
  assert(brightness >= 0.0);
  assert(brightness <= 1.0);

  //Create transparent background with inverted color
  if (red == 255 && green == 255 && blue == 255)
  {
    PaintVcl(image,0,255,0);
  }
  else
  {
    PaintVcl(image,
      255 - red,
      255 - green,
      255 - blue);
  }

  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;

  //Fraction red/green/blue
  const double fR = static_cast<double>(red  ) / 255.0;
  const double fG = static_cast<double>(green) / 255.0;
  const double fB = static_cast<double>(blue ) / 255.0;

  //Draw circle
  const double maxBrightness = 1.00* 255.0;
  const double minBrightness = 0.00 * maxBrightness;
  image->Canvas->Pen->Width = 1 + (std::min(width,height) / 25);
  image->Canvas->Pen->Color = clBlack;
  const int r = static_cast<int>(
    minBrightness + (fR * brightness * (maxBrightness - minBrightness) ) );
  const int g = static_cast<int>(
    minBrightness + (fG * brightness * (maxBrightness - minBrightness) ) );
  const int b = static_cast<int>(
    minBrightness + (fB * brightness * (maxBrightness - minBrightness) ) );
  assert( r >= 0 ); assert( r < 256);
  assert( g >= 0 ); assert( g < 256);
  assert( b >= 0 ); assert( b < 256);
  image->Canvas->Brush->Color = static_cast<TColor>(RGB(r,g,b));
  image->Canvas->Ellipse(0,0,width,height);
}
//---------------------------------------------------------------------------
void DrawLed(Extctrls::TImage * const image,
  const double ledBrightness,
  const int red, const int green, const int blue)
{
  assert(image!=0);
  assert(ledBrightness >= 0.0);
  assert(ledBrightness <= 1.0);

  //Create transparent background with inverted color
  if (red == 255 && green == 255 && blue == 255)
  {
    PaintVcl(image,0,255,0);
  }
  else
  {
    PaintVcl(image,
      255 - red,
      255 - green,
      255 - blue);
  }

  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;

  //Fraction red/green/blue
  const double fR = static_cast<double>(red  ) / 255.0;
  const double fG = static_cast<double>(green) / 255.0;
  const double fB = static_cast<double>(blue ) / 255.0;

  {
    //Draw circle and major surface
    const double maxBrightness = 0.66 * 255.0;
    const double minBrightness = 0.25 * maxBrightness;
    image->Canvas->Pen->Width = 1 + (std::min(width,height) / 25);
    image->Canvas->Pen->Color = clBlack;
    const int r = static_cast<int>(
      minBrightness + (fR * ledBrightness * (maxBrightness - minBrightness) ) );
    const int g = static_cast<int>(
      minBrightness + (fG * ledBrightness * (maxBrightness - minBrightness) ) );
    const int b = static_cast<int>(
      minBrightness + (fB * ledBrightness * (maxBrightness - minBrightness) ) );
    assert( r >= 0 ); assert( r < 256);
    assert( g >= 0 ); assert( g < 256);
    assert( b >= 0 ); assert( b < 256);
    image->Canvas->Brush->Color = static_cast<TColor>(RGB(r,g,b));
    image->Canvas->Ellipse(0,0,width,height);
  }
  {
    //Draw topleft smaller lighter surface
    const double maxBrightness = 1.00 * 255.0;
    const double minBrightness = 0.25 * maxBrightness;
    image->Canvas->Pen->Width = 1;
    const int r = static_cast<int>(
      minBrightness + (fR * ledBrightness * (maxBrightness - minBrightness) ) );
    const int g = static_cast<int>(
      minBrightness + (fG * ledBrightness * (maxBrightness - minBrightness) ) );
    const int b = static_cast<int>(
      minBrightness + (fB * ledBrightness * (maxBrightness - minBrightness) ) );
    assert( r >= 0 ); assert( r < 256);
    assert( g >= 0 ); assert( g < 256);
    assert( b >= 0 ); assert( b < 256);
    image->Canvas->Pen->Color   = static_cast<TColor>(RGB(r,g,b));
    image->Canvas->Brush->Color = static_cast<TColor>(RGB(r,g,b));
    const int x1 = (width  / 2) - (0.707 * static_cast<double>(width ) * 0.5);
    const int y1 = (height / 2) - (0.707 * static_cast<double>(height) * 0.5);
    const int x2 = width / 2;
    const int y2 = height / 2;
    image->Canvas->Ellipse(x1,y1,x2,y2);
  }
  {
    //Draw bottomright smaller lighter surface
    const double maxBrightness = 0.33 * 255.0;
    const double minBrightness = 0.25 * maxBrightness;
    image->Canvas->Pen->Width = 1;
    const int r = static_cast<int>(
      minBrightness + (fR * ledBrightness * (maxBrightness - minBrightness) ) );
    const int g = static_cast<int>(
      minBrightness + (fG * ledBrightness * (maxBrightness - minBrightness) ) );
    const int b = static_cast<int>(
      minBrightness + (fB * ledBrightness * (maxBrightness - minBrightness) ) );
    assert( r >= 0 ); assert( r < 256);
    assert( g >= 0 ); assert( g < 256);
    assert( b >= 0 ); assert( b < 256);
    image->Canvas->Pen->Color   = static_cast<TColor>(RGB(r,g,b));
    image->Canvas->Brush->Color = static_cast<TColor>(RGB(r,g,b));
    const int x1 = (width  / 2) - 1;
    const int y1 = (height / 2) - 1;
    const int x2 = (width  / 2) + (0.707 * static_cast<double>(width ) * 0.5);
    const int y2 = (height / 2) + (0.707 * static_cast<double>(height) * 0.5);
    image->Canvas->Ellipse(x1,y1,x2,y2);
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
const std::vector<TRect> GetRectsHorizontal(const TRect& rect, const int nRects)
{
  assert(nRects > 0);
  std::vector<TRect> rects;

  const int dx = rect.Width() / nRects;
  for (int i=0; i!=nRects; ++i)
  {
    TRect r;
    r.Left = rect.Left + (i * dx);
    r.Right = r.left + dx;
    r.Top = rect.Top;
    r.Bottom = rect.Bottom;
    rects.push_back(r);
  }
  return rects;
}
//---------------------------------------------------------------------------
const std::vector<TRect> GetRectsVertical(const TRect& rect, const int nRects)
{
  assert(nRects > 0);
  std::vector<TRect> rects;

  const int dy = rect.Height() / nRects;
  for (int i=0; i!=nRects; ++i)
  {
    TRect r;
    r.Left = rect.Left;
    r.Right = rect.Right;
    r.Top = rect.Top + (i * dy);
    r.Bottom = r.Top + dy;
    rects.push_back(r);
  }
  return rects;
}
//---------------------------------------------------------------------------
//Y-X-ordered
const std::vector<std::vector<TRect> > GetRectsGrid(
  const TRect& rect, const int nCols, const int nRows)
{
  assert(nCols > 0);
  assert(nRows > 0);
  std::vector<TRect> rowRects = GetRectsVertical(rect,nRows);
  assert(nRows == static_cast<int>(rowRects.size()));

  std::vector<std::vector<TRect> > rects(nRows,std::vector<TRect>(nCols));
  for (int i=0; i!=nRows; ++i)
  {
    std::vector<TRect> row(GetRectsHorizontal(rowRects[i],nCols));
    rects[i] = row;
  }

  assert(nRows == static_cast<int>(rects.size()));
  assert(nCols == static_cast<int>(rects[0].size()));
  return rects;
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
const bool OnImage(const int x, const int y,
  const Extctrls::TImage * const image)
{
  return ( x >= image->Left
    && x < image->Left + image->Width
    && y >= image->Top
    && y < image->Top + image->Height);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(Extctrls::TImage * const image,
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
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(Extctrls::TImage * const image, const Graphics::TColor color)
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
void PlaceInCenter(Extctrls::TImage * const image, const TRect& rect)
{
  assert(image!=0);
  image->Left = rect.Left + (rect.Width()  / 2) - (image->Picture->Bitmap->Width  / 2);
  image->Top  = rect.Top  + (rect.Height() / 2) - (image->Picture->Bitmap->Height / 2);
}
//---------------------------------------------------------------------------
void PlaceInCenter(Forms::TForm * const form, const TRect& rect)
{
  assert(form!=0);
  form->Left = rect.Left + (rect.Width()  / 2) - (form->ClientWidth  / 2);
  form->Top  = rect.Top  + (rect.Height() / 2) - (form->ClientHeight / 2);
}
//---------------------------------------------------------------------------
const TRect MergeRects(const TRect& r1, const TRect& r2)
{
  TRect r;
  r.Left   = std::min(r1.Left  ,r2.Left  );
  r.Top    = std::min(r1.Top   ,r2.Top   );
  r.Right  = std::max(r1.Right ,r2.Right );
  r.Bottom = std::max(r1.Bottom,r2.Bottom);
  return r;
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
void SetSize(Graphics::TBitmap * const bitmap, const TRect& rect)
{
  bitmap->Width  = rect.Width();
  bitmap->Height = rect.Height();
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
