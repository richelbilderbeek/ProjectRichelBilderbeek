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
#include <boost/shared_ptr.hpp>
#include "UnitChessBoard.h"
#include "UnitChessPiece.h"
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSearchAndDestroyChess2Menu.h"
#include "UnitFormAbout.h"
#include "UnitFormSearchAndDestroyChess2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSearchAndDestroyChessMenu *FormSearchAndDestroyChessMenu;
//---------------------------------------------------------------------------
__fastcall TFormSearchAndDestroyChessMenu::TFormSearchAndDestroyChessMenu(TComponent* Owner)
        : TForm(Owner)
{
  /*
  this->Width  = Screen->Width  / 2;
  this->Height = Screen->Height / 2;
  this->Left   = Screen->Width  / 4;
  this->Top    = Screen->Height / 4;
  */
  this->Width  = 430;
  this->Height = 430;
  this->Left   = (Screen->Width  - 430) / 2;
  this->Top    = (Screen->Height - 430) / 2;

  OnResize(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormSearchAndDestroyChessMenu::PanelQuitClick(
      TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TFormSearchAndDestroyChessMenu::PanelAboutClick(
      TObject *Sender)
{
  boost::shared_ptr<TFormAbout> form(new TFormAbout(0));
  form->ShowModal();

}
//---------------------------------------------------------------------------
void __fastcall TFormSearchAndDestroyChessMenu::PanelStartClick(
      TObject *Sender)
{
  const bool isWhiteHuman = ImageWhiteHuman->Visible;
  const bool isBlackHuman = ImageBlackHuman->Visible;
  boost::shared_ptr<TFormSearchAndDestroyChess2> form(
    new TFormSearchAndDestroyChess2(0, isWhiteHuman, isBlackHuman));
  form->ShowModal();

}
//---------------------------------------------------------------------------
void __fastcall TFormSearchAndDestroyChessMenu::FormKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
  if (Key == 's' || Key == 'S') PanelStartClick(0);
  if (Key == 'a' || Key == 'A') PanelAboutClick(0);
  if (Key == 'q' || Key == 'Q') PanelQuitClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TFormSearchAndDestroyChessMenu::ImageWhiteClick(
      TObject *Sender)
{
  ImageWhiteHuman->Visible = !ImageWhiteHuman->Visible;
  ImageWhiteComputer->Visible = !ImageWhiteComputer->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TFormSearchAndDestroyChessMenu::ImageBlackClick(
      TObject *Sender)
{
  ImageBlackHuman->Visible = !ImageBlackHuman->Visible;
  ImageBlackComputer->Visible = !ImageBlackComputer->Visible;
}
//---------------------------------------------------------------------------

void __fastcall TFormSearchAndDestroyChessMenu::FormResize(TObject *Sender)
{
  const int height = ClientHeight;
  const int panelHeight = height / 6;
  PanelTitle->Height = panelHeight * 2;
  PanelVersus->Height = panelHeight;
  PanelStart->Height = panelHeight;
  PanelAbout->Height = panelHeight;
  PanelQuit->Height = panelHeight;
  const int imageHeight = panelHeight - 2;
  const int imageWidth = panelHeight - 2;
  ImageBlackKing->Height = imageHeight;
  ImageWhiteKing->Height = imageHeight;
  ImageBlackQueen->Height = imageHeight;
  ImageWhiteQueen->Height = imageHeight;
  ImageBlackPawn->Height = imageHeight;
  ImageWhitePawn->Height = imageHeight;
  ImageWhiteHuman->Height = imageHeight;
  ImageBlackHuman->Height = imageHeight;
  ImageWhiteComputer->Height = imageHeight;
  ImageBlackComputer->Height = imageHeight;

  ImageBlackKing->Width = imageWidth;
  ImageWhiteKing->Width = imageWidth;
  ImageBlackQueen->Width = imageWidth;
  ImageWhiteQueen->Width = imageWidth;
  ImageBlackPawn->Width = imageWidth;
  ImageWhitePawn->Width = imageWidth;
  ImageWhiteHuman->Width = imageWidth;
  ImageBlackHuman->Width = imageWidth;
  ImageWhiteComputer->Width = imageWidth;
  ImageBlackComputer->Width = imageWidth;

}
//---------------------------------------------------------------------------

