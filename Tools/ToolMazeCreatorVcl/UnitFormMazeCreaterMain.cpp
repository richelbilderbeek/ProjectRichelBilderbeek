//---------------------------------------------------------------------------
/*
  Maze Creater, creates a maze and displays it on screen
  Copyright (C) 2007  Richel Bilderbeek

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
#include <ctime>
#include <cassert>
#include <vector>
#include <memory>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormMazeCreaterMain.h"
#include "UnitMazeCreater.h"
#include "UnitFormMazeCreaterAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMazeCreaterMain *FormMazeCreaterMain;
//---------------------------------------------------------------------------
__fastcall TFormMazeCreaterMain::TFormMazeCreaterMain(TComponent* Owner)
        : TForm(Owner)
{
  const int size = 33;
  std::srand( std::clock() );

  ImageBackground->Picture->Bitmap->Width  = size;
  ImageBackground->Picture->Bitmap->Height = size;

  const std::vector<std::vector<int> > maze = CreateMaze(size);
  assert(maze.size() == size);
  assert(maze[0].size() == size);

  for (int y=0; y!=size; ++y)
  {
    for (int x=0; x!=size; ++x)
    {
      switch(maze[x][y])
      {
        case 0: //Road
          SetPixel(ImageBackground,x,y,255,255,255);
          break;
        case 1: //Wall
          SetPixel(ImageBackground,x,y,0,0,0);
          break;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMazeCreaterMain::OnAnyClick(TObject *Sender)
{
  //
  std::auto_ptr<TFormMazeCreaterAbout> f(new TFormMazeCreaterAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
void GetPixel(
  const TImage * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue)
{
  assert(image!=0 && "Image is NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert( x >= 0 && "x coordinat is below zero");
  assert( y >= 0 && "y coordinat is below zero");
  assert( x < image->Picture->Bitmap->Width  && "x coordinat is beyond image width");
  assert( y < image->Picture->Bitmap->Height && "y coordinat is beyond image height");
  red   = (static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+2]);
  green = (static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+1]);
  blue  = (static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+0]);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppSetPixel.htm
void SetPixel(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  assert(image!=0 && "Image is NULL");
  assert(image->Picture->Bitmap!=0 && "Bitmap is NULL");
  assert(image->Picture->Bitmap->PixelFormat == pf24bit && "Bitmap must be 24 bit");
  assert( x >= 0 && "x coordinat is below zero");
  assert( y >= 0 && "y coordinat is below zero");
  assert( x < image->Picture->Bitmap->Width  && "x coordinat is beyond image width");
  assert( y < image->Picture->Bitmap->Height && "y coordinat is beyond image height");

  static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+2] = red;
  static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+1] = green;
  static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y])[x*3+0] = blue;
}
//---------------------------------------------------------------------------
