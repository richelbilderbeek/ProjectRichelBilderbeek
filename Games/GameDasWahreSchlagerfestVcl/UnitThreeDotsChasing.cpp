//---------------------------------------------------------------------------
/*
 *  Das Wahre Schlagerfest. A simple game.
 *  Copyright (C) 2003  Richel Bilderbeek
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
#include <vcl.h>
#pragma hdrstop

#include "UnitThreeDotsChasing.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormThreeDotsChasing *FormThreeDotsChasing;
//---------------------------------------------------------------------------
__fastcall TFormThreeDotsChasing::TFormThreeDotsChasing(TComponent* Owner)
  : TForm(Owner)
{
  points.resize(4);
  std::srand(clock());

  FormResize(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormThreeDotsChasing::ApplicationEvents1Idle(TObject *Sender, bool &Done)
{
  const char nPoints = points.size();
  const short maxy = Image1->Height;
  const short maxx = Image1->Width;
  for (char i=0; i<nPoints; ++i)
  {
    const char other = (i+1)%nPoints;
    assert(other>=0);
    assert(other<nPoints);
    if (points[i].x < points[other].x) ++(points[i].dx);
    else --(points[i].dx);
    if (points[i].y < points[other].y) ++(points[i].dy);
    else --(points[i].dy);
    points[i].x+=points[i].dx;
    if (points[i].x<0)
      { points[i].x=0; points[i].dx = -points[i].dx; }
    else if (points[i].x>=maxx)
      { points[i].x=maxx-1; points[i].dx = -points[i].dx; }
    points[i].y+=points[i].dy;
    if (points[i].y<0)
      { points[i].y=0; points[i].dy = -points[i].dy; }
    else if (points[i].y>=maxy)
      { points[i].y=maxy-1; points[i].dy = -points[i].dy; }
  }

  unsigned char * pLine;
  for (short y=0; y<maxy; ++y)
  {
    pLine=static_cast<unsigned char *>(Image1->Picture->Bitmap->ScanLine[y]);
    for (short x=0; x<maxx; ++x)
    {
      const short indexRedX   = abs(x-points[0].x)%maxx;
      const short indexRedY   = abs(y-points[0].y)%maxy;
      const short indexGreenX = abs(x-points[1].x)%maxx;
      const short indexGreenY = abs(y-points[1].y)%maxy;
      const short indexBlueX  = abs(x-points[2].x)%maxx;
      const short indexBlueY  = abs(y-points[2].y)%maxy;
      assert(indexRedX   >= 0 );
      assert(indexGreenX >= 0 );
      assert(indexBlueX  >= 0 );
      assert(indexRedY   >= 0 );
      assert(indexGreenY >= 0 );
      assert(indexBlueY  >= 0 );
      assert(indexRedX   < this->ClientWidth);
      assert(indexGreenX < this->ClientWidth);
      assert(indexBlueX  < this->ClientWidth);
      assert(indexRedY   < this->ClientHeight);
      assert(indexGreenY < this->ClientHeight);
      assert(indexBlueY  < this->ClientHeight);
      pLine[x*3+0]= distance[indexBlueX ][indexBlueY ]; //Blue
      pLine[x*3+1]= distance[indexGreenX][indexGreenY]; //Green
      pLine[x*3+2]= distance[indexRedX  ][indexRedY  ]; //Red
    }
  }
  this->Canvas->Draw(0,0,Image1->Picture->Graphic);
  Done = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormThreeDotsChasing::FormClick(TObject *Sender)
{
  resetPoints();
}
//---------------------------------------------------------------------------
void TFormThreeDotsChasing::resetPoints()
{
  const short width  = this->ClientWidth;
  const short height = this->ClientHeight;
  const char nPoints = points.size();
  for (int i=0; i<nPoints; ++i)
  {
    points[i].x = std::rand()%width;
    points[i].y = std::rand()%height;
    points[i].dx = (std::rand()%5)-2;
    points[i].dy = (std::rand()%5)-2;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormThreeDotsChasing::FormResize(TObject *Sender)
{
  //Generate vectors for look-up table
  const short width  = this->ClientWidth;
  const short height = this->ClientHeight;

  distance.resize(width);
  for (int i=0; i<width; ++i) distance[i].resize(height);

  for (int x=0; x<width; ++x)
  {
    for (int y=0; y<height; ++y)
    {
      const double xD = static_cast<double>(x);
      const double yD = static_cast<double>(y);
      const double dist = sqrt( (xD*xD) + (yD*yD) );
      distance[x][y] = 255.0 * std::exp(-dist/150.0);
    }
  }
  //Points
  resetPoints();
  //Create image
  Image1->Picture->Bitmap->Width  = width;
  Image1->Picture->Bitmap->Height = height;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
