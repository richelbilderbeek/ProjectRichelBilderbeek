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

#include "codetohtmlpagetype.h"

namespace c2h {

///Defines the header of the resulting HTML page
struct Header
{
  explicit Header(
    const PageType page_type,
    const std::string& filename);

  ///Convert this header to HTML
  const std::vector<std::string> ToHtml() const;

  ///Obtain the HTML page its filename
  const std::string& GetFilename() const { return m_filename; }

  ///Obtain the HTML page its filename
  PageType GetPageType() const { return m_page_type; }

  private:
  ///The HTML filename of the header
  const std::string m_filename;

  ///The page type of the CodeToHtmlHeader
  PageType m_page_type;

  ///The title of the header
  const std::string m_title;

  static const std::string CreateFilename(
    const PageType page_type,
    const std::string& filename);

  static const std::string CreateTitle(
    const PageType page_type,
    const std::string& filename);
};

} //~namespace CodeToHtml

#endif // CODETOHTMLHEADER_H
