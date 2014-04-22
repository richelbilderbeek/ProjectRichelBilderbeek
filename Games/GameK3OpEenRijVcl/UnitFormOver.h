//---------------------------------------------------------------------------
/*
    K3-Op-Een-Rij. A simple game.
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
        TImage *Image1;
        TImage *Image8;
        TImage *Image9;
        TImage *ImageTitle;
        TImage *Image11;
        TImage *Image12;
        TImage *Image13;
        TRichEdit *RichEditLicence;
        TButton *ButtonWhatsNew;
        TButton *ButtonCopyrightK3;
        void __fastcall ButtonWhatsNewClick(TObject *Sender);
        void __fastcall ButtonCopyrightK3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormOver(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOver *FormOver;
//---------------------------------------------------------------------------
#endif
