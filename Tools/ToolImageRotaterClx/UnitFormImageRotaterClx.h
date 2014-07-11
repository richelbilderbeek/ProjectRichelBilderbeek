//---------------------------------------------------------------------------
/*
 *  The Image Rotater (CLX edition). Rotates 24-bit bitmaps
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
#ifndef UnitFormImageRotaterClxH
#define UnitFormImageRotaterClxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <QControls.hpp>
#include <QStdCtrls.hpp>
#include <QForms.hpp>
#include <QComCtrls.hpp>
#include <QExtCtrls.hpp>
#include <QDialogs.hpp>
#include <QGraphics.hpp>
//---------------------------------------------------------------------------
class TFormImageRotaterClx : public TForm
{
__published:	// IDE-managed Components
        TButton *ButtonLoad;
        TPanel *PanelTop;
        TImage *ImageOriginal;
        TButton *ButtonSave;
        TTrackBar *TrackBar1;
        TImage *ImageResult;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TButton *ButtonAbout;
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall ButtonSaveClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormImageRotaterClx(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImageRotaterClx *FormImageRotaterClx;
//---------------------------------------------------------------------------
double GetAngle(const double dX, const double dY);
void SetPixelClx(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
void GetPixel(
  const TImage * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
void Rotate(
  const TImage * const imageOriginal,
  TImage * const imageResult,
  const double angle);
void GetPixel(
  const TImage * const image,
  const double x,
  const double y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
void GetPixel(
  const TImage * const image,
  const int x_tl,
  const int y_tl,
  const double left,
  const double top,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
void Translate(
  const double dx1,
  const double dy1,
  const double dAngle,
  double& dx2,
  double& dy2);








#endif
