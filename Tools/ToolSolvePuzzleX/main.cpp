//---------------------------------------------------------------------------
/*
ToolSolvePuzzleX, tool to solve the puzzle from X
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolSolvePuzzleX.htm
//---------------------------------------------------------------------------
#include <algorithm>
#include <iterator>
#include <iostream>
#include <map>
#include <vector>
//---------------------------------------------------------------------------
///plus/minus A                                  2
///times/divided by/plus/minus plus/minus B  4 * 2
///times/divided by/plus/minus plus/minus C  4 * 2
///times/divided by/plus/minus plus/minus D  4 * 2
///------------------------------------------------- *
///                                           1024
///Ordering of A,B,C and D: 4! =                24
///------------------------------------------------- *
///Total possibilities                      24,576
struct Formula
{
  Formula(
                              const int sign_a, const double a,
    const int operation_b, const int sign_b, const double b,
    const int operation_c, const int sign_c, const double c,
    const int operation_d, const int sign_d, const double d)
    :                             m_sign_a(sign_a), m_a(a),
      m_operation_b(operation_b), m_sign_b(sign_b), m_b(b),
      m_operation_c(operation_c), m_sign_c(sign_c), m_c(c),
      m_operation_d(operation_d), m_sign_d(sign_d), m_d(d)
  {
    m_value = (m_sign_a % 2 ? m_a : -m_a);
    switch (m_operation_b % 4)
    {
      case 0: m_value *= (m_sign_b % 2 ? m_b : -m_b); break;
      case 1: m_value /= (m_sign_b % 2 ? m_b : -m_b); break;
      case 2: m_value += (m_sign_b % 2 ? m_b : -m_b); break;
      case 3: m_value -= (m_sign_b % 2 ? m_b : -m_b); break;
    }
    switch (m_operation_c % 4)
    {
      case 0: m_value *= (m_sign_c % 2 ? m_c : -m_c); break;
      case 1: m_value /= (m_sign_c % 2 ? m_c : -m_c); break;
      case 2: m_value += (m_sign_c % 2 ? m_c : -m_c); break;
      case 3: m_value -= (m_sign_c % 2 ? m_c : -m_c); break;
    }
    switch (m_operation_d % 4)
    {
      case 0: m_value *= (m_sign_d % 2 ? m_d : -m_d); break;
      case 1: m_value /= (m_sign_d % 2 ? m_d : -m_d); break;
      case 2: m_value += (m_sign_d % 2 ? m_d : -m_d); break;
      case 3: m_value -= (m_sign_d % 2 ? m_d : -m_d); break;
    }
  }
  double GetValue() const { return m_value; }
  private:
  friend std::ostream& operator<<(std::ostream& os, const Formula& f);
  const int m_sign_a;
  const double m_a;
  const int m_operation_b;
  const int m_sign_b;
  const double m_b;
  const int m_operation_c;
  const int m_sign_c;
  const double m_c;
  const int m_operation_d;
  const int m_sign_d;
  const double m_d;
  double m_value;
};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Formula& f)
{
  os
    << (f.m_sign_a % 2 ? " " : "-") << f.m_a;
    switch (f.m_operation_b % 4)
    {
      case 0: os << "*" << (f.m_sign_b % 2 ? " " : "-") << f.m_b; break;
      case 1: os << "/" << (f.m_sign_b % 2 ? " " : "-") << f.m_b; break;
      case 2: os << "+" << (f.m_sign_b % 2 ? " " : "-") << f.m_b; break;
      case 3: os << "-" << (f.m_sign_b % 2 ? " " : "-") << f.m_b; break;
    }
    switch (f.m_operation_c % 4)
    {
      case 0: os << "*" << (f.m_sign_c % 2 ? " " : "-") << f.m_c; break;
      case 1: os << "/" << (f.m_sign_c % 2 ? " " : "-") << f.m_c; break;
      case 2: os << "+" << (f.m_sign_c % 2 ? " " : "-") << f.m_c; break;
      case 3: os << "-" << (f.m_sign_c % 2 ? " " : "-") << f.m_c; break;
    }
    switch (f.m_operation_d % 4)
    {
      case 0: os << "*" << (f.m_sign_d % 2 ? " " : "-") << f.m_d; break;
      case 1: os << "/" << (f.m_sign_d % 2 ? " " : "-") << f.m_d; break;
      case 2: os << "+" << (f.m_sign_d % 2 ? " " : "-") << f.m_d; break;
      case 3: os << "-" << (f.m_sign_d % 2 ? " " : "-") << f.m_d; break;
    }
  os << " = " << f.GetValue();
  return os;
}
//---------------------------------------------------------------------------
int main()
{
  std::map<double,int> tally;
  const std::vector<double> values = { 1.0,3.0,4.0,6.0 };

  for (int sign_a = 0; sign_a!=2; ++sign_a)
    for (int a = 0; a!=4; ++a)
      for (int operation_b = 0; operation_b!=4; ++operation_b)
        for (int sign_b = 0; sign_b!=2; ++sign_b)
          for (int b = 0; b!=4; ++b)
          {
            if (a == b) continue;
            for (int operation_c = 0; operation_c!=4; ++operation_c)
              for (int sign_c = 0; sign_c!=2; ++sign_c)
                for (int c = 0; c!=4; ++c)
                {
                  if (a==c || b ==c) continue;
                  for (int operation_d = 0; operation_d!=4; ++operation_d)
                    for (int sign_d = 0; sign_d!=2; ++sign_d)
                      for (int d = 0; d!=4; ++d)
                      {
                        if (a==d || b==d || c==d) continue;
                        Formula f(sign_a,values[a],
                          operation_b,sign_b,values[b],
                          operation_c,sign_c,values[c],
                          operation_d,sign_d,values[d]);
                        if (f.GetValue() > 23.9 && f.GetValue() < 24.01) std::cout << f << '\n';
                        ++tally[ f.GetValue() ];
                      }
                }
          }
  std::for_each(
    tally.begin(),tally.end(),
    [](const std::pair<const double,int>& p)
      { std::cout << p.first << " " << p.second << '\n'; }
    );
}
//---------------------------------------------------------------------------
