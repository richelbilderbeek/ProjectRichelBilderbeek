#ifndef GLOSSARYTYPES_H
#define GLOSSARYTYPES_H

#include <string>
#include <vector>
#include "glossarytype.h"

namespace ribi {

struct GlossaryTypes
{
  GlossaryTypes();

  std::vector<GlossaryType> GetAll() const noexcept;

  std::string GetPageName(const GlossaryType t) const noexcept;
  std::string GetPageUrl(const GlossaryType t) const noexcept;
  std::string GetPageRegex(const GlossaryType t) const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // GLOSSARYTYPES_H
