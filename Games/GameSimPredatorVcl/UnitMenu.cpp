//---------------------------------------------------------------------------
/*
 *  SimPredator. A simple game to demonstrate selection and mutation
 *  Copyright (C) 2006  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
// The program was developed from 19-05-2006 to 18-07-2006
// The program can be downloaded at http://www.richelbilderbeek.nl
// The author's e-mail adress can be found at http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop


#include "UnitMenu.h"
//---------------------------------------------------------------------------
#include <memory>
#include "UnitStartHunt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMenu *FormMenu;
//---------------------------------------------------------------------------
__fastcall TFormMenu::TFormMenu(TComponent* Owner)
  : TForm(Owner),
  mPlayedHunt1(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::TextAboutClick(TObject *Sender)
{
  ImagePredatorLeft->Visible  = !ImagePredatorLeft->Visible;
  ImagePredatorLeft->Align = (ImagePredatorLeft->Align==alNone ? alLeft : alNone);
  ImagePredatorRight->Visible = !ImagePredatorRight->Visible;
  ImagePredatorRight->Align = (ImagePredatorRight->Align==alNone ? alRight : alNone);
  ImageRichelLeft->Visible  = !ImageRichelLeft->Visible;
  ImageRichelLeft->Align = (ImageRichelLeft->Align==alNone ? alLeft : alNone);
  ImageRichelRight->Visible = !ImageRichelRight->Visible;
  ImageRichelRight->Align = (ImageRichelRight->Align==alNone ? alRight : alNone);
  RichEditAbout->Visible = !RichEditAbout->Visible;
  TextAbout->Caption = (TextAbout->Caption=="About" ? "Not about" : "About");
}
//---------------------------------------------------------------------------
void __fastcall TFormMenu::TextStartHunt1Click(TObject *Sender)
{
  ++mPlayedHunt1;
  FormStartHunt->setHunt(1);
  FormStartHunt->ShowModal();
  if (mPlayedHunt1==3) TextStartHunt2->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TFormMenu::TextQuitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMenu::TextStartHunt2Click(TObject *Sender)
{
  FormStartHunt->setHunt(2);
  FormStartHunt->ShowModal();
  if (mPlayedHunt1==3) TextStartHunt2->Enabled = true;

}
//---------------------------------------------------------------------------

