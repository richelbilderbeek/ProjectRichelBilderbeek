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
#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
#include <cassert>
#include <vector>
//---------------------------------------------------------------------------
enum EnumBlock { Player1, Player2, Player3, NoPlayer };
struct GameMove { int x; int y; EnumBlock anti; };
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TImage *ImageBuffer;
        TTimer *TimerThinker;
        TTimer *TimerDoer;
        TTimer *TimerDebug;
        TLabel *LabelQuit;
        void __fastcall FormMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall TimerThinkerTimer(TObject *Sender);
        void __fastcall TimerDoerTimer(TObject *Sender);
        void __fastcall TimerDebugTimer(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall LabelQuitClick(TObject *Sender);
private:	// User declarations
  GameMove mNextRobotMove;
  std::vector<std::vector<EnumBlock> > mBlocks;
  void DrawScreen();
  EnumBlock mPlayer;
  void CheckTwoHorizontalOwn(int& xMove,int& yMove) const;
  void CheckTwoVerticalOwn(int& xMove,int& yMove) const;
  const bool IsValidMove(const GameMove& move) const;
  const bool IsValidMove(const int x,const int y) const;
  void CheckTwoOther(int& xMove,int& yMove) const;

  const std::vector<GameMove> GetTwoHorizontalOtherMoves() const;
  const std::vector<GameMove> GetTwoVerticalOtherMoves() const;
  void CheckTwoDiagonally(int& xMove,int& yMove) const;
  void CheckOneOther(int& xMove,int& yMove) const;
  void MakeRandomMove(int& xMove,int& yMove) const;

public:		// User declarations
  __fastcall TFormMain(TComponent* Owner,
    const bool player1_human,
    const bool player2_human,
    const bool player3_human
    );

  const bool m_player1_human;
  const bool m_player2_human;
  const bool m_player3_human;
  const int mMaxx;
  const int mMaxy;
  const bool IsRobot(const EnumBlock player) const;
  const String GetName(const EnumBlock player) const;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
EnumBlock GetNextPlayer(const EnumBlock& player)
{
  assert(player!=NoPlayer);
  switch (player)
  {
    case Player1: return Player2;
    case Player2: return Player3;
    case Player3: return Player1;
  }
  assert(!"Should not get here");
  return Player1;
}
//---------------------------------------------------------------------------
/*
String EnumBlockToString(const EnumBlock& block)
{
  switch(block)
  {
    case Karen: return "Karen";
    case Kristel: return "Kristel";
    case Kathleen: return "Kathleen";
    case Heart: return Heart;
  }
  return Heart;
}
*/
//---------------------------------------------------------------------------
template <class T>
std::vector<T> Concatenate(const std::vector<T>& v1, const std::vector<T>& v2)
{
  std::vector<T> v(v1.size() + v2.size() );
  const int size1 = v1.size();
  const int size2 = v2.size();
  //Copy first vector
  for (int i=0; i<size1; ++i)
  {
    v[i] = v1[i];
  }
  //Copy second vector
  for (int i=0; i<size2; ++i)
  {
    v[size1+i] = v2[i];
  }
  return v;
}
//---------------------------------------------------------------------------
const double uniform();

#endif
