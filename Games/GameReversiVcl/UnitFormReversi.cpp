//---------------------------------------------------------------------------
/*
    Reversi, a simple board game
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

#include <memory>
#include <cassert>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormReversi.h"
#include "UnitFormAbout.h"
#include "UnitFormRestart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormReversi *FormReversi;
//---------------------------------------------------------------------------
__fastcall TFormReversi::TFormReversi(TComponent* Owner)
        : TForm(Owner), mReversi(8), mPlayer(player1)
{
  OnResize(0);
  SetPixel(ImageRed ,0,0,255,0  ,0  );
  SetPixel(ImageBlue,0,0,0  ,0  ,255);
  SetPixel(ImageRedActive ,0,0,255,0  ,0  );
  SetPixel(ImageBlueActive,0,0,0  ,0  ,255);
  ImageRed->Refresh();
  ImageBlue->Refresh();
  ImageRedActive->Refresh();
  ImageBlueActive->Refresh();

}
//---------------------------------------------------------------------------
void __fastcall TFormReversi::FormResize(TObject *Sender)
{
  const int size = mReversi.GetSize();
  const std::vector<std::vector<Square> >& board = mReversi.GetBoard();
  ImageBoard->Picture->Bitmap->Width  = size;
  ImageBoard->Picture->Bitmap->Height = size;
  for (int y=0; y!=size; ++y)
  {
    for (int x=0; x!=size; ++x)
    {
      const Square s = GetSquareXy(board,x,y);
      switch (s)
      {
        case player1: //Red
          SetPixel(ImageBoard,x,y,((x+y)%2==0?255:224),0,0);
          break;
        case player2: //Blue
          SetPixel(ImageBoard,x,y,0,0,((x+y)%2==0?255:224));
          break;
        case empty: //Empty
          SetPixel(ImageBoard,x,y,0,((x+y)%2==0?16:32),0);
          break;
      }
    }
  }
  ImageBoard->Refresh();
}
//---------------------------------------------------------------------------
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

void __fastcall TFormReversi::ImageBoardMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  //
  const int size   = mReversi.GetSize();
  const int width  = ImageBoard->Width;
  const int height = ImageBoard->Height;
  const double blockWidth  = static_cast<double>(width )
    / static_cast<double>(size);
  const double blockHeight = static_cast<double>(height)
    / static_cast<double>(size);
  const int x = static_cast<int>( static_cast<double>(X) / blockWidth );
  const int y = static_cast<int>( static_cast<double>(Y) / blockHeight);
  assert ( x < size);
  assert ( y < size);

  if (mReversi.IsValidMove(x,y,mPlayer)==true)
  {
    mReversi.DoMove(x,y,mPlayer);

    ImageRedActive->Visible  = !ImageRedActive->Visible;
    ImageBlueActive->Visible = !ImageBlueActive->Visible;
    mPlayer = GetOtherPlayer(mPlayer);

    LabelRed->Caption  = IntToStr(mReversi.Count(player1));
    LabelBlue->Caption = IntToStr(mReversi.Count(player2));
    OnResize(0);
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormReversi::ImageActiveClick(TObject *Sender)
{
  //Pass
  ImageRedActive->Visible  = !ImageRedActive->Visible;
  ImageBlueActive->Visible = !ImageBlueActive->Visible;
  mPlayer = GetOtherPlayer(mPlayer);
}
//---------------------------------------------------------------------------
void __fastcall TFormReversi::LabelRestartClick(TObject *Sender)
{
  std::auto_ptr<TFormRestart> f(new TFormRestart(0));
  f->ShowModal();

  const int result = f->ModalResult;
  if (result == -1) return;
  if (result < 4) mReversi = Reversi(4);
  else mReversi = Reversi(result);

  mPlayer = player1;
  ImageRedActive->Visible  = true;
  ImageBlueActive->Visible = false;
  LabelRed->Caption  = IntToStr(mReversi.Count(player1));
  LabelBlue->Caption = IntToStr(mReversi.Count(player2));
  OnResize(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormReversi::LabelAboutClick(TObject *Sender)
{
  std::auto_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
