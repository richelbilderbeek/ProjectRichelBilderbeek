//---------------------------------------------------------------------------
/*
  SearchAndDestroyChess 2, Kriegspiel/Dark Chess game
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
#ifndef UnitFormSearchAndDestroyChessMenuH
#define UnitFormSearchAndDestroyChessMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSearchAndDestroyChessMenu : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageBlackKing;
        TImage *ImageWhiteKing;
        TPanel *PanelStart;
        TImage *ImageBlackQueen;
        TImage *ImageWhiteQueen;
        TImage *ImageBlackPawn;
        TImage *ImageWhitePawn;
        TPanel *PanelAbout;
        TPanel *PanelQuit;
        TPanel *PanelTitle;
        TImage *ImageTitle;
        TPanel *PanelVersus;
        TImage *ImageWhiteHuman;
        TImage *ImageBlackHuman;
        TImage *ImageWhiteComputer;
        TImage *ImageBlackComputer;
        void __fastcall PanelQuitClick(TObject *Sender);
        void __fastcall PanelAboutClick(TObject *Sender);
        void __fastcall PanelStartClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ImageWhiteClick(TObject *Sender);
        void __fastcall ImageBlackClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSearchAndDestroyChessMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSearchAndDestroyChessMenu *FormSearchAndDestroyChessMenu;
//---------------------------------------------------------------------------
#endif
