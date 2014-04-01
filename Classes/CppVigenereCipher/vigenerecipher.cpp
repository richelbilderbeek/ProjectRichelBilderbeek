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
#include "vigenerecipher.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <vector>

#include "trace.h"
#include "loopreader.h"

ribi::VigenereCipher::VigenereCipher(const std::string& s)
  : m_key(StrToKey(s))
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::VigenereCipher::Encrypt(std::string s) const noexcept
{

  const int sz = static_cast<int>(s.size());
  for (int i=0; i!=sz; ++i)
  {
    const char c = s[i];
    assert(c >= 'A');
    assert(c <= 'Z');
    assert(m_key.size() > 0);
    const int key = m_key[ i % m_key.size() ];
    assert(key >= 0);
    assert(key  < 26);
    s[i] = Encrypt(c,key);
    assert(c >= 'A');
    assert(c <= 'Z');
  }
  return s;
}

std::string ribi::VigenereCipher::Deencrypt(std::string s) const noexcept
{
  const int sz = static_cast<int>(s.size());
  for (int i=0; i!=sz; ++i)
  {
    const char c = s[i];
    assert(c >= 'A');
    assert(c <= 'Z');
    const int key = m_key[ i % m_key.size() ];
    assert(key >= 0);
    assert(key  < 26);
    s[i] = Deencrypt(c,key);
    assert(c >= 'A');
    assert(c <= 'Z');
  }
  return s;
}

char ribi::VigenereCipher::Encrypt(const char c, const int d) const noexcept
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

char ribi::VigenereCipher::Deencrypt(const char c, const int d) const noexcept
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

std::string ribi::VigenereCipher::GetVersion() noexcept
{
  return "1.0";
}

std::vector<int> ribi::VigenereCipher::StrToKey(const std::string& s) noexcept
{
  std::vector<int> v;
  for (const auto c: s)
  {
    #ifndef NDEBUG
    if (!(c >= 'A'))
    {
      TRACE("BREAK");
    }
    #endif
    assert(c >= 'A');
    assert(c <= 'Z');
    const int i = static_cast<int>(c - 'A');
    v.push_back(i);
  }
  return v;
}

std::vector<std::string> ribi::VigenereCipher::GetVersionHistory() noexcept
{
  return {
    "2014-04-01: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::VigenereCipher::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::VigenereCipher::Test");
  {
    const VigenereCipher e("A");
    const std::string s = "ABCDEFGH";
    assert(s == e.Encrypt(s));
    assert(s == e.Deencrypt(s));
  }
  {
    const std::vector<std::string> v {
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXY",
      "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWX"
    };
    for (const std::string& s: v)
    {

      for (const std::string& key: { "AB", "ABC", "ABCDE"} )
      {
        const VigenereCipher e(key);
        assert(e.Deencrypt(e.Encrypt(s)) == s);
        //Test encryption with real, decryption with faker
        const VigenereCipher faker(key + "X");
        assert(faker.Deencrypt(e.Encrypt(s)) != s);
      }
    }
  }
  {
    const std::string key = "KEY";
    const std::string secret = "TSZNQHUWYJHRSCRPMIMMRYEMULIEHYTBKJQSOQKIRQXMIYHKLIRPDQAMVJQ";
    const VigenereCipher e(key);
    TRACE(e.Deencrypt(e.Encrypt(secret)));
  }
  TRACE("Finished ribi::VigenereCipher::Test successfully");
}
#endif
