//---------------------------------------------------------------------------
/*
  HistogramEqualizationer, tool to perform a histogram equalization
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
//From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitFormHistogramEqualizationerH
#define UnitFormHistogramEqualizationerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormHistogramEqualizationer : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *TabSheetLoadAndHistogramEqualization;
        TTabSheet *TabSheetViewAndSave;
        TPanel *Panel1;
        TPanel *Panel2;
        TImage *ImageOriginal;
        TImage *ImageResult;
        TButton *ButtonLoad;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TTabSheet *TabSheetViewGreyImage;
        TImage *ImageGrey;
        TPanel *Panel3;
        TButton *ButtonSaveGrey;
        TButton *ButtonSaveResult;
        TButton *ButtonAboutOriginal;
        TButton *ButtonAboutGrey;
        TButton *ButtonAboutResult;
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall ButtonSaveGreyClick(TObject *Sender);
        void __fastcall ButtonSaveResultClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormHistogramEqualizationer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormHistogramEqualizationer *FormHistogramEqualizationer;
//---------------------------------------------------------------------------
void DoHistogramEqualization(const TImage * const source, TImage * const target);
void ConvertToGrey(const TImage * const source, TImage * const target);
const std::vector<int> GetImageHistogram(const TImage * const image);
export template <class T> const std::vector<T> GetCumulativeHistogram(const std::vector<T>& histogram);


#endif
