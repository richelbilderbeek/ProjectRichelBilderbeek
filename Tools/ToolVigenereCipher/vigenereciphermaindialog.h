//---------------------------------------------------------------------------
/*
VigenereCipher, Vigenere cipher tool
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolVigenereCipher.htm
//---------------------------------------------------------------------------
#ifndef VIGENERECIPHERMAINDIALOG_H
#define VIGENERECIPHERMAINDIALOG_H

#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "about.h"
#include "vigenerecipher.h"

namespace ribi {

struct VigenereCipherMainDialog
{
  VigenereCipherMainDialog(const std::string& key) noexcept;
  void Deencrypt() noexcept;
  void Encrypt() noexcept;

  const std::string& GetEncryptedText() const noexcept { return m_encrypted_text; }
  const std::string& GetKey() const noexcept { return m_key; }
  const std::string& GetPlainText() const noexcept { return m_plain_text; }

  void SetEncryptedText(const std::string& s) noexcept;
  void SetKey(const std::string& s) noexcept;
  void SetPlainText(const std::string& s) noexcept;

  private:
  boost::scoped_ptr<VigenereCipher> m_vigenerecipher;
  std::string m_encrypted_text;
  std::string m_key;
  std::string m_plain_text;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // VIGENERECIPHERMAINDIALOG_H
