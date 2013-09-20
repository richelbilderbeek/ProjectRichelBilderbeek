//---------------------------------------------------------------------------
/*
  SoaSim, a simulator of sexually transmitted diseases
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
//From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitFormSoaSimAddH
#define UnitFormSoaSimAddH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSoaSimControl;
//---------------------------------------------------------------------------
class TFormSoaSimAddPerson : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TComboBox *ComboBoxStandardType;
        TComboBox *ComboBoxStandardInfected;
        TButton *ButtonAddStandard;
        TComboBox *ComboBoxCustomInfected;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *EditPagreeSafe;
        TEdit *EditPproposeSafe;
        TEdit *EditPagreeUnsafe;
        TButton *ButtonAddCustom;
        void __fastcall ButtonAddStandardClick(TObject *Sender);
        void __fastcall ButtonAddCustomClick(TObject *Sender);
private:	// User declarations
  TFormSoaSimControl * mFormSoaSimControl;
public:		// User declarations
        __fastcall TFormSoaSimAddPerson(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSoaSimAddPerson *FormSoaSimAddPerson;
//---------------------------------------------------------------------------
#endif
