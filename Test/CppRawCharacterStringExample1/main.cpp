#include <cassert>
#include <string>

int main()
{
  const std::string s { R"(/""\)" };
  assert(s.size() == 4);
  assert(s[0] == '/');
  assert(s[1] == '\"');
  assert(s[2] == '\"');
  assert(s[3] == '\\');
  const std::string t { "/\"\"\\" };
  assert(s == t);
}
