//---------------------------------------------------------------------------
/*
GrayCoder, tool to convert integers to and from Gray code
Copyright (C) 2009-2015 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolGrayCoder.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "graycodermaindialog.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::GrayCoderMainDialog::GrayCoderMainDialog(const int normal_int)
  : m_i(normal_int)
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::GrayCoderMainDialog::BitStringToInt(const std::string& s)
{
  int power = 1;
  int result = 0;
  const auto j = s.rend();
  for (auto i = s.rbegin(); i!=j; ++i)
  {
    const char c = *i;
    if (c == '0')
    {
      //OK
    }
    else if (c == '1')
    {
      result += power;
    }
    else
    {
      throw std::logic_error("A bitstring must consist of zeroes and ones only");
    }
    power *= 2;
  }
  return result;
}

int ribi::GrayCoderMainDialog::GrayToInt(int i)
{
  int power = 1;
  while (1)
  {
    const int j = i >> power;
    i ^= j;
    if (j == 0 || power == 16) return i;
    power <<= 1;
  }
}

std::string ribi::GrayCoderMainDialog::IntToBitString(int i)
{
  assert( i >= 0 && "Did not bother to supply this yet");
  std::string s =(i%2 ? "1" : "0" );
  i>>=1;
  while (i > 0)
  {
    s = (i%2 ? "1" : "0") + s;
    i>>=1;
  }
  return s;
}

int ribi::GrayCoderMainDialog::IntToGray(const int i)
{
  assert( i >= 0 && "Did not bother to supply this yet");
  return (i ^ (i>>1));
}

#ifndef NDEBUG
void ribi::GrayCoderMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  ///BitStringToInt
  {
    assert(BitStringToInt(   "0") == 0);
    assert(BitStringToInt(   "1") == 1);
    assert(BitStringToInt(  "10") == 2);
    assert(BitStringToInt(  "11") == 3);
    assert(BitStringToInt( "100") == 4);
    assert(BitStringToInt( "101") == 5);
    assert(BitStringToInt( "110") == 6);
    assert(BitStringToInt( "111") == 7);
    assert(BitStringToInt("1000") == 8);
    assert(BitStringToInt("1001") == 9);
    assert(BitStringToInt("10000") ==  16);
    assert(BitStringToInt("100000") ==  32);
    assert(BitStringToInt("1000000") ==  64);
    assert(BitStringToInt("10000000") == 128);
    assert(BitStringToInt("100000000") == 256);
    assert(BitStringToInt("1000000000") == 512);
  }
  ///IntToBitString
  {
    assert(IntToBitString(  0) ==    "0");
    assert(IntToBitString(  1) ==    "1");
    assert(IntToBitString(  2) ==   "10");
    assert(IntToBitString(  3) ==   "11");
    assert(IntToBitString(  4) ==  "100");
    assert(IntToBitString(  5) ==  "101");
    assert(IntToBitString(  6) ==  "110");
    assert(IntToBitString(  7) ==  "111");
    assert(IntToBitString(  8) == "1000");
    assert(IntToBitString(  9) == "1001");
    assert(IntToBitString( 16) == "10000");
    assert(IntToBitString( 32) == "100000");
    assert(IntToBitString( 64) == "1000000");
    assert(IntToBitString(128) == "10000000");
    assert(IntToBitString(256) == "100000000");
    assert(IntToBitString(512) == "1000000000");
  }
  //IntToGray
  {
    assert(IntToGray( 0)== 0);
    assert(IntToGray( 1)== 1);
    assert(IntToGray( 2)== 3);
    assert(IntToGray( 3)== 2);
    assert(IntToGray( 4)== 6);
    assert(IntToGray( 5)== 7);
    assert(IntToGray( 6)== 5);
    assert(IntToGray( 7)== 4);
    assert(IntToGray( 8)==12);
    assert(IntToGray( 9)==13);
    assert(IntToGray(10)==15);
    assert(IntToGray(11)==14);
    assert(IntToGray(12)==10);
    assert(IntToGray(13)==11);
    assert(IntToGray(14)== 9);
    assert(IntToGray(15)== 8);
  }
  //GrayToInt
  {
    assert(GrayToInt( 0)== 0);
    assert(GrayToInt( 1)== 1);
    assert(GrayToInt( 3)== 2);
    assert(GrayToInt( 2)== 3);
    assert(GrayToInt( 6)== 4);
    assert(GrayToInt( 7)== 5);
    assert(GrayToInt( 5)== 6);
    assert(GrayToInt( 4)== 7);
    assert(GrayToInt(12)== 8);
    assert(GrayToInt(13)== 9);
    assert(GrayToInt(15)==10);
    assert(GrayToInt(14)==11);
    assert(GrayToInt(10)==12);
    assert(GrayToInt(11)==13);
    assert(GrayToInt( 9)==14);
    assert(GrayToInt( 8)==15);
  }
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const GrayCoderMainDialog& dialog)
{
  os
    << "Normal value   : " << dialog.GetNormalInt() << " (" << dialog.GetNormalIntAsBitStr() << ")\n"
    << "Gray code value: " << dialog.GetGrayInt() << " (" << dialog.GetGrayIntAsBitStr() << ")\n";

  return os;
}
