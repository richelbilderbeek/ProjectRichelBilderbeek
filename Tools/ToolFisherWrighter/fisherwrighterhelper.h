#ifndef HELPER_H
#define HELPER_H

#include <map>
#include <string>
#include <vector>

namespace ribi {
namespace fw {

struct Helper
{
  Helper() noexcept;
  std::string ContainerToStr(const std::vector<std::string>& s, const std::string& seperator = " ") const noexcept;
  std::map<std::string,int> CreateSortedTally(const std::vector<std::string>& v) const noexcept;
  std::vector<std::pair<std::string,int>> CreateTally(const std::vector<std::string>& v) const noexcept;
  std::string GetFileBasename(const std::string& filename) const noexcept { return GetFileBasenameBoostXpressive(filename); }

  private:
  ///Most concise
  std::string GetFileBasenameBoostFilesystem(const std::string& filename) const noexcept;
  ///Can deal with Windows filenames as well
  std::string GetFileBasenameBoostXpressive(const std::string& filename) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace fw
} //~namespace ribi

#endif // HELPER_H
