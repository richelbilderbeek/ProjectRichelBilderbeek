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
#include <vcl.h>
#pragma hdrstop

#include <cassert>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "UnitFormMain.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{

  assert(IntToGray( 0)== 0);
  assert(IntToGray( 1)== 1);
  assert(IntToGray( 2)== 3);
  assert(IntToGray( 3)== 2);
  assert(IntToGray( 4)== 6);
  assert(IntToGray( 5)== 7);
  assert(IntToGray( 6)== 5);
  assert(IntToGray( 7)== 4);
  assert(IntToGray( 8)==12);
  assert(IntToGray( 9)==13);
  assert(IntToGray(10)==15);
  assert(IntToGray(11)==14);
  assert(IntToGray(12)==10);
  assert(IntToGray(13)==11);
  assert(IntToGray(14)== 9);
  assert(IntToGray(15)== 8);

  assert(GrayToInt( 0)== 0);
  assert(GrayToInt( 1)== 1);
  assert(GrayToInt( 3)== 2);
  assert(GrayToInt( 2)== 3);
  assert(GrayToInt( 6)== 4);
  assert(GrayToInt( 7)== 5);
  assert(GrayToInt( 5)== 6);
  assert(GrayToInt( 4)== 7);
  assert(GrayToInt(12)== 8);
  assert(GrayToInt(13)== 9);
  assert(GrayToInt(15)==10);
  assert(GrayToInt(14)==11);
  assert(GrayToInt(10)==12);
  assert(GrayToInt(11)==13);
  assert(GrayToInt( 9)==14);
  assert(GrayToInt( 8)==15);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::EditIntChange(TObject *Sender)
{
  const std::string int_digit = EditInt->Text.c_str();

  if (CanLexicalCast<int>(int_digit)==false) return;

  const int i = boost::lexical_cast<int>(int_digit);

  const std::string int_bits = IntToBitString(i);

  EditIntBinary->Text = int_bits.c_str();

  const int g = IntToGray(i);

  EditGray->Text = IntToStr(g);

  const std::string gray_bits = IntToBitString(g);

  EditGrayBinary->Text = gray_bits.c_str();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::EditGrayChange(TObject *Sender)
{
  const std::string gray_digit = EditGray->Text.c_str();

  if (CanLexicalCast<int>(gray_digit)==false) return;

  const int g = boost::lexical_cast<int>(gray_digit);

  const std::string gray_bits = IntToBitString(g);

  EditGrayBinary->Text = gray_bits.c_str();

  const int i = GrayToInt(g);

  EditInt->Text = IntToStr(i);

  const std::string int_bits = IntToBitString(i);

  EditIntBinary->Text = int_bits.c_str();

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonIntMinusClick(TObject *Sender)
{
  const std::string int_digit = EditInt->Text.c_str();

  if (CanLexicalCast<int>(int_digit)==false)
  {
    EditInt->Text = "0";
    return;
  }

  const int i = boost::lexical_cast<int>(int_digit);

  if (i > 0)
  {
    EditInt->Text = IntToStr(i-1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonIntPlusClick(TObject *Sender)
{
  const std::string int_digit = EditInt->Text.c_str();

  if (CanLexicalCast<int>(int_digit)==false)
  {
    EditInt->Text = "0";
    return;
  }

  const int i = boost::lexical_cast<int>(int_digit);

  const int max_int = -1 + (256 * 256) + (256 * 256);

  if (i < max_int)
  {
    EditInt->Text = IntToStr(i+1);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonGrayMinusClick(TObject *Sender)
{
  const std::string gray_digit = EditGray->Text.c_str();

  if (CanLexicalCast<int>(gray_digit)==false)
  {
    EditGray->Text = "0";
    return;
  }

  const int i = boost::lexical_cast<int>(gray_digit);

  if (i > 0)
  {
    EditGray->Text = IntToStr(i-1);
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonGrayPlusClick(TObject *Sender)
{
  const std::string gray_digit = EditGray->Text.c_str();

  if (CanLexicalCast<int>(gray_digit)==false)
  {
    EditGray->Text = "0";
    return;
  }

  const int i = boost::lexical_cast<int>(gray_digit);

  const int max_int = -1 + (256 * 256) + (256 * 256);

  if (i < max_int)
  {
    EditGray->Text = IntToStr(i+1);
  }

}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppIntToGray.htm
const int IntToGray(const int i)
{
  return (i ^ (i>>1));
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGrayToInt.htm
//Modified from Press et al., 2002, Numerical Recipies in C++,
//ISBN 0 521 75033 4
const int GrayToInt(int i)
{
  int power = 1;
  while (1)
  {
    const int j = i >> power;
    i ^= j;
    if (j == 0 || power == 16) return i;
    power <<= 1;
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppIntToBitString.htm
const std::string IntToBitString(int i)
{
  assert( i >= 0 && "Did not bother to supply this yet");
  std::string s =(i%2 ? "1" : "0" );
  i>>=1;
  while (i > 0)
  {
    s = (i%2 ? "1" : "0") + s;
    i>>=1;
  }
  return s;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCanLexicalCast.htm
template <class TargetType>
const bool CanLexicalCast(const std::string& from)
{
  try
  {
    boost::lexical_cast<TargetType>(from);
  }
  catch (boost::bad_lexical_cast)
  {
    return false;
  }
  catch (...)
  {
    assert(!"Something unexpected happened");
    throw;
  }
  return true;
}
//---------------------------------------------------------------------------



void __fastcall TFormMain::ButtonAboutClick(TObject *Sender)
{
  boost::shared_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

