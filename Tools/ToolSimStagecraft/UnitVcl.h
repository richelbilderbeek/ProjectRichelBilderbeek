//---------------------------------------------------------------------------

#ifndef UnitVclH
#define UnitVclH
//---------------------------------------------------------------------------
#include <vector>
#include <Graphics.hpp> //For TColor
namespace Extctrls { struct TImage; }
namespace Forms { struct TForm; }
//---------------------------------------------------------------------------
//Makes all red pixels even, except when there's a message pixel
//From http://www.richelbilderbeek.nl/CppAddMessageRed.htm
void AddMessageRed(
  const TImage * const original,
  const TImage * const message,
  TImage * const result);
//---------------------------------------------------------------------------
void Blacken(Extctrls::TImage * const image, const double intensity);
//---------------------------------------------------------------------------
void CreateWatermark(const Extctrls::TImage * const original,
  Extctrls::TImage * const image);
//---------------------------------------------------------------------------
void DrawAudioSignal(Extctrls::TImage * const image, const double intensity);
//---------------------------------------------------------------------------
void DrawDial(Extctrls::TImage * const image, const int x, const int y,
  const Graphics::TColor color = clGray);
//---------------------------------------------------------------------------
void DrawFader(Extctrls::TImage * const image, const int faderY);
//---------------------------------------------------------------------------
void DrawLamp(Extctrls::TImage * const image,
  const double brightness,
  const int red, const int green, const int blue);
//---------------------------------------------------------------------------
void DrawLed(Extctrls::TImage * const image,
  const double ledBrightness,
  const int red, const int green, const int blue);
//---------------------------------------------------------------------------
//Get a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
void GetPixel(
  const TImage * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
//---------------------------------------------------------------------------
const std::vector<TRect> GetRectsHorizontal(const TRect& rect, const int nRects);
//---------------------------------------------------------------------------
const std::vector<TRect> GetRectsVertical(const TRect& rect, const int nRects);
//---------------------------------------------------------------------------
//Y-X-ordered
const std::vector<std::vector<TRect> > GetRectsGrid(
  const TRect& rect, const int nCols, const int nRows);
//---------------------------------------------------------------------------
const bool IsWhite(const TImage * const image, const int x, const int y);
//---------------------------------------------------------------------------
const bool OnImage(const int x, const int y,
  const Extctrls::TImage * const image);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(Extctrls::TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(Extctrls::TImage * const image, const Graphics::TColor color);
//---------------------------------------------------------------------------
void PlaceInCenter(Extctrls::TImage * const image, const TRect& rect);
//---------------------------------------------------------------------------
void PlaceInCenter(Forms::TForm * const form, const TRect& rect);
//---------------------------------------------------------------------------
const TRect MergeRects(const TRect& r1, const TRect& r2);
//---------------------------------------------------------------------------
//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppSetPixel.htm
void SetPixel(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------
void SetSize(Graphics::TBitmap * const bitmap, const TRect& rect);
//---------------------------------------------------------------------------





#endif
