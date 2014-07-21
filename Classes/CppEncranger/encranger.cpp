//---------------------------------------------------------------------------
/*
Encranger, encryption and de-encryption class
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
// From http://www.richelbilderbeek.nl/ToolMultiEncranger.htm
//---------------------------------------------------------------------------
#include "encranger.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <vector>

#include "trace.h"
#include "loopreader.h"

ribi::Encranger::Encranger(const int key) noexcept
  : m_characters(CreateCharacters()),
    m_table(CreateTable(key,CreateCharacters().size()))
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<int> ribi::Encranger::CreateTestKeys() noexcept
{
  std::vector<int> v;
  int x=1;
  for (int i=0; i!=16; ++i)
  {
    v.push_back(x);
    x *= 2;
  }
  return v;
}

std::string ribi::Encranger::Encrypt(std::string s) const noexcept
{
  typedef std::string::iterator StringIterator;
  typedef std::vector<int>::const_iterator LoopReaderIteratorType;
  LoopReader<LoopReaderIteratorType> table_reader(m_table.begin(), m_table.end());

  const StringIterator j = s.end();
  for (StringIterator i = s.begin(); i!=j; ++i, table_reader.Next())
  {
    *i = Encrypt(*i,*table_reader.Read());
  }
  return s;
}

std::string ribi::Encranger::Deencrypt(std::string s) const noexcept
{
  typedef std::string::iterator StringIterator;
  LoopReader<std::vector<int>::const_iterator> table_reader(m_table.begin(), m_table.end());

  const StringIterator j = s.end();
  for (StringIterator i = s.begin(); i!=j; ++i, table_reader.Next())
  {
    *i = Deencrypt(*i,*table_reader.Read());
  }
  return s;
}

char ribi::Encranger::Encrypt(const char c, const int d) const noexcept
{
  const int i = GetIndex(c);
  const int n_chars = static_cast<int>(m_characters.size());
  const int i_new = (i + d) % n_chars;
  assert(i_new >= 0);
  assert(i_new < static_cast<int>(m_characters.size()));
  return m_characters[i_new];
}

char ribi::Encranger::Deencrypt(const char c, const int d) const noexcept
{
  const int i = GetIndex(c);
  const int n_chars = static_cast<int>(m_characters.size());
  const int i_new = (i - d + n_chars) % n_chars;
  assert(i_new >= 0);
  assert(i_new < static_cast<int>(m_characters.size()));
  return m_characters[i_new];
}

int ribi::Encranger::GetIndex(const char c) const noexcept
{
  if (c == '\t' || c == '\n') return GetIndex(' ');
  const std::vector<char>::const_iterator i
    = std::find(m_characters.begin(), m_characters.end(), c);
  assert(i!=m_characters.end());
  return i - m_characters.begin();
}

std::vector<int> ribi::Encranger::CreateTable(const int key, const unsigned int sz) const noexcept
{
  assert(sz != 0 && "Supplied table must not be of size zero");

  std::vector<int> v(sz);
  std::iota(v.begin(),v.end(),0);

  //The key is the seed
  std::srand(key);

  //Shuffle
  std::random_shuffle(v.begin(),v.end());

  return v;
}

std::vector<char> ribi::Encranger::CreateCharacters() noexcept
{
  std::vector<char> v;
  //Uppercase
  v.push_back('A');
  v.push_back('B');
  v.push_back('C');
  v.push_back('D');
  v.push_back('E');
  v.push_back('F');
  v.push_back('G');
  v.push_back('H');
  v.push_back('I');
  v.push_back('J');
  v.push_back('K');
  v.push_back('L');
  v.push_back('M');
  v.push_back('N');
  v.push_back('O');
  v.push_back('P');
  v.push_back('Q');
  v.push_back('R');
  v.push_back('S');
  v.push_back('T');
  v.push_back('U');
  v.push_back('V');
  v.push_back('W');
  v.push_back('X');
  v.push_back('Y');
  v.push_back('Z');
  //Lowercase
  v.push_back('a');
  v.push_back('b');
  v.push_back('c');
  v.push_back('d');
  v.push_back('e');
  v.push_back('f');
  v.push_back('g');
  v.push_back('h');
  v.push_back('i');
  v.push_back('j');
  v.push_back('k');
  v.push_back('l');
  v.push_back('m');
  v.push_back('n');
  v.push_back('o');
  v.push_back('p');
  v.push_back('q');
  v.push_back('r');
  v.push_back('s');
  v.push_back('t');
  v.push_back('u');
  v.push_back('v');
  v.push_back('w');
  v.push_back('x');
  v.push_back('y');
  v.push_back('z');
  //Digits
  v.push_back('0');
  v.push_back('1');
  v.push_back('2');
  v.push_back('3');
  v.push_back('4');
  v.push_back('5');
  v.push_back('6');
  v.push_back('7');
  v.push_back('8');
  v.push_back('9');
  //Above digits
  v.push_back('!');
  v.push_back('@');
  v.push_back('#');
  v.push_back('$');
  v.push_back('%');
  v.push_back('^');
  v.push_back('&');
  v.push_back('*');
  v.push_back('(');
  v.push_back(')');
  //Other interpunction
  v.push_back('~');
  v.push_back('`');
  v.push_back('-');
  v.push_back('_');
  v.push_back('=');
  v.push_back('+');
  v.push_back('[');
  v.push_back(']');
  v.push_back('{');
  v.push_back('}');
  v.push_back(';');
  v.push_back(':');
  v.push_back('\'');
  v.push_back('\"');
  v.push_back('<');
  v.push_back('>');
  v.push_back(',');
  v.push_back('.');
  v.push_back('/');
  v.push_back('?');
  v.push_back('\\');
  v.push_back('|');
  v.push_back(' ');
  return v;
}

std::string ribi::Encranger::GetVersion() noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::Encranger::GetVersionHistory() noexcept
{
  return {
    "2010-01-05: version 1.0: initial version",
    "2011-01-12: version 1.1: added version info",
    "2014-04-01: version 1.2: replaced use of custom Increase class by std::iota",
    "2014-07-21: version 1.3: rigid testing"
  };
}

#ifndef NDEBUG
void ribi::Encranger::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Encranger::Test");
  //Test Increase
  {
    const std::size_t sz { 5 };
    std::vector<int> v(sz);
    //std::for_each(v.begin(), v.end(), Increase() );
    std::iota(v.begin(),v.end(),0);
    for (std::size_t i=0; i!=sz; ++i) { assert( v[i] == static_cast<int>(i) ); }
  }
  {
    const std::vector<std::string> v {
      "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz",
      "a cde ghijklm opqrstuvwxyzabc efghijklmnopqrstuvwxyzabcdefghi klmnopqrstuvwxyz",
      "a",
      " a",
      "a ",
      " a ",
      "  a  "
    };
    for (const std::string& s: v)
    {
      for (const int key: CreateTestKeys())
      {
        const Encranger e(key);
        assert(e.Deencrypt(e.Encrypt(s)) == s);
        //Test encryption with real, decryption with faker
        const Encranger faker(key + 1);
        if (faker.Deencrypt(e.Encrypt(s)) == s)
        {
          TRACE("ERROR");
          TRACE(key);
          TRACE(s);
          TRACE("BREAK");
        }
        assert(faker.Deencrypt(e.Encrypt(s)) != s);
      }
    }
  }
  TRACE("Finished ribi::Encranger::Test successfully");
}
#endif
