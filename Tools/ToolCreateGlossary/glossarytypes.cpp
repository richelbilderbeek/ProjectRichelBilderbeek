#include "glossarytypes.h"

#include <cassert>

#include "testtimer.h"
#include "glossarytypes.h"

ribi::GlossaryTypes::GlossaryTypes()
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::vector<ribi::GlossaryType> ribi::GlossaryTypes::GetAll() const noexcept
{
  const std::vector<GlossaryType> v {
    GlossaryType::command_line,
    GlossaryType::cpp,
    GlossaryType::game,
    GlossaryType::levend_cluedo,
    GlossaryType::tool,
    GlossaryType::music,
    GlossaryType::sitemap
  };
  return v;
}

/*
    CreatePage("Command-line glossary","ClGlossary.htm","Cl.*\\.htm\\>");
    CreatePage("C++ glossary","CppGlossary.htm","Cpp.*\\.htm\\>");
    CreatePage("Game glossary","GameGlossary.htm","Game.*\\.htm\\>");
    CreatePage("Levend Cluedo glossary","LevendCluedoGlossary.htm","LevendCluedo.*\\.htm\\>");
    CreatePage("Tool glossary","ToolGlossary.htm","Tool.*\\.htm\\>");
    CreatePage("Music glossary","MusicGlossary.htm","(Music|Song|Cd).*\\.htm\\>");
    CreatePage("Sitemap","Sitemap.htm",".*\\.htm\\>");
*/

std::string ribi::GlossaryTypes::GetPageName(const GlossaryType t) const noexcept
{
  switch (t)
  {
    case GlossaryType::command_line: return "";
    case GlossaryType::cpp: return "";
    case GlossaryType::game: return "";
    case GlossaryType::levend_cluedo: return "";
    case GlossaryType::tool: return "";
    case GlossaryType::music: return "";
    case GlossaryType::sitemap: return "";
    case GlossaryType::n_types:
      assert(!"Never use the value GlossaryType::n_types, except for debugging");
      break;
  }
  assert(!"Should not get here");
  return "";
}

std::string ribi::GlossaryTypes::GetPageRegex(const GlossaryType t) const noexcept
{
  switch (t)
  {
    case GlossaryType::command_line: return "";
    case GlossaryType::cpp: return "";
    case GlossaryType::game: return "";
    case GlossaryType::levend_cluedo: return "";
    case GlossaryType::tool: return "";
    case GlossaryType::music: return "";
    case GlossaryType::sitemap: return "";
    case GlossaryType::n_types:
      assert(!"Never use the value GlossaryType::n_types, except for debugging");
      break;
  }
  assert(!"Should not get here");
  return "";
}

std::string ribi::GlossaryTypes::GetPageUrl(const GlossaryType t) const noexcept
{
  switch (t)
  {
    case GlossaryType::command_line: return "";
    case GlossaryType::cpp: return "";
    case GlossaryType::game: return "";
    case GlossaryType::levend_cluedo: return "";
    case GlossaryType::tool: return "";
    case GlossaryType::music: return "";
    case GlossaryType::sitemap: return "";
    case GlossaryType::n_types:
      assert(!"Never use the value GlossaryType::n_types, except for debugging");
      break;
  }
  assert(!"Should not get here");
  return "";
}

#ifndef NDEBUG
void ribi::GlossaryTypes::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  assert(static_cast<int>(GlossaryTypes().GetAll().size()) == static_cast<int>(GlossaryType::n_types));
  for (const auto t: GlossaryTypes().GetAll()) { assert(!GlossaryTypes().GetPageName(t).empty()); }
  for (const auto t: GlossaryTypes().GetAll()) { assert(!GlossaryTypes().GetPageRegex(t).empty()); }
  for (const auto t: GlossaryTypes().GetAll()) { assert(!GlossaryTypes().GetPageUrl(t).empty()); }
  assert(!"Refactor");
}
#endif
