//---------------------------------------------------------------------------
/*
  Hometrainer 2, tool to make exercises and tests
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
#ifndef UnitFormCreateTestH
#define UnitFormCreateTestH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <string>
//---------------------------------------------------------------------------
class TFormCreateTest : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelBottom;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TPageControl *PageControl1;
        TTabSheet *TabSheetOriginal;
        TTabSheet *TabSheetCipherText;
        TRichEdit *RichEdit1;
        TRichEdit *RichEdit2;
        TPanel *PanelCodedText;
        TPanel *PanelPlainTextTop;
        TLabel *LabelKey;
        TButton *ButtonLoad;
        TEdit *EditKey;
        TButton *ButtonEncrypt;
        TButton *ButtonSave;
        TButton *ButtonAbout1;
        TButton *ButtonAbout2;
        TLabel *LabelNquestions;
        TEdit *EditNquestions;
        void __fastcall ButtonEncryptClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall ButtonLoadClick(TObject *Sender);
        void __fastcall ButtonSaveClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
  std::vector<std::string> m_plaintext;  //Model (in MVC)
  std::vector<std::string> m_ciphertext; //Model (in MVC)
public:		// User declarations
        __fastcall TFormCreateTest(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCreateTest *FormCreateTest;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& fileName);
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileExists.htm
const bool FileExists(const std::string& fileName);
//---------------------------------------------------------------------------
void VectorToStringList(const std::vector<std::string>& v,TStrings * const l);
//---------------------------------------------------------------------------
#include <algorithm>
#include <iterator>
#include <fstream>
//From http://www.richelbilderbeek.nl/CppSaveContainer.htm
template <class Container>
void SaveContainer(const Container& c, const std::string& filename)
{
  std::ofstream f(filename.c_str());
  std::copy(c.begin(),c.end(),std::ostream_iterator<Container::value_type>(f,"\n"));
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer();
//---------------------------------------------------------------------------



#endif
