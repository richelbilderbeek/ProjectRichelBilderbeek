//---------------------------------------------------------------------------
/*
  PrimeExpert, tool to calculate whether a number is prime
  Copyright (C) 2008  Richèl Bilderbeek

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
#include <boost/shared_ptr.hpp>
#include <boost/timer.hpp>
#include <boost/lexical_cast.hpp>
#include <vcl.h>
#pragma hdrstop

#include "UnitFormPrimeExpert.h"
#include "UnitFormPrimeExpertAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPrimeExpert *FormPrimeExpert;
//---------------------------------------------------------------------------
__fastcall TFormPrimeExpert::TFormPrimeExpert(TComponent* Owner)
        : TForm(Owner)
{
  RichEdit1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormPrimeExpert::EditValueChange(TObject *Sender)
{
  {
    int temp = 0;
    if ( IsInt(EditValue->Text.c_str(),temp) == false)
    {
      RichEdit1->Lines->Insert(0,"NaN");
      return;
    }
  }
  const int value = boost::lexical_cast<int>( EditValue->Text.c_str() );
  if (value < 2)
  {
    RichEdit1->Lines->Insert(0,"Not prime");
    return;
  }
  if (value == 2)
  {
    RichEdit1->Lines->Insert(0,"Prime");
    return;
  }
  const boost::timer t;
  const bool isPrime = mPrimeExpert.IsPrime(value);
  const double time = t.elapsed();
  const String text
    = String(isPrime == true ? "Prime" : "Not prime")
    + String(" (")
    + FloatToStr(time)
    + String(" sec)");
  RichEdit1->Lines->Insert(0,text);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppStrIsInt.htm
bool IsInt(const std::string& s, int& rInt)
{
  std::istringstream i(s);
  if (!(i >> rInt))
  {
    rInt = 0;
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrimeExpert::ButtonAboutClick(TObject *Sender)
{
  boost::shared_ptr<TFormPrimeExpertAbout> form(new TFormPrimeExpertAbout(0));
  form->ShowModal();
}
//---------------------------------------------------------------------------
