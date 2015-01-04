//---------------------------------------------------------------------------
/*
CaesarCipher, Caesar cipher class
Copyright (C) 2010-2015 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppCaesarCipher.htm
//---------------------------------------------------------------------------
#ifndef RIBI_CAESARCIPHER_H
#define RIBI_CAESARCIPHER_H

#include <string>
#include <vector>

namespace ribi {

///Caesar cipher class
struct CaesarCipher
{
  CaesarCipher(const int key);

  ///Creates a clean string, which is a
  ///lowercasenospaces string
  static std::string Clean(const std::string& s) noexcept;

  ///Assumes IsClean, use Clean to make it so
  std::string Encrypt(std::string s) const noexcept;

  ///Assumes IsClean, use Clean to make it so
  std::string Deencrypt(std::string s) const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Checks if string is clean, which is a
  ///lowercasenospaces string. Use Clean to make it so.
  static bool IsClean(const std::string& s) noexcept;

  private:
  const int m_key;

  char Encrypt(const char c, const int d) const noexcept;
  char Deencrypt(const char c, const int d) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_CAESARCIPHER_H
