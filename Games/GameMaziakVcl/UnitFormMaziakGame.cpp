//---------------------------------------------------------------------------
/*
  Maziak, a simple maze game
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
#include <vcl.h>
#pragma hdrstop

#include <algorithm>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "UnitFormMaziakGame.h"
#include "UnitMazeCreater.h"
#include "UnitFormMaziakGameOver.h"
#include "UnitFormMaziakGameWon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMaziakGame *FormMaziakGame;
//---------------------------------------------------------------------------
__fastcall TFormMaziakGame::TFormMaziakGame(
  TComponent* Owner,
  const String mazeSize) //Must be String, otherwise compiler complains?!?!?
  : TForm(Owner),
    mHasSword(true),
    mFighting(0),
    mCheat(false),
    mViewWidth(9),
    mViewHeight(9),
    mDirection(pdDown),
    mMoveNow(none)
{
  CreateMaze(mazeSize.ToInt());
  assert(IsSquare(mMaze));
  assert(IsSquare(mIntMaze));
  assert(mSolution.empty() || IsSquare(mSolution));
  assert(IsSquare(mDistances));
  OnResize(0);
}
//---------------------------------------------------------------------------
void TFormMaziakGame::CreateMaze(const int sz)
{
  mIntMaze = ::CreateMaze(sz);
  mMaze = ConvertMatrix<int,MazeSquare>(mIntMaze);

  {
    std::vector<std::pair<int,int> > deadEnds = GetShuffledDeadEnds(mIntMaze);
    const int nDeadEnds = deadEnds.size();
    assert(nDeadEnds >= 2);
    const int nSwords    = (nDeadEnds - 2) / 3;
    const int nPrisoners = (nDeadEnds - 2) / 10;
    const int nEnemies   = (nDeadEnds - 2) / 4;

    //Set a minimum distance for the player to travel
    while (1)
    {
      const double x1 = static_cast<double>(deadEnds[0].first );
      const double y1 = static_cast<double>(deadEnds[0].second);
      const double x2 = static_cast<double>(deadEnds[1].first );
      const double y2 = static_cast<double>(deadEnds[1].second);
      const double a = x1 - x2;
      const double b = y1 - y2;
      const double minDist = 0.75 * static_cast<double>(sz);
      if (std::sqrt( (a * a) + (b * b) ) > minDist)
      {
        break;
      }
      else
      {
        std::swap(deadEnds[0],deadEnds[std::rand() % nDeadEnds]);
        std::swap(deadEnds[1],deadEnds[std::rand() % nDeadEnds]);
      }
    }

    mX = deadEnds[0].first;
    mY = deadEnds[0].second;
    assert(mMaze[deadEnds[0].second][deadEnds[0].first] == msEmpty);
    const int exitX = deadEnds[1].first;
    const int exitY = deadEnds[1].second;
    assert(mMaze[exitY][exitX] == msEmpty);
    mDistances = GetMazeDistances(mIntMaze,exitX,exitY);
    mMaze[deadEnds[1].second][deadEnds[1].first] = msExit;

    std::vector<std::pair<int,int> >::const_iterator deadEndIterator = deadEnds.begin() + 2;

    {
      //Place swords in maze, only in dead ends
      for (int i=0; i!=nSwords; ++i)
      {
        assert(deadEndIterator != deadEnds.end());
        const int x = (*deadEndIterator).first;
        const int y = (*deadEndIterator).second;
        assert(x!=mX || y!=mY);
        assert(mMaze[y][x] == msEmpty);
        mMaze[y][x] = msSword;
        ++deadEndIterator;
      }
      //Place prisoners in maze, only in dead ends
      for (int i=0; i!=nPrisoners; ++i)
      {
        assert(deadEndIterator != deadEnds.end());
        const int x = (*deadEndIterator).first;
        const int y = (*deadEndIterator).second;
        assert(x!=mX || y!=mY);
        assert(mMaze[y][x] == msEmpty);
        mMaze[y][x] = msPrisoner1;
        ++deadEndIterator;
      }

      for (int i=0; i!=nEnemies; ++i)
      {
        assert(deadEndIterator != deadEnds.end());
        const int x = (*deadEndIterator).first;
        const int y = (*deadEndIterator).second;
        assert(mMaze[y][x] == msEmpty);
        mMaze[y][x] = msEnemy1;
        ++deadEndIterator;
      }

    }


    {
      /*
      //Place enemies in nondead ends
      const std::vector<std::pair<int,int> > nonDeadEnds = GetShuffledNonDeadEnds(mIntMaze);
      std::vector<std::pair<int,int> >::const_iterator nonDeadEndIterator = nonDeadEnds.begin();
      for (int i=0; i!=nEnemies; ++i)
      {
        assert(nonDeadEndIterator != nonDeadEnds.end());
        const int x = (*nonDeadEndIterator).first;
        const int y = (*nonDeadEndIterator).second;
        assert(x!=mX || y!=mY);
        assert(mMaze[y][x] == msEmpty);
        mMaze[y][x] = msEnemy1;
        ++nonDeadEndIterator;
      }
      */
    }

  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGame::FormResize(TObject *Sender)
{
  ImageBuffer->Picture->Bitmap->Width  = ClientWidth;
  ImageBuffer->Picture->Bitmap->Height = ClientHeight;

  DrawScreen();
}
//---------------------------------------------------------------------------
void TFormMaziakGame::DrawScreen()
{
  const int sz = static_cast<int>(mMaze.size());
  const int block_width  = 1 + (ClientWidth  / mViewWidth );
  const int block_height = 1 + (ClientHeight / mViewHeight);

  if (mFighting > 0)
  {
    ++mFighting;
    if (mFighting == 13)
    {
      if (!mHasSword)
      {
        //Game over
        TimerPressKey->Enabled = false;
        TimerEnemy->Enabled = false;
        TimerShowSolution->Enabled = false;
        boost::scoped_ptr<TFormMaziakGameOver> f(new TFormMaziakGameOver(0));
        f->ShowModal();
        Close();
      }
      mFighting = 0;
      mHasSword = false;
    }
  }

  //Player-environment interactions
  switch (mMaze[mY][mX])
  {

    case msEmpty:
      break;
    case msWall:
      assert(!"Should not get here");
      throw std::logic_error("Player cannot be in wall");
    case msEnemy1: case msEnemy2:
      mFighting = 1;
      mMaze[mY][mX] = msEmpty;
      break;
    case msPrisoner1: case msPrisoner2:
      mMaze[mY][mX] = msEmpty;
      mSolution = GetDistancesPath(mDistances,mX,mY);
      assert(IsSquare(mSolution));
      mShowSolution = true;
      TimerShowSolution->Enabled = true;
      break;
    case msSword:
      mMaze[mY][mX] = msEmpty;
      mHasSword = true;
      break;
    case msExit:
      TimerPressKey->Enabled = false;
      TimerEnemy->Enabled = false;
      TimerShowSolution->Enabled = false;
      boost::scoped_ptr<TFormMaziakGameWon> f(new TFormMaziakGameWon(0));
      f->ShowModal();
      Close();
  }

  //Draw maze on buffer
  for (int y=0; y!=mViewHeight; ++y)
  {
    for (int x=0; x!=mViewWidth; ++x)
    {
      const int xVector = mX - (mViewWidth  / 2) + x;
      const int yVector = mY - (mViewHeight / 2) + y;

      const TRect r(
        (x * block_width )+0           ,  //Left
        (y * block_height)+0           ,  //Top
        (x * block_width )+block_width ,  //Right
        (y * block_height)+block_height); //Bottom

      //Clean square with black or golden path
      if ( xVector >= 0
        && yVector >= 0
        && xVector < sz
        && yVector < sz
        && (  mMaze[yVector][xVector] == msEmpty
           || mMaze[yVector][xVector] == msEnemy1
           || mMaze[yVector][xVector] == msEnemy2) 
        && mShowSolution
        && mSolution[yVector][xVector] == 1)
      {
        //Golden path
        ImageBuffer->Canvas->StretchDraw(r,ImagePath->Picture->Graphic);
      }
      else
      {
        ImageBuffer->Canvas->StretchDraw(r,ImageEmpty->Picture->Graphic);
      }

      //Draw real image
      const TImage * image = GetMazeImage(xVector,yVector);
      assert(image);
      ImageBuffer->Canvas->StretchDraw(r,image->Picture->Graphic);
    }
  }

  //Draw player on buffer
  {
    const TRect r(
      ((mViewWidth  / 2) * block_width )+0           ,  //Left
      ((mViewHeight / 2) * block_height)+0           ,  //Top
      ((mViewWidth  / 2) * block_width )+block_width ,  //Right
      ((mViewHeight / 2) * block_height)+block_height); //Bottom
    const TImage * const imagePlayer = GetPlayerImage(mDirection,mMoveNow);
    assert(imagePlayer);
    ImageBuffer->Canvas->StretchDraw(r,imagePlayer->Picture->Graphic);
  }

  //Draw buffer to screen
  this->Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);

}
//---------------------------------------------------------------------------
//Get the TImage from mMaze at (x,y)
const TImage * const TFormMaziakGame::GetMazeImage(
  const int x, const int y) const
{
  const int sz = static_cast<int>(mMaze.size());
  if ( x < 0
    || y < 0
    || x >= sz
    || y >= sz)
  {
    return ImageWall;
  }
  if ( mMaze[y][x] == msEmpty
    && mShowSolution
    && mSolution[y][x] == 1)
  {
    return ImagePath;
  }
  //What else here?
  switch(mMaze[y][x])
  {
    case msEmpty     : return ImageEmpty;
    case msWall      : return ImageWall;
    case msEnemy1    : return ImageEnemy1;
    case msEnemy2    : return ImageEnemy2;
    case msPrisoner1 : return ImagePrisoner1;
    case msPrisoner2 : return ImagePrisoner2;
    case msSword     : return ImageSword;
    case msExit      : return ImageExit;
    default:
      assert(!"Should not get here");
      throw std::logic_error("Unexpected MazeSquare at mMaze");
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGame::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (mFighting > 0) DrawScreen();

  mKeys.insert(Key);

  switch (Key)
  {
    case VK_LEFT : mKeys.erase(VK_RIGHT); break;
    case VK_RIGHT: mKeys.erase(VK_LEFT ); break;
    case VK_UP   : mKeys.erase(VK_DOWN ); break;
    case VK_DOWN : mKeys.erase(VK_UP   ); break;
    case VK_F1   : DoDebugF1(); break;
    case VK_F2   : DoDebugF2(); break;
  }

  if (mKeys.count(VK_F6)!=0 && mKeys.count(VK_F9)!=0) mCheat = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGame::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  mKeys.erase(Key);
  if (mKeys.count(VK_F6)==0 || mKeys.count(VK_F9)==0) mCheat = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGame::TimerPressKeyTimer(TObject *Sender)
{
  if (mFighting > 0) return;
  if (mKeys.empty()) { mMoveNow = none; }

  const std::set<WORD>::const_iterator j = mKeys.end();
  for(std::set<WORD>::const_iterator i = mKeys.begin(); i!=j; ++i)
  {
    //Check the keys pressed
    switch (*i)
    {
      case VK_LEFT :
        mDirection = pdLeft;
        if (!CanMoveTo(mMaze,mX-1,mY,mHasSword,mShowSolution))
        {
          mMoveNow = none;
          continue;
        }
        mMoveNow = (mMoveNow == left1 ? left2 : left1);
        --mX;
        break;
      case VK_RIGHT:
        mDirection = pdRight;
        if (!CanMoveTo(mMaze,mX+1,mY,mHasSword,mShowSolution))
        {
          mMoveNow = none;
          continue;
        }
        mMoveNow = (mMoveNow == right1 ? right2 : right1);
        ++mX;
        break;
      case VK_UP   :
        mDirection = pdUp;
        if (!CanMoveTo(mMaze,mX,mY-1,mHasSword,mShowSolution))
        {
          mMoveNow = none;
          continue;
        }
        mMoveNow = (mMoveNow == up1 ? up2 : up1);
        --mY;
        break;
      case VK_DOWN :
        mDirection = pdDown;
        if (!CanMoveTo(mMaze,mX,mY+1,mHasSword,mShowSolution))
        {
          mMoveNow = none;
          continue;
        }
        mMoveNow = (mMoveNow == down1 ? down2 : down1);
        ++mY;
        break;
      default:
        mMoveNow = none;
        continue;
    }
    //Draw the screen
    DrawScreen();
  }
}
//---------------------------------------------------------------------------
const bool CanMoveTo(
  const std::vector<std::vector<TFormMaziakGame::MazeSquare> >& maze,
  const int x, const int y,
  const bool hasSword,
  const bool showSolution)
{
  //Bump into edge
  if (x < 0) return false;
  if (y < 0) return false;
  const int maxy = static_cast<int>(maze.size());
  if (y >= maxy) return false;
  if (x >= static_cast<int>(maze[y].size())) return false;
  const TFormMaziakGame::MazeSquare s = maze[y][x];
  //Bump into wall
  if (s == TFormMaziakGame::msWall) return false;
  //Bump into sword
  if (s == TFormMaziakGame::msSword && hasSword) return false;
  //Bump into prisoner
  if (showSolution
    && (s == TFormMaziakGame::msPrisoner1
     || s == TFormMaziakGame::msPrisoner2) ) return false;
  //Bump into empty/enemy/exit, so player can move there
  return true;
}
//---------------------------------------------------------------------------
void TFormMaziakGame::DoDebugF1() const
{
  const int sizeVector = mMaze.size();

  for (int y=0; y!=mViewHeight; ++y)
  {
    String debug;
    debug+=y;
    debug+=':';
    for (int x=0; x!=mViewWidth; ++x)
    {
      const int xVector = mX - (mViewWidth  / 2) + x;
      const int yVector = mY - (mViewHeight / 2) + y;

      if ( xVector >= 0
        && xVector < sizeVector
        && yVector >= 0
        && yVector < sizeVector)
      {
        debug+=static_cast<int>(mMaze[yVector][xVector]);
      }
      else
      {
        debug+='x';
      }
    }
    OutputDebugString(debug.c_str());
  }

}
//---------------------------------------------------------------------------
void TFormMaziakGame::DoDebugF2() const
{
  //Obtain a bitmap of the entire maze
  const int sz = mMaze.size();
  Extctrls::TImage * const image = new Extctrls::TImage(0);
  image->Picture->Graphic = ImageEmpty->Picture->Graphic;
  image->Picture->Bitmap->Width = sz;
  image->Picture->Bitmap->Height = sz;

  for (int y=0; y!=sz; ++y)
  {
    for (int x=0; x!=sz; ++x)
    {
      const MazeSquare s = mMaze[y][x];
      switch(s)
      {
        case msEmpty     : SetPixel(image,x,y,255,255,255); break;
        case msWall      : SetPixel(image,x,y,  0,  0,  0); break;
        case msEnemy1    : SetPixel(image,x,y,  0,  0,255); break;
        case msEnemy2    : SetPixel(image,x,y,127,127,255); break;
        case msPrisoner1 : SetPixel(image,x,y,  0,255,  0); break;
        case msPrisoner2 : SetPixel(image,x,y,127,255,127); break;
        case msSword     : SetPixel(image,x,y,255,  0,  0); break;
        case msExit      : SetPixel(image,x,y,255,127,127); break;
      }
    }
  }
  //Player
  SetPixel(image,mX,mY,255,255,  0);

  image->Picture->SaveToFile("debug.bmp");

}
//---------------------------------------------------------------------------
const TImage * const TFormMaziakGame::GetPlayerImage(
  const PlayerDirection direction,
  const PlayerMove moveNow) const
{
  switch (mFighting)
  {
    case  0: break;
    case  1: return (mHasSword ? ImageFightSword1 : ImageFight1);
    case  2: return ImageFight2;
    case  3: return ImageFight3;
    case  4: return ImageFight4;
    case  5: return (mHasSword ? ImageFightSword1 : ImageFight1);
    case  6: return ImageFight2;
    case  7: return ImageFight3;
    case  8: return ImageFight4;
    case  9: return (mHasSword ? ImageFightWon1 : ImageFightLost1);
    case 10: return (mHasSword ? ImageFightWon2 : ImageFightLost2);
    case 11: return (mHasSword ? ImageFightWon1 : ImageFightLost1);
    case 12: return (mHasSword ? ImageFightWon2 : ImageFightLost2);
  }

  switch (direction)
  {
    case pdUp:
    {
      switch (moveNow)
      {
        case none: return (mHasSword ? ImagePlayerLookUpSword : ImagePlayerLookUp);
        case up1:  return (mHasSword ? ImagePlayerWalkUpSword1 : ImagePlayerWalkUp1);
        case up2:  return (mHasSword ? ImagePlayerWalkUpSword2 : ImagePlayerWalkUp2);
        default:
          assert("!Should not get here");
          throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == up");
      }
    }
    //break; Unreachable
    case pdRight:
    {
      switch (moveNow)
      {
        case none:   return (mHasSword ? ImagePlayerLookRightSword : ImagePlayerLookRight);
        case right1: return (mHasSword ? ImagePlayerWalkRightSword1 : ImagePlayerWalkRight1);
        case right2: return (mHasSword ? ImagePlayerWalkRightSword2 : ImagePlayerWalkRight2);
        default:
          assert("!Should not get here");
          throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == right");
      }
    }
    //break; Unreachable
    case pdDown:
    {
      switch (moveNow)
      {
        case none:  return (mHasSword ? ImagePlayerLookDownSword : ImagePlayerLookDown);
        case down1: return (mHasSword ? ImagePlayerWalkDownSword1 : ImagePlayerWalkDown1);
        case down2: return (mHasSword ? ImagePlayerWalkDownSword2 : ImagePlayerWalkDown2);
        default:
          assert("!Should not get here");
          throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == down");
      }
    }
    //break; Unreachable
    case pdLeft:
    {
      switch (moveNow)
      {
        case none:  return (mHasSword ? ImagePlayerLookLeftSword : ImagePlayerLookLeft);
        case left1: return (mHasSword ? ImagePlayerWalkLeftSword1 : ImagePlayerWalkLeft1);
        case left2: return (mHasSword ? ImagePlayerWalkLeftSword2 : ImagePlayerWalkLeft2);
        default:
          assert("!Should not get here");
          throw std::logic_error("Unsupported PlayerMove mMoveNow for mDirection == left");
      }
    }
    //break; Unreachable
    default:
      assert("!Should not get here");
      throw std::logic_error("Unsupported PlayerDirection");
  }
  //Unreachable
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGame::TimerEnemyTimer(TObject *Sender)
{
  //Move them
  const int minx = std::max(0,mX - mViewWidth );
  const int miny = std::max(0,mY - mViewHeight);
  const int maxy = std::min(static_cast<int>(mMaze.size()),mY + mViewHeight);
  const int maxx = std::min(static_cast<int>(mMaze[mY].size()),mX + mViewWidth);
  assert(miny >= 0);
  assert(miny <= static_cast<int>(mMaze.size()));
  assert(maxy >= 0);
  assert(maxy <= static_cast<int>(mMaze.size()));
  assert(minx >= 0);
  assert(minx <= static_cast<int>(mMaze[mY].size()));
  assert(maxx >= 0);
  assert(maxx <= static_cast<int>(mMaze[mY].size()));
  assert(miny <= maxy);
  assert(minx <= maxx);
  for (int y=miny; y!=maxy; ++y)
  {
    assert( y >= 0);
    assert( y < static_cast<int>(mMaze.size()));
    for (int x=minx; x!=maxx; ++x)
    {
      //msEnemy1 changes to msEnemy2
      //Only msEnemy2 moves, after moving turning to msEnemy1
      assert( x >= 0);
      assert( x < static_cast<int>(mMaze[y].size()));
      const MazeSquare s = mMaze[y][x];

      if (s == msEnemy1)
      {
        //msEnemy1 changes to msEnemy2
        mMaze[y][x] = msEnemy2;
        continue;
      }
      else if (s == msEnemy2)
      {
        //msEnemy 2 tries to walk
        std::vector<std::pair<int,int> > moves;
        if (y > mY && y >        1 && mMaze[y-1][x  ] == msEmpty) moves.push_back(std::make_pair(x,y-1));
        if (x < mX && x < maxx - 1 && mMaze[y  ][x+1] == msEmpty) moves.push_back(std::make_pair(x+1,y));
        if (y < mY && y < maxy - 1 && mMaze[y+1][x  ] == msEmpty) moves.push_back(std::make_pair(x,y+1));
        if (x > mX && x >        1 && mMaze[y  ][x-1] == msEmpty) moves.push_back(std::make_pair(x-1,y));
        const int nMoves = static_cast<int>(moves.size());
        if (nMoves == 1)
        {
          mMaze[y][x] = msEnemy1;
          std::swap(mMaze[y][x],mMaze[moves[0].second][moves[0].first]);
        }
        else if (nMoves > 1)
        {
          assert(nMoves == 2);
          mMaze[y][x] = msEnemy1;
          const int moveIndex = (std::rand() >> 4) % nMoves;
          std::swap(mMaze[y][x],mMaze[moves[moveIndex].second][moves[moveIndex].first]);
        }
      }
      else if (s==msPrisoner1)
      {
        //Animate prisoners
        mMaze[y][x] = msPrisoner2;
      }
      else if (s==msPrisoner2)
      {
        //Animate prisoners
        mMaze[y][x] = msPrisoner1;
      }
    }
  }
  DrawScreen();
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakGame::TimerShowSolutionTimer(TObject *Sender)
{
  mShowSolution = false;
  TimerShowSolution->Enabled = false;
}
//---------------------------------------------------------------------------
const std::vector<std::pair<int,int> > GetShuffledDeadEnds(
  const std::vector<std::vector<int> >& intMaze)
{
  std::vector<std::pair<int,int> > deadEnds = GetDeadEnds(intMaze);
  std::random_shuffle(deadEnds.begin(), deadEnds.end());
  return deadEnds;
}
//---------------------------------------------------------------------------
const std::vector<std::pair<int,int> > GetShuffledNonDeadEnds(
  const std::vector<std::vector<int> >& intMaze)
{
  std::vector<std::pair<int,int> > nonDeadEnds = GetNonDeadEnds(intMaze);
  std::random_shuffle(nonDeadEnds.begin(), nonDeadEnds.end());
  return nonDeadEnds;
}
//---------------------------------------------------------------------------
//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl
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

  unsigned char * const line
    = static_cast<unsigned char *>(image->Picture->Bitmap->ScanLine[y]);

  line[x*3+2] = red;
  line[x*3+1] = green;
  line[x*3+0] = blue;
}
//---------------------------------------------------------------------------



