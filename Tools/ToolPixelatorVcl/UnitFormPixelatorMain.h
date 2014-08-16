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
#ifndef UnitFormPixelatorMainH
#define UnitFormPixelatorMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormPixelatorMain : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *TabSheetOriginal;
        TTabSheet *TabSheetPixelator;
        TPanel *PanelTopOriginal;
        TButton *ButtonLoad;
        TPanel *PanelPixelatorTop;
        TButton *ButtonSavePixelateRgb;
        TTrackBar *TrackBarPixelSizeRgb;
        TLabel *Label1;
        TImage *ImagePixelateRgb;
        TImage *ImageOriginal;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TTabSheet *TabSheetPixelateGrey;
        TTabSheet *TabSheetAbout;
        TPanel *Panel1;
        TLabel *Label3;
        TButton *ButtonSavePixelateGrey;
        TTrackBar *TrackBarPixelSizeGrey;
        TImage *ImagePixelateGrey;
        TImage *Image1;
        TRichEdit *RichEdit1;
        TPanel *PanelAboutTop;
        TPanel *PanelAboutTopRight;
        TLabel *Label2;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall TrackBarPixelSizeRgbChange(TObject *Sender);
        void __fastcall ButtonSavePixelateRgbClick(TObject *Sender);
        void __fastcall TrackBarPixelSizeGreyChange(TObject *Sender);
        void __fastcall ButtonSavePixelateGreyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormPixelatorMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPixelatorMain *FormPixelatorMain;
//---------------------------------------------------------------------------
void ThresholdFilter(
  const TImage * const imageOriginal,
  TImage * const imageThreshold,
  const unsigned char threshold);
void DoPixelateRgb(
  const TImage * const imageOriginal,
  TImage * const imageResult,
  const int pixelSize);
void DoPixelateGrey(
  const TImage * const imageOriginal,
  TImage * const imageResult,
  const int pixelSize);


const unsigned char GetGreyness(
  const TImage * const image,
  const int x,
  const int y);
const unsigned char GetGreyness(
  const TImage * const image,
  const int x1,
  const int x2,
  const int y);
const unsigned char GetGreyness(
  const TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2);



void GetPixel(
  const TImage * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
void GetPixel(
  const TImage * const image,
  const int x1,
  const int x2,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);
void GetPixel(
  const TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);



void SetPixel(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
void SetPixel(
  TImage * const image,
  const int x1,
  const int x2,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
void SetPixel(
  TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);


void SetGreyness(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char grey);
void SetGreyness(
  TImage * const image,
  const int x1,
  const int x2,
  const int y,
  const unsigned char grey);
void SetGreyness(
  TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2,
  const unsigned char grey);


#endif
