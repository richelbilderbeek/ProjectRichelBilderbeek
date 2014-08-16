//---------------------------------------------------------------------------
/*
  MultiEncranger, encryption and de-encryption tool
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
#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelPlainText;
        TPanel *PanelMiddle;
        TPanel *PanelCodedText;
        TButton *ButtonEncrypt;
        TButton *ButtonDeencrypt;
        TImage *ImageDown;
        TImage *ImageUp;
        TEdit *EditKey;
        TLabel *LabelKey;
        TButton *ButtonAbout;
        TRichEdit *EditPlainText;
        TRichEdit *EditCodedText;
        void __fastcall ButtonEncryptClick(TObject *Sender);
        void __fastcall ButtonDeencryptClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
const std::vector<int> Evaluate();
//---------------------------------------------------------------------------


#endif
