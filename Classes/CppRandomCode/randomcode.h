//---------------------------------------------------------------------------
/*
RandomCode, class to generate random C++ code
Copyright (C) 2007-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppRandomCode.htm
//---------------------------------------------------------------------------
#ifndef RANDOMCODE_H
#define RANDOMCODE_H

#include "about.h"
#include <string>
#include <vector>

namespace ribi {

struct RandomCode
{
  static const std::vector<std::string> CreateRandomCode() noexcept;
  static const About GetAbout() noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
  private:
  static const std::string CreateRandomLine(const unsigned int length) noexcept;
  static const std::string CreateRandomString() noexcept;
};

} //~namespace ribi

#endif // RANDOMCODE_H
