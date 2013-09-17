//---------------------------------------------------------------------------
/*
    K3-Op-Een-Rij. A simple game.
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
#ifndef UnitFormMenuH
#define UnitFormMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormMenu : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageComputer3;
        TImage *ImageComputer2;
        TImage *ImageComputer1;
        TImage *ImagePlayer3;
        TImage *ImagePlayer2;
        TImage *ImagePlayer1;
        TImage *ImageQuit;
        TImage *ImageRules;
        TImage *ImageAbout;
        TImage *ImageStart;
        TImage *ImageTitle;
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TImage *Image4;
        void __fastcall ImagePlayer1Click(TObject *Sender);
        void __fastcall ImageComputer1Click(TObject *Sender);
        void __fastcall ImagePlayer2Click(TObject *Sender);
        void __fastcall ImageComputer2Click(TObject *Sender);
        void __fastcall ImagePlayer3Click(TObject *Sender);
        void __fastcall ImageComputer3Click(TObject *Sender);
        void __fastcall ImageStartClick(TObject *Sender);
        void __fastcall ImageAboutClick(TObject *Sender);
        void __fastcall ImageRulesClick(TObject *Sender);
        void __fastcall ImageQuitClick(TObject *Sender);
private:	// User declarations
  bool m_player1_human;
  bool m_player2_human;
  bool m_player3_human;
  void DrawPlayers();
public:		// User declarations
        __fastcall TFormMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMenu *FormMenu;
//---------------------------------------------------------------------------
#endif
