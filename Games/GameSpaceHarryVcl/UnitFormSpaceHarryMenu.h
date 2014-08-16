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
#ifndef UnitFormSpaceHarryMenuH
#define UnitFormSpaceHarryMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormSpaceHarryMenu : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TImage *Image2;
        TLabel *LabelTitleFront;
        TLabel *LabelTitleBack;
        TLabel *LabelQuit;
        TLabel *LabelStart;
        TLabel *LabelAbout;
        void __fastcall LabelStartClick(TObject *Sender);
        void __fastcall LabelAboutClick(TObject *Sender);
        void __fastcall LabelQuitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSpaceHarryMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSpaceHarryMenu *FormSpaceHarryMenu;
//---------------------------------------------------------------------------
#endif
