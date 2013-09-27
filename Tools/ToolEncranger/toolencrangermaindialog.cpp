//---------------------------------------------------------------------------
/*
Encranger, encryption tool
Copyright (C) 2009-2013 Richel Bilderbeek

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
#include "toolencrangermaindialog.h"

ribi::ToolEncrangerMainDialog::ToolEncrangerMainDialog()
  : m_encranger(new Encranger(0)), // 0 == m_key
    m_encrypted_text{},
    m_key(0),
    m_plain_text{}
{

}

void ribi::ToolEncrangerMainDialog::Deencrypt()
{
  m_plain_text = m_encranger->Deencrypt(m_encrypted_text);
}

void ribi::ToolEncrangerMainDialog::Encrypt()
{
  m_encrypted_text = m_encranger->Encrypt(m_plain_text);
}

void ribi::ToolEncrangerMainDialog::SetEncryptedText(const std::string& s)
{
  m_encrypted_text = s;
}

void ribi::ToolEncrangerMainDialog::SetKey(const int i)
{
  m_encranger.reset(new Encranger(i));
}

void ribi::ToolEncrangerMainDialog::SetPlainText(const std::string& s)
{
  m_plain_text = s;
}
