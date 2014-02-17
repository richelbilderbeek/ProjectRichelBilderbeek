#include <algorithm>
#include <cassert>
#include <map>

struct MyClass
{
  MyClass(const std::string& s) : m_s{s} {}
  const std::string& Get() const noexcept { return m_s; }
  private:
  std::string m_s;
};

int main()
{
  std::vector<MyClass> v;
  v.push_back(MyClass("one"));
  v.push_back(MyClass("two"));
  v.push_back(MyClass("three"));
  v.push_back(MyClass("four"));
  v.push_back(MyClass("five"));
  v.push_back(MyClass("six"));

  //Find the shortest word and, if there multiple of the same length, the lexicographically first
  assert(
    std::min_element(v.begin(),v.end(),
      [](const MyClass& lhs, const MyClass& rhs)
      {
        if (lhs.Get().size() < rhs.Get().size()) return true;
        if (lhs.Get().size() > rhs.Get().size()) return false;
        return lhs.Get() < rhs.Get();
      }
    )->Get() == "one"
  );

  //Find the longest word and, if there multiple of the same length, the lexicographically last
  assert(
    std::max_element(v.begin(),v.end(),
      [](const MyClass& lhs, const MyClass& rhs)
      {
        if (lhs.Get().size() < rhs.Get().size()) return true;
        if (lhs.Get().size() > rhs.Get().size()) return false;
        return lhs.Get() < rhs.Get();
      }
    )->Get() == "three"
  );

  //Find the lexicographically first word
  assert(
    std::min_element(v.begin(),v.end(),
      [](const MyClass& lhs, const MyClass& rhs)
      {
        return lhs.Get() < rhs.Get();
      }
    )->Get() == "five"
  );

  //Find the lexicographically last word
  assert(
    std::max_element(v.begin(),v.end(),
      [](const MyClass& lhs, const MyClass& rhs)
      {
        return lhs.Get() < rhs.Get();
      }
    )->Get() == "two"
  );

}
