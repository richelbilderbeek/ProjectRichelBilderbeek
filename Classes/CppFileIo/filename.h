#ifndef FILENAME_H
#define FILENAME_H

#include <iosfwd>
#include <string>
#include <vector>

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
void DeleteFile(const Filename& filename);
bool FilesAreIdentical(const Filename& filename_a,const Filename& filename_b);
const std::vector<std::string> FileToVector(const Filename& filename);
const std::string GetExtensionNoDot(const Filename& filename);
bool IsRegularFile(const Filename& filename);

bool operator==(const Filename& lhs, const Filename& rhs);
std::ostream& operator<<(std::ostream& os, const Filename& filename);

} //~namespace fileio
} //~namespace ribi

#endif // FILENAME_H
