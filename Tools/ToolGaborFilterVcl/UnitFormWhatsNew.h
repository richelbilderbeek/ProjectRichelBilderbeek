//---------------------------------------------------------------------------
/*
  GaborFilter, performs Gabor filter operations on images
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
#ifndef UnitFormWhatsNewH
#define UnitFormWhatsNewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormWhatsNew : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit;
private:	// User declarations
public:		// User declarations
        __fastcall TFormWhatsNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWhatsNew *FormWhatsNew;
//---------------------------------------------------------------------------
#endif
