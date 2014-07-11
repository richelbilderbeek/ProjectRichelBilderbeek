//---------------------------------------------------------------------------
/*
  MultiEncranger, encryption and de-encryption tool
  Copyright (C) 2010  Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#pragma hdrstop

#include <cassert>
#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <algorithm>
#include "UnitLoopReader.h"
#include "UnitEncranger.h"

//---------------------------------------------------------------------------
Encranger::Encranger(const int key)
  : characters(CreateCharacters()),
    table(CreateTable(key,characters.size()))
{

}
//---------------------------------------------------------------------------
const std::string Encranger::Encrypt(std::string s) const
{
  typedef std::string::iterator StringIterator;
  LoopReader<std::vector<int>::const_iterator> table_reader(table.begin(), table.end());

  const StringIterator j = s.end();
  for (StringIterator i = s.begin(); i!=j; ++i, table_reader.Next())
  {
    *i = Encrypt(*i,*table_reader.Read());
  }
  return s;
}
//---------------------------------------------------------------------------
const std::string Encranger::Deencrypt(std::string s) const
{
  typedef std::string::iterator StringIterator;
  LoopReader<std::vector<int>::const_iterator> table_reader(table.begin(), table.end());

  const StringIterator j = s.end();
  for (StringIterator i = s.begin(); i!=j; ++i, table_reader.Next())
  {
    *i = Deencrypt(*i,*table_reader.Read());
  }
  return s;
}
//---------------------------------------------------------------------------
const char Encranger::Encrypt(const char c, const int d) const
{
  const int i = GetIndex(c);
  const int n_chars = static_cast<int>(characters.size());
  const int i_new = (i + d) % n_chars;
  assert(i_new >= 0);
  assert(i_new < static_cast<int>(characters.size()));
  return characters[i_new];
}
//---------------------------------------------------------------------------
const char Encranger::Deencrypt(const char c, const int d) const
{
  const int i = GetIndex(c);
  const int n_chars = static_cast<int>(characters.size());
  const int i_new = (i - d + n_chars) % n_chars;
  assert(i_new >= 0);
  assert(i_new < static_cast<int>(characters.size()));
  return characters[i_new];
}
//---------------------------------------------------------------------------
const int Encranger::GetIndex(const char c) const
{
  const std::vector<char>::const_iterator i
    = std::find(characters.begin(), characters.end(), c);
  assert(i!=characters.end());
  return i - characters.begin();
}
//---------------------------------------------------------------------------
const std::vector<int> Encranger::CreateTable(const int key, const unsigned int sz) const
{
  assert(sz!=0);

  std::vector<int> v(sz);
  std::for_each(v.begin(), v.end(), Increase() );

  assert(sz > 5); //Only for these tests below
  assert(v[0] == 0);
  assert(v[1] == 1);
  assert(v[2] == 2);
  assert(v[3] == 3);
  assert(v[4] == 4);

  //The key is the seed
  std::srand(key);

  //Shuffle
  std::random_shuffle(v.begin(),v.end());

  return v;
}
//---------------------------------------------------------------------------
const std::vector<char> Encranger::CreateCharacters() const
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
//---------------------------------------------------------------------------
#pragma package(smart_init)

