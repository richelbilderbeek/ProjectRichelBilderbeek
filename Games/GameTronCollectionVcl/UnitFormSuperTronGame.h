//---------------------------------------------------------------------------
/*
  Super Tron, a simple game
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
#ifndef UnitFormSuperTronGameH
#define UnitFormSuperTronGameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include "UnitSuperTronPlayer.h"
//---------------------------------------------------------------------------
class TFormSuperTronGame : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBuffer;
        TTimer *TimerGame;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TimerGameTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
  typedef SuperTronPlayer Player;
  std::vector<Player> mPlayers;
  const bool mDonutShapedWorld;
  const bool mCanWalkThroughOwnColor;
  const int mMaxx;
  const int mMaxy;
  void AddPointToWinners(const TColor color);
  void RemovePointFromLosers(const TColor color);

public:		// User declarations
  __fastcall TFormSuperTronGame(TComponent* Owner,
    const std::vector<Player>& players,
    const int speed,
    const int maxx,
    const int maxy,
    const bool donutShapedWorld,
    const bool canWalkThroughOwnColor);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSuperTronGame *FormSuperTronGame;
//---------------------------------------------------------------------------



#endif
