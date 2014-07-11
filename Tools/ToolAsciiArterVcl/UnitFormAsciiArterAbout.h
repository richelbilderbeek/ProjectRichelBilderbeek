//---------------------------------------------------------------------------
/*
  AsciiArter, tool to convert images to ASCII art
  Copyright (C) 2006  Richel Bilderbeek

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
#ifndef UnitFormAsciiArterAboutH
#define UnitFormAsciiArterAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormAsciiArterAbout : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelAbout1;
        TPanel *Panel7;
        TPanel *Panel6;
        TPanel *Panel5;
        TPanel *Panel4;
        TPanel *Panel3;
        TPanel *Panel2;
        TPanel *Panel1;
        TPanel *PanelTopRight;
        TImage *Image1;
        TRichEdit *RichEditLicence;
        TPanel *PanelAboutTop;
private:	// User declarations
public:		// User declarations
        __fastcall TFormAsciiArterAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAsciiArterAbout *FormAsciiArterAbout;
//---------------------------------------------------------------------------
#endif
