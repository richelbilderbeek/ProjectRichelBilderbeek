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
#ifndef CODETOHTMLDIALOG_H
#define CODETOHTMLDIALOG_H

#include <string>
#include <vector>

#include "codetohtmlcontenttype.h"
#include "codetohtmlpagetype.h"
#include "codetohtmltechinfotype.h"

namespace c2h {

///CodeToHtmlDialog is the GUI independent UI of CodeToHtml
struct Dialog
{
  explicit Dialog(
    const PageType page_type,
    const std::string& source,
    const ContentType content_type,
    const TechInfoType tech_info);

  ///Convert a source (which can be a project file or code snippet text to an HTML page
  const std::vector<std::string> ToHtml() const;

  ///Test this class
  static void Test();

  private:
  const PageType m_page_type;
  const std::string m_source;
  const ContentType m_content_type;
  const TechInfoType m_tech_info;

};

} //~namespace CodeToHtml

#endif // CODETOHTMLDIALOG_H
