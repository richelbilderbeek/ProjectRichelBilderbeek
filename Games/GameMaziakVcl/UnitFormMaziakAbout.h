//---------------------------------------------------------------------------
/*
  Maziak, a simple maze game
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
#ifndef UnitFormMaziakAboutH
#define UnitFormMaziakAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormMaziakAbout : public TForm
{
__published:	// IDE-managed Components
        TImage *ImageRichelBilderbeek;
        TRichEdit *RichEditLicence;
        TPanel *PanelTop;
        TPanel *PanelTopLeft;
        TPanel *PanelUrl;
        TPanel *PanelLicence;
        TPanel *PanelAuthor;
        TPanel *PanelMaziak;
        TPanel *PanelFrom;
        TPanel *PanelVersion;
        TButton *ButtonWhatsNew;
        TPanel *PanelTo;
        TImage *ImageMaziak;
        TImage *ImageVersion;
        TImage *ImageAuthor;
        TImage *ImageFrom;
        TImage *ImageTo;
        TImage *ImageLicence;
        TImage *ImageUrl;
        void __fastcall ButtonWhatsNewClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMaziakAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMaziakAbout *FormMaziakAbout;
//---------------------------------------------------------------------------
#endif
