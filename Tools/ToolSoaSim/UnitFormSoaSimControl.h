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
#ifndef UnitFormSoaSimControlH
#define UnitFormSoaSimControlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSoaSimMain;
class TFormSoaSimChart;
class TFormSoaSimAddPerson;
//---------------------------------------------------------------------------
class TFormSoaSimControl : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TTimer *TimerMeasure;
        TButton *ButtonClearAll;
        TCheckBox *CheckBoxAddPerson;
        TCheckBox *CheckBoxShowChart;
        TButton *ButtonAbout;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall TimerMeasureTimer(TObject *Sender);
        void __fastcall CheckBoxAddPersonClick(TObject *Sender);
        void __fastcall CheckBoxShowChartClick(TObject *Sender);
        void __fastcall ButtonClearAllClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
  TFormSoaSimChart * mFormSoaSimChart;
  TFormSoaSimAddPerson * mFormSoaSimAddPerson;
public:		// User declarations
  __fastcall TFormSoaSimControl(TComponent* Owner);
  TFormSoaSimMain * mFormSoaSimMain;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSoaSimControl *FormSoaSimControl;
//---------------------------------------------------------------------------
#endif
