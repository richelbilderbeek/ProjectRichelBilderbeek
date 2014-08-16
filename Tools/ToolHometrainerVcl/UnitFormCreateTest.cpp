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
#include <vector>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vcl.h>
#pragma hdrstop
#include <boost/scoped_ptr.hpp>
#include <string>
#include "UnitEncranger.h"
#include "UnitFormCreateTest.h"
#include "UnitFormAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormCreateTest *FormCreateTest;
//---------------------------------------------------------------------------
__fastcall TFormCreateTest::TFormCreateTest(TComponent* Owner)
        : TForm(Owner)
{
  RandomizeTimer();
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateTest::ButtonEncryptClick(TObject *Sender)
{
  const int key = EditKey->Text.ToInt();
  const Encranger e(key);

  //Start at index one, because index zero is the copyright line
  std::random_shuffle(&m_plaintext[1],m_plaintext.end());

  m_ciphertext = m_plaintext;

  typedef std::vector<std::string>::iterator Iterator;
  const Iterator j = m_ciphertext.end();
  for (Iterator i = m_ciphertext.begin(); i!=j; ++i)
  {
    (*i) = e.Encrypt(*i); //TEMP
  }

  m_ciphertext.resize(EditNquestions->Text.ToInt()+1);

  VectorToStringList(m_ciphertext,RichEdit2->Lines);

  ++PageControl1->ActivePageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateTest::FormResize(TObject *Sender)
{
  RichEdit1->Width = ClientWidth / 2;
  RichEdit2->Width = ClientWidth - RichEdit1->Width;
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateTest::ButtonLoadClick(TObject *Sender)
{
  if (!OpenDialog1->Execute()) return;
  m_plaintext = FileToVector(OpenDialog1->FileName.c_str());
  VectorToStringList(m_plaintext,RichEdit1->Lines);
  EditNquestions->Text = m_plaintext.size() - 1;
  ButtonEncrypt->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateTest::ButtonSaveClick(TObject *Sender)
{
  if (!SaveDialog1->Execute()) return;
  SaveContainer(m_ciphertext,SaveDialog1->FileName.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TFormCreateTest::ButtonAboutClick(TObject *Sender)
{
  boost::scoped_ptr<TFormAbout> f(new TFormAbout(0));
  f->ShowModal();
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileToVector.htm
const std::vector<std::string> FileToVector(const std::string& fileName)
{
  assert(FileExists(fileName)==true);
  std::vector<std::string> myVector;
  std::ifstream in(fileName.c_str());
  std::string myString;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,myString);
    myVector.push_back(myString);
  }
  return myVector;
}
//---------------------------------------------------------------------------
void VectorToStringList(const std::vector<std::string>& v,TStrings * const l)
{
  l->Clear();
  typedef std::vector<std::string>::const_iterator Iterator;
  const Iterator j = v.end();
  for (Iterator i = v.begin(); i!=j; ++i)
  {
    l->Add((*i).c_str());
  }
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppFileExists.htm
const bool FileExists(const std::string& fileName)
{
  std::fstream fin;
  fin.open(fileName.c_str(),std::ios::in);
  if( fin.is_open() )
  {
    fin.close();
    return true;
  }
  fin.close();
  return false;
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer()
{
  std::srand(std::time(0));
}
//---------------------------------------------------------------------------


