/*
  Boenken 2, a simple game
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
#include <cassert>
#include <algorithm>
#include <cmath>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormBoenken2Game.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormBoenken2Game *FormBoenken2Game;
//---------------------------------------------------------------------------
__fastcall TFormBoenken2Game::TFormBoenken2Game(
  TComponent* Owner,
  const std::vector<Player>& players,
  const EnumGraphics graphics,
  const EnumControls controls,
  const double friction)
  : TForm(Owner),
    mPlayers(players),
    mGraphics(graphics),
    mControls(controls),
    mFriction(friction),
    mScoreBlue(0),
    mScoreRed(0)
{
  {
    //Initialize graphics
    ImageBuffer->Canvas->Pen->Width = 3;
    ImageBuffer->Canvas->Pen->Color = clWhite;
    if (mGraphics == graphicsOldSchool)
    {
      DrawCircle(ImageGrey,255,255,255);
      DrawCircle(ImageRed ,255,0  ,0  );
      DrawCircle(ImageBlue,0  ,0  ,255);
      DrawCircle(ImageBall,0  ,255,0  );
    }
    else
    {
      DrawGlobe(ImageGrey,255,255,255);
      DrawGlobe(ImageRed ,255,0  ,0  );
      DrawGlobe(ImageBlue,0  ,0  ,255);
      DrawGlobe(ImageBall,0  ,255,0  );
    }
  }

  {
    //Initialize players
    const int nPlayers = mPlayers.size();
    //mPlayers.resize(nPlayers);

    const int width  = ImageGrey->Picture->Bitmap->Width;
    const int height = ImageGrey->Picture->Bitmap->Height;
    const int midX = ClientWidth  / 2;
    const int midY = ClientHeight / 2;
    double angle = 1.5 * M_PI;
    const double angleStep = (2.0 * M_PI) / static_cast<double>(nPlayers);
    const double ray = static_cast<double>(ClientWidth) / 4.0;
    for (int i=0; i!=nPlayers; ++i)
    {
      mPlayers[i].x = midX + static_cast<int>(std::sin(angle) * ray) - (width / 2);
      mPlayers[i].y = midY - static_cast<int>(std::cos(angle) * ray) - (height/ 2);
      mPlayers[i].angle = angle + M_PI;
      mPlayers[i].speed = 0.0;
      mPlayers[i].dx = 0.0;
      mPlayers[i].dy = 0.0;
      angle+=angleStep;
    }
  }

  {
    //Initialize obstacles and ball
    const int nObstacles = 4;
    mObstacles.resize(nObstacles);
    //Objects are initialized at FormResize
    const int width  = ImageGrey->Picture->Bitmap->Width;
    const int height = ImageGrey->Picture->Bitmap->Height;
    mBall.x = (ClientWidth  / 2) - (height / 2);
    mBall.y = (ClientHeight / 2) - (width / 2);
    mBall.angle = 2.0 * M_PI * (static_cast<double>(std::rand() % 1000) / 1000.0);
    mBall.speed = 0.1;
  }



  FormResize(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Game::FormResize(TObject *Sender)
{
  ImageBackground->Picture->Bitmap->Width  = ClientWidth;
  ImageBackground->Picture->Bitmap->Height = ClientHeight;
  if (mGraphics == graphicsOldSchool)
    DrawOldSchoolBackground(ImageBackground);
  else
    DrawNewSchoolBackground(ImageBackground);

  ImageBuffer->Picture->Bitmap->Width  = ClientWidth;
  ImageBuffer->Picture->Bitmap->Height = ClientHeight;

  {
    //Place the obstacles
    //const int nObstacles = mObstacles.size();
    const int width  = ImageGrey->Picture->Bitmap->Width;
    const int height = ImageGrey->Picture->Bitmap->Height;
    mObstacles[0].x = 0;
    mObstacles[0].y = (1 * ClientHeight / 4) - (height / 2);
    mObstacles[1].x = 0;
    mObstacles[1].y = (3 * ClientHeight / 4) - (height / 2);
    mObstacles[2].x = ClientWidth - width;
    mObstacles[2].y = (1 * ClientHeight / 4) - (height / 2);
    mObstacles[3].x = ClientWidth - width;
    mObstacles[3].y = (3 * ClientHeight / 4) - (height / 2);
    /*
    mObstacles[4].x = (1 * ClientWidth  / 4) - (width  / 2);
    mObstacles[4].y = (1 * ClientHeight / 2) - (height / 2);
    mObstacles[5].x = (3 * ClientWidth  / 4) - (width  / 2);
    mObstacles[5].y = (1 * ClientHeight / 2) - (height / 2);
    */
  }


  if (mControls == control2keys)
  {
    TimerGame->OnTimer = TimerGameTwoKeys;
  }
  else
  {
    TimerGame->OnTimer = TimerGameFourKeys;
  }
  TimerGame->OnTimer(0);

}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Game::TimerGameTwoKeys(TObject *Sender)
{
  {
    //Press the keys
    std::vector<Player>::iterator i = mPlayers.begin();
    const std::vector<Player>::iterator j = mPlayers.end();
    const double acceleration = 0.2;
    for ( ; i!=j; ++i)
    {
      if (mKeys.count( (*i).keyAccel ) != 0)
      {
        //Accelerate
        (*i).dx += (std::sin( (*i).angle ) * acceleration);
        (*i).dy -= (std::cos( (*i).angle ) * acceleration);
      }
      assert(mKeys.count( (*i).keyBrake ) == 0);
      assert(mKeys.count( (*i).keyTurnLeft ) == 0);
      if (mKeys.count( (*i).keyTurnRight ) != 0)
      {
        //Turn right
        (*i).angle += 0.05 * M_PI;
      }
    }
  }

  {
    //Move players
    const double maxx = static_cast<double>(ClientWidth  - ImageRed->Width );
    const double maxy = static_cast<double>(ClientHeight - ImageRed->Height);
    std::vector<Player>::iterator i = mPlayers.begin();
    const std::vector<Player>::iterator j = mPlayers.end();
    for ( ; i!=j; ++i)
    {
      (*i).x += (*i).dx;
      (*i).y += (*i).dy;
      bool doAgain = false;
      if ((*i).x <  0.0) { ++(*i).x; (*i).dx = -(*i).dx; doAgain = true; }
      if ((*i).y <  0.0) { ++(*i).y; (*i).dy = -(*i).dy; doAgain = true; }
      if ((*i).x > maxx) { --(*i).x; (*i).dx = -(*i).dx; doAgain = true; }
      if ((*i).y > maxy) { --(*i).y; (*i).dy = -(*i).dy; doAgain = true; }
      if (doAgain == true) { --i; }
      else { (*i).dx*=mFriction; (*i).dy*=mFriction; }
    }
  }

  {
    //Move ball and check for goal
    const double maxx = static_cast<double>(ClientWidth  - ImageRed->Width );
    const double maxy = static_cast<double>(ClientHeight - ImageRed->Height);
    bool doAgain = false;
    bool redScored = false;
    bool blueScored = false;
    mBall.speed *= mFriction;
    while (1)
    {
      doAgain = false;
      mBall.x += (std::sin(mBall.angle) * mBall.speed);
      mBall.y -= (std::cos(mBall.angle) * mBall.speed);
      if (mBall.x <  0.0 && mBall.y > 1 * ClientHeight / 4 && mBall.y < 3 * ClientHeight / 4) blueScored = true;
      if (mBall.x > maxx && mBall.y > 1 * ClientHeight / 4 && mBall.y < 3 * ClientHeight / 4) redScored  = true;
      if (mBall.x <  0.0) { ++mBall.x; mBall.angle = (0.0*M_PI) + ((0.0*M_PI) - mBall.angle); doAgain = true; }
      if (mBall.y <  0.0) { ++mBall.y; mBall.angle = (0.5*M_PI) + ((0.5*M_PI) - mBall.angle); doAgain = true; }
      if (mBall.x > maxx) { --mBall.x; mBall.angle = (1.0*M_PI) + ((1.0*M_PI) - mBall.angle); doAgain = true; }
      if (mBall.y > maxy) { --mBall.y; mBall.angle = (1.5*M_PI) + ((1.5*M_PI) - mBall.angle); doAgain = true; }
      if (doAgain == false) break;
    }
    if (redScored  == true) { ++mScoreRed ; Caption = "Red:"+IntToStr(mScoreRed)+" vs Blue:"+IntToStr(mScoreBlue); }
    if (blueScored == true) { ++mScoreBlue; Caption = "Red:"+IntToStr(mScoreRed)+" vs Blue:"+IntToStr(mScoreBlue); }
  }

  //Check player-obstancle collisions
  {
    const double collisionDistance = ImageRed->Width;
    std::vector<Player>::iterator player = mPlayers.begin();
    const std::vector<Player>::iterator playerEnd = mPlayers.end();
    const std::vector<Obstacle>::iterator obstacleEnd = mObstacles.end();
    for ( ; player!=playerEnd; ++player)
    {
      std::vector<Obstacle>::iterator obstacle = mObstacles.begin();
      for ( ; obstacle!=obstacleEnd; ++obstacle)
      {
        const double dX = (*obstacle).x - (*player).x;
        const double dY = (*obstacle).y - (*player).y;
        const double distance = std::sqrt((dY * dY) + (dX * dX));
        if (distance < collisionDistance)
        {
          const double angle = GetAngle(dX,dY);
          double playerAngle = GetAngle( (*player).dx, (*player).dy);
          double playerSpeed = std::sqrt(((*player).dy * (*player).dy) + ((*player).dx * (*player).dx));
          double obstacleAngle = playerAngle + M_PI;
          double obstacleSpeed = playerSpeed;
          DoPerfectElasticCollision(angle, playerAngle, playerSpeed, obstacleAngle, obstacleSpeed );
          (*player).dx =  std::sin(playerAngle) * playerSpeed;
          (*player).dy = -std::cos(playerAngle) * playerSpeed;
          //Let them move once
          (*player).x += (*player).dx;
          (*player).y -= (*player).dy;
        }
      }
    }
  }

  {
    //Check ball-obstacle collisions
    const double collisionDistance = ImageRed->Width;
    const std::vector<Obstacle>::iterator obstacleEnd = mObstacles.end();
    std::vector<Obstacle>::iterator obstacle = mObstacles.begin();
    for ( ; obstacle!=obstacleEnd; ++obstacle)
    {
      const double dX = (*obstacle).x - mBall.x;
      const double dY = (*obstacle).y - mBall.y;
      const double distance = std::sqrt((dY * dY) + (dX * dX));
      if (distance < collisionDistance)
      {
        const double angle = GetAngle(dX,dY);
        double obstacleAngle = mBall.angle + M_PI;
        double obstacleSpeed = mBall.speed;
        DoPerfectElasticCollision(angle, mBall.angle,mBall.speed, obstacleAngle, obstacleSpeed );
        //Let them move once
        mBall.x += (std::sin(mBall.angle) * mBall.speed);
        mBall.y -= (std::cos(mBall.angle) * mBall.speed);
      }
    }
  }

  //Check player-player collisions
  {
    const double collisionDistance = ImageRed->Width;
    std::vector<Player>::iterator player1 = mPlayers.begin();
    const std::vector<Player>::iterator playerEnd = mPlayers.end();
    for ( ; player1!=playerEnd; ++player1)
    {
      std::vector<Player>::iterator player2 = player1 + 1;
      for ( ; player2!=playerEnd; ++player2)
      {
        assert(player1!=player2);
        const double dX = (*player2).x - (*player1).x;
        const double dY = (*player2).y - (*player1).y;
        const double distance = std::sqrt((dY * dY) + (dX * dX));
        if (distance < collisionDistance)
        {
          const double angle = GetAngle(dX,dY);
          double player1Angle = GetAngle( (*player1).dx, (*player1).dy);
          double player1Speed = std::sqrt(((*player1).dy * (*player1).dy) + ((*player1).dx * (*player1).dx));
          double player2Angle = GetAngle( (*player2).dx, (*player2).dy);
          double player2Speed = std::sqrt(((*player2).dy * (*player2).dy) + ((*player2).dx * (*player2).dx));

          DoPerfectElasticCollision(angle, player1Angle,player1Speed,player2Angle,player2Speed);

          (*player1).dx =  std::sin(player1Angle) * player1Speed;
          (*player1).dy = -std::cos(player1Angle) * player1Speed;
          (*player2).dx =  std::sin(player2Angle) * player2Speed;
          (*player2).dy = -std::cos(player2Angle) * player2Speed;
          //Let them move once
          (*player1).x += (*player1).dx;
          (*player1).y -= (*player1).dy;
          (*player2).x += (*player2).dx;
          (*player2).y -= (*player2).dy;
        }
      }
    }
  }


  //Check player-ball collisions
  {
    const double collisionDistance = ImageRed->Width;
    std::vector<Player>::iterator player = mPlayers.begin();
    const std::vector<Player>::iterator playerEnd = mPlayers.end();
    for ( ; player!=playerEnd; ++player)
    {
      const double dX = mBall.x - (*player).x;
      const double dY = mBall.y - (*player).y;
      const double distance = std::sqrt((dY * dY) + (dX * dX));
      if (distance < collisionDistance)
      {
        const double angle = GetAngle(dX,dY);
        double playerAngle = GetAngle( (*player).dx, (*player).dy);
        double playerSpeed = std::sqrt(((*player).dy * (*player).dy) + ((*player).dx * (*player).dx));
        DoPerfectElasticCollision(angle, playerAngle,playerSpeed, mBall.angle, mBall.speed );
        (*player).dx =  std::sin(playerAngle) * playerSpeed;
        (*player).dy = -std::cos(playerAngle) * playerSpeed;
        //Let them move once
        (*player).x += (*player).dx;
        (*player).y -= (*player).dy;
        mBall.x += (std::sin(mBall.angle) * mBall.speed);
        mBall.y -= (std::cos(mBall.angle) * mBall.speed);
      }
    }
  }





  //Draw background on buffer
  ImageBuffer->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);

  {
    //Draw obstacles on buffer
    //Goal poles
    ImageBuffer->Canvas->Draw(mObstacles[0].x,mObstacles[0].y,ImageRed->Picture->Graphic);
    ImageBuffer->Canvas->Draw(mObstacles[1].x,mObstacles[1].y,ImageRed->Picture->Graphic);
    ImageBuffer->Canvas->Draw(mObstacles[2].x,mObstacles[2].y,ImageBlue->Picture->Graphic);
    ImageBuffer->Canvas->Draw(mObstacles[3].x,mObstacles[3].y,ImageBlue->Picture->Graphic);
    //Others
    std::vector<Obstacle>::iterator i = mObstacles.begin() + 4;
    const std::vector<Obstacle>::iterator j = mObstacles.end();
    for ( ; i!=j; ++i)
    {
      ImageBuffer->Canvas->Draw((*i).x,(*i).y,ImageGrey->Picture->Graphic);
    }
  }

  {
    //Draw players on buffer
    std::vector<Player>::iterator i = mPlayers.begin();
    const std::vector<Player>::iterator j = mPlayers.end();
    for ( ; i!=j; ++i)
    {
      ImageBuffer->Canvas->Draw((*i).x,(*i).y,ImageRed->Picture->Graphic);
      ++i;
      if (i==j) break;
      ImageBuffer->Canvas->Draw((*i).x,(*i).y,ImageBlue->Picture->Graphic);
    }
  }

  {
    //Draw ball on buffer
    ImageBuffer->Canvas->Draw(mBall.x,mBall.y,ImageBall->Picture->Graphic);
  }

  {
    //Draw player's directions on buffer
    const int midX = ImageRed->Picture->Bitmap->Width / 2;
    const int midY = ImageRed->Picture->Bitmap->Height / 2;
    const int mid = std::min(midX,midY);
    const double ray = static_cast<double>(mid);
    std::vector<Player>::iterator i = mPlayers.begin();
    const std::vector<Player>::iterator j = mPlayers.end();
    for ( ; i!=j; ++i)
    {
      const double x1 = mid + (*i).x;
      const double y1 = mid + (*i).y;
      const double x2 = x1 + (std::sin( (*i).angle) * ray);
      const double y2 = y1 - (std::cos( (*i).angle) * ray);
      ImageBuffer->Canvas->MoveTo(x1,y1);
      ImageBuffer->Canvas->LineTo(x2,y2);
    }
  }

  //Draw buffer to foreground (ImageArea)
  this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Game::TimerGameFourKeys(TObject *Sender)
{
  {
    //Press the keys
    std::vector<Player>::iterator i = mPlayers.begin();
    const std::vector<Player>::iterator j = mPlayers.end();
    const double acceleration = 0.05;
    for ( ; i!=j; ++i)
    {
      if (mKeys.count( (*i).keyAccel ) != 0)
      {
        //Accelerate
        (*i).speed += acceleration;
      }
      if (mKeys.count( (*i).keyBrake ) != 0)
      {
        //Brake
        (*i).speed -= acceleration;
      }
      if (mKeys.count( (*i).keyTurnLeft ) != 0)
      {
        //Turn left
        (*i).angle -= 0.05 * M_PI;
      }
      if (mKeys.count( (*i).keyTurnRight ) != 0)
      {
        //Turn
        (*i).angle += 0.05 * M_PI;
      }
    }
  }

  {
    //Move players
    const double maxx = static_cast<double>(ClientWidth  - ImageRed->Width );
    const double maxy = static_cast<double>(ClientHeight - ImageRed->Height);
    std::vector<Player>::iterator i = mPlayers.begin();
    const std::vector<Player>::iterator j = mPlayers.end();
    for ( ; i!=j; ++i)
    {
      (*i).x += (std::sin((*i).angle) * (*i).speed);
      (*i).y -= (std::cos((*i).angle) * (*i).speed);
      bool doAgain = false;
      if ((*i).x <  0.0) { ++(*i).x; (*i).angle = (0.0*M_PI) + ((0.0*M_PI) - (*i).angle); doAgain = true; }
      if ((*i).y <  0.0) { ++(*i).y; (*i).angle = (0.5*M_PI) + ((0.5*M_PI) - (*i).angle); doAgain = true; }
      if ((*i).x > maxx) { --(*i).x; (*i).angle = (1.0*M_PI) + ((1.0*M_PI) - (*i).angle); doAgain = true; }
      if ((*i).y > maxy) { --(*i).y; (*i).angle = (1.5*M_PI) + ((1.5*M_PI) - (*i).angle); doAgain = true; }
      if (doAgain == true) { --i; }
      else (*i).speed*=mFriction;
    }
  }

  {
    //Move ball and check for goal
    const double maxx = static_cast<double>(ClientWidth  - ImageRed->Width );
    const double maxy = static_cast<double>(ClientHeight - ImageRed->Height);
    bool doAgain = false;
    bool redScored = false;
    bool blueScored = false;
    mBall.speed*=mFriction;
    while (1)
    {
      doAgain = false;
      mBall.x += (std::sin(mBall.angle) * mBall.speed);
      mBall.y -= (std::cos(mBall.angle) * mBall.speed);
      if (mBall.x <  0.0 && mBall.y > 1 * ClientHeight / 4 && mBall.y < 3 * ClientHeight / 4) blueScored = true;
      if (mBall.x > maxx && mBall.y > 1 * ClientHeight / 4 && mBall.y < 3 * ClientHeight / 4) redScored  = true;
      if (mBall.x <  0.0) { ++mBall.x; mBall.angle = (0.0*M_PI) + ((0.0*M_PI) - mBall.angle); doAgain = true; }
      if (mBall.y <  0.0) { ++mBall.y; mBall.angle = (0.5*M_PI) + ((0.5*M_PI) - mBall.angle); doAgain = true; }
      if (mBall.x > maxx) { --mBall.x; mBall.angle = (1.0*M_PI) + ((1.0*M_PI) - mBall.angle); doAgain = true; }
      if (mBall.y > maxy) { --mBall.y; mBall.angle = (1.5*M_PI) + ((1.5*M_PI) - mBall.angle); doAgain = true; }
      if (doAgain == false) break;
    }
    if (redScored  == true) { ++mScoreRed ; Caption = "Red:"+IntToStr(mScoreRed)+" vs Blue:"+IntToStr(mScoreBlue); }
    if (blueScored == true) { ++mScoreBlue; Caption = "Red:"+IntToStr(mScoreRed)+" vs Blue:"+IntToStr(mScoreBlue); }
  }

  //Check player-obstancle collisions
  {
    const double collisionDistance = ImageRed->Width;
    std::vector<Player>::iterator player = mPlayers.begin();
    const std::vector<Player>::iterator playerEnd = mPlayers.end();
    const std::vector<Obstacle>::iterator obstacleEnd = mObstacles.end();
    for ( ; player!=playerEnd; ++player)
    {
      std::vector<Obstacle>::iterator obstacle = mObstacles.begin();
      for ( ; obstacle!=obstacleEnd; ++obstacle)
      {
        const double dX = (*obstacle).x - (*player).x;
        const double dY = (*obstacle).y - (*player).y;
        const double distance = std::sqrt((dY * dY) + (dX * dX));
        if (distance < collisionDistance)
        {
          const double angle = GetAngle(dX,dY);
          double obstacleAngle = (*player).angle + M_PI;
          double obstacleSpeed = (*player).speed;
          DoPerfectElasticCollision(angle, (*player).angle,(*player).speed, obstacleAngle, obstacleSpeed );
          //Let them move once
          (*player).x += (std::sin((*player).angle) * (*player).speed);
          (*player).y -= (std::cos((*player).angle) * (*player).speed);
        }
      }
    }
  }

  {
    //Check ball-obstacle collisions
    const double collisionDistance = ImageRed->Width;
    const std::vector<Obstacle>::iterator obstacleEnd = mObstacles.end();
    std::vector<Obstacle>::iterator obstacle = mObstacles.begin();
    for ( ; obstacle!=obstacleEnd; ++obstacle)
    {
      const double dX = (*obstacle).x - mBall.x;
      const double dY = (*obstacle).y - mBall.y;
      const double distance = std::sqrt((dY * dY) + (dX * dX));
      if (distance < collisionDistance)
      {
        const double angle = GetAngle(dX,dY);
        double obstacleAngle = mBall.angle + M_PI;
        double obstacleSpeed = mBall.speed;
        DoPerfectElasticCollision(angle, mBall.angle,mBall.speed, obstacleAngle, obstacleSpeed );
        //Let them move once
        mBall.x += (std::sin(mBall.angle) * mBall.speed);
        mBall.y -= (std::cos(mBall.angle) * mBall.speed);
      }
    }
  }

  //Check player-player collisions
  {
    const double collisionDistance = ImageRed->Width;
    std::vector<Player>::iterator player1 = mPlayers.begin();
    const std::vector<Player>::iterator playerEnd = mPlayers.end();
    for ( ; player1!=playerEnd; ++player1)
    {
      std::vector<Player>::iterator player2 = player1 + 1;
      for ( ; player2!=playerEnd; ++player2)
      {
        assert(player1!=player2);
        const double dX = (*player2).x - (*player1).x;
        const double dY = (*player2).y - (*player1).y;
        const double distance = std::sqrt((dY * dY) + (dX * dX));
        if (distance < collisionDistance)
        {
          const double angle = GetAngle(dX,dY);
          DoPerfectElasticCollision(angle, (*player1).angle,(*player1).speed,(*player2).angle,(*player2).speed);
          //Let them move once
          (*player1).x += (std::sin((*player1).angle) * (*player1).speed);
          (*player1).y -= (std::cos((*player1).angle) * (*player1).speed);
          (*player2).x += (std::sin((*player2).angle) * (*player2).speed);
          (*player2).y -= (std::cos((*player2).angle) * (*player2).speed);
        }
      }
    }
  }


  //Check player-ball collisions
  {
    const double collisionDistance = ImageRed->Width;
    std::vector<Player>::iterator player = mPlayers.begin();
    const std::vector<Player>::iterator playerEnd = mPlayers.end();
    for ( ; player!=playerEnd; ++player)
    {
      const double dX = mBall.x - (*player).x;
      const double dY = mBall.y - (*player).y;
      const double distance = std::sqrt((dY * dY) + (dX * dX));
      if (distance < collisionDistance)
      {
        const double angle = GetAngle(dX,dY);
        DoPerfectElasticCollision(angle, (*player).angle,(*player).speed, mBall.angle, mBall.speed );
        //Let them move once
        (*player).x += (std::sin((*player).angle) * (*player).speed);
        (*player).y -= (std::cos((*player).angle) * (*player).speed);
        mBall.x += (std::sin(mBall.angle) * mBall.speed);
        mBall.y -= (std::cos(mBall.angle) * mBall.speed);
      }
    }
  }





  //Draw background on buffer
  ImageBuffer->Canvas->Draw(0,0,ImageBackground->Picture->Graphic);

  {
    //Draw obstacles on buffer
    //Goal poles
    ImageBuffer->Canvas->Draw(mObstacles[0].x,mObstacles[0].y,ImageRed->Picture->Graphic);
    ImageBuffer->Canvas->Draw(mObstacles[1].x,mObstacles[1].y,ImageRed->Picture->Graphic);
    ImageBuffer->Canvas->Draw(mObstacles[2].x,mObstacles[2].y,ImageBlue->Picture->Graphic);
    ImageBuffer->Canvas->Draw(mObstacles[3].x,mObstacles[3].y,ImageBlue->Picture->Graphic);
    //Others
    std::vector<Obstacle>::iterator i = mObstacles.begin() + 4;
    const std::vector<Obstacle>::iterator j = mObstacles.end();
    for ( ; i!=j; ++i)
    {
      ImageBuffer->Canvas->Draw((*i).x,(*i).y,ImageGrey->Picture->Graphic);
    }
  }

  {
    //Draw players on buffer
    std::vector<Player>::iterator i = mPlayers.begin();
    const std::vector<Player>::iterator j = mPlayers.end();
    for ( ; i!=j; ++i)
    {
      ImageBuffer->Canvas->Draw((*i).x,(*i).y,ImageRed->Picture->Graphic);
      ++i;
      if (i==j) break;
      ImageBuffer->Canvas->Draw((*i).x,(*i).y,ImageBlue->Picture->Graphic);
    }
  }

  {
    //Draw ball on buffer
    ImageBuffer->Canvas->Draw(mBall.x,mBall.y,ImageBall->Picture->Graphic);
  }

  {
    //Draw player's directions on buffer
    const int midX = ImageRed->Picture->Bitmap->Width / 2;
    const int midY = ImageRed->Picture->Bitmap->Height / 2;
    const int mid = std::min(midX,midY);
    const double ray = static_cast<double>(mid);
    std::vector<Player>::iterator i = mPlayers.begin();
    const std::vector<Player>::iterator j = mPlayers.end();
    for ( ; i!=j; ++i)
    {
      const double x1 = mid + (*i).x;
      const double y1 = mid + (*i).y;
      const double x2 = x1 + (std::sin( (*i).angle) * ray);
      const double y2 = y1 - (std::cos( (*i).angle) * ray);
      ImageBuffer->Canvas->MoveTo(x1,y1);
      ImageBuffer->Canvas->LineTo(x2,y2);
    }
  }

  //Draw buffer to foreground (ImageArea)
  this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
}
//---------------------------------------------------------------------------
void DrawOldSchoolBackground(TImage * const image)
{
  PaintVcl(image,0,0,0);
}
//---------------------------------------------------------------------------
void DrawNewSchoolBackground(TImage * const image)
{
  assert(image!=0);
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    const double fracY = static_cast<double>(y) / static_cast<double>(height);
    for (int x=0; x!=width; ++x)
    {
      const double fracX = static_cast<double>(x) / static_cast<double>(width);
      const double grey = 0.5 + (0.25 * (std::sin(fracX * M_PI * 7.0) + std::sin(fracY * M_PI * 7.0)));
      const int g = static_cast<int>(grey * 255.0);
      assert( g >= 0);
      assert( g <  256);
      line[x*3+0] = g; //Blue
      line[x*3+1] = g; //Green
      line[x*3+2] = g; //Red
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  )
{
  assert(image!=0);
  assert(image->Picture->Bitmap != 0);
  assert(image->Picture->Bitmap->PixelFormat == pf24bit);

  const int maxx = image->Picture->Bitmap->Width;
  const int maxy = image->Picture->Bitmap->Height;
  for (int y = 0; y != maxy; ++y)
  {
    unsigned char * const myLine
      = static_cast<unsigned char*>(image->Picture->Bitmap->ScanLine[y]);
    for (int x = 0; x != maxx; ++x)
    {
      myLine[x*3+2] = red  ; //Red
      myLine[x*3+1] = green; //Green
      myLine[x*3+0] = blue ; //Blue
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDrawGlobe.htm
void DrawGlobe(
  TImage * const image,
  unsigned char rMax,
  unsigned char gMax,
  unsigned char bMax)
{
  assert(image!=0);
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  const double midX = static_cast<double>(width ) / 2.0;
  const double midY = static_cast<double>(height) / 2.0;
  const double maxDist = std::min(midX,midY);
  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    const double yD = static_cast<double>(y);
    for (int x=0; x!=width; ++x)
    {
      const double xD = static_cast<double>(x);
      const double dist = std::sqrt( ((xD - midX) * (xD - midX)) + ((yD - midY) * (yD - midY)) );
      if (dist <= maxDist)
      {
        const double relDist = dist / maxDist;
        const int r = relDist * static_cast<double>(rMax);
        const int g = relDist * static_cast<double>(gMax);
        const int b = relDist * static_cast<double>(bMax);
        assert( r >= 0);
        assert( r < 256);
        assert( g >= 0);
        assert( g < 256);
        assert( b >= 0);
        assert( b < 256);
        line[x*3+2] = (r == 0 ? 1 : r); //Never use a zero for red
        line[x*3+1] = (g == 0 ? 1 : g); //Never use a zero for green
        line[x*3+0] = (b == 0 ? 1 : b); //Never use a zero for blue
      }
      else
      {
        line[x*3+2] = 0;
        line[x*3+1] = 0;
        line[x*3+0] = 0;
      }
    }
  }
}
//---------------------------------------------------------------------------
void DrawCircle(
  TImage * const image,
  unsigned char r,
  unsigned char g,
  unsigned char b)
{
  assert(image!=0);
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  const double midX = static_cast<double>(width ) / 2.0;
  const double midY = static_cast<double>(height) / 2.0;
  const double maxDist = std::min(midX,midY);
  const double minDist = maxDist - 3.0;
  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
    const double yD = static_cast<double>(y);
    for (int x=0; x!=width; ++x)
    {
      const double xD = static_cast<double>(x);
      const double dist = std::sqrt( ((xD - midX) * (xD - midX)) + ((yD - midY) * (yD - midY)) );
      if (dist > minDist && dist < maxDist)
      {
        line[x*3+2] = r;
        line[x*3+1] = g;
        line[x*3+0] = b;
      }
      else
      {
        line[x*3+2] = 0;
        line[x*3+1] = 0;
        line[x*3+0] = 0;
      }
    }
  }
}
//---------------------------------------------------------------------------
//From www.richelbilderbeek.nl/CppGetAngle.htm
double GetAngle(const double dX, const double dY)
{
  //In which quadrant are we?
  if (dX > 0.0)
  {
    if (dY > 0.0)
    {
      //dX > 0 && dY > 0
      //Quadrant IV
      assert(dX > 0.0 && dY > 0.0);
      const double angle = (1.0 * M_PI) - std::atan(dX / dY);
      assert(angle >= 0.5 * M_PI && angle <= 1.0 * M_PI);
      return angle;
    }
    else if (dY < 0.0)
    {
      //dX > 0 && dY <= 0
      //Quadrant I
      assert(dX > 0.0 && dY < 0.0);
      const double angle = (0.0 * M_PI) - std::atan(dX / dY);
      assert(angle >= 0.0 * M_PI && angle <= 0.5 * M_PI);
      return angle;
    }
    else
    {
      //dX > 0.0 && dY == 0.0
      //On Y-axis, right side
      assert(dX > 0.0 && dY == 0.0);
      const double angle = (0.5 * M_PI);
      return angle;
    }
  }
  else if (dX < 0.0)
  {
    if (dY > 0.0)
    {
      //dX < 0 && dY > 0
      //Quadrant III
      assert(dX < 0.0 && dY > 0.0);
      const double angle = (1.0 * M_PI) - std::atan(dX / dY);
      assert(angle >= 1.0 * M_PI && angle <= 1.5 * M_PI);
      return angle;
    }
    else if (dY < 0.0)
    {
      //dX < 0 && dY < 0
      //Quadrant II
      assert(dX < 0.0 && dY < 0.0);
      const double angle = (2.0 * M_PI) - std::atan(dX / dY);
      assert(angle >= 1.5 * M_PI && angle <= 2.0 * M_PI);
      return angle;
    }
    else
    {
      //dX < 0 && dY == 0
      //On X-axis
      assert(dX < 0.0 && dY == 0.0);
      const double angle = (1.5 * M_PI);
      return angle;
    }
  }
  else
  {
    if (dY > 0.0)
    {
      //dX == 0 && dY > 0.0)
      //On Y-axis, right side of origin
      assert(dX==0.0 && dY > 0.0);
      const double angle = (1.0 * M_PI);
      return angle;
    }
    else if (dY < 0.0)
    {
      //dX == 0 && dY < 0.0)
      //On Y-axis, left side of origin
      assert(dX==0.0 && dY < 0.0);
      const double angle = (0.0 * M_PI);
      return angle;
    }
    else
    {
      //dX == 0 && dY == 0.0)
      //On origin
      assert(dX==0.0 && dY == 0.0);
      const double angle = (0.0 * M_PI);
      return angle;
    }
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppDoPerfectElasticCollision.htm
void DoPerfectElasticCollision(
  const double angleCollision,
  double& angle1,
  double& speed1,
  double& angle2,
  double& speed2)
{
  //The length of the impulse of player 1 (assumes both players have equal mass!)
  const double A = speed1;
  //The length of the impulse of player 2 (assumes both players have equal mass!)
  const double E = speed2;
  //The angles between the two globes
  const double c = angleCollision;
  //The angle between c and the impulse direction of player 1
  const double a = c - angle1;
  //The angle between c and the impulse direction of player 2
  const double b = c + M_PI - angle2;

  //Seperate the impulses to their impulses paralel and othoganal the angle of collision
  //The length of the impulse of player 1 parallel to the collision
  const double B = A * std::cos(a);
  //The length of the impulse of player 1 orthogonal to the collision
  const double C = A * std::sin(a);
  //The length of the impulse of player 2 parallel to the collision
  const double F = E * std::cos(b);
  //The length of the impulse of player 2 orthogonal to the collision
  const double G = E * std::sin(b);

  //Seperate the impulses in X and Y directions
  const double BdX = B *  std::sin(c + (0.0 * M_PI));
  const double BdY = B * -std::cos(c + (0.0 * M_PI));
  const double CdX = C *  std::sin(c + (1.5 * M_PI));
  const double CdY = C * -std::cos(c + (1.5 * M_PI));
  const double FdX = F *  std::sin(c + (1.0 * M_PI));
  const double FdY = F * -std::cos(c + (1.0 * M_PI));
  const double GdX = G *  std::sin(c + (0.5 * M_PI));
  const double GdY = G * -std::cos(c + (0.5 * M_PI));

  //The resulting impulses
  //The resulting impulse of player 1 in the X direction
  const double DdX = CdX + FdX;
  //The resulting impulse of player 1 in the Y direction
  const double DdY = CdY + FdY;
  //The resulting impulse of player 2 in the X direction
  const double HdX = BdX + GdX;
  //The resulting impulse of player 2 in the Y direction
  const double HdY = BdY + GdY;

  //Write the final results
  angle1 = GetAngle(DdX, DdY);
  angle2 = GetAngle(HdX, HdY);
  speed1 = std::sqrt( (DdX * DdX) + (DdY * DdY) ); //Pythagoras
  speed2 = std::sqrt( (HdX * HdX) + (HdY * HdY) ); //Pythagoras
}
//---------------------------------------------------------------------------
void __fastcall TFormBoenken2Game::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  mKeys.insert(Key);
}
//---------------------------------------------------------------------------

void __fastcall TFormBoenken2Game::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  mKeys.erase(Key);
}
//---------------------------------------------------------------------------

