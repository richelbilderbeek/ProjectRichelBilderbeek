//---------------------------------------------------------------------------
/*
  Hometrainer 2, tool to make exercises and tests
  Copyright (C) 2009  Richel Bilderbeek

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
#ifndef UnitFormCorrectH
#define UnitFormCorrectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormCorrect : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelCorrect;
        TTimer *TimerAutoClose;
        void __fastcall TimerAutoCloseTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormCorrect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCorrect *FormCorrect;
//---------------------------------------------------------------------------
#endif
