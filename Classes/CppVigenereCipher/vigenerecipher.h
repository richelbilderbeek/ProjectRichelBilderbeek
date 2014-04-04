//---------------------------------------------------------------------------
/*
VigenereCipher, Vigenere cipher class
Copyright (C) 2010-2014 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppVigenereCipher.htm
//---------------------------------------------------------------------------
#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <string>
#include <vector>

namespace ribi {

///Vigenere cipher class
struct VigenereCipher
{
  VigenereCipher(const std::string& s);
  std::string Encrypt(std::string s) const;
  std::string Deencrypt(std::string s) const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  const std::vector<int> m_key;

  char Encrypt(const char c, const int d) const noexcept;
  char Deencrypt(const char c, const int d) const noexcept;

  static std::vector<int> StrToKey(const std::string& s) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // VIGENERECIPHER_H
