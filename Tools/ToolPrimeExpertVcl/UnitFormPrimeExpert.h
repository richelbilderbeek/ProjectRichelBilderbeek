//---------------------------------------------------------------------------
/*
  PrimeExpert, tool to calculate whether a number is prime
  Copyright (C) 2008  Richel Bilderbeek

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
#ifndef UnitFormPrimeExpertH
#define UnitFormPrimeExpertH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "UnitPrimeExpert.h"
#include <Mask.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormPrimeExpert : public TForm
{
__published:	// IDE-managed Components
        TLabeledEdit *EditValue;
        TButton *ButtonAbout;
        TRichEdit *RichEdit1;
        void __fastcall EditValueChange(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
  PrimeExpert mPrimeExpert;
public:		// User declarations
        __fastcall TFormPrimeExpert(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPrimeExpert *FormPrimeExpert;
//---------------------------------------------------------------------------
bool IsInt(const std::string& s, int& rInt);

#endif
