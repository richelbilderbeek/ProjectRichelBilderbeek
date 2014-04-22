//---------------------------------------------------------------------------
/*
    Met Z'n Drieën. A 3-player tic-tac-toe-like game.
    Copyright (C) 2010  Richel Bilderbeek

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

#include "UnitFormMain.h"
//---------------------------------------------------------------------------
#include "UnitFormGewonnen.h"
#include "UnitFormStoppen.h"
//---------------------------------------------------------------------------
#include <cassert>
#include <ctime>
#include <boost/scoped_ptr.hpp>
#include "UnitFormSprites.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(
  TComponent* Owner,
  const bool player1_human,
  const bool player2_human,
  const bool player3_human)
  : TForm(Owner),
    m_player1_human(player1_human),
    m_player2_human(player2_human),
    m_player3_human(player3_human),
    mBlocks(16, std::vector<EnumBlock>(12,NoPlayer)),
    mPlayer(Player1),
    mMaxx(16),
    mMaxy(12)
{
  std::srand(std::clock());
  mNextRobotMove.x = -1;
  mNextRobotMove.y = -1;
  ImageBuffer->Picture->Bitmap->Width  = 800;
  ImageBuffer->Picture->Bitmap->Height = 600;
  DrawScreen();
  if (IsRobot(mPlayer)) TimerThinker->Enabled = true;
}
//---------------------------------------------------------------------------
void TFormMain::DrawScreen()
{

  //Draw blocks on buffer
  assert(FormSprites);
  for (int y=0; y!=mMaxy; ++y)
  {
    for (int x=0; x!=mMaxx; ++x)
    {
      const int xCo = x * 50;
      const int yCo = y * 50;
      Graphics::TGraphic * graphic = 0;
      switch (mBlocks[x][y])
      {
        case Player1:
          graphic = FormSprites->ImagePlayer1->Picture->Graphic;
          break;
        case Player2:
          graphic = FormSprites->ImagePlayer2->Picture->Graphic;
          break;
        case Player3:
          graphic = FormSprites->ImagePlayer3->Picture->Graphic;
          break;
        case NoPlayer:
          graphic = FormSprites->ImageEmpty->Picture->Graphic;
          break;
        default: assert(!"Should not get here");
      }
      //Draw sprite on buffer
      ImageBuffer->Canvas->Draw(xCo,yCo,graphic);
    }
  }
  //Draw buffer on canvas
  Canvas->Draw(0,0,ImageBuffer->Picture->Graphic);

  //Draw players on canvas (buffer is only used as game arena)
  if (mPlayer==Player1)
  {
    Canvas->Draw(Image1->Left,Image1->Top,FormSprites->ImagePlayer1->Picture->Graphic);
  }
  else
  {
    Canvas->Draw(Image1->Left,Image1->Top,FormSprites->ImagePlayer1Grey->Picture->Graphic);
  }
  if (mPlayer==Player2)
  {
    Canvas->Draw(Image2->Left,Image2->Top,FormSprites->ImagePlayer2->Picture->Graphic);
  }
  else
  {
    Canvas->Draw(Image2->Left,Image2->Top,FormSprites->ImagePlayer2Grey->Picture->Graphic);
  }
  if (mPlayer==Player3)
  {
    Canvas->Draw(Image3->Left,Image3->Top,FormSprites->ImagePlayer3->Picture->Graphic);
  }
  else
  {
    Canvas->Draw(Image3->Left,Image3->Top,FormSprites->ImagePlayer3Grey->Picture->Graphic);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  //When the AI is 'thinking' no clicks are allowed
  if (IsRobot(mPlayer)==true && Sender->ClassNameIs("TTimer")==false) return;

  //ImageBuffer->Visible = false;
  const int x = X / 50;
  const int y = Y / 50;
  //Is this a relevant move?
  if (mBlocks[x][y] != NoPlayer) return;
  // Yes, a relevant move
  mBlocks[x][y] = mPlayer;
  mPlayer = GetNextPlayer(mPlayer);
  //Start the AI robot!
  if (IsRobot(mPlayer)) TimerThinker->Enabled = true;

  DrawScreen();

  //Check for three on a row
  {
    for (int y=0; y!=mMaxy; ++y)
    {
      for (int x=0; x!=mMaxx; ++x)
      {
        if (mBlocks[x][y] == NoPlayer) continue;
        EnumBlock winner = NoPlayer;
        //Horizontal
        if (x + 2 < mMaxx && mBlocks[x][y] == mBlocks[x+1][y] && mBlocks[x+1][y] == mBlocks[x+2][y])
        {
          winner = mBlocks[x][y];
        }
        //Vertical
        if (y + 2 < mMaxy && mBlocks[x][y] == mBlocks[x][y+1] && mBlocks[x][y+1] == mBlocks[x][y+2])
        {
          winner = mBlocks[x][y];
        }
        if (winner!=NoPlayer)
        {
          //A winner has been found!
          TimerDoer->Enabled = false;
          TimerThinker->Enabled = false;
          boost::scoped_ptr<TFormGewonnen> formGewonnen(
            new TFormGewonnen(0,static_cast<int>(winner),!IsRobot(winner)));
          formGewonnen->Hide();
          formGewonnen->ShowModal();
          //Show FormStoppen
          boost::scoped_ptr<TFormStoppen> formStoppen(new TFormStoppen(0));
          formStoppen->Hide();
          formStoppen->ShowModal();
          if (formStoppen->ModalResult == 1)
          { //Nog een keer
            TimerDoer->Enabled = true;
            mBlocks = std::vector<std::vector<EnumBlock> >(16, std::vector<EnumBlock>(12,NoPlayer));
            mPlayer = Player1;
            if (IsRobot(mPlayer)) TimerThinker->Enabled = true;
            DrawScreen();
          }
          else
          { //Stoppen
            ModalResult = 1;
          }


        }

      }
    }
  }
}
//---------------------------------------------------------------------------



void __fastcall TFormMain::TimerThinkerTimer(TObject *Sender)
{
  //Check if moves already have been calculated
  if (mNextRobotMove.x!=-1) return;
  if (mNextRobotMove.y!=-1) return;
  if (IsRobot(mPlayer)==false)
  {
    OutputDebugString("Hey, I ain't a player!");
    return;
  }
  int xMove = -1;
  int yMove = -1;
  //Make a non-random move
  if (xMove == -1 && yMove == -1) CheckTwoHorizontalOwn(xMove,yMove);
  if (xMove == -1 && yMove == -1) CheckTwoVerticalOwn(xMove,yMove);
  if (xMove == -1 && yMove == -1) CheckTwoOther(xMove,yMove);
  if (xMove == -1 && yMove == -1) CheckTwoDiagonally(xMove,yMove);
  if (xMove == -1 && yMove == -1) CheckOneOther(xMove,yMove);
  if (xMove == -1 && yMove == -1) MakeRandomMove(xMove,yMove);
  assert(IsValidMove(xMove,yMove));
  //Do it then...
  mNextRobotMove.x = xMove;
  mNextRobotMove.y = yMove;
  //Click it on the playfield virtually
  //This will be done by TimerDoer
}
//---------------------------------------------------------------------------
void TFormMain::CheckTwoHorizontalOwn(int& xMove,int& yMove) const
{
  assert(xMove == -1 && yMove == -1);
  for (int y=0; y!=mMaxy; ++y)
  {
    for (int x=0; x!=mMaxx-1; ++x) //-1 to prevent out of range
    {
      //Two consequtive selfs
      if (mBlocks[x][y] == mPlayer && mBlocks[x+1][y] == mPlayer)
      {
        if (x >= 1)
        {
          if (mBlocks[x-1][y] == NoPlayer)
          {
            xMove = x-1; yMove = y;
            assert(IsValidMove(xMove,yMove));
            return;
          }
        }
        if (x < mMaxx-2 && mBlocks[x+2][y] == NoPlayer)
        {
          xMove = x+2; yMove = y;
          assert(IsValidMove(xMove,yMove));
          return;
        }
      }
      //Perhaps a gap?
      if (x < mMaxx-2)
      {
        if (mBlocks[x][y] == mPlayer && mBlocks[x+1][y] == NoPlayer && mBlocks[x+2][y] == mPlayer)
        {
            xMove = x+1; yMove = y;
            assert(IsValidMove(xMove,yMove));
            return;
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void TFormMain::CheckTwoVerticalOwn(int& xMove,int& yMove) const
{
  assert(xMove == -1 && yMove == -1);
  for (int y=0; y!=mMaxy-1; ++y) //-1 to prevent out of range
  {
    for (int x=0; x!=mMaxx; ++x)
    {
      //Two consequtive selfs?
      if (mBlocks[x][y] == mPlayer && mBlocks[x][y+1] == mPlayer)
      {
        if (y >= 1)
        {
          if (mBlocks[x][y-1] == NoPlayer)
          {
            xMove = x; yMove = y-1;
            assert(IsValidMove(xMove,yMove));
            return;
          }
        }
        if (y < mMaxy-2)
        {
          if (mBlocks[x][y+2] == NoPlayer)
          {
            xMove = x; yMove = y+2;
            assert(IsValidMove(xMove,yMove));
            return;
          }
        }
      }
      //Perhaps a gap?
      if (y < mMaxy-2)
      {
        if (mBlocks[x][y] == mPlayer && mBlocks[x][y+1] == NoPlayer && mBlocks[x][y+2] == mPlayer)
        {
            xMove = x; yMove = y+1;
            assert(IsValidMove(xMove,yMove));
            return;
        }
      }

    }
  }
}
//---------------------------------------------------------------------------
void TFormMain::CheckTwoOther(int& xMove,int& yMove) const
{
  assert(xMove == -1 && yMove == -1);
  const std::vector<GameMove> moves1(GetTwoHorizontalOtherMoves());
  const std::vector<GameMove> moves2(GetTwoVerticalOtherMoves());
  const std::vector<GameMove> moves(Concatenate(moves1,moves2));
  assert(moves.size() == moves1.size() + moves2.size());

  const int nMoves = moves.size();
  if (nMoves==0) return;

  { //Get moves anti-player
    std::vector<GameMove> antiPlayerMoves;
    for (int i=0; i<nMoves; ++i)
    {
      assert(IsValidMove(moves[i]));
      if (IsRobot(moves[i].anti) == false) antiPlayerMoves.push_back(moves[i]);
    }
    //If there are anti-player moves, choose one at random
    if (antiPlayerMoves.empty()==false)
    {
      const int nAntiPlayerMoves = antiPlayerMoves.size();
      const int index = std::rand() % nAntiPlayerMoves;
      xMove = antiPlayerMoves[index].x;
      yMove = antiPlayerMoves[index].y;
      assert(IsValidMove(xMove,yMove));
      return;
    }
  }
  { //Get moves anti-next-player
    std::vector<GameMove> antiNextPlayerMoves;
    for (int i=0; i<nMoves; ++i)
    {
      if (GetNextPlayer(mPlayer) == moves[i].anti) antiNextPlayerMoves.push_back(moves[i]);
    }
    //If there are anti-next-player moves, choose one at random
    if (antiNextPlayerMoves.empty()==false)
    {
      const int nAntiNextPlayerMoves = antiNextPlayerMoves.size();
      const int index = std::rand() % nAntiNextPlayerMoves;
      xMove = antiNextPlayerMoves[index].x;
      yMove = antiNextPlayerMoves[index].y;
      assert(IsValidMove(xMove,yMove));
      return;
    }
  }
  //Choose a move at random
  {
    const int index = std::rand() % nMoves;
    xMove = moves[index].x;
    yMove = moves[index].y;
    assert(IsValidMove(xMove,yMove));
  }
}
//---------------------------------------------------------------------------
const std::vector<GameMove> TFormMain::GetTwoHorizontalOtherMoves() const
{
  std::vector<GameMove> moves;
  for (int y=0; y!=mMaxy; ++y)
  {
    for (int x=0; x!=mMaxx-1; ++x) //-1 to prevent out of range
    {
      //Check consequtive
      if (mBlocks[x][y]!=NoPlayer && mBlocks[x][y] == mBlocks[x+1][y])
      {
        //Check A X B
        if (x > 0 && mBlocks[x-1][y] == NoPlayer)
        {
          //xMove = x-1; yMove = y;
          GameMove move;
          move.x = x-1;
          move.y = y;
          move.anti = mBlocks[x][y];
          assert(IsValidMove(move));
          moves.push_back(move);
        }
        //Check X B C
        if (x < mMaxx-2 && mBlocks[x+2][y] == NoPlayer)
        {
          GameMove move;
          move.x = x+2;
          move.y = y;
          move.anti = mBlocks[x][y];
          assert(IsValidMove(move));
          moves.push_back(move);
        }
      }
      //Check gap, also X B C
      if (mBlocks[x][y] != NoPlayer && x + 2 < mMaxx && mBlocks[x+1][y] == NoPlayer && mBlocks[x][y] == mBlocks[x+2][y])
      {
        GameMove move;
        move.x = x+1;
        move.y = y;
        move.anti = mBlocks[x][y];
        assert(IsValidMove(move));
        moves.push_back(move);
      }

    }
  }
  return moves;
}
//---------------------------------------------------------------------------
//A X B C (x is focus of for loop)
const std::vector<GameMove> TFormMain::GetTwoVerticalOtherMoves() const
{
  std::vector<GameMove> moves;
  for (int y=0; y!=mMaxy-1; ++y) //-1 to prevent out of range
  {
    for (int x=0; x!=mMaxx; ++x)
    {
      //Check consequtive
      if (mBlocks[x][y] != NoPlayer && mBlocks[x][y] == mBlocks[x][y+1])
      {
        //Check A X B
        if (y > 0 && mBlocks[x][y-1] == NoPlayer)
        {
          GameMove move;
          move.x = x;
          move.y = y-1;
          move.anti = mBlocks[x][y];
          assert(IsValidMove(move));
          moves.push_back(move);
        }
        //Check X B C
        if (y < mMaxy-2 && mBlocks[x][y+2] == NoPlayer)
        {
          GameMove move;
          move.x = x;
          move.y = y+2;
          move.anti = mBlocks[x][y];
          assert(IsValidMove(move));
          moves.push_back(move);
        }
      }
      //Check gap, also X B C
      if (mBlocks[x][y] != NoPlayer && y < mMaxy && mBlocks[x][y+1] == NoPlayer && mBlocks[x][y] == mBlocks[x][y+2])
      {
        GameMove move;
        move.x = x;
        move.y = y+1;
        move.anti = mBlocks[x][y];
        assert(IsValidMove(move));
        moves.push_back(move);
      }
    }
  }
  return moves;
}
//---------------------------------------------------------------------------
void TFormMain::CheckTwoDiagonally(int& xMove,int& yMove) const
{
  assert(xMove == -1 && yMove == -1);
  std::vector<GameMove> moves;

  for (int y=0; y!=mMaxy-1; ++y) //-1 To prevent out of range
  {
    for (int x=0; x!=mMaxx-1; ++x) //-1 to prevent out of range
    {
      if (mBlocks[x][y] == mPlayer && mBlocks[x+1][y+1] == mPlayer)
      {
        if (mBlocks[x+1][y] == NoPlayer)
        {
          GameMove move;
          move.x = x+1;
          move.y = y;
          assert(IsValidMove(move));
          moves.push_back(move);
        }
        if (mBlocks[x][y+1] == NoPlayer)
        {
          GameMove move;
          move.x = x;
          move.y = y+1;
          assert(IsValidMove(move));
          moves.push_back(move);
        }
      }
    }
  }
  const int nMoves = moves.size();
  if (nMoves == 0) return;
  const int index = std::rand() % nMoves;
  xMove = moves[index].x;
  yMove = moves[index].y;
  assert(IsValidMove(xMove,yMove));
}
//---------------------------------------------------------------------------
void TFormMain::CheckOneOther(int& xMove,int& yMove) const
{
  assert(xMove == -1 && yMove == -1);
  std::vector<GameMove> moves;

  for (int y=0; y!=mMaxy; ++y)
  {
    for (int x=0; x!=mMaxx; ++x)
    {
      if (mBlocks[x][y] != NoPlayer)
      {
        if (y >= 1)
        {
          if (mBlocks[x][y-1] == NoPlayer)
          {
            GameMove move;
            move.x = x;
            move.y = y-1;
            move.anti = mBlocks[x][y];
            assert(IsValidMove(move));
            moves.push_back(move);
          }
        }
        if (y < mMaxy-1)
        {
          if (mBlocks[x][y+1] == NoPlayer)
          {
            GameMove move;
            move.x = x;
            move.y = y+1;
            move.anti = mBlocks[x][y];
            assert(IsValidMove(move));
            moves.push_back(move);
          }
        }
        if (x >= 1)
        {
          if (mBlocks[x-1][y] == NoPlayer)
          {
            GameMove move;
            move.x = x-1;
            move.y = y;
            move.anti = mBlocks[x][y];
            assert(IsValidMove(move));
            moves.push_back(move);
          }
        }
        if (x < mMaxx-1)
        {
          if (mBlocks[x+1][y] == NoPlayer)
          {
            GameMove move;
            move.x = x+1;
            move.y = y;
            move.anti = mBlocks[x][y];
            assert(IsValidMove(move));
            moves.push_back(move);
          }
        }
      }
    }
  }
  const int nMoves = moves.size();
  if (nMoves == 0) return;

  { //Get moves anti-player
    std::vector<GameMove> antiPlayerMoves;
    for (int i=0; i<nMoves; ++i)
    {
      if (IsRobot(moves[i].anti) == false) antiPlayerMoves.push_back(moves[i]);
    }
    //If there are anti-player moves, choose one at random
    if (antiPlayerMoves.empty()==false)
    {
      const int nAntiPlayerMoves = antiPlayerMoves.size();
      const int index = std::rand() % nAntiPlayerMoves;
      xMove = antiPlayerMoves[index].x;
      yMove = antiPlayerMoves[index].y;
      assert(IsValidMove(antiPlayerMoves[index]));
      return;
    }
  }
  { //Get moves anti-next-player
    std::vector<GameMove> antiNextPlayerMoves;
    for (int i=0; i<nMoves; ++i)
    {
      if (GetNextPlayer(mPlayer) == moves[i].anti) antiNextPlayerMoves.push_back(moves[i]);
    }
    //If there are anti-next-player moves, choose one at random
    if (antiNextPlayerMoves.empty()==false)
    {
      const int nAntiNextPlayerMoves = antiNextPlayerMoves.size();
      const int index = std::rand() % nAntiNextPlayerMoves;
      xMove = antiNextPlayerMoves[index].x;
      yMove = antiNextPlayerMoves[index].y;
      assert(IsValidMove(antiNextPlayerMoves[index]));
      return;
    }
  }
  //Choose a move at random
  {
    const int index = std::rand() % nMoves;
    xMove = moves[index].x;
    yMove = moves[index].y;
    assert(IsValidMove(xMove,yMove));
  }

}
//---------------------------------------------------------------------------


void TFormMain::MakeRandomMove(int& xMove,int& yMove) const
{
  assert(xMove == -1 && yMove == -1);
  while(1)
  {
    xMove = std::rand() % mMaxx;
    yMove = std::rand() % mMaxy;
    if (mBlocks[xMove][yMove] == NoPlayer)
    {
      assert(IsValidMove(xMove,yMove));
      return;
    }
  }
}
//---------------------------------------------------------------------------
const bool TFormMain::IsRobot(const EnumBlock player) const
{
  assert(player!=NoPlayer);
  switch (player)
  {
    case Player1: return !m_player1_human;
    case Player2: return !m_player2_human;
    case Player3: return !m_player3_human;
    default: assert(!"Should not get here");
  }
  assert(!"Should not get here");
  return true;
}
//---------------------------------------------------------------------------
const String TFormMain::GetName(const EnumBlock player) const
{
  assert(player!=NoPlayer);
  if (IsRobot(player)==true) return "Robot";
  switch (player)
  {
    case Player1: return "Speler 1";
    case Player2: return "Speler 2";
    case Player3: return "Speler 3";
    default: assert(!"Should not get here");
  }
  assert(!"Should not get here");
  return "Richel";
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerDoerTimer(TObject *Sender)
{
  if (mNextRobotMove.x!=-1 && mNextRobotMove.y!=-1)
  {
    //Move in range?
    assert(mNextRobotMove.x >= 0 && mNextRobotMove.x < mMaxx);
    assert(mNextRobotMove.y >= 0 && mNextRobotMove.y < mMaxy);
    //Move relevant?
    assert(mBlocks[mNextRobotMove.x][mNextRobotMove.y] == NoPlayer);
    TimerThinker->Enabled = false;
    FormMouseDown(TimerDoer,TMouseButton(), TShiftState(), mNextRobotMove.x*50, mNextRobotMove.y*50);
    mNextRobotMove.x=-1;
    mNextRobotMove.y=-1;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TimerDebugTimer(TObject *Sender)
{
  String s = "Debug: ";
  s+=" TimerThinker: "; s+=(TimerThinker->Enabled ? "Y" : "N");
  s+=" TimerDoer: ";s+=(TimerDoer->Enabled ? "Y" : "N");
  s+=" Player: ";s+= GetName(mPlayer);
  s+=" IsRobot: ";s+=(IsRobot(mPlayer) ? "Y" : "N");
  OutputDebugString(s.c_str());

}
//---------------------------------------------------------------------------
const bool TFormMain::IsValidMove(const int x,const int y) const
{
  if ( x < 0)
  {
    const String s = "x < 0 : " +IntToStr(x); OutputDebugString(s.c_str());
    return false;
  }
  if (x >= mMaxx)
  {
    const String s = "x >= mMaxx : " +IntToStr(x); OutputDebugString(s.c_str());
    return false;
  }
  if (y < 0)
  {
    const String s = "y < 0 : " +IntToStr(y); OutputDebugString(s.c_str());
    return false;
  }
  if (y >= mMaxy)
  {
    String s = "y >= mMaxy : "  + IntToStr(x); OutputDebugString(s.c_str());
    return false;
  }
  if (mBlocks[x][y] != NoPlayer)
  {
    String s = "Already occupied : (" +IntToStr(x) + "," + IntToStr(y) + ")";
    OutputDebugString(s.c_str());
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
const bool TFormMain::IsValidMove(const GameMove& move) const
{
  return IsValidMove(move.x,move.y);
}
//---------------------------------------------------------------------------
const double uniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::FormPaint(TObject *Sender)
{
  DrawScreen();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::LabelQuitClick(TObject *Sender)
{
  ModalResult = 1;
}
//---------------------------------------------------------------------------

