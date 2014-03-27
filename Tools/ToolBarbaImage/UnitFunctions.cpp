//---------------------------------------------------------------------------
/*
  BarbaImage, tool to perform image manipulations
  Copyright (C) 2008  Richèl Bilderbeek

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
#include <vector>
#include <cassert>
#include <ExtCtrls.hpp>
#pragma hdrstop

#include "UnitFunctions.h"

//---------------------------------------------------------------------------
namespace bikkel //Start of namespace
{
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppAddColoredNoise.htm
void AddColoredNoise(
  const Extctrls::TImage * const source,
  const int max_rand,
  Extctrls::TImage * const target)
{
  if (max_rand == 0) return;
  assert(source!=0 && "Source image is NULL");
  assert(target!=0 && "Target image is NULL");
  assert(source->Picture->Bitmap!=0 && "Source bitmap is NULL");
  assert(target->Picture->Bitmap!=0 && "Target bitmap is NULL");
  assert(source->Picture->Bitmap->PixelFormat == pf24bit && "Source bitmap must be 24 bit");
  assert(target->Picture->Bitmap->PixelFormat == pf24bit && "Target bitmap must be 24 bit");
  assert(max_rand >=   0);
  assert(max_rand  < 256);
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
      const int rand = std::rand() % max_rand;
      const int blue  = (static_cast<int>(lineSource[x*3+0]) + rand) % 256;
      const int green = (static_cast<int>(lineSource[x*3+1]) + rand) % 256;
      const int red   = (static_cast<int>(lineSource[x*3+2]) + rand) % 256;
      assert(red   >=   0);
      assert(red    < 256);
      assert(green >=   0);
      assert(green  < 256);
      assert(blue  >=   0);
      assert(blue   < 256);
      lineTarget[x*3+0]=blue; //Blue
      lineTarget[x*3+1]=green; //Green
      lineTarget[x*3+2]=red; //Red
    }
  }
}
//---------------------------------------------------------------------------
void Bleach(
  const TImage * const imageOriginal,
  const int fraction_of_256,
  TImage * const imageResult)
{
  assert(fraction_of_256 >=   0);
  assert(fraction_of_256 <= 256);
  const double f = static_cast<double>(fraction_of_256) / 256.0;
  Bleach(imageOriginal,f,imageResult);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppBleach.htm
void Bleach(
  const TImage * const source,
  const double f,
  TImage * const target)
{
  assert(f >=  0.0);
  assert(f <=  1.0);
  assert(source!=0 && "Image is NULL");
  assert(source->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(source->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
  assert(target!=0 && "Image is NULL");
  assert(target->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(target->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
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
      const int r = lineSource[x*3+2]; //Red;
      const int g = lineSource[x*3+1]; //Green;
      const int b = lineSource[x*3+0]; //Blue;
      const int max_dist_r = 256 - r;
      const int max_dist_g = 256 - g;
      const int max_dist_b = 256 - b;
      const double dist_r = static_cast<double>(max_dist_r) * f;
      const double dist_g = static_cast<double>(max_dist_g) * f;
      const double dist_b = static_cast<double>(max_dist_b) * f;
      const int new_r = r + static_cast<int>(dist_r);
      const int new_g = g + static_cast<int>(dist_g);
      const int new_b = b + static_cast<int>(dist_b);
      assert(new_r >=   0);
      assert(new_r <  256);
      assert(new_g >=   0);
      assert(new_g <  256);
      assert(new_b >=   0);
      assert(new_b <  256);
      lineTarget[x*3+2] = new_r; //Red
      lineTarget[x*3+1] = new_g; //Green
      lineTarget[x*3+0] = new_b; //Blue
    }
  }

}
//---------------------------------------------------------------------------
void Darken(
  const TImage * const imageOriginal,
  const int fraction_of_256,
  TImage * const imageResult)
{
  assert(fraction_of_256 >=   0);
  assert(fraction_of_256 <= 256);
  const double f = static_cast<double>(fraction_of_256) / 256.0;
  Darken(imageOriginal,f,imageResult);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDarken.htm
void Darken(
  const TImage * const source,
  const double f,
  TImage * const target)
{
  assert(f >=  0.0);
  assert(f <=  1.0);
  assert(source!=0 && "Image is NULL");
  assert(source->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(source->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
  assert(target!=0 && "Image is NULL");
  assert(target->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(target->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
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
      const int r = lineSource[x*3+2]; //Red;
      const int g = lineSource[x*3+1]; //Green;
      const int b = lineSource[x*3+0]; //Blue;
      const double dist_r = static_cast<double>(r) * (1.0-f);
      const double dist_g = static_cast<double>(g) * (1.0-f);
      const double dist_b = static_cast<double>(b) * (1.0-f);
      const int new_r = static_cast<int>(dist_r);
      const int new_g = static_cast<int>(dist_g);
      const int new_b = static_cast<int>(dist_b);
      assert(new_r >=   0);
      assert(new_r <  256);
      assert(new_g >=   0);
      assert(new_g <  256);
      assert(new_b >=   0);
      assert(new_b <  256);
      lineTarget[x*3+2] = new_r; //Red
      lineTarget[x*3+1] = new_g; //Green
      lineTarget[x*3+0] = new_b; //Blue
    }
  }

}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDoHistogramEqualization.htm
void DoHistogramEqualization(
  const Extctrls::TImage * const source,
  Extctrls::TImage * const target)
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppExtractBlue.htm
void ExtractBlue(
  const Extctrls::TImage * const source,
  Extctrls::TImage * const target)
{
  assert(source!=0 && "Image is NULL");
  assert(source->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(source->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
  assert(target!=0 && "Image is NULL");
  assert(target->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(target->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
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
      lineTarget[x*3+0] = lineSource[x*3+0]; //Blue
      lineTarget[x*3+1] = 0; //Green
      lineTarget[x*3+2] = 0; //Red
    }
  }

}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppExtractGreen.htm
void ExtractGreen(
  const Extctrls::TImage * const source,
  Extctrls::TImage * const target)
{
  assert(source!=0 && "Image is NULL");
  assert(source->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(source->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
  assert(target!=0 && "Image is NULL");
  assert(target->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(target->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
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
      lineTarget[x*3+0] = 0; //Blue
      lineTarget[x*3+1] = lineSource[x*3+1]; //Green
      lineTarget[x*3+2] = 0; //Red
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppExtractRed.htm
void ExtractRed(
  const Extctrls::TImage * const source,
  Extctrls::TImage * const target)
{
  assert(source!=0 && "Image is NULL");
  assert(source->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(source->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
  assert(target!=0 && "Image is NULL");
  assert(target->Picture->Bitmap!=0 && "Image bitmap is NULL");
  assert(target->Picture->Bitmap->PixelFormat == pf24bit && "Image bitmap must be 24 bit");
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
      lineTarget[x*3+0] = 0; //Blue
      lineTarget[x*3+1] = 0; //Green
      lineTarget[x*3+2] = lineSource[x*3+2]; //Red
    }
  }

}
//---------------------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetImageHistogram.htm
const std::vector<int> GetImageHistogram(const Extctrls::TImage * const image)
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
      ++histogram[grey];
    }
  }
  return histogram;
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//If a pixel's grey value is below threshold, the pixel is made black
//Else it keeps it color
//From http://www.richelbilderbeek.nl/CppThresholdFilter.htm
void ThresholdFilterColor(
  const TImage * const imageOriginal,
  const int threshold,
  TImage * const imageResult)
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
  TImage * const imageResult)
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
//From http://www.richelbilderbeek.nl/CppEnhanceContrast.htm
void EnhanceContrast(const TImage * const image)
{
  //Find lowest and highest value
  assert(image!=0 && "image must not be NULL");
  assert(image->Picture->Bitmap!=0 && "image bitmap must not be NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "image bitmap must be 24 bit");

  //Get the width and height from the source
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  const double averageGreyness = GetAverageGreyness(image);

  double stretch = 1000.0; //Way too much for nearly all images

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * const line
      = static_cast<const unsigned char *>(
        image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const double grey
        = static_cast<double>(line[x*3+0] + line[x*3+1] + line[x*3+2])
        / 3.0;
      const double diff = grey - averageGreyness;
      if (diff < 0.0)
      {
        //pixel was darker then average
        const double newStretch = -averageGreyness / diff;
        assert(newStretch >= 0.0);
        if (newStretch < stretch) stretch = newStretch;
      }
      else if (diff > 0.0)
      {
        //pixel was lighter then average
        const double newStretch = (255.9 - averageGreyness)  / diff;
        if (newStretch < stretch) stretch = newStretch;
      }
    }
  }

  //Enhance the contrast
  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(
        image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      const double grey
        = static_cast<double>(line[x*3+0] + line[x*3+1] + line[x*3+2])
        / 3.0;
      const double diff = grey - averageGreyness;
      const double diffGreyNew = averageGreyness + (static_cast<double>(diff) * stretch);
      const int newGrey = static_cast<int>(diffGreyNew);
      assert(newGrey >=   0);
      assert(newGrey <  256);
      line[x*3+2] = newGrey; //Red
      line[x*3+1] = newGrey; //Green
      line[x*3+0] = newGrey; //Blue
    }
  }
}
//---------------------------------------------------------------------------
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

      lineTarget[x*3+0]=grey; //Blue
      lineTarget[x*3+1]=grey; //Green
      lineTarget[x*3+2]=grey; //Red
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetAverageGreyness.htm
const double GetAverageGreyness(const TImage * const image)
{
  assert(image!=0 && "image must not be NULL");
  assert(image->Picture->Bitmap!=0 && "image bitmap must not be NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "image bitmap must be 24 bit");

  //Get the width and height from the source
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  double sum = 0.0;

  for (int y=0; y!=height; ++y)
  {
    assert(y >= 0);
    assert(y < image->Picture->Bitmap->Height);
    const unsigned char * line
      = static_cast<const unsigned char *>(
        image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      assert(x >= 0);
      assert(x < image->Picture->Bitmap->Width);
      const double grey
        = static_cast<double>(line[x*3+0] + line[x*3+1] + line[x*3+2])
        / 3.0;
      sum += grey;
    }
  }
  const int surface = width * height;
  assert(surface>0);
  const double average = sum / static_cast<double>(surface);
  assert(average >=    0.0);
  assert(average  <  256.0);
  return average;
}
//---------------------------------------------------------------------------
} //End of namespace bikkel
//---------------------------------------------------------------------------


#pragma package(smart_init)
