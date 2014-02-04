#ifndef CONTAINER_H
#define CONTAINER_H

#include <set>
#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#pragma GCC diagnostic pop

namespace ribi {

///Class with container class helper functions
struct Container
{
  template <class T>
  static std::string ToStr(const std::set<T>& set) noexcept
  {
    std::string str;
    std::stringstream s;
    for (const auto t: set) { s << t << ","; }
    str = s.str();
    str.pop_back();
    str = "{" + str + "}";
    return str;
  }

  template <class T>
  static std::string ToStr(const std::vector<T>& v) noexcept
  {
    std::string str;
    std::stringstream s;
    for (const auto t: v) { s << t << ","; }
    str = s.str();
    str.pop_back();
    str = "{" + str + "}";
    return str;
  }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif
