//---------------------------------------------------------------------------
/*
Encranger, encryption tool
Copyright (C) 2009-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolEncranger.htm
//---------------------------------------------------------------------------
#include "encrangermaindialog.h"

#include "trace.h"
#include "testtimer.h"

ribi::ToolEncrangerMainDialog::ToolEncrangerMainDialog(const int key) noexcept
  : m_encranger(new Encranger(key)),
    m_encrypted_text{},
    m_key(key),
    m_plain_text{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

void ribi::ToolEncrangerMainDialog::Deencrypt() noexcept
{
  m_plain_text = m_encranger->Deencrypt(m_encrypted_text);
}

void ribi::ToolEncrangerMainDialog::Encrypt() noexcept
{
  m_encrypted_text = m_encranger->Encrypt(m_plain_text);
}

void ribi::ToolEncrangerMainDialog::SetEncryptedText(const std::string& s) noexcept
{
  m_encrypted_text = s;
}

void ribi::ToolEncrangerMainDialog::SetKey(const int i) noexcept
{
  m_encranger.reset(new Encranger(i));
}

void ribi::ToolEncrangerMainDialog::SetPlainText(const std::string& s) noexcept
{
  m_plain_text = s;
}

#ifndef NDEBUG
void ribi::ToolEncrangerMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    ToolEncrangerMainDialog d;
    const std::string s = "Hello World";
    d.SetKey(123);
    d.SetPlainText(s);
    d.Encrypt();
    const std::string encrypted = d.GetEncryptedText();
    d.SetEncryptedText(encrypted);
    d.Deencrypt();
    const std::string deencrypted = d.GetPlainText();
    assert(s == deencrypted);
  }
}
#endif
