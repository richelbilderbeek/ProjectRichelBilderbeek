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

#include "about.h"

namespace ribi {

struct Program;

struct GalleryMenuDialog
{
  ///Create the page CppClassGallery.htm
  static const std::vector<std::string> CreateHtmlClassGallery();

  ///Create the page GameGallery.htm
  static const std::vector<std::string> CreateHtmlGameGallery();

  ///Create the page ProjectGallery.htm
  static const std::vector<std::string> CreateHtmlProjectGallery();

  ///Create the page CppRichelBilderbeekStatus.htm
  static const std::vector<std::string> CreateHtmlStatus();

  ///Create the page ToolGallery.htm
  static const std::vector<std::string> CreateHtmlToolGallery();

  static const About GetAbout() noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Test this class
  static void Test();

  private:

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
  static const std::vector<std::string> ToHtml(const Program& p);
};

} //~namespace ribi

#endif // RICHELBILDERBEEKGALLERYMENUDIALOG_H
