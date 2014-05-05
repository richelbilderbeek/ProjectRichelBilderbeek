#ifndef RIBI_RICHELBILDERBEEKPROGRAMTYPES_H
#define RIBI_RICHELBILDERBEEKPROGRAMTYPES_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/bimap.hpp>
#include "richelbilderbeekprogramtype.h"
#pragma GCC diagnostic pop

namespace ribi {

struct ProgramTypes
{
  ///Convert a type to its enum name
  ///For example, ProgramType 'x' becomes std::string "x"
  static std::string ProgramTypeToEnumName(const ProgramType t) noexcept;

  ///Convert a type to its screen name
  ///For example, ProgramType 'abcDef' might become std::string "Abc Def"
  static std::string ProgramTypeToScreenName(const ProgramType t) noexcept;

  static ProgramType EnumNameToProgramType(const std::string& s);

  static std::vector<std::string> GetAllEnumNames() noexcept;
  static std::vector<std::string> GetAllScreenNames() noexcept;
  static std::vector<ProgramType> GetAll() noexcept;

  private:
  ///Created by lazy initialization
  static boost::bimap<ProgramType,std::string> m_map_to_enumname;

  ///Created by lazy initialization
  static boost::bimap<ProgramType,std::string> m_map_to_screenname;

  static boost::bimap<ProgramType,std::string> CreateEnumNameMap();
  static boost::bimap<ProgramType,std::string> CreateScreenNameMap();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_RICHELBILDERBEEKPROGRAMTYPES_H
