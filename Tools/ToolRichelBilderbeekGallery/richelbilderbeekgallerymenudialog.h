//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRichelBilderbeekGallery.htm
//---------------------------------------------------------------------------
#ifndef RICHELBILDERBEEKGALLERYMENUDIALOG_H
#define RICHELBILDERBEEKGALLERYMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

struct Program;

struct GalleryMenuDialog final : public MenuDialog
{
  GalleryMenuDialog();

  ///Create the page CppClassGallery.htm
  std::vector<std::string> CreateHtmlClassGallery() const noexcept;
  ///Create the page GameGallery.htm
  std::vector<std::string> CreateHtmlGameGallery() const noexcept;
  ///Create the page ProjectGallery.htm
  std::vector<std::string> CreateHtmlProjectGallery() const noexcept;
  ///Create the page CppRichelBilderbeekStatus.htm
  std::vector<std::string> CreateHtmlStatus() const noexcept;
  ///Create the page ToolGallery.htm
  std::vector<std::string> CreateHtmlToolGallery() const noexcept;

  ///Create the page CppClassGallery.md
  std::vector<std::string> CreateMarkdownClassGallery() const noexcept;
  ///Create the page GameGallery.md
  std::vector<std::string> CreateMarkdownGameGallery() const noexcept;
  ///Create the page ProjectGallery.md
  std::vector<std::string> CreateMarkdownProjectGallery() const noexcept;
  ///Create the page ToolGallery.md
  std::vector<std::string> CreateMarkdownToolGallery() const noexcept;


  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  boost::shared_ptr<const Program> GetProgram() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;


  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;

  ///Converts a program to a gallery item
  ///Example:
  ///<h2 style="border:5px solid;background-color:#BBBBBB">&nbsp;<br/><a href="ToolAsciiArter.htm">Ascii Arter</a><br/>&nbsp;</h2>
  ///<p>&nbsp;</p>
  ///<p><img src="ToolAsciiArter_1_0.png" alt="Ascii Arter" width="383" height="400"/></p>
  ///<p>&nbsp;</p>
  ///<p>&nbsp;</p>
  ///<p>&nbsp;</p>
  ///<p>&nbsp;</p>
  ///<p>&nbsp;</p>
  std::vector<std::string> ToHtml(const Program& p) const noexcept;
  std::vector<std::string> ToMarkdown(const Program& p) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RICHELBILDERBEEKGALLERYMENUDIALOG_H
