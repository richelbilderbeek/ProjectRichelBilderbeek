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
#ifndef UnitFormSpritesH
#define UnitFormSpritesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormSprites : public TForm
{
__published:	// IDE-managed Components
        TImage *ImagePlayer3;
        TImage *ImagePlayer1;
        TImage *ImagePlayer2;
        TImage *ImageEmpty;
        TImage *ImagePlayer1Grey;
        TImage *ImagePlayer2Grey;
        TImage *ImagePlayer3Grey;
        TImage *ImageComputer1;
        TImage *ImageComputer1Grey;
        TImage *ImageComputer2;
        TImage *ImageComputer3;
        TImage *ImageComputer2Grey;
        TImage *ImageComputer3Grey;
        TImage *ImagePlayerRed;
        TImage *ImageComputerRed;
        TLabel *Label1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormSprites(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSprites *FormSprites;
//---------------------------------------------------------------------------
#endif
