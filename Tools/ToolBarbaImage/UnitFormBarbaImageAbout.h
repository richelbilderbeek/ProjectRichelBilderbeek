//---------------------------------------------------------------------------
/*
  BarbaImage, tool to perform image manipulations
  Copyright (C) 2008  Rich�l Bilderbeek

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
#ifndef UnitFormBarbaImageAboutH
#define UnitFormBarbaImageAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormBarbaImageAbout : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit;
        TImage *ImageAuthor;
        TPanel *PanelTop;
        TPanel *PanelTopRight;
        TPanel *PanelWebsite;
        TPanel *PanelLicence;
        TPanel *PanelDate;
        TPanel *PanelAuthor;
        TPanel *PanelCopyright;
        TPanel *PanelTitle;
        TPanel *PanelVersion;
        TButton *ButtonWhatsNew;
        void __fastcall ButtonWhatsNewClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormBarbaImageAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormBarbaImageAbout *FormBarbaImageAbout;
//---------------------------------------------------------------------------
#endif
