//---------------------------------------------------------------------------
/*
FileIo, class with file I/O functions
Copyright (C) 2013-2015 Richel Bilderbeek

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
#ifdef REALLY_USE_FILENAME
#include "filename.h"

#include <cassert>
#include <stdexcept>

#include "fileio.h"

std::string::Filename(
  const std::string& filename,
  const bool delete_file_on_destroy)
  : m_delete_file_on_destroy(delete_file_on_destroy),
    m_filename(filename)
{
  if (m_filename.empty())
  {
    throw std::logic_error("A filio::Filename must consist of at least one character");
  }
  //if (!IsRegularFile(filename))
  //{
  //  throw std::logic_error("filio::Filename must have the name of an existing file");
  //}
  //assert(IsRegularFile(m_filename));

  assert(!m_filename.empty());
}

std::string::~Filename() noexcept
{
  if (m_delete_file_on_destroy)
  {
    DeleteFile(m_filename);
  }
}

const std::string& std::string::Get() const noexcept
{
  assert(!m_filename.empty());
  //assert(IsRegularFile(m_filename));
  return m_filename;
}



void ribi::fileio::CopyFile(
  const Filename& fileNameFrom,
  const Filename& fileNameTo,
  const CopyMode copy_mode)
{
  ribi::fileio::FileIo().CopyFile(fileNameFrom.Get(),fileNameTo.Get(),copy_mode);
}

void ribi::fileio::DeleteFile(const Filename& filename) { ribi::fileio::FileIo().DeleteFile(filename.Get()); }
bool ribi::fileio::FilesAreIdentical(const Filename& filename_a,const Filename& filename_b)
{
  return ribi::fileio::FileIo().FilesAreIdentical(filename_a.Get(),filename_b.Get());
}
std::vector<std::string> ribi::fileio::FileToVector(const Filename& filename) { return ribi::fileio::FileIo().FileToVector(filename.Get()); }
std::string ribi::fileio::GetExtensionNoDot(const Filename& filename) { return ribi::fileio::FileIo().GetExtensionNoDot(filename.Get()); }
bool ribi::fileio::FileIo().IsRegularFile(const Filename& filename) { return ribi::fileio::FileIo().IsRegularFile(filename.Get()); }
bool ribi::fileio::operator==(const Filename& lhs, const Filename& rhs)
{
  return lhs.Get() == rhs.Get();
}

std::ostream& ribi::fileio::operator<<(std::ostream& os, const Filename& filename)
{
  os << filename.Get();
  return os;
}

#endif //#ifdef REALLY_USE_FILENAME
