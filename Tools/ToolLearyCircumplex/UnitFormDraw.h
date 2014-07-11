//---------------------------------------------------------------------------
/*
  Leary Circumplex, tool to draw a Leary circumplex
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
#ifndef UnitFormDrawH
#define UnitFormDrawH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <boost/array.hpp>
//---------------------------------------------------------------------------
class TFormDraw : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageLeary;
        TImage *ImageBuffer1;
        TImage *ImageBuffer2;
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
  const boost::array<TImage*,2> buffers;
  const boost::array<double,8> scores;
  const boost::array<std::string,8> legend;
  const boost::array<TImage*,2> GetBuffers() const;

public:		// User declarations
  __fastcall TFormDraw(
  TComponent* Owner,
  const boost::array<double,8>& any_scores,
  const boost::array<std::string,8>& any_legend);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDraw *FormDraw;
//---------------------------------------------------------------------------
void DrawLearyCircumplex(
  const boost::array<double,8>& scores,
  const boost::array<std::string,8>& legend,
  TImage * const image,
  const boost::array<TImage*,2>& image_buffer);
//---------------------------------------------------------------------------
//From www.richelbilderbeek.nl/CppGetAngle.htm
const double GetAngle(const double dX, const double dY);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRotate.htm
void Rotate(
  const TImage * const imageOriginal,
  TImage * const imageResult,
  const double angle);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl
void SetPixelVcl(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
const TColor GetPixel(
  const TImage * const image,
  const int x,
  const int y);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
void GetPixel(
  const TImage * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRotate.htm
void GetPixel(
  const TImage * const image,
  const double x,
  const double y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
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
  unsigned char& blue);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRotate.htm
void Translate(
  const double dx1,
  const double dy1,
  const double dAngle,
  double& dx2,
  double& dy2);
//---------------------------------------------------------------------------

#endif
