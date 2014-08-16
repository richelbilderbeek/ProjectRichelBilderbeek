//---------------------------------------------------------------------------
/*
  AsciiArter, tool to convert images to ASCII art
  Copyright (C) 2006  Richel Bilderbeek

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
#ifndef UnitFormAsciiArterH
#define UnitFormAsciiArterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
class TFormAsciiArter : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControlMain;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TImage *ImageOriginal;
        TRichEdit *RichEditAscii;
        TPanel *PanelOriginal;
        TPanel *PanelAscii;
        TEdit *EditWidth;
        TLabel *LabelWidth;
        TButton *ButtonLoad;
        TOpenDialog *OpenDialog1;
        TButton *ButtonAboutLoad;
        TButton *ButtonAboutAscii;
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall EditWidthChange(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
  bool mImageLoaded;
  const bool CanConvert() const;
  void Convert();
public:		// User declarations
        __fastcall TFormAsciiArter(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAsciiArter *FormAsciiArter;
//---------------------------------------------------------------------------
const std::vector<std::string> ImageToAscii(
  const TImage* const image,
  const int charWidth); //How many chars the ASCII image will be wide

const double GetFractionGrey(
  const TImage* const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2);

const unsigned char GetGreyness(
  const TImage * const image,
  const int x1,
  const int y1,
  const int x2,
  const int y2);

const unsigned char GetGreyness(
  const TImage * const image,
  const int x1,
  const int x2,
  const int y);

const unsigned char GetGreyness(
  const TImage * const image,
  const int x,
  const int y);

const std::vector<char> GetAsciiArtGradient();

const bool IsInt(const std::string& s);



#endif
