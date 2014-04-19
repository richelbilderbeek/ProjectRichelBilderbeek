//---------------------------------------------------------------------------
/*
ToolSolvePuzzleX, tool to solve the puzzle from X
Copyright (C) 2011-2014 Richel Bilderbeek

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
      m_operation_d(operation_d), m_sign_d(sign_d), m_d(d),
      m_value{}
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

/* Screen output

-15 64
-14 320
-14 8
-13 384
-12.6667 8
-12.5 8
-12 360
-11.5 8
-11.3333 8
-11 32
-10.5 8
-10.3333 16
-10 48
-9.66667 8
-9.66667 8
-9.33333 32
-9.25 16
-9 96
-8.75 16
-8.33333 16
-8.33333 16
-8 496
-7.75 16
-7.66667 32
-7.5 8
-7.33333 64
-7.16667 8
-7.16667 8
-7 480
-6.83333 16
-6.75 64
-6.66667 32
-6.5 16
-6.33333 16
-6.33333 16
-6.25 16
-6.08333 16
-6 856
-5.91667 16
-5.75 16
-5.66667 32
-5.5 80
-5.25 96
-5 456
-4.75 32
-4.66667 80
-4.66667 16
-4.5 384
-4.33333 16
-4.33333 32
-4.25 48
-4.05556 16
-4 200
-3.94444 16
-3.83333 16
-3.75 32
-3.66667 16
-3.66667 128
-3.5 144
-3.33333 144
-3.25 32
-3.04167 16
-3 192
-2.95833 16
-2.75 16
-2.66667 48
-2.5 128
-2.33333 88
-2.33333 24
-2.25 112
-2.16667 16
-2.16667 32
-2.08333 8
-2 568
-2 8
-1.91667 8
-1.83333 16
-1.75 32
-1.66667 16
-1.66667 32
-1.58333 8
-1.5 128
-1.41667 8
-1.38889 8
-1.33333 16
-1.33333 80
-1.27778 8
-1.25 32
-1.22222 16
-1.16667 8
-1.16667 128
-1.16667 8
-1.125 16
-1 536
-0.875 16
-0.833333 16
-0.833333 24
-0.791667 8
-0.777778 16
-0.75 120
-0.722222 8
-0.708333 8
-0.666667 112
-0.611111 8
-0.583333 32
-0.555556 8
-0.541667 8
-0.5 224
-0.458333 8
-0.416667 32
-0.388889 8
-0.375 8
-0.333333 16
-0.333333 96
-0.291667 8
-0.277778 32
-0.25 24
-0.222222 144
-0.166667 16
-0.166667 184
-0.125 152
-0.111111 8
-0.0833333 32
-0.0555556 8
-0.0416667 8
-0.0138889 48
-0 576
0.0138889 48
0.0416667 8
0.0555556 8
0.0833333 32
0.111111 8
0.125 152
0.166667 184
0.166667 16
0.222222 144
0.25 24
0.277778 32
0.291667 8
0.333333 96
0.333333 16
0.375 8
0.388889 8
0.416667 32
0.458333 8
0.5 224
0.541667 8
0.555556 8
0.583333 32
0.611111 8
0.666667 112
0.708333 8
0.722222 8
0.75 120
0.777778 16
0.791667 8
0.833333 24
0.833333 16
0.875 16
1 536
1.125 16
1.16667 8
1.16667 128
1.16667 8
1.22222 16
1.25 32
1.27778 8
1.33333 80
1.33333 16
1.38889 8
1.41667 8
1.5 128
1.58333 8
1.66667 32
1.66667 16
1.75 32
1.83333 16
1.91667 8
2 8
2 568
2.08333 8
2.16667 32
2.16667 16
2.25 112
2.33333 24
2.33333 88
2.5 128
2.66667 48
2.75 16
2.95833 16
3 192
3.04167 16
3.25 32
3.33333 144
3.5 144
3.66667 128
3.66667 16
3.75 32
3.83333 16
3.94444 16
4 200
4.05556 16
4.25 48
4.33333 32
4.33333 16
4.5 384
4.66667 16
4.66667 80
4.75 32
5 456
5.25 96
5.5 80
5.66667 32
5.75 16
5.91667 16
6 856
6.08333 16
6.25 16
6.33333 16
6.33333 16
6.5 16
6.66667 32
6.75 64
6.83333 16
7 480
7.16667 8
7.16667 8
7.33333 64
7.5 8
7.66667 32
7.75 16
8 496
8.33333 16
8.33333 16
8.75 16
9 96
9.25 16
9.33333 32
9.66667 8
9.66667 8
10 48
10.3333 16
10.5 8
11 32
11.3333 8
11.5 8
12 360
12.5 8
12.6667 8
13 384
14 8
14 320
15 64
16 64
16.5 8
17 64
17.25 8
18 112
18.75 8
19 48
19.5 8
20 48
21 176
22 168
22.6667 8
23 48
25 32
25.3333 8
26 40
27 176
28 48
29 16
30 112
31 32
32 48
33 64
35 16
36 160
37 16
40 48
41 16
42 112
43 16
48 80
54 32
60 32
66 16
68 16
69 16
71 48
72 336
73 48
75 16
76 16
78 16
84 32
90 32
96 32

*/
