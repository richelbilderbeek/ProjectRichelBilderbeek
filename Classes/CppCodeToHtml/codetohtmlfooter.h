//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#ifndef CODETOHTMLFOOTER_H
#define CODETOHTMLFOOTER_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "codetohtmlfootertype.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace c2h {

///Defines the header of the resulting HTML page
struct Footer
{
  static std::vector<std::string> ToHtml(const FooterType page_type) noexcept;
  static std::vector<std::string> ToMarkdown(const FooterType page_type) noexcept;

  //private:
  //~Footer() noexcept {}
  //friend void boost::checked_delete<>(Footer*);
  //friend void boost::checked_delete<>(const Footer*);
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLFOOTER_H
