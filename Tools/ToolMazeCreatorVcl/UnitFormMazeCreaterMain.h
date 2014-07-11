//---------------------------------------------------------------------------
/*
  Maze Creater, creates a maze and displays it on screen
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
#ifndef UnitFormMazeCreaterMainH
#define UnitFormMazeCreaterMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormMazeCreaterMain : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBackground;
        void __fastcall OnAnyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMazeCreaterMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMazeCreaterMain *FormMazeCreaterMain;
//---------------------------------------------------------------------------
void SetPixel(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);
void GetPixel(
  const TImage * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);


#endif
