//---------------------------------------------------------------------------
/*
  Space Harry, a simple 'Space Harrier' clone
<<<<<<< HEAD
  Copyright (C) 2007  Richèl Bilderbeek
=======
  Copyright (C) 2007  Richel Bilderbeek
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
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <memory>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSpaceHarryGame.h"
#include "UnitFormSpaceHarryGameOver.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSpaceHarryGame *FormSpaceHarryGame;
//---------------------------------------------------------------------------
__fastcall TFormSpaceHarryGame::TFormSpaceHarryGame(TComponent* Owner)
        : TForm(Owner), mIsHarryTransparent(false), mLife(1.0), mScore(0)
{
  this->WindowState = wsMaximized;
  this->Refresh();
  OnResize(0);
  mX = (ClientWidth  / 2);
  mY = (ClientHeight / 2);
  mZ = 0.0;
<<<<<<< HEAD
  Caption = "Space Harry (C) 2007 Richèl Bilderbeek. Score: " + IntToStr(mScore);
=======
  Caption = "Space Harry (C) 2007 Richel Bilderbeek. Score: " + IntToStr(mScore);
>>>>>>> develop

}
//---------------------------------------------------------------------------
void __fastcall TFormSpaceHarryGame::FormResize(TObject *Sender)
{
  ImageBuffer->Picture->Bitmap->Width = ClientWidth;
  ImageBuffer->Picture->Bitmap->Height = ClientHeight;
  ImageBackgroundSky->Picture->Bitmap->Width = ClientWidth;
  ImageBackgroundSky->Picture->Bitmap->Height = ClientHeight / 2;
  ImageBackgroundSoil1->Picture->Bitmap->Width = ClientWidth;
  ImageBackgroundSoil1->Picture->Bitmap->Height
  = ClientHeight - ImageBackgroundSky->Picture->Bitmap->Height;
  ImageBackgroundSoil2->Picture->Bitmap->Width = ClientWidth;
  ImageBackgroundSoil2->Picture->Bitmap->Height
  = ClientHeight - ImageBackgroundSky->Picture->Bitmap->Height;

  ImageLifebar->Picture->Bitmap->Height = ClientHeight;
  ImageLifebar->Picture->Bitmap->Width  = 20;

  VclPaint(ImageBackgroundSky,0,0,255);
  DrawSoil(ImageBackgroundSoil1,0,255,0,0,128,0);
  DrawSoil(ImageBackgroundSoil2,0,128,0,0,255,0);
  DrawNewLifebar();
  DrawScreen();
}
//---------------------------------------------------------------------------
void __fastcall TFormSpaceHarryGame::TimerGameTimer(TObject *Sender)
{
  if (mEnemies.empty()==true)
  {
    for (int i=0; i!=5; ++i)
    {
      mEnemies.push_back(
        Enemy(
          (ClientWidth  / 2) + (std::rand() % ClientWidth ) - (ClientWidth / 2),
          (ClientHeight / 2) + (std::rand() % ClientHeight) - (ClientHeight/ 2),
          1.0,                                          //z
          2,                                            //nHits
          ImageEnemySkull )                             //Image
        );
    }
  }
  /*
  if (std::rand() % 100 == 0)
  {
    for (int i=0; i!=5; ++i)
    {
    mEnemies.push_back(
      Enemy(
        (ClientWidth  / 2) + (std::rand() % ClientWidth ) - (ClientWidth / 2),
        (ClientHeight / 2) + (std::rand() % ClientHeight) - (ClientHeight/ 2),
        1.0,                                          //z
        2,                                            //nHits
        ImageEnemySkull )                             //Image
      );
    }
  }
  */
  //Move Collision
  {
    for (
      std::list<Collision>::iterator i = mCollisions.begin();
      i!=mCollisions.end();
      ++i)
    {
      ++(*i).nTicks;
      if ((*i).nTicks >= (*i).timeLength)
      {
        mCollisions.erase(i);
        --i;
      }
    }
  }

  //Move enemies
  {
    const std::list<Enemy>::iterator j = mEnemies.end();
    for(
      std::list<Enemy>::iterator i = mEnemies.begin();
      i!=j;
      ++i)
    {
      if ((*i).z > 0.5) { (*i).z -=0.01; } //Move enemy forward


      if ((*i).x < ClientWidth / 2)
      {
        if ((*i).y < ClientHeight / 2)
        {
          if ((*i).x > -(*i).image->Picture->Graphic->Width )
          {
            (*i).x -=10;
          }
          (*i).y +=10;
        }
        else
        {
          if ((*i).y < ClientHeight - (*i).image->Picture->Graphic->Height)
          {
            (*i).y +=10;
          }
          (*i).x +=10;
        }
      }
      else
      {
        if ((*i).y < ClientHeight / 2)
        {
          if ((*i).y > -(*i).image->Picture->Graphic->Height)
          {
            (*i).y -=10;
          }
          (*i).x -=10;
        }
        else
        {
          if ((*i).x < ClientWidth -(*i).image->Picture->Graphic->Width )
          {
            (*i).x +=10;
          }
          (*i).y -=10;
        }
      }
      //if ( (*i).x > ClientWidth) (*i).x-=ClientWidth;
      //(*i).y += (std::rand() % 3 - 1) * 5.0 ;
      //(*i).z += static_cast<double>(std::rand() % 3 -1) * 0.01;

      if (std::rand() % 25 == 0)
      {
        //Enemy fires bullet!
        const double x = (*i).x;
        const double y = (*i).y;
        const double z = (*i).z - 0.0501;
        const double dZ = -0.05;
        const double dX = dZ * ( (ClientWidth  / 2.0) - x);
        const double dY = dZ * ( (ClientHeight / 2.0) - y);
        mBullets.push_back( Bullet(x,y,z,dX,dY,dZ, ImageBulletBlue) );
      }
    }
  }


  //Move bullets
  {
    for (
      std::list<Bullet>::iterator i = mBullets.begin();
      i!=mBullets.end();
      ++i)
    {
      (*i).x += (*i).dX;
      (*i).y += (*i).dY;
      (*i).z += (*i).dZ;
      //Remove bullet if out of screen
      if ((*i).z < -1.0 || (*i).z > 0.6)
      {
        mBullets.erase(i);
        --i;
      }
      //Check if bullet hit Harry
      if ( (*i).x > mX - (ImageHarry->Picture->Bitmap->Width  / 2)
        && (*i).x < mX + (ImageHarry->Picture->Bitmap->Width  / 2)
        && (*i).y > mY - (ImageHarry->Picture->Bitmap->Height / 2)
        && (*i).y < mY + (ImageHarry->Picture->Bitmap->Height / 2)
        && (*i).z > mZ
        && (*i).z < mZ + 0.1)
      {
        //Decrease Harry's life
        mLife -= 0.1;
        //Game over?
        if (mLife < 0.0)
        {
          //Game over
          TimerGame->Enabled = false;
          TimerKeyPress->Enabled = false;
          std::auto_ptr<TFormSpaceHarryGameOver> f(new TFormSpaceHarryGameOver(0));
          f->ShowModal();
          Close();
        }
        DrawNewLifebar();
        //Add a Collision sprite
        mCollisions.push_back(
          Collision(mX,mY,mZ - 0.01,
            2, //1000 / TimerGame->Interval,
            ImageCollisionBlue )
          );
        //Remove the bullet
        mBullets.erase(i);
        --i;

      }

      //Check if bullet hit one of the enemies
      {
        for (std::list<Enemy>::iterator j = mEnemies.begin();
          j != mEnemies.end(); ++j)
        {
          if ( (*i).x > (*j).x - ((*j).image->Picture->Bitmap->Width  / 2)
            && (*i).x < (*j).x + ((*j).image->Picture->Bitmap->Width  / 2)
            && (*i).y > (*j).y - ((*j).image->Picture->Bitmap->Height / 2)
            && (*i).y < (*j).y + ((*j).image->Picture->Bitmap->Height / 2)
            && (*i).z > (*j).z - 0.05
            && (*i).z < (*j).z + 0.05)
          {
            //Add the collision
            mCollisions.push_back(
              Collision((*i).x,(*i).y,(*j).z - 0.01,
                2, //1000 / TimerGame->Interval,
                ImageCollisionGreen )
              );

            //Remove the bullet
            mBullets.erase(i);
            --i;
            //Damage the enemy
            --(*j).nHitpoints;
            if ((*j).nHitpoints <= 0)
            {
              mEnemies.erase(j);
              --j;
              ++mScore; //Harry scored!
<<<<<<< HEAD
              Caption = "Space Harry (C) 2007 Richèl Bilderbeek. Score: " + IntToStr(mScore);
=======
              Caption = "Space Harry (C) 2007 Richel Bilderbeek. Score: " + IntToStr(mScore);
>>>>>>> develop
            }
          }
        }
      }
    }
  }


  DrawScreen();
}
//---------------------------------------------------------------------------
void TFormSpaceHarryGame::DrawScreen()
{

  //Draw background to buffer
  ImageBuffer->Canvas->Draw(0,0,ImageBackgroundSky->Picture->Graphic);

  //Draw the soil
  {
    static bool drawSoil1 = true;
    drawSoil1 = !drawSoil1;
    if (drawSoil1 == true)
      ImageBuffer->Canvas->Draw(0,ClientHeight/2,ImageBackgroundSoil1->Picture->Graphic);
    else
      ImageBuffer->Canvas->Draw(0,ClientHeight/2,ImageBackgroundSoil2->Picture->Graphic);
  }

  //Draw sprites to buffer
  {
    //Collect all sprites
    std::vector<Sprite> sprites;
    //Add Harry to sprites

    sprites.push_back(
      Sprite(mX, mY, mZ,
      (mIsHarryTransparent == false ? ImageHarry : ImageHarryTransparent) ) );
    //Add Bullets to sprites
    {
      const std::list<Bullet>::iterator j = mBullets.end();
      for (
      std::list<Bullet>::iterator i = mBullets.begin(); i!=j; ++i)
      {
        sprites.push_back( Sprite( (*i).x, (*i).y, (*i).z, (*i).image) );
      }
    }
    //Add Enemies to sprites
    {
      const std::list<Enemy>::iterator j = mEnemies.end();
      for (
      std::list<Enemy>::iterator i = mEnemies.begin(); i!=j; ++i)
      {
        sprites.push_back( Sprite( (*i).x, (*i).y, (*i).z, (*i).image) );
      }
    }
    //Add Collisions to sprites
    {
      const std::list<Collision>::iterator j = mCollisions.end();
      for (
      std::list<Collision>::iterator i = mCollisions.begin(); i!=j; ++i)
      {
        sprites.push_back( Sprite( (*i).x, (*i).y, (*i).z, (*i).image) );
      }
    }

    //Sort sprites in Z order
    std::sort(sprites.begin(),sprites.end());

    //Draw the sprites
    const std::vector<Sprite>::iterator j = sprites.end();
    for (
    std::vector<Sprite>::iterator i = sprites.begin(); i!=j; ++i)
    {
      const double spriteWidth  = (*i).image->Picture->Graphic->Width;
      const double spriteHeight = (*i).image->Picture->Graphic->Height;
      const double width =  (1.0 - (*i).z) * (spriteWidth  / 2.0);
      const double height = (1.0 - (*i).z) * (spriteHeight / 2.0);
      const TPoint topLeft(     (*i).x - width , (*i).y - height );
      const TPoint bottomRight( (*i).x + width , (*i).y + height );
      TRect rect(topLeft, bottomRight);
      ImageBuffer->Canvas->StretchDraw(rect, (*i).image->Picture->Graphic);
    }
  }


  //Draw lifebar to buffer
  ImageBuffer->Canvas->Draw(
    ClientWidth - ImageLifebar->Picture->Bitmap->Width,
    0,
    ImageLifebar->Picture->Graphic);


  //ImageBuffer->Canvas->Draw(mX,mY,ImageHarry->Picture->Graphic);
  //Draw buffer to screen
  this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);
}
//---------------------------------------------------------------------------
void TFormSpaceHarryGame::DrawNewLifebar()
{
  {
    const int width  = ImageLifebar->Picture->Bitmap->Width;
    const int height = ImageLifebar->Picture->Bitmap->Height;
    for (int y=0; y!=height; ++y)
    {
      unsigned char * const line
        = static_cast<unsigned char *>(ImageLifebar->Picture->Bitmap->ScanLine[y]);
      for (int x=0; x!=width; ++x)
      {
        const double fraction
          = static_cast<double>(y)
          / static_cast<double>(height);
        const int grey = fraction * 256.0;
        assert(grey <  256);
        assert(grey >= 0  );
        line[x*3+0]= grey; //Blue
        line[x*3+1]= grey; //Green
        line[x*3+2]= grey; //Red
      }
    }
  }
  {
    const int width  = ImageLifebar->Picture->Bitmap->Width;
    const int height = ImageLifebar->Picture->Bitmap->Height;
    const int quarterWidth = width / 4;
    const int heightLeft = height - quarterWidth - quarterWidth;
    for (int y=quarterWidth; y!=height-quarterWidth; ++y)
    {
      unsigned char * const line
        = static_cast<unsigned char *>(ImageLifebar->Picture->Bitmap->ScanLine[y]);
      for (int x=quarterWidth; x!=width-quarterWidth; ++x)
      {
        const double fraction
          = static_cast<double>(y - quarterWidth)
          / static_cast<double>(heightLeft);
        unsigned char r,g,b;
        if (1.0 - fraction > mLife)
        {
          r = g = b = 0;
        }
        else
        {
          Rainbow(fraction,r,g,b);
        }
        line[x*3+0]= b; //Blue
        line[x*3+1]= g; //Green
        line[x*3+2]= r; //Red
      }
    }
  }


}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void VclPaint(TImage * const image,
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

void __fastcall TFormSpaceHarryGame::TimerKeyPressTimer(TObject *Sender)
{
  const int speed = 32;
  //Press the keys
  if (mKeys.count( VK_LEFT ) != 0)
  {
    mX-=speed;
    if (mX < (ImageHarry->Picture->Bitmap->Width / 2) )
      mX = (ImageHarry->Picture->Bitmap->Width / 2);
  }
  if (mKeys.count( VK_RIGHT ) != 0)
  {
    mX+=speed;
    if (mX + (ImageHarry->Picture->Bitmap->Width / 2) > ClientWidth)
      mX = ClientWidth - (ImageHarry->Picture->Bitmap->Width / 2);
  }
  if (mKeys.count( VK_UP ) != 0)
  {
    mY-=speed;
    if (mY < (ImageHarry->Picture->Bitmap->Height / 2) )
      mY = (ImageHarry->Picture->Bitmap->Height / 2);
  }
  if (mKeys.count( VK_DOWN ) != 0)
  {
    mY+=speed;
    if (mY + (ImageHarry->Picture->Bitmap->Height / 2) > ClientHeight)
      mY = ClientHeight - (ImageHarry->Picture->Bitmap->Height / 2);
  }
  if (mKeys.count( VK_SPACE ) != 0)
  {
    const double x = mX;
    const double y = mY;
    const double z = mZ + 0.0501  ;
    const double dZ = 0.05;
    const double dX = dZ * ( (ClientWidth  / 2.0) - x);
    const double dY = dZ * ( (ClientHeight / 2.0) - y);
    mBullets.push_back( Bullet(x,y,z,dX,dY,dZ, ImageBulletHarry) );
    mKeys.erase(VK_SPACE);
  }
  if (mKeys.count( VK_F1 ) != 0)
  {
    mIsHarryTransparent = !mIsHarryTransparent;
    mKeys.erase(VK_F1);
  }

}
//---------------------------------------------------------------------------

void __fastcall TFormSpaceHarryGame::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  mKeys.insert(Key);
}
//---------------------------------------------------------------------------

