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
#ifndef UnitFormOverH
#define UnitFormOverH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormOver : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageRichel;
        TRichEdit *RichEditLicence;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TButton *ButtonWhatsNew;
        TButton *ButtonAdditionalCopyright;
        void __fastcall ButtonWhatsNewClick(TObject *Sender);
        void __fastcall ButtonAdditionalCopyrightClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormOver(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOver *FormOver;
//---------------------------------------------------------------------------
#endif
