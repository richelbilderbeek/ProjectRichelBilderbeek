//---------------------------------------------------------------------------
/*
  PokeVolley, Pokemon volleyball game
<<<<<<< HEAD
  Copyright (C) 2005  Richèl Bilderbeek
=======
  Copyright (C) 2005  Richel Bilderbeek
>>>>>>> develop

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
#include <cassert>
#include "UnitFormMain.h"
#include "UnitFormSprites.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
#include <algorithm>
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner),
  mKeyA(false),
  mKeyD(false),
  mKeyW(false),
  mKeyLeft(false),
  mKeyRight(false),
  mKeyUp(false),
  mScoreLeft(0),
  mScoreRight(0),
  mPlayerLeftJumps(false),
  mPlayerRightJumps(false),
  mPlayerLeftX(0),
  mPlayerLeftY(ClientHeight - ImagePlayer1->Height),
  mPlayerRightX(ClientWidth - ImagePlayer2->Width),
  mPlayerRightY(ClientHeight - ImagePlayer2->Height),
  mPlayerLeftSpeedY(0.0),
  mPlayerRightSpeedY(0.0)
{
  assert(FormSprites);

  //Load all images
  ImageBasket1->Picture = FormSprites->ImageBasket1_0->Picture;
  ImageBasket2->Picture = FormSprites->ImageBasket2_0->Picture;
  ImageBackground->Picture = FormSprites->ImageBackground->Picture;
  ImageBuffer->Picture = FormSprites->ImageBackground->Picture;
  ImagePlayer1->Picture = FormSprites->ImagePlayer1->Picture;
  ImagePlayer2->Picture = FormSprites->ImagePlayer2->Picture;
  ImageBall->Picture = FormSprites->ImageBallR->Picture;

  resetCoordinats();



}
//---------------------------------------------------------------------------
void TFormMain::resetCoordinats()
{
  //Set coordinats
  mBallX = (ClientWidth / 2) - (ImageBall->Width / 2);
  mBallY = 0.0;
  mBallSpeedX = (static_cast<double>(rand()%100)/10.0)-5.0;
  mBallSpeedY = 0.0;

  ImageBasket1->Left = 0;
  ImageBasket1->Top = (ClientHeight / 2) - (ImageBasket1->Height / 2);
  ImageBasket2->Left = ClientWidth - ImageBasket2->Width;
  ImageBasket2->Top = (ClientHeight / 2) - (ImageBasket2->Height / 2);

<<<<<<< HEAD
  Caption = "PokeVolley (C) 2005 Richèl Bilderbeek: " + IntToStr(mScoreLeft) + " : " + IntToStr(mScoreRight);
=======
  Caption = "PokeVolley (C) 2005 Richel Bilderbeek: " + IntToStr(mScoreLeft) + " : " + IntToStr(mScoreRight);
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
      ImagePlayer1->Picture = FormSprites->ImagePlayer1Jump->Picture;
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
      ImagePlayer2->Picture = FormSprites->ImagePlayer2Jump->Picture;
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
  if (mBallX + ImageBall->Width > ClientWidth)
  {
    mBallSpeedX = -mBallSpeedX;
    mBallX = ClientWidth - ImageBall->Width;
  }
  if (mBallY + ImageBall->Height > ClientHeight)
  {
    mBallSpeedY = -mBallSpeedY;
    mBallY = ClientHeight - ImageBall->Height;
  }

  ImageBall->Left = mBallX;
  ImageBall->Top = mBallY;
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

  if (mPlayerLeftX + ImagePlayer1->Width > ClientWidth)
  {  //Player left leaves screen on right side
    mPlayerLeftX = ClientWidth - ImagePlayer1->Width;
    mPlayerLeftSpeedX = ( mPlayerLeftSpeedX > 0 ? -mPlayerLeftSpeedX : mPlayerLeftSpeedX);
  }

  if (mPlayerRightX + ImagePlayer2->Width > ClientWidth)
  {  //Player right leaves screen on right side
    mPlayerRightX = ClientWidth - ImagePlayer2->Width;
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
  if (mPlayerLeftY + ImagePlayer1->Height > ClientHeight)
  { //Player left leaves screen with feet
    mPlayerLeftSpeedY = 0.0;
    mPlayerLeftJumps = false;
    ImagePlayer1->Picture = FormSprites->ImagePlayer1->Picture;
    mPlayerLeftY = ClientHeight - ImagePlayer1->Height;
  }
  if (mPlayerRightY + ImagePlayer2->Height > ClientHeight)
  { //Player right leaves screen with feet
    mPlayerRightSpeedY = 0.0;
    mPlayerRightJumps = false;
    ImagePlayer2->Picture = FormSprites->ImagePlayer2->Picture;
    mPlayerRightY = ClientHeight - ImagePlayer2->Height;
  }

  ImagePlayer1->Left  = mPlayerLeftX;
  ImagePlayer2->Left = mPlayerRightX;
  ImagePlayer1->Top  = mPlayerLeftY;
  ImagePlayer2->Top = mPlayerRightY;

}
//---------------------------------------------------------------------------
void TFormMain::detectCollision()
{
  TRect rect;

  //Check collision of player left and ball
  IntersectRect(rect,ImageBall->BoundsRect, ImagePlayer1->BoundsRect);
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
      ImagePlayer1->Left += ( ImageBall->Left < ImagePlayer1->Left ? 10 : -10);
    }
    //Move the ball
    mBallX += mBallSpeedX; mBallY += mBallSpeedY;
  }

  //Check collision of player right and ball
  IntersectRect(rect,ImageBall->BoundsRect, ImagePlayer2->BoundsRect);
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
      ImagePlayer2->Left += ( ImageBall->Left < ImagePlayer2->Left ? 10 : -10);
    }
    //Move the ball
    mBallX += mBallSpeedX; mBallY += mBallSpeedY;
  }

  //Check collision of basket left and ball
  IntersectRect(rect,ImageBasket1->BoundsRect, ImageBall->BoundsRect);
  if (IsRectEmpty(rect)==false)
  { //Right player has scored
    ++mScoreRight;
    resetCoordinats();
  }
  IntersectRect(rect,ImageBasket2->BoundsRect, ImageBall->BoundsRect);
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

  //Draw ImageBackground on ImageBuffer
  ImageBuffer->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);
  //Draw Baskets on ImageBuffer
  ImageBuffer->Canvas->Draw(ImageBasket1->Left,ImageBasket1->Top,GetRandomBasket1()->Picture->Graphic);
  ImageBuffer->Canvas->Draw(ImageBasket2->Left,ImageBasket2->Top,GetRandomBasket2()->Picture->Graphic);
  //Draw Squirtles and ball on ImageBuffer
  ImageBuffer->Canvas->Draw(ImagePlayer1->Left, ImagePlayer1->Top,ImagePlayer1->Picture->Graphic);
  ImageBuffer->Canvas->Draw(ImagePlayer2->Left, ImagePlayer2->Top,ImagePlayer2->Picture->Graphic);
  ImageBuffer->Canvas->Draw(ImageBall->Left, ImageBall->Top, ImageBall->Picture->Graphic);
  //Draw ImageBuffer on Form
  Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
        
}
//---------------------------------------------------------------------------
const Extctrls::TImage * TFormMain::GetRandomBasket1() const
{
  switch (std::rand() % 3)
  {
    case 0: return FormSprites->ImageBasket1_0;
    case 1: return FormSprites->ImageBasket1_1;
    case 2: return FormSprites->ImageBasket1_2;
  }
  assert(!"Should not get here");
  return 0;
}
//---------------------------------------------------------------------------
const Extctrls::TImage * TFormMain::GetRandomBasket2() const
{
  switch (std::rand() % 3)
  {
    case 0: return FormSprites->ImageBasket2_0;
    case 1: return FormSprites->ImageBasket2_1;
    case 2: return FormSprites->ImageBasket2_2;
  }
  assert(!"Should not get here");
  return 0;
}
//---------------------------------------------------------------------------



