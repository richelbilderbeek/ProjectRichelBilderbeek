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
#ifndef UnitEncrangerH
#define UnitEncrangerH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
//Encranger stands for 'ENCryption by RAndom Number GEneratoR'
struct Encranger
{
  Encranger(const int key);
  const std::string Encrypt(std::string s) const;
  const std::string Deencrypt(std::string s) const;

  const std::vector<char> characters;
  const std::vector<int>  table;

  private:

  const char Encrypt(const char c, const int d) const;
  const char Deencrypt(const char c, const int d) const;
  const int GetIndex(const char c) const;

  const std::vector<int> CreateTable(const int key, const unsigned int sz) const;
  const std::vector<char> CreateCharacters() const;

};
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl
struct Increase : public std::unary_function<void,int>
{
  explicit Increase(const int initValue = 0) : mValue(initValue) {}
  void operator()(int& anything)
  {
    anything = mValue;
    ++mValue;
  }

  private:
  int mValue;
};
//---------------------------------------------------------------------------
#endif
