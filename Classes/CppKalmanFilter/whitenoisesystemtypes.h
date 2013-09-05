#ifndef WHITENOISESYSTEMTYPES_H
#define WHITENOISESYSTEMTYPES_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

#include "whitenoisesystemtype.h"

namespace ribi {

struct WhiteNoiseSystemTypes
{
  static const std::vector<WhiteNoiseSystemType> GetAllTypes();
  static const std::string ToStr(const WhiteNoiseSystemType type);
  static WhiteNoiseSystemType ToType(const std::string& s);

  private:
  static boost::bimap<WhiteNoiseSystemType,std::string> m_map;
  static const boost::bimap<WhiteNoiseSystemType,std::string> CreateMap();

  #ifndef NDEBUG
  static void Test();
  #endif

};

} //~namespace ribi

#endif // WHITENOISESYSTEMTYPES_H
