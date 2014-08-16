//---------------------------------------------------------------------------
/*
  Random Code, generates random C++ code
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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <memory>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormRandomCode.h"
#include "UnitFormRandomCodeAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormRandomCode *FormRandomCode;
//---------------------------------------------------------------------------
__fastcall TFormRandomCode::TFormRandomCode(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormRandomCode::ButtonAboutClick(TObject *Sender)
{
  std::auto_ptr<TFormRandomCodeAbout> f(new TFormRandomCodeAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormRandomCode::ButtonGenerateClick(TObject *Sender)
{
  RichEdit1->Lines->Clear();
  RichEdit1->Lines->Add("#include <iostream>");
  RichEdit1->Lines->Add("#include <string>");
  RichEdit1->Lines->Add("#include <vector>");
  RichEdit1->Lines->Add("");
  RichEdit1->Lines->Add("int main(int argc, char* argv[])");
  RichEdit1->Lines->Add("{");

  for (int i=0; i<50; ++i)
  {
    RichEdit1->Lines->Add(generateString(3+rand()%10));
  }

  RichEdit1->Lines->Add("  return 0;");
  RichEdit1->Lines->Add("}");

}
//---------------------------------------------------------------------------
String TFormRandomCode::generateString(const unsigned int length) const
{
  String string = "  ";
  for (unsigned int i=0; i!=length; ++i)
  {
    string+=generateString();
  }
  string+=";";
  return string;
}
//---------------------------------------------------------------------------
String TFormRandomCode::generateString() const
{
  switch (rand()%70)
  {
    case 0: return "a = ";
    case 1: return "b = ";
    case 2: return "c = ";
    case 3: return "d = ";
    case 4: return "e = ";
    case 5: return "f = ";
    case 6: return "g = ";
    case 7: return "h = ";
    case 8: return "i = ";
    case 9: return "j = ";
    case 10: return "k = ";
    case 11: return "l = ";
    case 12: return "m = ";
    case 13: return "n = ";
    case 14: return "o = ";
    case 15: return "p = ";
    case 16: return "q = ";
    case 17: return "r = ";
    case 18: return "s = ";
    case 19: return "t = ";
    case 20: return "u = ";
    case 21: return "v = ";
    case 22: return "w = ";
    case 23: return "x = ";
    case 24: return "y = ";
    case 25: return "z = ";
    case 26: return "{";
    case 27: return "}";
    case 28: return "(";
    case 29: return ")";
    case 30: return "*";
    case 31: return "&";
    case 32: return "int ";
    case 33: return "const ";
    case 34: return "double ";
    case 35: return "std::string ";
    case 36: return "++";
    case 37: return "--";
    case 38: return "+";
    case 39: return "-";
    case 40: return "/";
    case 41: return "*";
    case 42: return "static_cast<int>(";
    case 43: return "static_cast<double>(";
    case 44: return "class ";
    case 45: return "struct ";
    case 46: return "std::vector<double> ";
    case 47: return "std::vector<int> ";
    case 48: return "std::vector<std::string> ";
    case 49: return "std::vector<std::vector<double> >";
    case 50: return "std::vector<std::vector<int> >";
    case 51: return "std::vector<std::vector<std::string> >";
    case 52: return "for(int i=0; i!=j; ++i) { ";
    case 53: return "while(1) { ";
    case 55: return ")";
    case 56: return ")";
    case 57: return ")";
    case 58: return "}";
    case 59: return "}";
    case 60: return "}";
  }
  return " ";
}
//---------------------------------------------------------------------------

