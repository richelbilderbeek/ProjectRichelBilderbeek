//---------------------------------------------------------------------------
/*
  Classic Tron, a simple game
  Copyright (C) 2008  Richel Bilderbeek

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
#include <memory>
#include <cmath>
#include <cassert>
#include "UnitGraphics.h"
#include <vcl.h>
#pragma hdrstop

#include "UnitFormClassicTronGame.h"
#include "UnitFormChart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormClassicTronGame *FormClassicTronGame;
//---------------------------------------------------------------------------
__fastcall TFormClassicTronGame::TFormClassicTronGame(
  TComponent* Owner,
  const std::vector<Player>& players,
  const int speed,
  const int maxx,
  const int maxy,
  const bool donutShapedWorld,
  const bool canWalkThroughOwnColor)
  : TForm(Owner),
    mPlayers(players),
    mMaxx(maxx),
    mMaxy(maxy),
    mDonutShapedWorld(donutShapedWorld),
    mCanWalkThroughOwnColor(canWalkThroughOwnColor)
{
  this->Constraints->MinWidth  = maxx + (Width - ClientWidth);
  this->Constraints->MinHeight = maxy + (Height - ClientHeight);

  //Put the players on screen in the correct position
  {
    const int nPlayers = mPlayers.size();
    for (int i=0; i!=nPlayers; ++i)
    {
      const double fraction = static_cast<double>(i) / static_cast<double>(nPlayers);
      const double angle = (0.5 * M_PI) + ( fraction * M_PI * 2.0);
      mPlayers[i].x = (static_cast<double>(mMaxx) / 2.0)
        + (  std::sin( angle ) * 10.0 );
      mPlayers[i].y = (static_cast<double>(mMaxx) / 2.0)
        + ( -std::cos( angle ) * 10.0 );
      if (angle < 0.75 * M_PI) mPlayers[i].direction = 1;
      else if (angle < 1.25 * M_PI) mPlayers[i].direction = 2;
      else if (angle < 1.75 * M_PI) mPlayers[i].direction = 3;
      else if (angle < 2.25 * M_PI) mPlayers[i].direction = 0;
      else if (angle < 2.75 * M_PI) mPlayers[i].direction = 1;
    }
  }
  TimerGame->Interval = speed;
  ImageBuffer->Picture->Graphic->Width  = mMaxx;
  ImageBuffer->Picture->Graphic->Height = mMaxy;
  PaintVcl(ImageBuffer,clBlack);
  TimerGame->OnTimer(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormClassicTronGame::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  const std::vector<Player>::iterator j = mPlayers.end();
  for (std::vector<Player>::iterator i = mPlayers.begin(); i!=j; ++i)
  {
    if (i->keyLeft  == Key) { i->direction = (i->direction + 3) % 4; }
    if (i->keyRight == Key) { i->direction = (i->direction + 1) % 4; }
  }
  //Caption = Key;
}
//---------------------------------------------------------------------------
void __fastcall TFormClassicTronGame::TimerGameTimer(TObject *Sender)
{
  //Check for collisions
  {
    const std::vector<Player>::iterator j = mPlayers.end();
    for (std::vector<Player>::iterator i = mPlayers.begin(); i!=j; ++i)
    {
      int xTo = (*i).x;
      int yTo = (*i).y;
      switch ((*i).direction)
      {
        case 0: //Up
          yTo = (*i).y - 1;
          if (mDonutShapedWorld == true && yTo < 0) yTo+=mMaxy;
          break;
        case 1: //Right
          xTo = (*i).x + 1;
          if (mDonutShapedWorld == true && xTo >= mMaxx) xTo-=mMaxx;
          break;
        case 2: //Down
          yTo = (*i).y + 1;
          if (mDonutShapedWorld == true && yTo >= mMaxy) yTo-=mMaxy;
          break;
        case 3: //Left
          xTo = (*i).x - 1;
          if (mDonutShapedWorld == true && xTo < 0) xTo+=mMaxx;
          break;
      }
      if (mDonutShapedWorld == false
        && ( xTo < 0 || yTo < 0 || xTo >= mMaxx || yTo >= mMaxy) )
      {
        RemovePointFromLosers( (*i).color );
        RemoveColor(ImageBuffer, (*i).color );
        (*i).direction = ((*i).direction + 2) % 4;
        continue;
      }
      const TColor color = GetPixelVcl(ImageBuffer, xTo, yTo);
      if (color == clBlack || color == static_cast<TColor>(-1) ) continue; //Nothing there...
      if (color!=(*i).color)
      {
        AddPointToWinners(color);
        RemovePointFromLosers( (*i).color );
        RemoveColor(ImageBuffer, color );
      }
      if (mCanWalkThroughOwnColor == false && color==(*i).color)
      {
        RemovePointFromLosers( (*i).color );
        RemoveColor(ImageBuffer, color );
      }
    }
  }

  //Move the players
  {
    const std::vector<Player>::iterator j = mPlayers.end();
    for (std::vector<Player>::iterator i = mPlayers.begin(); i!=j; ++i)
    {
      switch ((*i).direction)
      {
        case 0: //Up
          --(*i).y;
          if ((*i).y < 0) (*i).y+=mMaxy;
          break;
        case 1: //Right
          ++(*i).x;
          if ((*i).x >= mMaxx) (*i).x-=mMaxx;
          break;
        case 2: //Down
          ++(*i).y;
          if ((*i).y >= mMaxy) (*i).y-=mMaxy;
          break;
        case 3: //Left
          --(*i).x;
          if ((*i).x < 0) (*i).x+=mMaxx;
          break;
      }
    }
  }


  //Draw new player locations to buffer
  {
    const std::vector<Player>::iterator j = mPlayers.end();
    for (std::vector<Player>::iterator i = mPlayers.begin(); i!=j; ++i)
    {
      SetPixel(ImageBuffer, (*i).x, (*i).y, (*i).color );
    }
  }

  //Draw buffer to screen
  Canvas->StretchDraw(this->ClientRect,ImageBuffer->Picture->Graphic);
}
//---------------------------------------------------------------------------
void TFormClassicTronGame::AddPointToWinners(const TColor color)
{
  const std::vector<Player>::iterator j = mPlayers.end();
  for (std::vector<Player>::iterator i = mPlayers.begin(); i!=j; ++i)
  {
    if (i->color == color) ++(i->nWins);
  }
}
//---------------------------------------------------------------------------
void TFormClassicTronGame::RemovePointFromLosers(const TColor color)
{
  const std::vector<Player>::iterator j = mPlayers.end();
  for (std::vector<Player>::iterator i = mPlayers.begin(); i!=j; ++i)
  {
    if (i->color == color) ++(i->nLose);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormClassicTronGame::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  TimerGame->Enabled = false;
  const int size = mPlayers.size();
  std::vector<int> losses(size);
  std::vector<int> wins(size);
  for (int i=0; i!=size; ++i)
  {
    losses[i] = mPlayers[i].nLose;
    wins[i]   = mPlayers[i].nWins;
  }

  std::auto_ptr<TFormChart> f(new TFormChart(0,losses,wins));
  f->ShowModal();
}
//---------------------------------------------------------------------------


