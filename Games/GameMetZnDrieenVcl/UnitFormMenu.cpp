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
#include <vcl.h>
#pragma hdrstop

#include "UnitFormMenu.h"
#include "UnitFormMain.h"
//---------------------------------------------------------------------------
#include <cassert>
#include <boost\scoped_ptr.hpp>
#include "UnitFormOver.h"
#include "UnitFormSpelregels.h"
#include "UnitFormSprites.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMenu *FormMenu;
//---------------------------------------------------------------------------
__fastcall TFormMenu::TFormMenu(TComponent* Owner)
  : TForm(Owner),
  m_player1_human(true),
  m_player2_human(true),
  m_player3_human(true)
{

}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImagePlayer1Click(TObject *Sender)
{
  m_player1_human = true;
  DrawPlayers();
}
//---------------------------------------------------------------------------

void __fastcall TFormMenu::ImageComputer1Click(TObject *Sender)
{
  m_player1_human = false;
  DrawPlayers();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImagePlayer2Click(TObject *Sender)
{
  m_player2_human = true;
  DrawPlayers();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageComputer2Click(TObject *Sender)
{
  m_player2_human = false;
  DrawPlayers();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImagePlayer3Click(TObject *Sender)
{
  m_player3_human = true;
  DrawPlayers();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageComputer3Click(TObject *Sender)
{
  m_player3_human = false;
  DrawPlayers();
}
//---------------------------------------------------------------------------
void TFormMenu::DrawPlayers()
{
  assert(FormSprites);
  if (m_player1_human)
  {
    ImagePlayer1->Picture   = FormSprites->ImagePlayer1->Picture;
    ImageComputer1->Picture = FormSprites->ImageComputer1Grey->Picture;
  }
  else
  {
    ImagePlayer1->Picture   = FormSprites->ImagePlayer1Grey->Picture;
    ImageComputer1->Picture = FormSprites->ImageComputer1->Picture;
  }
  if (m_player2_human)
  {
    ImagePlayer2->Picture   = FormSprites->ImagePlayer2->Picture;
    ImageComputer2->Picture = FormSprites->ImageComputer2Grey->Picture;
  }
  else
  {
    ImagePlayer2->Picture   = FormSprites->ImagePlayer2Grey->Picture;
    ImageComputer2->Picture = FormSprites->ImageComputer2->Picture;
  }
  if (m_player3_human)
  {
    ImagePlayer3->Picture   = FormSprites->ImagePlayer3->Picture;
    ImageComputer3->Picture = FormSprites->ImageComputer3Grey->Picture;
  }
  else
  {
    ImagePlayer3->Picture   = FormSprites->ImagePlayer3Grey->Picture;
    ImageComputer3->Picture = FormSprites->ImageComputer3->Picture;
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageStartClick(TObject *Sender)
{
  boost::scoped_ptr<TFormMain> form(
    new TFormMain(0,
      m_player1_human,
      m_player2_human,
      m_player3_human));
  form->Hide();
  this->Hide();
  form->ShowModal();
  this->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageRulesClick(TObject *Sender)
{
  this->Hide();
  boost::scoped_ptr<TFormSpelregels> form(new TFormSpelregels(0));
  form->Hide();
  form->ShowModal();
  this->Show();

}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageAboutClick(TObject *Sender)
{
  this->Hide();
  boost::scoped_ptr<TFormOver> form(new TFormOver(0));
  form->Hide();
  form->ShowModal();
  this->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::ImageQuitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

