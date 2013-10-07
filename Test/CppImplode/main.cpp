#include <cassert>
#include <string>
#include <vector>

const std::string Implode(
  const std::string& seperator,
  const std::vector<std::string>& v)
{
  std::string s;
  if (v.empty()) return s;
  s += v[0];
  const std::size_t sz = v.size();
  for (std::size_t i=1; i!=sz; ++i)
  {
    s += seperator + v[i];
  }
  return s;
}

int main()
{
  {
    const std::vector<std::string> v { "a", "b", "c" };
    const std::string s = Implode(",",v);
    const std::string expected { "a,b,c" };
    assert(expected == s);
  }
  {
    const std::vector<std::string> v {};
    const std::string s = Implode(",",v);
    const std::string expected { "" };
    assert(expected == s);
  }

}
