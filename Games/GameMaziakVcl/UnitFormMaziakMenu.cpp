//---------------------------------------------------------------------------
/*
  Maziak, a simple maze game
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
#include <vcl.h>
#pragma hdrstop

#include <ctime>
#include <stdexcept>
#include <cstdlib>
#include <boost/scoped_ptr.hpp>
#include "UnitMazeCreater.h"

#include "UnitFormMaziakMenu.h"
#include "UnitFormMaziakAbout.h"
#include "UnitFormMaziakGame.h"
#include "UnitFormMaziakInstructions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMaziakMenu *FormMaziakMenu;
//---------------------------------------------------------------------------
__fastcall TFormMaziakMenu::TFormMaziakMenu(TComponent* Owner)
  : TForm(Owner),
    mDifficulty(easy)
{
  RandomizeTimer();
  ImageEasyClick(0);
}
//---------------------------------------------------------------------------
const int TFormMaziakMenu::GetSize() const
{
  switch (mDifficulty)
  {
    case easy  : return  99;
    case medium: return 499;
    case hard  : return 999;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unsupported value of mDifficulty");
}
//---------------------------------------------------------------------------

void __fastcall TFormMaziakMenu::ImageStartClick(TObject *Sender)
{
  boost::scoped_ptr<TFormMaziakGame> f(new TFormMaziakGame(0,GetSize()));
  f->WindowState = wsMaximized;
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakMenu::ImageAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormMaziakAbout> f(new TFormMaziakAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakMenu::ImageQuitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormMaziakMenu::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  switch (Key)
  {
    case 's': case 'S': ImageStartClick(0); break;
    case 'i': case 'I': ImageInstructionsClick(0); break;
    case 'a': case 'A': ImageAboutClick(0); break;
    case 'q': case 'Q': ImageQuitClick(0); break;
    case '+': case VK_NEXT: case VK_DOWN: case VK_ADD: case VK_RIGHT:
    {
      switch (mDifficulty)
      {
        case easy  : ImageMediumClick(0); break;
        case medium: ImageHardClick(0); break;
        case hard  : break;
      }
    }
    break;
    case '-': case VK_PRIOR: case VK_UP: case VK_SUBTRACT: case VK_LEFT:
    {
      switch (mDifficulty)
      {
        case easy  : break;
        case medium: ImageEasyClick(0); break;
        case hard  : ImageMediumClick(0);break;
      }
    }
    break;
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer()
{
  std::srand(std::time(0));
}
//---------------------------------------------------------------------------

void __fastcall TFormMaziakMenu::ImageInstructionsClick(TObject *Sender)
{
  boost::scoped_ptr<TFormMaziakInstructions> f(new TFormMaziakInstructions(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TFormMaziakMenu::ImageEasyClick(TObject *Sender)
{
  ImageEasy->Picture   = ImageEasySelected->Picture;
  ImageMedium->Picture = ImageMediumNotSelected->Picture;
  ImageHard->Picture   = ImageHardNotSelected->Picture;
  mDifficulty = easy;
  ImagePlayer->Picture = ImagePlayerEasy->Picture;
  ImageEnemy->Picture  = ImageEnemyEasy->Picture;
}
//---------------------------------------------------------------------------

void __fastcall TFormMaziakMenu::ImageMediumClick(TObject *Sender)
{
  ImageEasy->Picture   = ImageEasyNotSelected->Picture;
  ImageMedium->Picture = ImageMediumSelected->Picture;
  ImageHard->Picture   = ImageHardNotSelected->Picture;
  mDifficulty = medium;
  ImagePlayer->Picture = ImagePlayerMedium->Picture;
  ImageEnemy->Picture  = ImageEnemyMedium->Picture;
}
//---------------------------------------------------------------------------

void __fastcall TFormMaziakMenu::ImageHardClick(TObject *Sender)
{
  ImageEasy->Picture   = ImageEasyNotSelected->Picture;
  ImageMedium->Picture = ImageMediumNotSelected->Picture;
  ImageHard->Picture   = ImageHardSelected->Picture;
  mDifficulty = hard;
  ImagePlayer->Picture = ImagePlayerHard->Picture;
  ImageEnemy->Picture  = ImageEnemyHard->Picture;
}
//---------------------------------------------------------------------------


