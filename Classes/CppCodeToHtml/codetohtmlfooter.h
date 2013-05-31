//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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

#include "codetohtmlpagetype.h"

namespace c2h {

///Defines the header of the resulting HTML page
struct Footer
{
  explicit Footer(const PageType page_type);

  const std::vector<std::string> ToHtml() const;

  private:
  const PageType m_page_type;
};

} //~namespace CodeToHtml

#endif // CODETOHTMLFOOTER_H
