//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015 Richel Bilderbeek

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
#ifndef CODETOHTMLFILETYPES_H
#define CODETOHTMLFILETYPES_H

#include <string>
#include <vector>

#include "codetohtmlfwd.h"

namespace ribi {
namespace c2h {

///Manages all FileType instances and conversion to std::string
struct FileTypes
{
  FileTypes();
  bool CanStrToFileType(const std::string& s) const noexcept;

  ///Deduce the content type from a filename
  FileType DeduceFileType(const std::string& filename) const noexcept;

  std::string FileTypeToStr(const FileType t) const noexcept;
  std::vector<FileType> GetAllFileTypes() const noexcept;
  FileType StrToFileType(const std::string& s) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi
} //~namespace c2h

#endif // CODETOHTMLFILETYPES_H
