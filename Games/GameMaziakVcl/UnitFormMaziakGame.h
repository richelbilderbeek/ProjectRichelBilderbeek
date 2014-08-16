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
#ifndef UnitFormMaziakGameH
#define UnitFormMaziakGameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <set>
#include <list>
#include <vector>
#include "UnitLocation.h"
//---------------------------------------------------------------------------
class TFormMaziakGame : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBuffer;
        TImage *ImagePlayerLookDown;
        TTimer *TimerPressKey;
        TTimer *TimerEnemy;
        TImage *ImagePlayerLookLeftSword;
        TImage *ImageSword;
        TImage *ImageExit;
        TImage *ImagePrisoner1;
        TTimer *TimerShowSolution;
        TImage *ImageEntrace;
        TImage *ImageGold;
        TImage *Image1;
        TImage *ImageFightWon1;
        TImage *ImagePlayerWon1;
        TImage *Image2;
        TImage *Image3;
        TImage *Image4;
        TImage *ImageFight1;
        TImage *ImagePlayerLookRightSword;
        TImage *ImagePlayerWalkLeft2;
        TImage *ImagePlayerWalkLeft1;
        TImage *ImagePlayerWalkLeftSword2;
        TImage *ImagePlayerWalkLeftSword1;
        TImage *ImagePlayerWalkDown1;
        TImage *ImagePlayerWalkDown2;
        TImage *ImagePlayerWalkDownSword1;
        TImage *ImagePlayerWalkDownSword2;
        TImage *ImagePlayerWalkUp2;
        TImage *ImagePlayerWalkUp1;
        TImage *ImagePlayerWalkUpSword1;
        TImage *ImagePlayerWalkUpSword2;
        TImage *ImagePlayerWalkRightSword1;
        TImage *ImagePlayerWalkRightSword2;
        TImage *ImagePlayerWalkRight1;
        TImage *ImagePlayerWalkRight2;
        TImage *ImagePlayerLookLeft;
        TImage *ImagePlayerLookRight;
        TImage *ImagePlayerLookDownSword;
        TImage *ImagePlayerLookUp;
        TImage *ImagePlayerLookUpSword;
        TImage *ImagePrisoner2;
        TImage *ImageFightWon2;
        TImage *ImageFightSword1;
        TImage *ImageFight2;
        TImage *ImageFight3;
        TImage *ImageFight4;
        TImage *ImageFightLost1;
        TImage *ImageFightLost2;
        TImage *ImageEmpty;
        TImage *ImageWall;
        TImage *ImageEnemy1;
        TImage *ImageEnemy2;
        TImage *ImagePath;
        TImage *ImagePlayerWon2;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TimerPressKeyTimer(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TimerEnemyTimer(TObject *Sender);
        void __fastcall TimerShowSolutionTimer(TObject *Sender);
private:	// User declarations
  int mX;
  int mY;
public:
  enum PlayerDirection { pdLeft, pdRight, pdUp, pdDown };
  enum PlayerMove { none, left1, left2, right1, right2, up1, up2, down1, down2 };
  enum MazeSquare { msEmpty, msWall, msEnemy1, msEnemy2, msPrisoner1, msPrisoner2, msSword, msExit };
private:
  const int mViewWidth;
  const int mViewHeight;
  bool mHasSword;
  int mFighting;
  bool mCheat;
  bool mShowSolution;
  PlayerDirection mDirection;
  PlayerMove mMoveNow;
  std::set<WORD> mKeys;
  std::vector<std::vector<int> > mSolution;
  std::vector<std::vector<int> > mIntMaze;
  std::vector<std::vector<MazeSquare> > mMaze;
  std::vector<std::vector<int> > mDistances;
  void DrawScreen();
  const TImage * const GetMazeImage(const int x, const int y) const;
  const TImage * const GetPlayerImage(
    const PlayerDirection direction,
    const PlayerMove moveNow) const;
  void CreateMaze(const int sz);
  void DoDebugF1() const;
  void DoDebugF2() const;
public:		// User declarations
  __fastcall TFormMaziakGame(TComponent* Owner, const String mazeSize);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormMaziakGame *FormMaziakGame;
//---------------------------------------------------------------------------
template <class Source, class Target>
const std::vector<std::vector<Target> > ConvertMatrix(
  const std::vector<std::vector<Source> >& v)
{
  const int maxy = static_cast<int>(v.size());
  assert(maxy>0);
  const int maxx = static_cast<int>(v[0].size());
  std::vector<std::vector<Target> > t(maxy,std::vector<Target>(maxx));
  for (int y=0; y!=maxy; ++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      t[y][x] = static_cast<Target>(v[y][x]);
    }
  }
  return t;
}
//---------------------------------------------------------------------------
const std::vector<std::pair<int,int> > GetShuffledDeadEnds(
  const std::vector<std::vector<int> >& intMaze);
//---------------------------------------------------------------------------
const std::vector<std::pair<int,int> > GetShuffledNonDeadEnds(
  const std::vector<std::vector<int> >& intMaze);
//---------------------------------------------------------------------------
const bool CanMoveTo(
  const std::vector<std::vector<TFormMaziakGame::MazeSquare> >& maze,
  const int x, const int y,
  const bool hasSword,
  const bool showSolution);
//---------------------------------------------------------------------------
template <class T>
const bool IsSquare(const std::vector<std::vector<T> >& v)
{
  if (v.empty()) return false;
  const int sz = static_cast<int>(v.size());
  const std::vector<std::vector<T> >::const_iterator j = v.end();
  std::vector<std::vector<T> >::const_iterator i = v.begin();
  for ( ; i!=j; ++i)
  {
    if (sz != static_cast<int>(i->size())) return false;
  }
  return true;
}
//---------------------------------------------------------------------------
void SetPixel(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
//---------------------------------------------------------------------------
#endif
