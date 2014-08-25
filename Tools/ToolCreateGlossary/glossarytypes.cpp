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

std::string ribi::GlossaryTypes::GetPageName(const GlossaryType t) const noexcept
{
  switch (t)
  {
    case GlossaryType::command_line: return "Command-line glossary";
    case GlossaryType::cpp: return "C++ glossary";
    case GlossaryType::game: return "Game glossary";
    case GlossaryType::levend_cluedo: return "Levend Cluedo glossary";
    case GlossaryType::tool: return "Tool glossary";
    case GlossaryType::music: return "Music glossary";
    case GlossaryType::sitemap: return "Sitemap";
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
    case GlossaryType::command_line: return "Cl.*\\.htm\\>";
    case GlossaryType::cpp: return "Cpp.*\\.htm\\>";
    case GlossaryType::game: return "Game.*\\.htm\\>";
    case GlossaryType::levend_cluedo: return "LevendCluedo.*\\.htm\\>";
    case GlossaryType::tool: return "Tool.*\\.htm\\>";
    case GlossaryType::music: return "(Music|Song|Cd).*\\.htm\\>";
    case GlossaryType::sitemap: return ".*\\.htm\\>";
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
    case GlossaryType::command_line: return "ClGlossary.htm";
    case GlossaryType::cpp: return "CppGlossary.htm";
    case GlossaryType::game: return "GameGlossary.htm";
    case GlossaryType::levend_cluedo: return "LevendCluedoGlossary.htm";
    case GlossaryType::tool: return "ToolGlossary.htm";
    case GlossaryType::music: return "MusicGlossary.htm";
    case GlossaryType::sitemap: return "Sitemap.htm";
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
  //assert(!"Refactor");
}
#endif
