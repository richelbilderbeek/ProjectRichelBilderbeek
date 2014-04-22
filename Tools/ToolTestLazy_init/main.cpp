//---------------------------------------------------------------------------
/*
TestLazy_init. Tests the Lazy_init class.
Copyright (C) 2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestLazy_init.htm
//---------------------------------------------------------------------------
#include <iostream>

#include "lazy_init.h"

struct W
{
  W() { std::cout << "W contructor\n"; }
  void f() const { std::cout << "I am W" << '\n'; }
};

struct X
{
  X(const int x) : m_x(x) { std::cout << "X contructor\n"; }
  void f() const { std::cout << m_x << '\n'; }
  const int m_x;
};

struct Y
{
  Y(const std::string& s) : m_s(s) { std::cout << "Y contructor\n"; }
  void f() const { std::cout << m_s << '\n'; }
  const std::string m_s;
};

struct Z
{
  Z(const std::string& s, const int i) : m_s(s), m_i(i) { std::cout << "Z contructor\n"; }
  void f() const { std::cout << m_s << m_i << '\n'; }
  const std::string m_s;
  const int m_i;
};

int main()
{
  std::cout << "Lazy construction\n";
  ribi::LazyInit0<W> w;
  ribi::LazyInit1<X,int> x(314);
  ribi::LazyInit1<Y,std::string> y("Hello World");
  ribi::LazyInit2<Z,std::string,int> z("Hell",0);
  std::cout << "Calling objects\n";
  z.Get().f();
  y.Get().f();
  x.Get().f();
  w.Get().f();
}

/* Screen output:

Lazy construction
Calling objects
Z contructor
Hell0
Y contructor
Hello World
X contructor
314
W contructor
I am W
Press <RETURN> to close this window...

*/
