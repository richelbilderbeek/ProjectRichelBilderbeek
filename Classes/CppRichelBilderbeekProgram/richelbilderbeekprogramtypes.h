#ifndef RICHELBILDERBEEKPROGRAMTYPES_H
#define RICHELBILDERBEEKPROGRAMTYPES_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#include "richelbilderbeekprogramtype.h"
#pragma GCC diagnostic pop

namespace ribi {

struct ProgramTypes
{
  ///Convert a type to its enum name
  ///For example, ProgramType 'x' becomes std::string "x"
  static const std::string ProgramTypeToEnumName(const ProgramType t) noexcept;

  ///Convert a type to its screen name
  ///For example, ProgramType 'abcDef' might become std::string "Abc Def"
  static const std::string ProgramTypeToScreenName(const ProgramType t) noexcept;

  static ProgramType EnumNameToProgramType(const std::string& s);

  static const std::vector<std::string> GetAllEnumNames() noexcept;
  static const std::vector<std::string> GetAllScreenNames() noexcept;
  static const std::vector<ProgramType> GetAll() noexcept;

  private:
  ///Created by lazy initialization
  static boost::bimap<ProgramType,std::string> m_map_to_enumname;

  ///Created by lazy initialization
  static boost::bimap<ProgramType,std::string> m_map_to_screenname;

  static const boost::bimap<ProgramType,std::string> CreateEnumNameMap();
  static const boost::bimap<ProgramType,std::string> CreateScreenNameMap();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RICHELBILDERBEEKPROGRAMTYPES_H
