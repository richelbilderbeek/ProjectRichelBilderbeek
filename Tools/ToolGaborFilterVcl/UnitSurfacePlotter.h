//---------------------------------------------------------------------------
#ifndef UnitSurfacePlotterH
#define UnitSurfacePlotterH
//---------------------------------------------------------------------------
/*
  SurfacePlotter, class to plot a 2D std::vector
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
#include <vector>
#include <algorithm>
#include <cassert>

#include <Graphics.hpp> //VCL specific
#include <ExtCtrls.hpp> //VCL specific
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
struct SurfacePlotter
{
  SurfacePlotter(Extctrls::TImage * const image)
  : mImage(image)
  {
    assert(mImage);
    assert(mImage->Picture->Bitmap!=0);
    assert(mImage->Picture->Bitmap->PixelFormat == pf24bit);
  }
  //Sets the image of the surface plot to the values of the vector
  //The doubles can be in any range
  void SetSurfaceGrey(const std::vector<std::vector<double> >& surface)
  {
    //Get the size
    const int maxx = surface.size();
    const int maxy = surface[0].size();
    //Resize Image to the correct size
    mImage->Picture->Bitmap->Width  = maxx;
    mImage->Picture->Bitmap->Height = maxy;
    //Minimum and maximum are not given, so these need to be calculated
    double minVal = *(std::min_element(surface[0].begin(),surface[0].end()));
    double maxVal = *(std::max_element(surface[0].begin(),surface[0].end()));
    for (int x=1; x!=maxx; ++x) //1, because 0 gets know the lines above
    {
      const double localMinVal = *(std::min_element(surface[x].begin(),surface[x].end()));
      const double localMaxVal = *(std::max_element(surface[x].begin(),surface[x].end()));
      if (localMinVal < minVal) minVal = localMinVal;
      if (localMaxVal > maxVal) maxVal = localMaxVal;
    }
    if (minVal == maxVal)
    {
      //Draw black
      for (int y=0; y!=maxy; ++y)
      {
        unsigned char * const line
          = static_cast<unsigned char *>(mImage->Picture->Bitmap->ScanLine[y]);
        for (int x=0; x!=maxx; ++x)
        {
          line[x*3+0] = 0; //Blue
          line[x*3+1] = 0; //Green
          line[x*3+2] = 0; //Red
        }
      }
      return;
    }

    //Draw the pixels
    for (int y=0; y!=maxy; ++y)
    {
      unsigned char * const line
        = static_cast<unsigned char *>(mImage->Picture->Bitmap->ScanLine[y]);
      for (int x=0; x!=maxx; ++x)
      {
        assert(minVal != maxVal);
        assert(minVal < maxVal);
        const double greyValueDouble = (surface[x][y] - minVal) / (maxVal - minVal);
        assert(greyValueDouble >= 0.0 && greyValueDouble <= 1.0);
        const char greyValue = greyValueDouble * 255.0;
        line[x*3+0] = greyValue; //Blue
        line[x*3+1] = greyValue; //Green
        line[x*3+2] = greyValue; //Red
      }
    }
  }
  //Sets the image of the surface plot to the values of the vector
  //Assumes that the chars are in the range [0,255] (a char's range)
  //If the chars are in a shorter range, they will NOT be rescaled to [0,255]
  void SetSurfaceGrey(const std::vector<std::vector<char> >& surface)
  {
    const int maxx = surface.size();
    const int maxy = surface[0].size();
    mImage->Picture->Bitmap->Width = maxx;
    mImage->Picture->Bitmap->Height = maxy;

    for (int y=0; y!=maxy; ++y)
    {
      unsigned char * const line
        = static_cast<unsigned char *>(mImage->Picture->Bitmap->ScanLine[y]);
      for (int x=0; x!=maxx; ++x)
      {
        const char greyValue = surface[x][y];
        line[x*3+0] = greyValue; //Blue
        line[x*3+1] = greyValue; //Green
        line[x*3+2] = greyValue; //Red
      }
    }
  }
  private:
  Extctrls::TImage * const mImage;
};
//---------------------------------------------------------------------------
#endif
