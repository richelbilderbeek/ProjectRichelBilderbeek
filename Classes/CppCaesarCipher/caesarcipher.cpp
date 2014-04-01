//---------------------------------------------------------------------------
/*
CaesarCipher, Caesar cipher class
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
// From http://www.richelbilderbeek.nl/CppCaesarCipher.htm
//---------------------------------------------------------------------------
#include "caesarcipher.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <vector>

#include "trace.h"
#include "loopreader.h"

ribi::CaesarCipher::CaesarCipher(const int key)
  : m_key(key)
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::CaesarCipher::Encrypt(std::string s) const noexcept
{
  for (auto& c:s)
  {
    assert(c >= 'A');
    assert(c <= 'Z');
    c = Encrypt(c,m_key);
    assert(c >= 'A');
    assert(c <= 'Z');
  }
  return s;
}

std::string ribi::CaesarCipher::Deencrypt(std::string s) const noexcept
{
  for (auto& c:s)
  {
    assert(c >= 'A');
    assert(c <= 'Z');
    c = Deencrypt(c,m_key);
    assert(c >= 'A');
    assert(c <= 'Z');
  }
  return s;
}

char ribi::CaesarCipher::Encrypt(const char c, const int d) const noexcept
{
  assert(c >= 'A');
  assert(c <= 'Z');
  const int i = static_cast<int>(c - 'A');
  const int i_new = (((i + d) % 26) + 26) % 26;
  assert(i_new >= 0);
  assert(i_new < 26);
  const char r = static_cast<char>('A' + i_new);
  assert(d != 0 || c == r);
  assert(r >= 'A');
  assert(r <= 'Z');
  return r;
}

char ribi::CaesarCipher::Deencrypt(const char c, const int d) const noexcept
{
  assert(c >= 'A');
  assert(c <= 'Z');
  const int i = static_cast<int>(c - 'A');
  const int i_new = (((i - d) % 26) + 26) % 26;
  assert(i_new >= 0);
  assert(i_new < 26);
  const char r = static_cast<char>('A' + i_new);
  assert(d != 0 || c == r);
  assert(r >= 'A');
  assert(r <= 'Z');
  return r;
}

std::string ribi::CaesarCipher::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::CaesarCipher::GetVersionHistory() noexcept
{
  return {
    "2014-04-01: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::CaesarCipher::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::CaesarCipher::Test");
  {
    const CaesarCipher e(0);
    const std::string s = "ABCDEFGH";
    assert(s == e.Encrypt(s));
    assert(s == e.Deencrypt(s));
  }
  {
    const std::vector<std::string> v {
      "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "A",
      "AB"
    };
    for (const std::string& s: v)
    {
      for (const int key: {0,1,2,4,8,16,257,-13,-12345} )
      {
        const CaesarCipher e(key);
        assert(e.Deencrypt(e.Encrypt(s)) == s);
        //Test encryption with real, decryption with faker
        const CaesarCipher faker(key + 1);
        assert(faker.Deencrypt(e.Encrypt(s)) != s);
      }
    }
  }
  TRACE("Finished ribi::CaesarCipher::Test successfully");
}
#endif
