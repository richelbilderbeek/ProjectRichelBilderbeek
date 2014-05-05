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
#ifndef RIBI_CODETOHTMLDIALOG_H
#define RIBI_CODETOHTMLDIALOG_H

#include <string>
#include <vector>

#include <boost/scoped_ptr.hpp>

#include "codetohtmlfiletype.h"
#include "codetohtmlsnippettype.h"
#include "codetohtmlfoldertype.h"

namespace ribi {
namespace c2h {

struct Info;

///c2h::Dialog is the GUI independent UI of CodeToHtml
///It provides a higher-level interface than Replacer:
///where Replacer can convert text, Dialog converts
///- code snippets
///- files
///- folders
struct Dialog
{
  ///Convert a file to an HTML page
  ///The file type will be deduced from the file name
  static std::vector<std::string> FileToHtml(
    const std::string& file_name) noexcept;

  ///Convert a folder to an HTML page
  ///The project type will be deduced from the folder its content
  static std::vector<std::string> FolderToHtml(
    const std::string& folder_name
    ) noexcept;

  ///Convert a snippet to an HTML page
  static std::vector<std::string> SnippetToHtml(
    const std::vector<std::string>& code,
    const SnippetType snippet_type
  ) noexcept;

  private:
  Dialog() = delete;
  ~Dialog() noexcept {}
  friend void boost::checked_delete<>(Dialog*);
  friend void boost::checked_delete<>(const Dialog*);

  ///Extract the page name, from, for example
  /// '/home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml'
  /// to 'ToolCodeToHtml'
  static std::string ExtractPageName(const std::string& s) noexcept;

  static std::vector<std::string> FoamFolderToHtml(
    const std::string& folder_name
    ) noexcept;

  static std::vector<std::string> GetProFilesInFolder(
    const std::string& folder);

  static std::vector<std::string> ProFolderToHtml(
    const std::string& folder_name
    ) noexcept;

  static std::vector<std::string> TextFolderToHtml(
    const std::string& folder_name
    ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace c2h
} //~namespace ribi

#endif // RIBI_CODETOHTMLDIALOG_H
