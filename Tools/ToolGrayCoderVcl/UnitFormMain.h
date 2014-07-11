//---------------------------------------------------------------------------
/*
  GrayCoder, tool to convert integers to and from Gray code
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
#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TEdit *EditInt;
        TEdit *EditGray;
        TPanel *PanelInt;
        TPanel *PanelGray;
        TPanel *PanelTop;
        TPanel *PanelBottom;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *EditIntBinary;
        TEdit *EditGrayBinary;
        TButton *ButtonIntPlus;
        TButton *ButtonIntMinus;
        TButton *ButtonGrayMinus;
        TButton *ButtonGrayPlus;
        TButton *ButtonAbout;
        void __fastcall EditIntChange(TObject *Sender);
        void __fastcall EditGrayChange(TObject *Sender);
        void __fastcall ButtonIntMinusClick(TObject *Sender);
        void __fastcall ButtonIntPlusClick(TObject *Sender);
        void __fastcall ButtonGrayPlusClick(TObject *Sender);
        void __fastcall ButtonGrayMinusClick(TObject *Sender);
        void __fastcall ButtonAboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppIntToBitString.htm
const std::string IntToBitString(int i);
//From http://www.richelbilderbeek.nl/CppIntToGray.htm
const int IntToGray(const int i);
//From http://www.richelbilderbeek.nl/CppGrayToInt.htm
const int GrayToInt(int i);
//From http://www.richelbilderbeek.nl/CppCanLexicalCast.htm
export template <class TargetType>
const bool CanLexicalCast(const std::string& from);
//---------------------------------------------------------------------------





#endif
