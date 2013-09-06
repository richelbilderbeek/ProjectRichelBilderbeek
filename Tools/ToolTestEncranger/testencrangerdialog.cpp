//---------------------------------------------------------------------------
/*
TestEncranger, tool to test the Encranger class
Copyright (C) 2009-2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestEncranger.htm
//---------------------------------------------------------------------------


#include "testencrangerdialog.h"

#include "loopreader.h"
//---------------------------------------------------------------------------
TestEncrangerDialog::TestEncrangerDialog()
  : m_encranger(new Encranger(0))
{

}
//---------------------------------------------------------------------------
void TestEncrangerDialog::Deencrypt()
{
  m_plain_text = m_encranger->Deencrypt(m_encrypted_text);
}
//---------------------------------------------------------------------------
void TestEncrangerDialog::Encrypt()
{
  m_encrypted_text = m_encranger->Encrypt(m_plain_text);
}
//---------------------------------------------------------------------------
void TestEncrangerDialog::SetEncryptedText(const std::string& s)
{
  m_encrypted_text = s;
}
//---------------------------------------------------------------------------
void TestEncrangerDialog::SetKey(const int i)
{
  m_encranger.reset(new Encranger(i));
}
//---------------------------------------------------------------------------
void TestEncrangerDialog::SetPlainText(const std::string& s)
{
  m_plain_text = s;
}
//---------------------------------------------------------------------------
const About TestEncrangerDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestEncranger",
    "tool to test the Encranger class",
    "the 31st of August 2011",
    "2009-2011",
    "http://www.richelbilderbeek.nl/ToolTestEncranger.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Encranger version: " + Encranger::GetVersion());
  a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());
  return a;
}
//---------------------------------------------------------------------------
const std::string TestEncrangerDialog::GetVersion()
{
  return "2.4";
}
//---------------------------------------------------------------------------
const std::vector<std::string> TestEncrangerDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2009-08-22: Version 1.0: initial version (then called 'Encranger') programmed in C++ Builder");
  v.push_back("2011-03-06: Version 2.0: port to Qt Creator, renamed application to TestEncranger");
  v.push_back("2011-03-22: Version 2.1: seperated GUI from logic, added website version");
  v.push_back("2011-04-25: Version 2.2: removed website version\'s Close button");
  v.push_back("2011-06-22: Version 2.3: improved website version");
  v.push_back("2011-08-31: Version 2.4: added arrows and Welcome image");
  return v;
}
//---------------------------------------------------------------------------
