//---------------------------------------------------------------------------
/*
CreateGlossary, tool to create my glossaries
Copyright (C) 2011-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateGlossary.htm
//---------------------------------------------------------------------------
#ifndef CREATEGLOSSARYMAINDIALOG_H
#define CREATEGLOSSARYMAINDIALOG_H

#include <string>
#include <vector>

struct CreateGlossaryMainDialog
{
  ///Create all glossaries
  CreateGlossaryMainDialog();

  private:
  ///Create a glossary
  static void CreatePage(
    const std::string& page_name,
    const std::string& page_url,
    const std::string& regex);

  ///Obtain all files in a folder
  //From http://www.richelbilderbeek.nl/CppGetFilesInFolder.htm
  static const std::vector<std::string> GetFilesInFolder(const std::string& folder);

  ///Obtain the files in a folder with a regex
  static const std::vector<std::string> GetFilesInFolder(
    const std::string& folder,
    const std::string& regex_str);

};

#endif // CREATEGLOSSARYMAINDIALOG_H

