//---------------------------------------------------------------------------
/*
  The Thor Veen Project, simulation to investigate honest signalling
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
#ifndef UnitFormAboutTheAuthorH
#define UnitFormAboutTheAuthorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormAboutTheAuthor : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEditLicence;
        TImage *ImageAuthor;
        TPanel *PanelTop;
        TPanel *PanelTopRight;
        TPanel *PanelTitle;
        TPanel *PanelLicence;
        TPanel *PanelCollaboration2;
        TPanel *PanelCollaboration1;
        TPanel *PanelDate;
        TPanel *PanelAuthor;
        TPanel *PanelVersion;
        TPanel *PanelWebsite;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TRichEdit *RichEditWhatsNew;
private:	// User declarations
public:		// User declarations
  __fastcall TFormAboutTheAuthor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAboutTheAuthor *FormAboutTheAuthor;
//---------------------------------------------------------------------------
#endif
