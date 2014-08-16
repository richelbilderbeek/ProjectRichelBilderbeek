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
#ifndef UnitFormMaziakMenuH
#define UnitFormMaziakMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormMaziakMenu : public TForm
{
__published:	// IDE-managed Components
        TImage *ImagePlayer;
        TImage *ImageQuit;
        TImage *ImageAbout;
        TImage *ImageStart;
        TImage *ImageInstructions;
        TImage *ImageEasy;
        TImage *ImageMedium;
        TImage *ImageHard;
        TImage *ImageEasySelected;
        TImage *ImageMediumSelected;
        TImage *ImageHardSelected;
        TImage *ImageEasyNotSelected;
        TImage *ImageMediumNotSelected;
        TImage *ImageHardNotSelected;
        TImage *ImagePlayerHard;
        TImage *ImagePlayerEasy;
        TImage *ImagePlayerMedium;
        TImage *ImageEnemy;
        TImage *ImageEnemyHard;
        TImage *ImageEnemyMedium;
        TImage *ImageEnemyEasy;
        void __fastcall ImageQuitClick(TObject *Sender);
        void __fastcall ImageAboutClick(TObject *Sender);
        void __fastcall ImageStartClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ImageInstructionsClick(TObject *Sender);
        void __fastcall ImageEasyClick(TObject *Sender);
        void __fastcall ImageMediumClick(TObject *Sender);
        void __fastcall ImageHardClick(TObject *Sender);
private:	// User declarations
  const int GetSize() const;
  enum Difficulty { easy, medium, hard } mDifficulty;
public:		// User declarations
        __fastcall TFormMaziakMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMaziakMenu *FormMaziakMenu;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer();
//---------------------------------------------------------------------------

#endif
