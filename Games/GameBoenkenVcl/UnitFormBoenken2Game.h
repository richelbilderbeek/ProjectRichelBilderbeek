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
#ifndef UnitFormBoenken2GameH
#define UnitFormBoenken2GameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <set>
#include "UnitPlayer.h"
#include "UnitEnums.h"
//---------------------------------------------------------------------------
class TFormBoenken2Game : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBackground;
        TImage *ImageBuffer;
        TImage *ImageRed;
        TImage *ImageBlue;
        TTimer *TimerGame;
        TImage *ImageBall;
        TImage *ImageGrey;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
  struct Obstacle
  {
    double x;
    double y;
  };
  std::vector<Player> mPlayers;
  std::vector<Obstacle> mObstacles;
  Player mBall;
  int mScoreRed;
  int mScoreBlue;
  std::set<WORD> mKeys;
  const EnumGraphics mGraphics;
  const EnumControls mControls;
  const double mFriction;

  void __fastcall TimerGameTwoKeys(TObject *Sender);
  void __fastcall TimerGameFourKeys(TObject *Sender);

public:		// User declarations
  __fastcall TFormBoenken2Game(
    TComponent* Owner,
    const std::vector<Player>& players,
    const EnumGraphics graphics,
    const EnumControls controls,
    const double friction);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBoenken2Game *FormBoenken2Game;
//---------------------------------------------------------------------------
void DrawGlobe(
  TImage * const image,
  unsigned char rMax,
  unsigned char gMax,
  unsigned char bMax);

void DrawCircle(
  TImage * const image,
  unsigned char r,
  unsigned char g,
  unsigned char b);

double GetAngle(const double dX, const double dY);
void DoPerfectElasticCollision(const double angleCollision, double& angle1, double& speed1, double& angle2, double& speed2);
void PaintVcl(TImage * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );

void DrawOldSchoolBackground(TImage * const image);
void DrawNewSchoolBackground(TImage * const image);

#endif
