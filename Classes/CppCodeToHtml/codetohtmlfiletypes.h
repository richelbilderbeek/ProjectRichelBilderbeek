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
  bool CanStrToFileType(const std::string& s) noexcept;

  ///Deduce the content type from a filename
  static FileType DeduceFileType(const std::string& filename);

  const std::string FileTypeToStr(const FileType t);
  const std::vector<FileType> GetAllFileTypes() noexcept;
  FileType StrToFileType(const std::string& s);

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi
} //~namespace c2h

#endif // CODETOHTMLFILETYPES_H
