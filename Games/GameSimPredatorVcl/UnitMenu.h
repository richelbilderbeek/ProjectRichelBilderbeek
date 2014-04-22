//---------------------------------------------------------------------------
/*
 *  SimPredator. A simple game to demonstrate selection and mutation
 *  Copyright (C) 2006  Richel Bilderbeek
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//---------------------------------------------------------------------------
// The program was developed from 19-05-2006 to 18-07-2006
// The program can be downloaded at http://www.richelbilderbeek.nl
// The author's e-mail adress can be found at http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitMenuH
#define UnitMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMenu : public TForm
{
__published:	// IDE-managed Components
        TStaticText *TextSimPredator;
        TStaticText *TextStartHunt1;
        TStaticText *TextQuit;
        TStaticText *TextStartHunt2;
        TStaticText *TextAbout;
        TPanel *PanelMenu;
        TImage *ImagePredatorLeft;
        TImage *ImagePredatorRight;
        TImage *ImageRichelLeft;
        TImage *ImageRichelRight;
        TRichEdit *RichEditAbout;
        void __fastcall TextAboutClick(TObject *Sender);
        void __fastcall TextStartHunt1Click(TObject *Sender);
        void __fastcall TextQuitClick(TObject *Sender);
        void __fastcall TextStartHunt2Click(TObject *Sender);
private:	// User declarations
  int mPlayedHunt1;
public:		// User declarations
        __fastcall TFormMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMenu *FormMenu;
//---------------------------------------------------------------------------
#endif
