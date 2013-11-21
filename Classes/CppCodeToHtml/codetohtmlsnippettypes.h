#ifndef CODETOHTMLSNIPPETTYPES_H
#define CODETOHTMLSNIPPETTYPES_H

#include <string>
#include <vector>

namespace ribi {
namespace c2h {

struct SnippetTypes
{
  static bool CanStrToSnippetType(const std::string& s);
  static const std::string SnippetTypeToStr(const SnippetType t);
  static const std::vector<SnippetType> GetAllSnippetTypes();
  static SnippetType StrToSnippetType(const std::string& s);
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLSNIPPETTYPES_H
