//---------------------------------------------------------------------------
/*
    Reversi, a simple board game
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
#ifndef UnitFormRestartH
#define UnitFormRestartH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormRestart : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelTop;
        TPanel *PanelBottom;
        TPanel *PanelYes;
        TPanel *PanelNo;
        TLabeledEdit *EditSize;
        void __fastcall PanelYesClick(TObject *Sender);
        void __fastcall PanelNoClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormRestart(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRestart *FormRestart;
//---------------------------------------------------------------------------
#endif
