//---------------------------------------------------------------------------
/*
  HistogramEqualizationer, tool to perform a histogram equalization
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
//From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <cassert>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormHistogramEqualizationer.h"
#include "UnitFormHistogramEqualizationerAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormHistogramEqualizationer *FormHistogramEqualizationer;
//---------------------------------------------------------------------------
__fastcall TFormHistogramEqualizationer::TFormHistogramEqualizationer(TComponent* Owner)
        : TForm(Owner)
{
  ImageOriginal->Stretch = false;
  ImageGrey->Stretch = false;
  ImageResult->Stretch = false;
  ImageOriginal->AutoSize = true;
  ImageGrey->AutoSize = true;
  ImageResult->AutoSize = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormHistogramEqualizationer::ButtonLoadClick(TObject *Sender)
{
  if (OpenDialog1->Execute() == false) return;

  ImageOriginal->Picture->LoadFromFile(OpenDialog1->FileName);

  if(ImageOriginal==0 || ImageOriginal->Picture->Bitmap==0)
  {
     ShowMessage("Unable to load image");
     return;
  }
  if (ImageOriginal->Picture->Bitmap->PixelFormat != pf24bit)
  {
     ShowMessage("Image must be a 24-bit bitmap. Please load another image");
     return;
  }


  DoHistogramEqualization(ImageOriginal,ImageResult);
  ConvertToGrey(ImageOriginal,ImageGrey);
  ImageOriginal->Visible = true;
  ImageGrey->Visible = true;
  ImageResult->Visible = true;
  ButtonSaveGrey->Visible = true;
  ButtonSaveResult->Visible = true;
  ++PageControl1->ActivePageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFormHistogramEqualizationer::ButtonSaveGreyClick(
      TObject *Sender)
{
  if (SaveDialog1->Execute() == false) return;
  ImageGrey->Picture->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormHistogramEqualizationer::ButtonSaveResultClick(
      TObject *Sender)
{
  if (SaveDialog1->Execute() == false) return;
  ImageResult->Picture->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormHistogramEqualizationer::ButtonAboutClick(
      TObject *Sender)
{
  boost::scoped_ptr<TFormHistogramEqualizationerAbout> form(
    new TFormHistogramEqualizationerAbout(0) );

  form->ShowModal();
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDoHistogramEqualization.htm
void DoHistogramEqualization(const TImage * const source, TImage * const target)
{
  assert(source!=0 && "Source image is NULL");
  assert(target!=0 && "Target image is NULL");
  assert(source->Picture->Bitmap!=0 && "Source bitmap is NULL");
  assert(target->Picture->Bitmap!=0 && "Target bitmap is NULL");
  assert(source->Picture->Bitmap->PixelFormat == pf24bit && "Source bitmap must be 24 bit");
  assert(target->Picture->Bitmap->PixelFormat == pf24bit && "Target bitmap must be 24 bit");
  //Get the width and height from the source
  const int width  = source->Picture->Bitmap->Width;
  const int height = source->Picture->Bitmap->Height;
  //Set the target's width and height
  target->Picture->Bitmap->Width  = width;
  target->Picture->Bitmap->Height = height;

  const int surface = width * height;
  const int nGreyValues = 256; //There are 256 different pixel intensities
  const std::vector<int> histogram = GetImageHistogram(source);
  assert(nGreyValues==static_cast<int>(histogram.size()));
  const std::vector<int> cumulativeHistogram = GetCumulativeHistogram(histogram);
  assert(nGreyValues==static_cast<int>(cumulativeHistogram.size()));

  //Works, but anybody knows how to use std::for_each or std::transform for this?
  std::vector<int> rescaledHistogram(nGreyValues,0);
  for (int i=0; i!=nGreyValues; ++i)
  {
    //'surface + 1' to prevent that rescaledGreyValue == 256
    const int rescaledGreyValue
      = static_cast<int>(
          static_cast<double>(nGreyValues)
        * static_cast<double>(cumulativeHistogram[i])
        / static_cast<double>(surface + 1) );
    assert(rescaledGreyValue >= 0);
    assert(rescaledGreyValue < 256);
    rescaledHistogram[i] = rescaledGreyValue;
  }

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * lineSource
      = static_cast<const unsigned char *>(
        source->Picture->Bitmap->ScanLine[y]);
    unsigned char * lineTarget
      = static_cast<unsigned char *>(
        target->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const int greyOriginal
        = (lineSource[x*3+0] + lineSource[x*3+1] + lineSource[x*3+2]) / 3;
      assert(greyOriginal >=   0);
      assert(greyOriginal  < 256);
      const int greyNew = rescaledHistogram[greyOriginal];
      assert(greyNew >= 0);
      assert(greyNew  < 256);

      lineTarget[x*3+0]=greyNew; //Blue
      lineTarget[x*3+1]=greyNew; //Green
      lineTarget[x*3+2]=greyNew; //Red
    }
  }
}
//------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConvertToGrey.htm
void ConvertToGrey(const TImage * const source, TImage * const target)
{
  assert(source!=0 && "Source image is NULL");
  assert(target!=0 && "Target image is NULL");
  assert(source->Picture->Bitmap!=0 && "Source bitmap is NULL");
  assert(target->Picture->Bitmap!=0 && "Target bitmap is NULL");
  assert(source->Picture->Bitmap->PixelFormat == pf24bit && "Source bitmap must be 24 bit");
  assert(target->Picture->Bitmap->PixelFormat == pf24bit && "Target bitmap must be 24 bit");
  //Get the width and height from the source
  const int width  = source->Picture->Bitmap->Width;
  const int height = source->Picture->Bitmap->Height;
  //Set the target's width and height
  target->Picture->Bitmap->Width  = width;
  target->Picture->Bitmap->Height = height;

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * lineSource
      = static_cast<const unsigned char *>(
        source->Picture->Bitmap->ScanLine[y]);
    unsigned char * lineTarget
      = static_cast<unsigned char *>(
        target->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const int grey
        = (lineSource[x*3+0] + lineSource[x*3+1] + lineSource[x*3+2]) / 3;
      assert(grey >= 0 && grey < 256);

      lineTarget[x*3+0]=grey; //Blue
      lineTarget[x*3+1]=grey; //Green
      lineTarget[x*3+2]=grey; //Red
    }
  }
}
//------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetImageHistogram.htm
const std::vector<int> GetImageHistogram(const TImage * const image)
{
  assert(image!=0 && "Image is NULL");
  assert(image->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
  //Get the width and height from the source
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;

  std::vector<int> histogram(256,0); //There are 256 different color values

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * line
      = static_cast<const unsigned char *>(
        image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const int grey
        = (line[x*3+0] + line[x*3+1] + line[x*3+2]) / 3;
      assert(grey >= 0 && grey < 256);
      ++histogram[grey];
    }
  }
  return histogram;
}
//------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetCumulativeHistogram.htm
template <class T> const std::vector<T> GetCumulativeHistogram(const std::vector<T>& histogram)
{
  std::vector<T> v(histogram.begin(),histogram.end() );
  const int size = v.size();
  for (int i=1; i!=size; ++i)
  {
    v[i] += v[i-1];
  }
  return v;
}
//------------------------------------------------------------



