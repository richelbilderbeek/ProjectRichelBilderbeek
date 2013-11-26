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
#ifndef CODETOHTMLHEADER_H
#define CODETOHTMLHEADER_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
//#include <boost/checked_delete.hpp>

#include "codetohtmlheadertype.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace c2h {

///Defines the header of the resulting HTML page
struct Header
{
  ///Convert this header to HTML
  static const std::vector<std::string> ToHtml(
    const HeaderType header_type,
    const std::string& filename
    ) noexcept;

  ///Obtain the HTML page its filename
  //const std::string& GetFilename() const { return m_filename; }

  ///Obtain the HTML page its filename
  //HeaderType GetHeaderType() const { return m_header_type; }

  private:
  Header() = delete;
  //~Header() noexcept {}
  //friend void boost::checked_delete<>(Header*);
  //friend void boost::checked_delete<>(const Header*);

  static const std::string CreateFilename(
    const HeaderType page_type,
    const std::string& filename);

  static const std::string CreateTitle(
    const HeaderType page_type,
    const std::string& filename);
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLHEADER_H
