//---------------------------------------------------------------------------
/*
  Random Code, generates random C++ code
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
#ifndef UnitFormRandomCodeH
#define UnitFormRandomCodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormRandomCode : public TForm
{
__published:	// IDE-managed Components
        TButton *ButtonGenerate;
  TRichEdit *RichEdit1;
        TPanel *PanelTop;
        TButton *ButtonAbout;
  void __fastcall ButtonGenerateClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TFormRandomCode(TComponent* Owner);
  String generateString(const unsigned int length) const;
  String generateString() const;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormRandomCode *FormRandomCode;
//---------------------------------------------------------------------------
#endif
