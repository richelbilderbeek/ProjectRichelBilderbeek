#ifndef OPENFOAMPATCHFIELDTYPES_H
#define OPENFOAMPATCHFIELDTYPES_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

#include "openfoampatchfieldtype.h"

namespace ribi {
namespace foam {

struct PatchFieldTypes
{
  static std::vector<PatchFieldType> GetAllTypes();
  static std::string ToStr(const PatchFieldType type);
  static PatchFieldType ToType(const std::string& s);

  private:
  static boost::bimap<PatchFieldType,std::string> m_map;
  static boost::bimap<PatchFieldType,std::string> CreateMap();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const PatchFieldType patch_field) noexcept;
std::istream& operator>>(std::istream& is, PatchFieldType& patch_field);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMPATCHFIELDTYPES_H
