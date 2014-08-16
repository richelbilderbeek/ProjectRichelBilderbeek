//---------------------------------------------------------------------------
/*
  PokeVolley, Pokemon volleyball game
<<<<<<< HEAD
  Copyright (C) 2005  Richèl Bilderbeek
=======
  Copyright (C) 2005  Richel Bilderbeek
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
#ifndef UnitFormSpritesH
#define UnitFormSpritesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSprites : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBallR;
        TImage *ImageBallG;
        TImage *ImageBallB;
        TImage *ImagePlayer1;
        TImage *ImagePlayer1Jump;
        TImage *ImagePlayer2;
        TImage *ImagePlayer2Jump;
        TImage *ImageBasket2_0;
        TImage *ImageBasket2_1;
        TImage *ImageBasket2_2;
        TImage *ImageBasket1_2;
        TImage *ImageBasket1_1;
        TImage *ImageBasket1_0;
        TImage *ImageBackground;
        TImage *Image7;
        TImage *Image1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormSprites(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSprites *FormSprites;
//---------------------------------------------------------------------------
#endif
