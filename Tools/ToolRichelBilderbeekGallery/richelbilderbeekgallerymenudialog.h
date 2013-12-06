//---------------------------------------------------------------------------
/*
RichelBilderbeekGallery, gallery of Richel Bilderbeek's work
Copyright (C) 2012 Richel Bilderbeek

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

struct GalleryMenuDialog : public MenuDialog
{
  GalleryMenuDialog();

  ///Create the page CppClassGallery.htm
  const std::vector<std::string> CreateHtmlClassGallery() const noexcept;

  ///Create the page GameGallery.htm
  const std::vector<std::string> CreateHtmlGameGallery() const noexcept;

  ///Create the page ProjectGallery.htm
  const std::vector<std::string> CreateHtmlProjectGallery() const noexcept;

  ///Create the page CppRichelBilderbeekStatus.htm
  const std::vector<std::string> CreateHtmlStatus() const noexcept;

  ///Create the page ToolGallery.htm
  const std::vector<std::string> CreateHtmlToolGallery() const noexcept;

  const About GetAbout() const noexcept;
  const Help GetHelp() const noexcept;
  const boost::shared_ptr<const Program> GetProgram() const noexcept;
  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;


  private:

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

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
  const std::vector<std::string> ToHtml(const Program& p) const noexcept;
};

} //~namespace ribi

#endif // RICHELBILDERBEEKGALLERYMENUDIALOG_H
