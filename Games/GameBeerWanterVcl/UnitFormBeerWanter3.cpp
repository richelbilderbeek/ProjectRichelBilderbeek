//---------------------------------------------------------------------------
/*
 *  BeerWanter 3. A simple game.
 *  Copyright (C) 2005  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
// This game can be downloaded at http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitFormBeerWanter3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
  speed = 1;
  this->ClientWidth = mScreenWidth;
  this->ClientHeight = mScreenHeight;
  maxTop = Screen->Height - Height;
  maxLeft = Screen->Width - Width;
  ImageBackGround->Picture->Bitmap->Width = mScreenWidth;
  ImageBackGround->Picture->Bitmap->Height = mScreenHeight;
  ImageBuffer->Picture->Bitmap->Width = mScreenWidth;
  ImageBuffer->Picture->Bitmap->Height = mScreenHeight;
  EmptyBitmap(ImageBuffer);
  ImageBeer->Left = random(mScreenWidth-ImageBeer->Width);
  ImageBeer->Top  = random(mScreenHeight-ImageBeer->Height);
  Caption = mCaptionBegin + IntToStr(Tag);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ApplicationEvents1Idle(TObject *Sender,
      bool &Done)
{
  TPoint here = Mouse->CursorPos;
  here.x += random(2*(speed/2)+1)-(speed/2);
  here.y += random(2*(speed/2)+1)-(speed/2);
  Mouse->CursorPos = here;
  int left = Left;
  int top = Top;
  left += random(2*((speed-1)/2)+1)-((speed-1)/2);
  top  += random(2*((speed-1)/2)+1)-((speed-1)/2);
  if (left<0) left=-left;
  if (top<0) top=-top;
  if (left > maxLeft) left=maxLeft - (left-maxLeft);
  if (top > maxTop) top=maxTop - (top-maxTop);
  Left = left;
  Top = top;

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (X > ImageBeer->Left && X < ImageBeer->Left + ImageBeer->Width)
  {
    if (Y > ImageBeer->Top && Y < ImageBeer->Top + ImageBeer->Height)
    {
      //Raak!
    ImageBeer->Left = random(mScreenWidth-ImageBeer->Width);
    ImageBeer->Top  = random(mScreenHeight-ImageBeer->Height);
    ImageBuffer->Canvas->Draw(0,0,ImageBackGround->Picture->Graphic);
    ImageBuffer->Canvas->Draw(ImageBeer->Left,ImageBeer->Top,ImageBeer->Picture->Graphic);
    this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
    ++(this->Tag);
    Caption = mCaptionBegin + IntToStr(Tag);
    ++speed;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormPaint(TObject *Sender)
{
  ImageBuffer->Canvas->Draw(0,0,ImageBackGround->Picture->Graphic);
  ImageBuffer->Canvas->Draw(ImageBeer->Left,ImageBeer->Top,ImageBeer->Picture->Graphic);
  this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);

}
//---------------------------------------------------------------------------
