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
#ifndef UnitFormPressKeyH
#define UnitFormPressKeyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormPressKey : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Panel1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormPressKey(TComponent* Owner, const String& s);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPressKey *FormPressKey;
//---------------------------------------------------------------------------
#endif
