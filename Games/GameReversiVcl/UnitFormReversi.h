//---------------------------------------------------------------------------
/*
    Reversi, a simple board game
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
#ifndef UnitFormReversiH
#define UnitFormReversiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "UnitReversi.h"
//---------------------------------------------------------------------------
class TFormReversi : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBoard;
        TPanel *PanelBottom;
        TPanel *PanelMenu;
        TImage *ImageRed;
        TLabel *LabelRed;
        TLabel *LabelBlue;
        TImage *ImageBlue;
        TImage *ImageRedActive;
        TImage *ImageBlueActive;
        TLabel *LabelRestart;
        TLabel *LabelAbout;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall ImageBoardMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ImageActiveClick(TObject *Sender);
        void __fastcall LabelRestartClick(TObject *Sender);
        void __fastcall LabelAboutClick(TObject *Sender);
private:	// User declarations
  Reversi mReversi;
  Square mPlayer;
public:		// User declarations
  __fastcall TFormReversi(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormReversi *FormReversi;
//---------------------------------------------------------------------------
void SetPixel(
  TImage * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);

#endif
