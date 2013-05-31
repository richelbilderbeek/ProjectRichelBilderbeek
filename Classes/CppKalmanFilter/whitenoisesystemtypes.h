#ifndef WHITENOISESYSTEMTYPES_H
#define WHITENOISESYSTEMTYPES_H

#include <string>
#include <vector>
#include <boost/bimap.hpp>
#include "whitenoisesystemtype.h"

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

#endif // WHITENOISESYSTEMTYPES_H
