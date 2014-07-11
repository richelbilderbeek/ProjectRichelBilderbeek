//---------------------------------------------------------------------------
/*
    Morpher, a tool to generate a series of morphed images
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
#ifndef UnitFormMorpherH
#define UnitFormMorpherH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMorpher : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelTop;
        TButton *ButtonLoad1;
        TButton *ButtonLoad2;
        TButton *ButtonMorph;
        TButton *ButtonAbout;
        TEdit *EditNumber;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *EditFileStart;
        TImage *Image1;
        TImage *Image2;
        TOpenDialog *OpenDialog1;
        TOpenDialog *OpenDialog2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TImage *Image3;
        void __fastcall ButtonLoad1Click(TObject *Sender);
        void __fastcall ButtonLoad2Click(TObject *Sender);
        void __fastcall ButtonMorphClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMorpher(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMorpher *FormMorpher;
//---------------------------------------------------------------------------
#endif
