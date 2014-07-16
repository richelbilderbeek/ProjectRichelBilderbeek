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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trace.h"
#include "loopreader.h"
#pragma GCC diagnostic pop

ribi::CaesarCipher::CaesarCipher(const int key)
  : m_key(key)
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::CaesarCipher::Clean(const std::string& s) noexcept
{
  std::string t;
  std::copy_if(s.begin(),s.end(),std::back_inserter(t),
    [](const char c)
    {
      const char d = std::tolower(c);
      return d >= 'a' && d <= 'z';
    }
  );
  std::for_each(t.begin(),t.end(),
    [](char& c) { c = std::tolower(c); }
  );
  assert(IsClean(t));
  return t;
}

std::string ribi::CaesarCipher::Deencrypt(std::string s) const noexcept
{
  assert(IsClean(s));
  for (auto& c:s)
  {
    assert(c >= 'a');
    assert(c <= 'z');
    c = Deencrypt(c,m_key);
    assert(c >= 'a');
    assert(c <= 'z');
  }
  return s;
}

char ribi::CaesarCipher::Deencrypt(const char c, const int d) const noexcept
{
  assert(c >= 'a');
  assert(c <= 'z');
  const int i = static_cast<int>(c - 'a');
  const int i_new = (((i - d) % 26) + 26) % 26;
  assert(i_new >= 0);
  assert(i_new < 26);
  const char r = static_cast<char>('a' + i_new);
  assert(d != 0 || c == r);
  assert(r >= 'a');
  assert(r <= 'z');
  return r;
}


std::string ribi::CaesarCipher::Encrypt(std::string s) const noexcept
{
  #ifndef NDEBUG
  if(!IsClean(s))
  {
    TRACE("BREAK");
  }
  #endif
  assert(IsClean(s));
  for (auto& c:s)
  {
    assert(c >= 'a');
    assert(c <= 'z');
    c = Encrypt(c,m_key);
    assert(c >= 'a');
    assert(c <= 'z');
  }
  return s;
}


char ribi::CaesarCipher::Encrypt(const char c, const int d) const noexcept
{
  assert(c >= 'a');
  assert(c <= 'z');
  const int i = static_cast<int>(c - 'a');
  const int i_new = (((i + d) % 26) + 26) % 26;
  assert(i_new >= 0);
  assert(i_new < 26);
  const char r = static_cast<char>('a' + i_new);
  assert(d != 0 || c == r);
  assert(r >= 'a');
  assert(r <= 'z');
  return r;
}


std::string ribi::CaesarCipher::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::CaesarCipher::GetVersionHistory() noexcept
{
  return {
    "2014-04-01: version 1.0: initial version",
    "2014-04-07: version 1.1: use lowercase characters, added Clean and IsClean member functions"
  };
}

bool ribi::CaesarCipher::IsClean(const std::string& s) noexcept
{
  for (const auto& c:s) { if (c < 'a' || c > 'z') return false; }
  return true;
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
    assert(!CaesarCipher::IsClean(s));
    const std::string t = CaesarCipher::Clean(s);
    assert(t == "abcdefgh");
    assert(CaesarCipher::IsClean(t));
    assert(t == e.Encrypt(t));
    assert(t == e.Deencrypt(t));
  }
  {
    const std::vector<std::string> v {
      "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "A",
      "AB",
      "I am a dirty string"
    };
    for (const std::string& s: v)
    {
      for (const int key: {0,1,2,4,8,16,257,-13,-12345} )
      {
        const CaesarCipher e(key);
        const std::string t = CaesarCipher::Clean(s);
        assert(CaesarCipher::IsClean(t));
        assert(e.Deencrypt(e.Encrypt(t)) == t);
        //Test encryption with real, decryption with faker
        const CaesarCipher faker(key + 1);
        assert(faker.Deencrypt(e.Encrypt(t)) != t);
      }
    }
  }
  TRACE("Finished ribi::CaesarCipher::Test successfully");
}
#endif
