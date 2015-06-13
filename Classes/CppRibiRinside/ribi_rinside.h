#ifndef RIBI_INSIDE_R_H
#define RIBI_INSIDE_R_H

#include <string>
#include <vector>

struct RInside;

namespace ribi {

//Singleton for an InsideR instance
struct Rinside
{
  Rinside();
  RInside& Get();

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi


#endif // RIBI_INSIDE_R_H
