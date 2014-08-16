//---------------------------------------------------------------------------
/*
  ThresholdFilterer, tool to perform threshold filter operations
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
#include <boost/scoped_ptr.hpp>
#include <cassert>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormThresholdFilterer.h"
#include "UnitFormThresholdFiltererAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormThresholdFilterer *FormThresholdFilterer;
//---------------------------------------------------------------------------
__fastcall TFormThresholdFilterer::TFormThresholdFilterer(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormThresholdFilterer::ButtonLoadClick(TObject *Sender)
{
  if (OpenDialog1->Execute() == false) return;

  ImageOriginal->Picture->LoadFromFile(OpenDialog1->FileName);

  if (ImageResult->Picture->Bitmap->PixelFormat != pf24bit)
  {
    TrackBarThreshold->Enabled = false;
    ButtonSave->Enabled = false;
    ImageResult->Visible = false;
    ImageOriginal->Visible = false;
    CheckBoxColor->Enabled = false;
    ShowMessage("Bitmap must be 24 bit");
  }

  CheckBoxColor->Enabled = true;
  ImageOriginal->Visible = true;
  TrackBarThreshold->Enabled = true;
  TrackBarThresholdChange(0);
  ButtonSave->Enabled = true;
  SaveDialog1->FileName = OpenDialog1->FileName;
  ImageResult->Visible = true;
  ++PageControl->ActivePageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFormThresholdFilterer::TrackBarThresholdChange(
      TObject *Sender)
{
  if (CheckBoxColor->Checked == true)
  {
    ThresholdFilterColor(ImageOriginal,TrackBarThreshold->Position, ImageResult);
  }
  else
  {
    ThresholdFilterNoColor(ImageOriginal,TrackBarThreshold->Position, ImageResult);
  }
  ImageResult->Refresh();

  TrackBarThreshold->Hint
    = String(TrackBarThreshold->Position)
    + String("/")
    + String(TrackBarThreshold->Max);
}
//---------------------------------------------------------------------------
void __fastcall TFormThresholdFilterer::ButtonSaveClick(TObject *Sender)
{
  if (SaveDialog1->Execute() == false) return;
  ImageResult->Picture->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormThresholdFilterer::CheckBoxColorClick(TObject *Sender)
{
  TrackBarThresholdChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormThresholdFilterer::ButtonAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormThresholdFiltererAbout> form (new TFormThresholdFiltererAbout(0));
  form->ShowModal();
}
//---------------------------------------------------------------------------
//If a pixel's grey value is below threshold, the pixel is made black
//Else it keeps it color
//From http://www.richelbilderbeek.nl/CppThresholdFilter.htm
void ThresholdFilterColor(
  const TImage * const imageOriginal,
  const int threshold,
  const TImage * const imageResult)
{
  assert(imageOriginal!=0
    && "imageOriginal must not be NULL");
  assert(imageOriginal->Picture !=0
    && "Picture of imageOriginal must not be NULL");
  assert(imageOriginal->Picture->Bitmap !=0
    && "Bitmap of imageOriginal must not be NULL");
  assert(imageOriginal->Picture->Bitmap->PixelFormat == pf24bit
    && "Bitmap of imageOriginal must be 24 bit");
  assert(imageResult!=0
    && "imageResult must not be NULL");
  assert(imageResult->Picture !=0
    && "Picture of imageResult must not be NULL");
  assert(imageResult->Picture->Bitmap !=0
    && "Bitmap of imageResult must not be NULL");
  assert(imageResult->Picture->Bitmap->PixelFormat == pf24bit
    && "Bitmap of imageResult must be 24 bit");
  assert(threshold >= 0 && threshold < 256
    && "Threshold must be in range [0,255]");

  const int width  = imageOriginal->Picture->Bitmap->Width;
  const int height = imageOriginal->Picture->Bitmap->Height;
  imageResult->Picture->Bitmap->Width  = width;
  imageResult->Picture->Bitmap->Height = height;


  for (int y=0; y!=height; ++y)
  {
    const unsigned char * const lineOriginal
      = static_cast<unsigned char *>(imageOriginal->Picture->Bitmap->ScanLine[y]);
    unsigned char * const lineResult
      = static_cast<unsigned char *>(imageResult->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const int grey
        = (lineOriginal[x*3+2] + lineOriginal[x*3+1] + lineOriginal[x*3+0]) / 3;
      if (grey < threshold)
      {
        lineResult[x*3+2] = 0; //Red
        lineResult[x*3+1] = 0; //Green
        lineResult[x*3+0] = 0; //Blue
      }
      else
      {
        lineResult[x*3+2] = lineOriginal[x*3+2]; //Red
        lineResult[x*3+1] = lineOriginal[x*3+1]; //Green
        lineResult[x*3+0] = lineOriginal[x*3+0]; //Blue
      }
    }
  }
}
//---------------------------------------------------------------------------
//If a pixel's grey value is below threshold, the pixel is made black
//Else it is made white
//From http://www.richelbilderbeek.nl/CppThresholdFilter.htm
void ThresholdFilterNoColor(
  const TImage * const imageOriginal,
  const int threshold,
  const TImage * const imageResult)
{
  assert(imageOriginal!=0
    && "imageOriginal must not be NULL");
  assert(imageOriginal->Picture !=0
    && "Picture of imageOriginal must not be NULL");
  assert(imageOriginal->Picture->Bitmap !=0
    && "Bitmap of imageOriginal must not be NULL");
  assert(imageOriginal->Picture->Bitmap->PixelFormat == pf24bit
    && "Bitmap of imageOriginal must be 24 bit");
  assert(imageResult!=0
    && "imageResult must not be NULL");
  assert(imageResult->Picture !=0
    && "Picture of imageResult must not be NULL");
  assert(imageResult->Picture->Bitmap !=0
    && "Bitmap of imageResult must not be NULL");
  assert(imageResult->Picture->Bitmap->PixelFormat == pf24bit
    && "Bitmap of imageResult must be 24 bit");
  assert(threshold >= 0 && threshold < 256
    && "Threshold must be in range [0,255]");

  const int width  = imageOriginal->Picture->Bitmap->Width;
  const int height = imageOriginal->Picture->Bitmap->Height;
  imageResult->Picture->Bitmap->Width  = width;
  imageResult->Picture->Bitmap->Height = height;


  for (int y=0; y!=height; ++y)
  {
    const unsigned char * const lineOriginal
      = static_cast<unsigned char *>(imageOriginal->Picture->Bitmap->ScanLine[y]);
    unsigned char * const lineResult
      = static_cast<unsigned char *>(imageResult->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const int grey
        = (lineOriginal[x*3+2] + lineOriginal[x*3+1] + lineOriginal[x*3+0]) / 3;
      if (grey < threshold)
      {
        lineResult[x*3+2] = 0; //Red
        lineResult[x*3+1] = 0; //Green
        lineResult[x*3+0] = 0; //Blue
      }
      else
      {
        lineResult[x*3+2] = 255; //Red
        lineResult[x*3+1] = 255; //Green
        lineResult[x*3+0] = 255; //Blue
      }
    }
  }
}
//---------------------------------------------------------------------------

