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
#include <vcl.h>
#pragma hdrstop

#include <cassert>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "UnitEncranger.h"
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
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonEncryptClick(TObject *Sender)
{
  const int key = EditKey->Text.ToInt();
  Encranger e(key);

  EditCodedText->Lines->Clear();
  const int n_lines = EditPlainText->Lines->Count;
  for (int i=0; i!=n_lines; ++i)
  {
    const std::string s = EditPlainText->Lines->operator[](i).c_str();
    const std::string s_encrypted = e.Encrypt(s);
    EditCodedText->Lines->Add(s_encrypted.c_str());
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonDeencryptClick(TObject *Sender)
{
  const int key = EditKey->Text.ToInt();
  Encranger e(key);

  EditPlainText->Lines->Clear();
  const int n_lines = EditCodedText->Lines->Count;
  for (int i=0; i!=n_lines; ++i)
  {
    const std::string s = EditCodedText->Lines->operator[](i).c_str();
    const std::string s_deencrypted = e.Deencrypt(s);
    EditPlainText->Lines->Add(s_deencrypted.c_str());
  }

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------

