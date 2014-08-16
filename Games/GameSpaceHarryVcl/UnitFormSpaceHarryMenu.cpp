//---------------------------------------------------------------------------
/*
  Space Harry, a simple 'Space Harrier' clone
<<<<<<< HEAD
  Copyright (C) 2007  Richèl Bilderbeek
=======
  Copyright (C) 2007  Richel Bilderbeek
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
#include <memory>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormSpaceHarryMenu.h"
#include "UnitFormSpaceHarryGame.h"
#include "UnitFormSpaceHarryAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSpaceHarryMenu *FormSpaceHarryMenu;
//---------------------------------------------------------------------------
__fastcall TFormSpaceHarryMenu::TFormSpaceHarryMenu(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSpaceHarryMenu::LabelStartClick(TObject *Sender)
{
  //Start Game
  std::auto_ptr<TFormSpaceHarryGame> f(new TFormSpaceHarryGame(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormSpaceHarryMenu::LabelAboutClick(TObject *Sender)
{
  //About
  std::auto_ptr<TFormSpaceHarryAbout> f(new TFormSpaceHarryAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormSpaceHarryMenu::LabelQuitClick(TObject *Sender)
{
  //Quit
  Close();
}
//---------------------------------------------------------------------------
