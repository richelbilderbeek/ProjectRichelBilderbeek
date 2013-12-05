#include "filename.h"

#include <cassert>
#include <stdexcept>

#include "fileio.h"

ribi::fileio::Filename::Filename(
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

ribi::fileio::Filename::~Filename()
{
  if (m_delete_file_on_destroy)
  {
    DeleteFile(m_filename);
  }
}

const std::string& ribi::fileio::Filename::Get() const noexcept
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
  CopyFile(fileNameFrom.Get(),fileNameTo.Get(),copy_mode);
}
void ribi::fileio::DeleteFile(const Filename& filename) { DeleteFile(filename.Get()); }
bool ribi::fileio::FilesAreIdentical(const Filename& filename_a,const Filename& filename_b)
{
  return FilesAreIdentical(filename_a.Get(),filename_b.Get());
}
const std::vector<std::string> ribi::fileio::FileToVector(const Filename& filename) { return FileToVector(filename.Get()); }
const std::string ribi::fileio::GetExtensionNoDot(const Filename& filename) { return GetExtensionNoDot(filename.Get()); }
bool ribi::fileio::IsRegularFile(const Filename& filename) { return IsRegularFile(filename.Get()); }

bool ribi::fileio::operator==(const Filename& lhs, const Filename& rhs)
{
  return lhs.Get() == rhs.Get();
}

std::ostream& ribi::fileio::operator<<(std::ostream& os, const Filename& filename)
{
  os << filename.Get();
  return os;
}
