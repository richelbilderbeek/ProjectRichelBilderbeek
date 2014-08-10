#ifndef WHITENOISESYSTEMTYPES_H
#define WHITENOISESYSTEMTYPES_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

#include "whitenoisesystemtype.h"

namespace ribi {
namespace kalman {

struct WhiteNoiseSystemTypes
{
  WhiteNoiseSystemTypes();
  std::vector<WhiteNoiseSystemType> GetAllTypes() const noexcept;
  std::string ToStr(const WhiteNoiseSystemType type) const noexcept;
  WhiteNoiseSystemType ToType(const std::string& s) const;

  private:
  static boost::bimap<WhiteNoiseSystemType,std::string> m_map;
  static boost::bimap<WhiteNoiseSystemType,std::string> CreateMap() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace kalman
} //~namespace ribi

#endif // WHITENOISESYSTEMTYPES_H
