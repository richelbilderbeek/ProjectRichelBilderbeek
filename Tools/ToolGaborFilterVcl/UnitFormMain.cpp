//---------------------------------------------------------------------------
/*
  GaborFilter, performs Gabor filter operations on images
  Copyright (C) 2010  Richel Bilderbeek

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
#include <vcl.h>
#pragma hdrstop

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "UnitFormMain.h"
#include "UnitSurfacePlotter.h"
#include "UnitFormWhatsNew.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
  const int sz = 200;
  ImageSource->Picture->Bitmap->Width  = sz;
  ImageSource->Picture->Bitmap->Height = sz;
  //Create test image
  const double midx = static_cast<double>(sz) / 2.0;
  const double midy = static_cast<double>(sz) / 2.0;
  Extctrls::TImage * image = ImageSource;
  for (int y=0; y!=sz; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    const double dy = static_cast<double>(y) - midy;
    for (int x=0; x!=sz; ++x)
    {
      const double dx = static_cast<double>(x) - midx;
      const double distance = std::sqrt( (dx*dx)+(dy*dy) );
      const int grey = (std::sin(distance*0.8) > 0.0 ? 255 : 0);
      assert(grey>=0.0 && grey<256.0);
      line[x*3+2] = grey;
      line[x*3+1] = grey;
      line[x*3+0] = grey;
    }
  }
  image->Refresh();
  OnAnyTrackBarChange(0);  
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonLoadClick(TObject *Sender)
{
  if (OpenDialog1->Execute()==false) return;
  ImageSource->Picture->LoadFromFile(OpenDialog1->FileName);
  OnAnyTrackBarChange(0);
  ++PageControl->ActivePageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonSaveResultClick(TObject *Sender)
{
  if (SaveDialog1->Execute()==false) return;
  ImageTarget->Picture->SaveToFile(SaveDialog1->FileName);
  ShowMessage("Image saved successfully");
  ++PageControl->ActivePageIndex;
}
//---------------------------------------------------------------------------
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
//values from range [MinElement(filter),MaxElement(filter)]
//after the filter operation
//From http://www.richelbilderbeek.nl/CppDoFilterOperation.htm
const std::vector<std::vector<double> > DoFilterOperation(
  const std::vector<std::vector<double> >& source, //y-x-ordered
  const std::vector<std::vector<double> >& filter) //y-x-ordered
{
  assert(!source.empty());
  assert(!filter.empty());
  const int maxx = static_cast<int>(source[0].size());
  const int maxy = static_cast<int>(source.size());
  std::vector<std::vector<double> > v(maxy,std::vector<double>(maxx));
  const int midX = static_cast<int>(filter[0].size()) / 2;
  const int midY = static_cast<int>(filter.size()   ) / 2;

  for (int y=0; y!=maxy; ++y)
  {
    const int writeY = y;
    assert(writeY >= 0 && writeY < static_cast<int>(v.size()) );
    std::vector<double>& vLine = v[writeY];
    for (int x=0; x!=maxx; ++x)
    {
      //The x and y values are the topleft coordinate of where
      //  the filter will be applied to. This coordinat can be out of
      //  the range, but at least one pixel of where the filter will be
      //  applied to will be in range
      //The pixel value is normalized to the area the
      //  filter operation took place on
      vLine[x] = GetFilterOperationPixel(source,x-midX,y-midY,filter);
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
  const std::vector<std::vector<double> >& source, //y-x-ordered
  const int sourceX,
  const int sourceY,
  const std::vector<std::vector<double> >& filter) //y-x-ordered
{
  assert(!source.empty());
  assert(!filter.empty());
  const int sourceMaxY = static_cast<int>(source.size());
  const int sourceMaxX = static_cast<int>(source[0].size());
  const int filterMaxY = static_cast<int>(filter.size());
  const int filterMaxX = static_cast<int>(filter[0].size());

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
    const std::vector<double>& lineSource = source[readY];
    for (int x=0; x!=filterMaxX; ++x)
    {
      const int readX = sourceX + x;
      if ( readX < 0 || readX >= sourceMaxX) continue;
      assert(x >= 0);
      assert(x < filterMaxX);
      assert(readX >= 0);
      assert(readX < sourceMaxX);
      const double deltaResult = lineSource[readX] * lineFilter[x];
      result += deltaResult;
      ++nPixels;
    }
  }
  assert(nPixels!=0);
  const double filteredValue = result / static_cast<double>(nPixels);
  return filteredValue;

}
//---------------------------------------------------------------------------
const std::pair<double,double> GetMinMax(const std::vector<std::vector<double> >& v)
{
  assert(!v.empty());
  const int maxy = static_cast<int>(v.size());
  assert(maxy > 0);
  const int maxx = v[0].size();
  assert(maxx > 0);
  double min = 0.0;
  double max = 0.0;
  for(int y=0; y!=maxy; ++y)
  {
    assert(y >= 0);
    assert(y  < static_cast<int>(v.size()) );

    const std::vector<double>& row = v[y];
    for(int x=0; x!=maxx; ++x)
    {
      assert(x >= 0);
      assert(x  < static_cast<int>(row.size()) );

      const double value = row[x];
      if (value < 0.0) min +=value;
      else if (value > 0.0) max +=value;
    }
  }
  return std::make_pair(min, max);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonDoClick(
      TObject *Sender)
{

  const std::vector<std::vector<int> > source_int = ImageToVector(ImageSource);
  const std::vector<std::vector<double> > source = Convert<int,double>(source_int);
  const std::vector<std::vector<double> > result_unscaled = DoFilterOperation(source,mFilter);
  const std::vector<std::vector<double> > result_scaled = Rescale(result_unscaled,0.0,255.9);
  const std::vector<std::vector<int> > result = Convert<double,int>(result_scaled);
  VectorToImage(result,ImageTarget);
  ImageTarget->Visible = true;
  ImageTarget->Refresh();
  ButtonSaveResult->Enabled = true;
  ++PageControl->ActivePageIndex;
}
//---------------------------------------------------------------------------
#include <cassert>
#include <algorithm>
//From http://www.richelbilderbeek.nl/CppRescale.htm
const double Rescale(
  const double value,
  const double oldMin,
  const double oldMax,
  const double newMin,
  const double newMax)
{
  assert(value >= oldMin);
  assert(value <= oldMax);
  const double oldDistance = oldMax - oldMin;
  //At which relative distance is value on oldMin to oldMax ?
  const double distance = (value - oldMin) / oldDistance;
  assert(distance >= 0.0);
  assert(distance <= 1.0);
  const double newDistance = newMax - newMin;
  const double newValue = newMin + (distance * newDistance);
  assert(newValue >= newMin);
  assert(newValue <= newMax);
  return newValue;
}

//---------------------------------------------------------------------------
#include <cassert>
#include <algorithm>
#include <vector>
//From http://www.richelbilderbeek.nl/CppRescale.htm
const std::vector<double> Rescale(
  std::vector<double> v,
  const double newMin,
  const double newMax)
{
  const double oldMin = *std::min_element(v.begin(),v.end());
  const double oldMax = *std::max_element(v.begin(),v.end());
  typedef std::vector<double>::iterator Iter;
  Iter i = v.begin();
  const Iter j = v.end();
  for ( ; i!=j; ++i)
  {
    *i = Rescale(*i,oldMin,oldMax,newMin,newMax);
  }
  return v;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRescale.htm
const std::vector<std::vector<double> > Rescale(
  std::vector<std::vector<double> > v,
  const double newMin,
  const double newMax)
{
  const double oldMin = MinElement(v);
  const double oldMax = MaxElement(v);
  typedef std::vector<std::vector<double> >::iterator RowIter;
  RowIter y = v.begin();
  const RowIter maxy = v.end();
  for ( ; y!=maxy; ++y)
  {
    typedef std::vector<double>::iterator ColIter;
    ColIter x = y->begin();
    const ColIter maxx = y->end();
    for ( ; x!=maxx; ++x)
    {
      *x = Rescale(*x,oldMin,oldMax,newMin,newMax);
    }
  }
  return v;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::OnAnyTrackBarChange(
      TObject *Sender)
{
  const int sz = TrackBarSize->Position;
  const double angle = 2.0 * M_PI
    * static_cast<double>(TrackBarAngle->Position)
    / static_cast<double>(TrackBarAngle->Max);
  const double wavelength = 16.0
    * static_cast<double>(TrackBarWavelength->Position)
    / static_cast<double>(TrackBarWavelength->Max);
  const double sigma = CalculateSigma(sz/2);
  LabelSize->Caption = "Size: " + IntToStr(sz) + " pixels";
  LabelAngle->Caption = "Angle: " + FloatToStr(angle) + " radians";
  LabelWavelength->Caption = "Wavelength: " + FloatToStr(wavelength) + " pixels";
  LabelSigma->Caption = "Sigma: " + FloatToStr(sigma);

  mFilter = CreateGaborFilter(sz,angle,wavelength,sigma);

  SurfacePlotter p(ImageFilter);
  p.SetSurfaceGrey(mFilter);
  ImageFilter->Refresh();


}
//---------------------------------------------------------------------------
//From http://richelbilderbeek.nl/CppToolGaborFilter.htm
//Returns a y-x-ordered 2D std::vector
//f_Gabor(x)
// = cos(frequency*x)
// * exp(-(x*x)/(sigma*sigma))
const std::vector<std::vector<double> > CreateGaborFilter(
  const int sz,
  const double angle,
  const double wavelength,
  const double sigma)
{
  std::vector<std::vector<double> > v(sz,std::vector<double>(sz,0.0));
  const double midx = static_cast<double>(sz / 2);
  const double midy = static_cast<double>(sz / 2);
  const double frequency = 1.0 / wavelength;
  for (int y=0; y!=sz; ++y)
  {
    for (int x=0; x!=sz; ++x)
    {
      const double dx = midx - static_cast<double>(x);
      const double dy = midy - static_cast<double>(y);
      const double distance = std::sqrt((dx * dx) + (dy * dy));
      const double fx = std::cos(angle) * frequency;
      const double fy = std::sin(angle) * frequency;
      const double cosine = std::cos((dx * fx) + (dy * fy));
      const double gauss = std::exp( -(distance * distance) / (2.0 * sigma * sigma));
      const double z = cosine * gauss;
      v[x][y] = z;
    }
  }
  return v;
}
//---------------------------------------------------------------------------
//From http://richelbilderbeek.nl/CppToolGaborFilter.htm
//Notes:
// - sz is not the total width/height of the filter, it is that
//   value halved
// - std::log takes the natural logarithm
const double CalculateSigma(const int sz)
{
  const double s = static_cast<double>(sz);
  return std::sqrt(-(s * s) / (2.0*std::log(1.0/510.0)));
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonWhatsNewClick(TObject *Sender)
{
  boost::scoped_ptr<TFormWhatsNew> f(new TFormWhatsNew(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

