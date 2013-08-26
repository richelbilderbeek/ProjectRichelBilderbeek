//---------------------------------------------------------------------------
/*
  SimImmuneResponse. Active simulation about the human immune response
  Copyright (C) 2008  Richèl Bilderbeek

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
#ifndef UnitFormSimImmuneResponseOptionsH
#define UnitFormSimImmuneResponseOptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
struct TFormSimImmuneResponseMain;
//---------------------------------------------------------------------------
class TFormSimImmuneResponseOptions : public TForm
{
__published:	// IDE-managed Components
        TButton *ButtonProduceBcell;
        TButton *ButtonQuit;
        TButton *ButtonProduceCtl;
        TButton *ButtonProduceThelperCell;
        TButton *ButtonProduceMacrophage;
        TButton *ButtonAbout;
        TButton *ButtonRestart;
        void __fastcall ButtonQuitClick(TObject *Sender);
        void __fastcall ButtonProduceBcellClick(TObject *Sender);
        void __fastcall ButtonProduceCtlClick(TObject *Sender);
        void __fastcall ButtonProduceMacrophageClick(TObject *Sender);
        void __fastcall ButtonProduceThelperCellClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall ButtonRestartClick(TObject *Sender);
private:	// User declarations
  TFormSimImmuneResponseMain * const mFormMain;
public:		// User declarations
        __fastcall TFormSimImmuneResponseOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimImmuneResponseOptions *FormSimImmuneResponseOptions;
//---------------------------------------------------------------------------
#endif
