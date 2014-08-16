//---------------------------------------------------------------------------
/*
FileIo, class with file I/O functions
Copyright (C) 2013-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppFileIo.htm
//---------------------------------------------------------------------------
#ifdef REALLY_USE_RIBI_FILENAME

#ifndef RIBI_FILENAME_H
#define RIBI_FILENAME_H

#include <iosfwd>
#include <string>
#include <vector>

#include "filecopymode.h"

namespace ribi {
namespace fileio {

///A Filename is the name a regular file
///Will not do anything with the file itself
struct Filename
{
  Filename(
    const std::string& filename,
    const bool delete_file_on_destroy = false);

  ~Filename() noexcept;

  ///Obtain the filename
  const std::string& Get() const noexcept;

  private:
  const bool m_delete_file_on_destroy;
  const std::string m_filename;
};

///Free functions on Filename. These call the fileio functions
///working on std::string
void CopyFile(
  const Filename& fileNameFrom,
  const Filename& fileNameTo,
  const ribi::fileio::CopyMode copy_mode = CopyMode::prevent_overwrite);
void DeleteFile(const Filename& filename);
bool FilesAreIdentical(const Filename& filename_a,const Filename& filename_b);
std::vector<std::string> FileToVector(const Filename& filename);
std::string GetExtensionNoDot(const Filename& filename);
bool IsRegularFile(const Filename& filename);

bool operator==(const Filename& lhs, const Filename& rhs);
std::ostream& operator<<(std::ostream& os, const Filename& filename);

} //~namespace fileio
} //~namespace ribi

#endif // RIBI_FILENAME_H

#endif //#ifdef REALLY_USE_FILENAME
