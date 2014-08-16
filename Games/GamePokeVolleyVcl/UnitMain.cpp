//---------------------------------------------------------------------------
/*
 *  PokeVolley. A simple game.
 *  Copyright (C) 2005  Richel Bilderbeek
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
// The program was created at the 24th of September of 2005
// The program can be downloaded at http://www.richelbilderbeek.nl
// The author's e-mail adress can be found at http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "UnitMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
#include <algorithm>
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner), mBigImages(false)
{
  //List of keys that are/aren't pressed
  mKeyA = false;
  mKeyD = false;
  mKeyW = false;
  mKeyLeft = false;
  mKeyRight = false;
  mKeyUp = false;
  mScoreLeft = 0;
  mScoreRight = 0;

  BackGround->Picture->LoadFromFile("BeachSmall.bmp");
  Buffer->Picture->LoadFromFile("BeachSmall.bmp");


  if (mBigImages==true)
  { //Big images
    PlayerLeft->Picture->LoadFromFile("SquirtleStaandLinks.bmp");
    PlayerRight->Picture->LoadFromFile("SquirtleStaandRechts.bmp");
    Ball->Picture->LoadFromFile("Pokeball.bmp");
  }
  else
  { //Small images
    PlayerLeft->Picture->LoadFromFile("SquirtleLeftSmall.bmp");
    PlayerRight->Picture->LoadFromFile("SquirtleRightSmall.bmp");
    Ball->Picture->LoadFromFile("PokeballSmall.bmp");
  }

  //Fill Basket ImageLists
  //Left Basket
  BasketLeft->Picture->LoadFromFile("GhastlyLeft1.bmp");
  ImageListBasketLeft->Width = BasketLeft->Width;
  ImageListBasketLeft->Height = BasketLeft->Height;
  ImageListBasketLeft->AddMasked(BasketLeft->Picture->Bitmap,clLime);
  BasketLeft->Picture->LoadFromFile("GhastlyLeft2.bmp");
  ImageListBasketLeft->AddMasked(BasketLeft->Picture->Bitmap,clLime);
  //Right Basket
  BasketRight->Picture->LoadFromFile("GhastlyRight1.bmp");
  ImageListBasketRight->Width = BasketRight->Width;
  ImageListBasketRight->Height = BasketRight->Height;
  ImageListBasketRight->AddMasked(BasketRight->Picture->Bitmap,clLime);
  BasketRight->Picture->LoadFromFile("GhastlyRight2.bmp");
  ImageListBasketRight->AddMasked(BasketRight->Picture->Bitmap,clLime);


  mPlayerLeftJumps = false;
  mPlayerRightJumps = false;
  mPlayerLeftX = 0;
  mPlayerLeftY = ClientHeight - PlayerLeft->Height;
  mPlayerRightX = ClientWidth - PlayerRight->Width;
  mPlayerRightY = ClientHeight - PlayerRight->Height;
  mPlayerLeftSpeedY = 0.0;
  mPlayerRightSpeedY = 0.0;

  resetCoordinats();



}
//---------------------------------------------------------------------------
void TFormMain::resetCoordinats()
{
  //Set coordinats
  mBallX = (ClientWidth / 2) - (Ball->Width / 2);
  mBallY = 0.0;
  mBallSpeedX = (static_cast<double>(rand()%100)/10.0)-5.0;
  mBallSpeedY = 0.0;

  BasketLeft->Left = 0;
  BasketLeft->Top = (ClientHeight / 2) - (BasketLeft->Height / 2);
  BasketRight->Left = ClientWidth - BasketRight->Width;
  BasketRight->Top = (ClientHeight / 2) - (BasketRight->Height / 2);

<<<<<<< HEAD
  Caption = "PokeVolley, Copyright (C) 2006 Richèl Bilderbeek: " + IntToStr(mScoreLeft) + " : " + IntToStr(mScoreRight);
=======
  Caption = "PokeVolley, Copyright (C) 2006 Richel Bilderbeek: " + IntToStr(mScoreLeft) + " : " + IntToStr(mScoreRight);
>>>>>>> develop
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch(Key)
  {
    case 65: //A: Left
      mKeyA = true; mKeyD = false; break;
    case 87: //W: Up
      mKeyW = true; mKeyS = false; break;
    case 68: //D: Right
      mKeyD = true; mKeyA = false; break;
    case 83: //S: Down
      mKeyS = true; mKeyW = false; break;
    case VK_LEFT:
      mKeyLeft = true; mKeyRight = false; break;
    case VK_UP:
      mKeyUp = true; mKeyDown = false; break;
    case VK_RIGHT:
      mKeyRight = true; mKeyLeft = false; break;
    case VK_DOWN:
      mKeyDown = true; mKeyUp = false; break;
  }
}
//---------------------------------------------------------------------------
void TFormMain::processKeys()
{
  if (mKeyA == true)
  {
    mPlayerLeftSpeedX -= 1.0;
  }
  if (mKeyD == true)
  {
    mPlayerLeftSpeedX += 1.0;
  }
  if (mKeyW == true)
  {
    if (mPlayerLeftJumps==false)
    {
      mPlayerLeftJumps = true;
      PlayerLeft->Picture->LoadFromFile("SquirtleLeftSmallJump.bmp");

      mPlayerLeftY -=50;
      mPlayerLeftSpeedY = -20.0;
    }
  }
  if (mKeyS == true)
  {
    if (mPlayerLeftJumps==true) mPlayerLeftSpeedY += 0.5;
  }
  if (mKeyLeft == true)
  {
    mPlayerRightSpeedX -= 1.0;
  }
  if (mKeyRight == true)
  {
    mPlayerRightSpeedX += 1.0;
  }
  if (mKeyUp == true)
  {
    if (mPlayerRightJumps==false)
    {
      mPlayerRightJumps = true;
      PlayerRight->Picture->LoadFromFile("SquirtleRightSmallJump.bmp");
      mPlayerRightY -=50;
      mPlayerRightSpeedY = -20.0;
    }
  }
  if (mKeyDown == true)
  {
    if (mPlayerRightJumps==true) mPlayerRightSpeedY += 0.5;
  }


}
//---------------------------------------------------------------------------
void TFormMain::moveBall()
{
  mBallX += mBallSpeedX;
  mBallY += mBallSpeedY;
  mBallSpeedY += 0.5;

  if (mBallX < 0)
  {
    mBallSpeedX = -mBallSpeedX;
    mBallX = 0.0;
  }
  if (mBallY < 0)
  {
    mBallSpeedY = -mBallSpeedY;
    mBallY = 0.0;
  }
  if (mBallX + Ball->Width > ClientWidth)
  {
    mBallSpeedX = -mBallSpeedX;
    mBallX = ClientWidth - Ball->Width;
  }
  if (mBallY + Ball->Height > ClientHeight)
  {
    mBallSpeedY = -mBallSpeedY;
    mBallY = ClientHeight - Ball->Height;
  }

  Ball->Left = mBallX;
  Ball->Top = mBallY;
}
//---------------------------------------------------------------------------
void TFormMain::movePlayers()
{
  //Friction
  mPlayerLeftSpeedX *=0.95;
  mPlayerRightSpeedX *=0.95;

  //Gravity
  if (mPlayerLeftJumps == true) mPlayerLeftSpeedY +=0.5;
  if (mPlayerRightJumps == true) mPlayerRightSpeedY +=0.5;

  mPlayerLeftX  += mPlayerLeftSpeedX;
  mPlayerRightX += mPlayerRightSpeedX;
  mPlayerLeftY  += mPlayerLeftSpeedY;
  mPlayerRightY += mPlayerRightSpeedY;

  if (mPlayerLeftX < 0)
  {  //Player left leaves screen on left side
    mPlayerLeftX = 0;
    mPlayerLeftSpeedX = ( mPlayerLeftSpeedX < 0 ? -mPlayerLeftSpeedX : mPlayerLeftSpeedX);
  }

  if (mPlayerRightX < 0)
  {  //Player right leaves screen on left side
    mPlayerRightX = 0;
    mPlayerRightSpeedX = ( mPlayerRightSpeedX < 0 ? -mPlayerRightSpeedX : mPlayerRightSpeedX);
  }

  if (mPlayerLeftX + PlayerLeft->Width > ClientWidth)
  {  //Player left leaves screen on right side
    mPlayerLeftX = ClientWidth - PlayerLeft->Width;
    mPlayerLeftSpeedX = ( mPlayerLeftSpeedX > 0 ? -mPlayerLeftSpeedX : mPlayerLeftSpeedX);
  }

  if (mPlayerRightX + PlayerRight->Width > ClientWidth)
  {  //Player right leaves screen on right side
    mPlayerRightX = ClientWidth - PlayerRight->Width;
    mPlayerRightSpeedX = ( mPlayerRightSpeedX > 0 ? -mPlayerRightSpeedX : mPlayerRightSpeedX);
  }


  if (mPlayerLeftY < 0)
  { //Player left leaves screen with head
    mPlayerLeftSpeedY = -mPlayerLeftSpeedY;
    mPlayerLeftY = 0.0;
  }
  if (mPlayerRightY < 0)
  { //Player right leaves screen with head
    mPlayerRightSpeedY = -mPlayerRightSpeedY;
    mPlayerRightY = 0.0;
  }
  if (mPlayerLeftY + PlayerLeft->Height > ClientHeight)
  { //Player left leaves screen with feet
    mPlayerLeftSpeedY = 0.0;
    mPlayerLeftJumps = false;
    PlayerLeft->Picture->LoadFromFile("SquirtleLeftSmall.bmp");
    mPlayerLeftY = ClientHeight - PlayerLeft->Height;
  }
  if (mPlayerRightY + PlayerRight->Height > ClientHeight)
  { //Player right leaves screen with feet
    mPlayerRightSpeedY = 0.0;
    mPlayerRightJumps = false;
    PlayerRight->Picture->LoadFromFile("SquirtleRightSmall.bmp");
    mPlayerRightY = ClientHeight - PlayerRight->Height;
  }

  PlayerLeft->Left  = mPlayerLeftX;
  PlayerRight->Left = mPlayerRightX;
  PlayerLeft->Top  = mPlayerLeftY;
  PlayerRight->Top = mPlayerRightY;

}
//---------------------------------------------------------------------------
void TFormMain::detectCollision()
{
  TRect rect;

  //Check collision of player left and ball
  IntersectRect(rect,Ball->BoundsRect, PlayerLeft->BoundsRect);
  if (IsRectEmpty(rect)==false)
  {
    //Change the direction
    if (rect.Width() > rect.Height())
    { //Vertical collision
      if (mPlayerLeftSpeedY==0.0)
      { //Bounce on head
        mBallSpeedY = -mBallSpeedY;
      }
      else
      {
        std::swap(mBallSpeedY,mPlayerLeftSpeedY);

      }
      //Bounce ball
      //mBallSpeedY = -mBallSpeedY;
      mBallSpeedX += random(3)-1;
      //Bounce player
      //mPlayerLeftSpeedY = -mPlayerLeftSpeedY;
    }
    else
    { //Horizontal collision
      std::swap(mBallSpeedX,mPlayerLeftSpeedX);
      if (mBallSpeedX > 0 && mPlayerLeftSpeedX > 0) mPlayerLeftSpeedX = -mPlayerLeftSpeedX;
      if (mBallSpeedX < 0 && mPlayerLeftSpeedX < 0) mPlayerLeftSpeedX = -mPlayerLeftSpeedX;
      //Bounce ball
      //mBallSpeedX = -mBallSpeedX;
      mBallSpeedY += random(3)-1;
      //Push player
      PlayerLeft->Left += ( Ball->Left < PlayerLeft->Left ? 10 : -10);
    }
    //Move the ball
    mBallX += mBallSpeedX; mBallY += mBallSpeedY;
  }

  //Check collision of player right and ball
  IntersectRect(rect,Ball->BoundsRect, PlayerRight->BoundsRect);
  if (IsRectEmpty(rect)==false)
  {
    //Change the direction
    if (rect.Width() > rect.Height())
    { //Vertical collision
      if (mPlayerRightSpeedY==0.0)
      { //Bounce on head
        mBallSpeedY = -mBallSpeedY;
      }
      else
      {
        std::swap(mBallSpeedY,mPlayerRightSpeedY);
      }
      //mBallSpeedY = -mBallSpeedY;
      mBallSpeedX += random(3)-1;
      //Bounce player
      //mPlayerRightSpeedY = -mPlayerRightSpeedY;
    }
    else
    { //Horizonal collision
      std::swap(mBallSpeedX,mPlayerRightSpeedX);
      if (mBallSpeedX > 0 && mPlayerRightSpeedX > 0) mPlayerRightSpeedX = -mPlayerRightSpeedX;
      if (mBallSpeedX < 0 && mPlayerRightSpeedX < 0) mPlayerRightSpeedX = -mPlayerRightSpeedX;
      //mBallSpeedX = -mBallSpeedX;
      mBallSpeedY += random(3)-1;
      //Push the player
      PlayerRight->Left += ( Ball->Left < PlayerRight->Left ? 10 : -10);
    }
    //Move the ball
    mBallX += mBallSpeedX; mBallY += mBallSpeedY;
  }

  //Check collision of basket left and ball
  IntersectRect(rect,BasketLeft->BoundsRect, Ball->BoundsRect);
  if (IsRectEmpty(rect)==false)
  { //Right player has scored
    ++mScoreRight;
    resetCoordinats();
  }
  IntersectRect(rect,BasketRight->BoundsRect, Ball->BoundsRect);
  if (IsRectEmpty(rect)==false)
  { //Right player has scored
    ++mScoreLeft;
    resetCoordinats();
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch(Key)
  {
    case 65: mKeyA = false; break;
    case 68: mKeyD = false; break;
    case 83: mKeyS = false; break;
    case 87: mKeyW = false; break;
    case VK_LEFT: mKeyLeft = false; break;
    case VK_RIGHT: mKeyRight = false; break;
    case VK_UP: mKeyUp = false; break;
    case VK_DOWN: mKeyDown = false; break;
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Timer1Timer(TObject *Sender)
{
  moveBall();
  processKeys();
  movePlayers();
  detectCollision();

  //Draw BackGround on Buffer
  Buffer->Canvas->Draw(0,0,BackGround->Picture->Graphic);
  //Draw Baskets on Buffer
  ImageListBasketLeft->Draw(Buffer->Canvas,BasketLeft->Left,BasketLeft->Top,rand()%2,true);
  ImageListBasketRight->Draw(Buffer->Canvas,BasketRight->Left,BasketRight->Top,rand()%2,true);
  //Draw Squirtles and ball on Buffer
  Buffer->Canvas->Draw(PlayerLeft->Left, PlayerLeft->Top,PlayerLeft->Picture->Graphic);
  Buffer->Canvas->Draw(PlayerRight->Left, PlayerRight->Top,PlayerRight->Picture->Graphic);
  Buffer->Canvas->Draw(Ball->Left, Ball->Top, Ball->Picture->Graphic);
  //Draw Buffer on Form
  Canvas->Draw(0,0,Buffer->Picture->Graphic);
        
}
//---------------------------------------------------------------------------


