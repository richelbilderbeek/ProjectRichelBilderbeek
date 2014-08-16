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
#ifndef UnitFormSpaceHarryGameH
#define UnitFormSpaceHarryGameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
//#include <vector>
#include <list>
#include <set>
#include "UnitSpaceHarryStructs.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TFormSpaceHarryGame : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBuffer;
        TImage *ImageBackgroundSky;
        TImage *ImageBackgroundSoil1;
        TImage *ImageHarry;
        TImage *ImageBulletHarry;
        TTimer *TimerGame;
        TTimer *TimerKeyPress;
        TImage *ImageBackgroundSoil2;
        TImage *ImageEnemySkull;
        TImage *ImageBulletBlue;
        TImage *ImageCollisionBlue;
        TImage *ImageCollisionGreen;
        TImage *ImageHarryTransparent;
        TImage *ImageLifebar;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall TimerGameTimer(TObject *Sender);
        void __fastcall TimerKeyPressTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
  int mX,mY,mZ; //Harry's coordinats
  int mScore;
  bool mIsHarryTransparent;
  double mLife;
  std::list<Bullet> mBullets;
  std::list<Enemy> mEnemies;
  std::list<Collision> mCollisions;
  void DrawScreen();
  void DrawNewLifebar();
  std::set<WORD> mKeys;
public:		// User declarations
        __fastcall TFormSpaceHarryGame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSpaceHarryGame *FormSpaceHarryGame;
//---------------------------------------------------------------------------
void VclPaint(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );
void DrawSoil(TImage * const image,
  const unsigned char red1,
  const unsigned char green1,
  const unsigned char blue1,
  const unsigned char red2,
  const unsigned char green2,
  const unsigned char blue2);
//From http://www.richelbilderbeek.nl/CppRainbow.htm
void Rainbow(
  const double x,
  unsigned char& r,
  unsigned char& g,
  unsigned char& b);
unsigned char GetRed(const double x);
unsigned char GetGreen(const double x);
unsigned char GetBlue(const double x);


#endif
