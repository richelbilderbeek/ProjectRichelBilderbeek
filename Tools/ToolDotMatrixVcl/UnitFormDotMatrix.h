//---------------------------------------------------------------------------
/*
  DotMatrix, tool to demonstrate dot-matrix text drawing
  Copyright (C) 2009  Richel Bilderbeek

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
#ifndef UnitFormDotMatrixH
#define UnitFormDotMatrixH
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
#include <vector>
#include <string>
//---------------------------------------------------------------------------
class TFormDotMatrix : public TForm
{
__published:	// IDE-managed Components
        TImage *Image;
        TRichEdit *RichEdit;
        TSplitter *Splitter;
        TPanel *PanelBottom;
        TButton *Button1;
        TButton *ButtonSave;
        TSaveDialog *SaveDialog;
        void __fastcall RichEditChange(TObject *Sender);
        void __fastcall ButtonSaveClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormDotMatrix(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDotMatrix *FormDotMatrix;
//---------------------------------------------------------------------------
const std::vector<std::string> StringsToVector(const TStrings * const strings);
//---------------------------------------------------------------------------
const int FindLongestStringLength(const std::vector<std::string>& v);
//---------------------------------------------------------------------------
#endif
