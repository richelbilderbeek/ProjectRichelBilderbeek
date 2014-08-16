//---------------------------------------------------------------------------
/*
  KeySender, demonstration of CSendKey class by Lallous
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
#ifndef UnitFormKeySenderH
#define UnitFormKeySenderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormKeySender : public TForm
{
__published:	// IDE-managed Components
        TButton *ButtonSend;
        TLabeledEdit *EditWindowTitle;
        TRichEdit *RichEdit;
        TButton *ButtonStartNotepad;
        TButton *ButtonAbout;
        void __fastcall ButtonSendClick(TObject *Sender);
        void __fastcall ButtonStartNotepadClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormKeySender(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormKeySender *FormKeySender;
//---------------------------------------------------------------------------
#endif
