//---------------------------------------------------------------------------
/*
  FilterOperationer, performs filter operations on images
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
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <cassert>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormFilterOperationer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormFilterOperationer *FormFilterOperationer;
//---------------------------------------------------------------------------
__fastcall TFormFilterOperationer::TFormFilterOperationer(TComponent* Owner)
        : TForm(Owner)
{
  //A vertical edge detection filter
  StringGridFilter->Cells[0][0] = -1.0;
  StringGridFilter->Cells[1][0] =  0.0;
  StringGridFilter->Cells[2][0] =  1.0;
  StringGridFilter->Cells[0][1] = -1.0;
  StringGridFilter->Cells[1][1] =  0.0;
  StringGridFilter->Cells[2][1] =  1.0;
  StringGridFilter->Cells[0][2] = -1.0;
  StringGridFilter->Cells[1][2] =  0.0;
  StringGridFilter->Cells[2][2] =  1.0;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::ButtonLoadClick(TObject *Sender)
{
  if (OpenDialog1->Execute()==false) return;
  ImageSource->Picture->LoadFromFile(OpenDialog1->FileName);
  ImageSource->Visible = true;
  OnStringGridFilterChange(0);
  ++PageControl->ActivePageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::OnStringGridFilterChange2(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
  OnStringGridFilterChange(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::OnStringGridFilterChange(
      TObject *Sender)
{
  ButtonDo->Enabled = CanDoFilterOperation(ImageSource, StringGridFilter, ImageTarget);
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::ButtonDoClick(TObject *Sender)
{
  //Check StringGrid for valid strings
  assert(CanDoFilterOperation(ImageSource, StringGridFilter, ImageTarget)==true);

  //Convert StringGrid to std::vector and then the other way round,
  //to clean up the StringGrid after lousy input
  {
    const std::vector<std::vector<double> > v = StringGridToVector<double>(StringGridFilter);
    assert(v.empty()==false);
    const int maxy = v.size();
    assert(maxy>0);
    const int maxx = v[0].size();
    assert(maxx>0);
    for (int y=0; y!=maxy; ++y)
    {
      for (int x=0; x!=maxx; ++x)
      {
        StringGridFilter->Cells[x][y] = v[y][x];
      }
    }
  }

  DoFilterOperation(ImageSource, StringGridFilter, ImageTarget);
  ImageTarget->Visible = true;
  ImageTarget->Refresh();
  ButtonSaveResult->Enabled = true;
  ButtonEnhance->Enabled = true;
  ++PageControl->ActivePageIndex;

}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::ButtonEnhanceClick(TObject *Sender)
{
  ImageEnhanced->Picture->Graphic = ImageTarget->Picture->Graphic;

  #ifndef NDEBUG
    const double averageGreynessOld = GetAverageGreyness(ImageEnhanced);
  #endif

  EnhanceContrast(ImageEnhanced);

  #ifndef NDEBUG
    const double averageGreynessNew = GetAverageGreyness(ImageEnhanced);
    assert( std::fabs(averageGreynessOld - averageGreynessNew) < 1.0 );
  #endif

  ImageEnhanced->Visible = true;
  ImageEnhanced->Refresh();
  ButtonSaveEnhanced->Enabled = true;
  ++PageControl->ActivePageIndex;

}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::ButtonSaveResultClick(TObject *Sender)
{
  if (SaveDialog1->Execute()==false) return;
  ImageTarget->Picture->SaveToFile(SaveDialog1->FileName);
  ShowMessage("Image saved successfully");
  PageControl->ActivePageIndex+=2;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::ItemAddColClick(TObject *Sender)
{
  ++StringGridFilter->ColCount;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::ItemAddRowClick(TObject *Sender)
{
  ++StringGridFilter->RowCount;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::ItemRemoveColClick(TObject *Sender)
{
  if (StringGridFilter->ColCount > 1) --StringGridFilter->ColCount;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::ItemRemoveRowClick(TObject *Sender)
{
  if (StringGridFilter->RowCount > 1) --StringGridFilter->RowCount;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::ButtonSaveEnhancedClick(
      TObject *Sender)
{
  if (SaveDialog1->Execute()==false) return;
  ImageEnhanced->Picture->SaveToFile(SaveDialog1->FileName);
  ShowMessage("Image saved successfully");
  ++PageControl->ActivePageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFormFilterOperationer::PanelAbout3Click(TObject *Sender)
{
  ImageSource->Picture = ImageRichel->Picture;
  ImageSource->Refresh();
  ImageSource->Visible = true;
  ButtonDo->Enabled = true;
  PageControl->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------
const bool CanDoFilterOperation(const TImage * const imageSource,
  const TStringGrid * const stringGridFilter,
  TImage * const imageTarget)
{
  if (imageSource == 0) return false;
  if (imageSource->Picture->Bitmap == 0) return false;
  if (imageSource->Picture->Bitmap->PixelFormat != pf24bit) return false;
  if (stringGridFilter == 0) return false;
  if (imageTarget == 0) return false;
  if (imageTarget->Picture->Bitmap == 0) return false;
  if (imageTarget->Picture->Bitmap->PixelFormat != pf24bit) return false;
  if (stringGridFilter->ColCount < 1) return false;
  if (stringGridFilter->RowCount < 1) return false;
  if (stringGridFilter->ColCount == 1 && stringGridFilter->RowCount == 1) return false;

  if (CanStringGridToVector<double>(stringGridFilter) == false) return false;

  //Does the filter yield a valid filter range?
  const std::vector<std::vector<double> > filter = StringGridToVector<double>(stringGridFilter);
  const std::pair<double,double> filterRange = GetFilterRange(filter);
  if (filterRange.first == filterRange.second) return false;
  return true;
}
//---------------------------------------------------------------------------
void DoFilterOperation(const TImage * const imageSource,
  const TStringGrid * const stringGridFilter,
  TImage * const imageTarget)
{
  assert(imageSource != 0
    && "imageSource must not be NULL");
  assert(imageSource->Picture->Bitmap != 0
    && "imageSource bitmap must not be NULL");
  assert(imageSource->Picture->Bitmap->PixelFormat == pf24bit
    && "imageSource must be a 24-bit bitmap");
  assert(stringGridFilter != 0
    && "stringGridFilter must not be NULL");
  assert(imageTarget != 0
    && "imageTarget must not be NULL");
  assert(imageTarget->Picture->Bitmap != 0
    && "imageSource bitmap must not be NULL");
  assert(imageTarget->Picture->Bitmap->PixelFormat == pf24bit
    && "imageTarget must be a 24-bit bitmap");
  assert(stringGridFilter->ColCount >= 1
    && "stringGridFilter must have at least one collumn");
  assert(stringGridFilter->RowCount >= 1
    && "stringGridFilter must have at least one row");
  assert( (stringGridFilter->ColCount > 1 || stringGridFilter->RowCount > 1)
    && "stringGridFilter must be larger then 1x1 cell");
  assert(CanStringGridToVector<double>(stringGridFilter) == true
    && "stringGridFilter's content must be convertable to doubles");

  const std::vector<std::vector<int> > source = ImageToVector(imageSource);

  const std::vector<std::vector<double> > filter = StringGridToVector<double>(stringGridFilter);

  assert(!source.empty());
  assert(!filter.empty());

  #ifndef NDEBUG
  {
    const std::pair<double,double> filterRange = GetFilterRange(filter);
    assert(filterRange.first != filterRange.second && "Filter must have a valid range");
  }
  #endif

  const std::vector<std::vector<int> > result = DoFilterOperation(source,filter);
  VectorToImage(result,imageTarget);
}
//---------------------------------------------------------------------------
//VCL dependent
//From http://www.richelbilderbeek.nl/CppStringGridToVector.htm
template <class T>
const std::vector<std::vector<T> > StringGridToVector(const TStringGrid * const stringGrid)
{
  assert(CanStringGridToVector<T>(stringGrid)==true);
  assert(stringGrid!=0 && "StringGrid must not be NULL");
  const int height = stringGrid->RowCount;
  const int width  = stringGrid->ColCount;
  std::vector<std::vector<T> > v(height,std::vector<T>(width));
  for (int y=0; y!=height; ++y)
  {
    assert(y >=0);
    assert(y < static_cast<int>(v.size()) );
    std::vector<T>& line = v[y];
    //Don't have the guts to do a line-access on a TStringGrid...

    for (int x=0; x!=width; ++x)
    {
      assert(x >=0);
      assert(x < static_cast<int>(line.size()) );
      //const_cast because the VCL is not const-correct. Grumble, grumble...
      const std::string s = (const_cast<TStringGrid*>(stringGrid)->Cells[x][y]).c_str();
      const T t = LexicalCast<T>(s);
      line[x] = t;
    }
  }
  return v;
}
//---------------------------------------------------------------------------
//VCL dependent
//From http://www.richelbilderbeek.nl/CanStringGridToVector.htm
template <class T>
const bool CanStringGridToVector(const TStringGrid * const stringGrid)
{
  if (stringGrid==0) return false;

  const int height = stringGrid->RowCount;
  const int width  = stringGrid->ColCount;

  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      //const_cast because the VCL is not const-correct. Grumble, grumble...
      const std::string s = (const_cast<TStringGrid*>(stringGrid)->Cells[x][y]).c_str();
      if (CanCast<T>(s) == false) return false;
    }
  }
  return true;
}
//---------------------------------------------------------------------------
void Trace(const std::vector<std::string>& v)
{
  #ifndef NTRACE
    const int size = v.size();
    for (int i=0; i!=size; ++i)
    {
      OutputDebugString( v[i].c_str() );
    }
  #endif
}
//---------------------------------------------------------------------------
void Trace(const std::string& s)
{
  #ifndef NTRACE
    OutputDebugString(s.c_str());
  #endif
}
//---------------------------------------------------------------------------
export template <class T>
void Trace(const std::vector<std::vector<T> >& v)
{
  #ifndef NTRACE
    if (v.empty() == true) { OutputDebugString("{empty}"); return; }
    const int maxy = v.size();
    const int maxx = v[0].size();
    for (int y=0; y!=maxy; ++y)
    {
      const std::vector<T>& vLine = v[y];
      std::string s;
      for (int x=0; x!=maxx; ++x)
      {
        s+=boost::lexical_cast<std::string>(vLine[x]) + std::string(",");
      }
      s.pop_back(); //Remove last comma
      OutputDebugString(s.c_str());
    }
  #endif
}
//---------------------------------------------------------------------------
void Trace(const std::vector<std::vector<int> >& v)
{
  #ifndef NTRACE
    if (v.empty() == true) { OutputDebugString("{empty}"); return; }
    const int maxy = v.size();
    const int maxx = v[0].size();
    for (int y=0; y!=maxy; ++y)
    {
      const std::vector<int>& vLine = v[y];
      std::string s;
      for (int x=0; x!=maxx; ++x)
      {
        s+=boost::lexical_cast<std::string>(static_cast<int>(vLine[x])) + std::string(",");
      }
      s.pop_back(); //Remove last comma
      OutputDebugString(s.c_str());
    }
  #endif
}
//---------------------------------------------------------------------------
//VCL independent
//Creates a 2D-std::vector (y-x-ordered) from a TImage
//From http://www.richelbilderbeek.nl/CppImageToVector.htm
const std::vector<std::vector<int> > ImageToVector(const TImage * const image)
{
  assert(image!=0 && "Image must not be NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap must not be NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");

  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;

  std::vector<std::vector<int> > v(height,std::vector<int>(width));

  for (int y=0; y!=height; ++y)
  {
    assert(y >= 0);
    assert(y < static_cast<int>(v.size()));
    std::vector<int>& vLine = v[y];
    const unsigned char * const line
      = static_cast<const unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      assert(x >= 0);
      assert(x < static_cast<int>(vLine.size()));
      const double grey = static_cast<double>(line[x*3+0] + line[x*3+1] + line[x*3+2])
        / 3.0;
      vLine[x] = grey;
      assert(grey>=0.0 && grey<256.0);
    }
  }
  return v;
}
//---------------------------------------------------------------------------
//VCL independent
//Creates a 2D-std::vector (y-x-ordered) from a TImage
//Draws a (grey) TImage from a 2D-std::vector (y-x-ordered)
//From http://www.richelbilderbeek.nl/CppVectorToImage.htm
void VectorToImage(const std::vector<std::vector<int> >& v, const TImage * const image)
{
  assert(image!=0 && "Image must not be NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap must not be NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");

  const int height = v.size();
  const int width  = v[0].size();

  image->Picture->Bitmap->Height = height;
  image->Picture->Bitmap->Width  = width;

  for (int y=0; y!=height; ++y)
  {
    assert(y >= 0);
    assert(y < static_cast<int>(v.size()));
    const std::vector<int>& vLine = v[y];
    unsigned char * const line
      = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    for (int x=0; x!=width; ++x)
    {
      assert(x >= 0);
      assert(x < static_cast<int>(vLine.size()));
      const int grey = vLine[x];
      line[x*3+2] = grey; //Red
      line[x*3+1] = grey; //Green
      line[x*3+0] = grey; //Blue
    }
  }
}
//---------------------------------------------------------------------------
//Return a y-x-ordered 2D std::vector with the intensitief of grey
//values from range [0,255] (0=black,255=white) after the filter operation
//From http://www.richelbilderbeek.nl/CppDoFilterOperation.htm
const std::vector<std::vector<int> > DoFilterOperation(
  const std::vector<std::vector<int> >& source, //y-x-ordered
  const std::vector<std::vector<double> >& filter) //y-x-ordered
{
  assert(!source.empty());
  assert(!filter.empty());
  const int width = source[0].size();
  const int height = source.size();
  std::vector<std::vector<int> > v(height,std::vector<int>(width));
  const int maxx = source[0].size();
  const int maxy = source.size();
  const int midX = filter[0].size() / 2;
  const int midY = filter.size()    / 2;

  const std::pair<double,double> filterRange = GetFilterRange(filter);
  assert(filterRange.first < filterRange.second);

  for (int y=0; y!=maxy; ++y)
  {
    const int writeY = y;
    assert(writeY >= 0 && writeY < static_cast<int>(v.size()) );
    std::vector<int>& vLine = v[writeY];
    for (int x=0; x!=maxx; ++x)
    {
      //The x and y values are the topleft coordinate of where
      //  the filter will be applied to. This coordinat can be out of
      //  the range, but at least one pixel of where the filter will be
      //  applied to will be in range
      //The pixel value is normalized to the area the
      //  filter operation took place on
      //The outcome of the filter operation is written to
      //  (x + midX, y + midY), which HAS to be in range
      const double unscaledPixelValue = GetFilterOperationPixel(source,x-midX,y-midY,filter);
      //Scale the unscaledPixelValue.
      //The maximal value of unscaledPixelValue is the sum of all positive
      //values in the filter * 255.
      //The minimum value of unscaledPixelValue is the sum of all negative
      //values in the filter * 255.
      //The scaled pixel value must be obtained by transforming the unscaled
      //range [min,max] to [0,256>.
      const double relUnscaledRange
        = (unscaledPixelValue - filterRange.first)
        / (filterRange.second - filterRange.first);
      assert(relUnscaledRange >= 0.0 && relUnscaledRange <= 1.0);
      const double scaledRange = relUnscaledRange * 255;
      assert(scaledRange >= 0.0 && scaledRange < 256.0);
      const int pixel = scaledRange;
      const int writeX = x;
      assert(writeX >= 0 && writeX < width);
      vLine[writeX] = pixel;
    }
  }
  assert(source[0].size()==v[0].size());
  assert(source.size()==v.size());
  return v;
}
//---------------------------------------------------------------------------
//The sourceX and sourceY values are the topleft coordinate of where
//  the filter will be applied to. This coordinat can be out of
//  the range, but at least one pixel of where the filter will be
//  applied to will be in range. If there are no pixels in range,
//  an assertion will fail.
//The pixel value is normalized to the area the
//  filter operation took place on. Therefore, this area must be non-zero
//The outcome of this filter operation will be written to
//  (x + midX, y + midY), which HAS to be in range
//From http://www.richelbilderbeek.nl/CppDoFilterOperation.htm
const double GetFilterOperationPixel(
  const std::vector<std::vector<int> >& source, //y-x-ordered
  const int sourceX,
  const int sourceY,
  const std::vector<std::vector<double> >& filter) //y-x-ordered
{
  assert(!source.empty());
  assert(!filter.empty());
  const int sourceMaxY = source.size();
  const int sourceMaxX = source[0].size();
  const int filterMaxY = filter.size();
  const int filterMaxX = filter[0].size();

  double result = 0.0;
  int nPixels = 0;
  for (int y=0; y!=filterMaxY; ++y)
  {
    const int readY = sourceY + y;
    if ( readY < 0 || readY >= sourceMaxY) continue;
    assert(y >= 0);
    assert(y < static_cast<int>(filter.size()));
    const std::vector<double>& lineFilter = filter[y];
    assert(readY >= 0);
    assert(readY < static_cast<int>(source.size()));
    const std::vector<int>& lineSource = source[readY];
    for (int x=0; x!=filterMaxX; ++x)
    {
      const int readX = sourceX + x;
      if ( readX < 0 || readX >= sourceMaxX) continue;
      assert(x >= 0);
      assert(x < filterMaxX);
      assert(readX >= 0);
      assert(readX < sourceMaxX);
      const double deltaResult = static_cast<double>(lineSource[readX]) * lineFilter[x];
      result += deltaResult;
      ++nPixels;
    }
  }
  assert(nPixels!=0);
  const double filteredValue = result / static_cast<double>(nPixels);
  return filteredValue;

}
//---------------------------------------------------------------------------
//Obtains the range a filter can have
//Assumes the every element has a maximum value of 255
//From http://www.richelbilderbeek.nl/CppDoFilterOperation.htm
const std::pair<double,double> GetFilterRange(const std::vector<std::vector<double> >& filter)
{
  assert(!filter.empty());
  const int maxx = filter[0].size();
  const int maxy = filter.size();
  assert(maxx + maxy > 2 && "Filter size must be bigger then 1x1");
  double min = 0.0;
  double max = 0.0;
  for(int y=0; y!=maxy; ++y)
  {
    assert(y >= 0);
    assert(y  < static_cast<int>(filter.size()) );

    const std::vector<double>& lineFilter = filter[y];
    for(int x=0; x!=maxx; ++x)
    {
      assert(x >= 0);
      assert(x  < static_cast<int>(lineFilter.size()) );

      const double value = lineFilter[x];
      if (value < 0.0) min +=value;
      else if (value > 0.0) max +=value;
    }
  }
  const std::pair<double,double> range
  = std::make_pair(min * 255.0, max * 255.0);
  return range;
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
//From http://www.richelbilderbeek.nl/CppCanCast.htm
template <class TargetType> const bool CanCast(const std::string& from)
{
  std::istringstream i(from);
  TargetType temp;
  return ( (i >> temp) ? true : false );
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
template <>
const int LexicalCast<int>(const std::string& s)
{
  assert(CanCast<int>(s) == true);
  return std::atoi(s.c_str());
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppLexicalCast.htm
template <>
const double LexicalCast<double>(const std::string& s)
{
  assert(CanCast<double>(s) == true);
  return std::atof(s.c_str());
}
//---------------------------------------------------------------------------













