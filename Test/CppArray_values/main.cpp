#include <cassert>
#include <map>
#include <vector>

template <class KeyType, class ValueType>
const std::vector<ValueType> array_values(
  const std::map<KeyType,ValueType>& m)
{
  std::vector<ValueType> v;
  for (auto p: m)
  {
    v.push_back(p.second);
  }
  return v;
}

int main()
{
  {
    typedef int KeyType;
    typedef int ValueType;
    std::map<KeyType,ValueType> m;
    m[1] = 1;
    m[2] = 4;
    m[3] = 9;
    m[4] = 16;

    const std::vector<ValueType> values   { array_values(m) };
    const std::vector<ValueType> expected { 1,4,9,16 };
    assert(values == expected);
  }
  {
    typedef std::string KeyType;
    typedef int ValueType;
    std::map<KeyType,ValueType> m;
    m["four" ] = 4;
    m["one"  ] = 1;
    m["three"] = 3;
    m["two"  ] = 2;

    const std::vector<ValueType> values   { array_values(m) };
    const std::vector<ValueType> expected { 4,1,3,2 };
    assert(values == expected);
  }
  {
    typedef int KeyType;
    typedef std::string ValueType;
    std::map<KeyType,ValueType> m;
    m[1] = "one";
    m[2] = "two";
    m[4] = "four";
    m[8] = "eight";

    const std::vector<ValueType> values   { array_values(m) };
    const std::vector<ValueType> expected { "one", "two", "four", "eight" };
    assert(values == expected);
  }
  assert(1==2);
}
