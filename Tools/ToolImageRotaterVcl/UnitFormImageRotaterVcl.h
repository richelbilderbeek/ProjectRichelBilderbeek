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
#ifndef UnitFormImageRotaterVclH
#define UnitFormImageRotaterVclH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormImageRotaterVcl : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelTop;
        TButton *ButtonLoad;
        TTrackBar *TrackBar1;
        TButton *ButtonSave;
        TButton *ButtonAbout;
        TOpenDialog *OpenDialog1;
        TImage *ImageOriginal;
        TImage *ImageResult;
        TSaveDialog *SaveDialog1;
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall ButtonSaveClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormImageRotaterVcl(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormImageRotaterVcl *FormImageRotaterVcl;
//---------------------------------------------------------------------------
double GetAngle(const double dX, const double dY);
void SetPixelVcl(
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
