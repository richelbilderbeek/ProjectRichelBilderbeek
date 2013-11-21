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

#include <boost/scoped_ptr.hpp>

#include "codetohtmlfiletype.h"
#include "codetohtmlsnippettype.h"
#include "codetohtmltechinfotype.h"
#include "codetohtmlfoldertype.h"

namespace ribi {
namespace c2h {

struct Info;

///CodeToHtmlDialog is the GUI independent UI of CodeToHtml
struct Dialog
{
  explicit Dialog(
    const PageType page_type,
    const std::string& source,
    const FileType content_type
  );

  ///Convert a file to an HTML page
  const std::vector<std::string> FileToHtml(
    const std::string& file_name,
    const FileType file_type
    ) const;

  ///Convert a folder to an HTML page
  const std::vector<std::string> FolderToHtml(
    const std::string& folder_name,
    const FolderType folder_type
    ) const;

  ///Convert a snippet to an HTML page
  const std::vector<std::string> SnippetToHtml(
    const std::string& folder_name,
    const SnippetType folder_type
    ) const;



  private:
  ~Dialog() noexcept;
  friend void boost::checked_delete<>(Dialog*);
  friend void boost::checked_delete<>(const Dialog*);

  const FileType m_content_type;
  const boost::scoped_ptr<const Info> m_info;
  const PageType m_page_type;
  const std::string m_source;
  //const TechInfoType m_tech_info;

  ///Extract the page name, from, for example
  /// '/home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml'
  /// to 'ToolCodeToHtml'
  static const std::string ExtractPageName(const std::string& s) noexcept;

  #ifndef NDEBUG
  ///Test this class
  static void Test();
  #endif

};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLDIALOG_H
