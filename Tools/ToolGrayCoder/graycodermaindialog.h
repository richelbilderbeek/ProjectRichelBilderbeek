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
#ifndef GRAYCODERMAINDIALOG_H
#define GRAYCODERMAINDIALOG_H

#include <string>
#include <vector>

namespace ribi {

struct GrayCoderMainDialog
{
  GrayCoderMainDialog(const int normal_int = 0);

  ///From http://www.richelbilderbeek.nl/CppBitStringToInt.htm
  static int BitStringToInt(const std::string& s);

  ///Get the Gray code integer
  int GetGrayInt() const noexcept { return IntToGray(m_i); }

  ///Get the Gray code integer as a std::string of zeroes and ones
  std::string GetGrayIntAsBitStr() const { return IntToBitString(IntToGray(m_i)); }

  ///Get the normal integer
  int GetNormalInt() const noexcept { return m_i; }

  ///Get the normal integer as a std::string of zeroes and ones
  std::string GetNormalIntAsBitStr() const { return IntToBitString(m_i); }

  ///Set the Gray code integer, creates the normal integer
  void SetGrayInt(const int i) { m_i = GrayToInt(i); }

  ///Set the normal integer, creates the Gray code integer
  void SetNormalInt(const int i) { m_i = i; }


  private:
  ///Store a normal integer only
  int m_i;

  ///Convert a Gray coded integer to a normal integer
  ///From http://www.richelbilderbeek.nl/CppGrayToInt.htm
  ///Modified from Press et al., 2002, Numerical Recipies in C++,
  ///ISBN 0 521 75033 4
  static int GrayToInt(int i);

  ///From http://www.richelbilderbeek.nl/CppIntToBitString.htm
  static std::string IntToBitString(int i);

  ///Convert a normal integer to a Gray coded integer
  ///From http://www.richelbilderbeek.nl/CppIntToGray.htm
  static int IntToGray(const int i);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const GrayCoderMainDialog& dialog);

} //~namespace ribi

#endif // GRAYCODERMAINDIALOG_H