void __fastcall TFormSpaceHarryGame::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  mKeys.erase(Key);
}
//---------------------------------------------------------------------------
void DrawSoil(TImage * const image,
  const unsigned char red1,
  const unsigned char green1,
  const unsigned char blue1,
  const unsigned char red2,
  const unsigned char green2,
  const unsigned char blue2)
{
  assert(image!=0);
  const int width  = image->Picture->Bitmap->Width;
  const int height = image->Picture->Bitmap->Height;
  bool use1 = true;
  for (int y=0; y!=height; ++y)
  {
    const double yD = static_cast<double>(y);
    const double sqrtY = std::sqrt(yD);
    const int sqrtYint = static_cast<int>(sqrtY + 0.5);
    if (sqrtYint * sqrtYint == y) use1 = !use1;

    if (use1 == true)
    {
      unsigned char * const line
        = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
      for (int x=0; x!=width; ++x)
      {
        line[x*3+0]= blue1; //Blue
        line[x*3+1]= green1; //Green
        line[x*3+2]= red1; //Red
      }
    }
    else
    { //use1 == false
      unsigned char * const line
        = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);
      for (int x=0; x!=width; ++x)
      {
        line[x*3+0]= blue2; //Blue
        line[x*3+1]= green2; //Green
        line[x*3+2]= red2; //Red
      }
    }
  }

}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
void Rainbow(
  const double x,
  unsigned char& r,
  unsigned char& g,
  unsigned char& b)
{
  const int r0 = GetRed(x);
  const int g0 = GetGreen(x);
  const int b0 = GetBlue(x);
  const int max = std::max(r0, std::max(g0,b0));
  assert(max!=0);

  r = 255.0 * static_cast<double>(r0) / static_cast<double>(max);
  g = 255.0 * static_cast<double>(g0) / static_cast<double>(max);
  b = 255.0 * static_cast<double>(b0) / static_cast<double>(max);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
unsigned char GetRed(const double x)
{
  assert( x >= 0.0 && x < 1.0);
  const double f = std::max(0.0,
    (x < 0.5
    ?  std::cos(x * 1.5 * M_PI)
    : -std::sin(x * 1.5 * M_PI)
    ) );
  assert( f >= 0.0);
  assert( f <= 1.0);
  const double y = 255.0 * f;
  assert( static_cast<int>(y) < 256 );
  return static_cast<unsigned char>(y);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
unsigned char GetGreen(const double x)
{
  assert( x >= 0.0 && x < 1.0);

  const double f = std::max(0.0, std::sin( x * 1.5 * M_PI ) );
  assert( f >= 0.0);
  assert( f <= 1.0);
  const double y = 255.0 * f;
  assert( static_cast<int>(y) < 256 );
  return static_cast<unsigned char>(y);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRainbow.htm
unsigned char GetBlue(const double x)
{
  assert( x >= 0.0 && x < 1.0);

  const double f = std::max(0.0, -std::cos( x * 1.5 * M_PI ) );

  assert( f >= 0.0);
  assert( f <= 1.0);
  const double y = 255.0 * f;
  assert( static_cast<int>(y) < 256 );
  return static_cast<unsigned char>(y);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

