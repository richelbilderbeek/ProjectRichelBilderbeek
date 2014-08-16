//---------------------------------------------------------------------------
/*
  ThresholdFilterer, tool to perform threshold filter operations
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
#ifndef UnitFormThresholdFiltererH
#define UnitFormThresholdFiltererH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormThresholdFilterer : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl;
        TTabSheet *TabSheetOriginal;
        TTabSheet *TabSheetResult;
        TPanel *PanelOriginal;
        TPanel *PanelResult;
        TImage *ImageOriginal;
        TImage *ImageResult;
        TButton *ButtonLoad;
        TButton *ButtonSave;
        TTrackBar *TrackBarThreshold;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TButton *ButtonAbout0;
        TButton *ButtonAbout1;
        TCheckBox *CheckBoxColor;
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall TrackBarThresholdChange(TObject *Sender);
        void __fastcall ButtonSaveClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
        void __fastcall CheckBoxColorClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormThresholdFilterer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormThresholdFilterer *FormThresholdFilterer;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppThresholdFilter.htm
void ThresholdFilterColor(
  const TImage * const imageOriginal,
  const int threshold,
  const TImage * const imageResult);

//From http://www.richelbilderbeek.nl/CppThresholdFilter.htm
void ThresholdFilterNoColor(
  const TImage * const imageOriginal,
  const int threshold,
  const TImage * const imageResult);

#endif
