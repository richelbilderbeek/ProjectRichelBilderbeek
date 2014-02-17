#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

struct MyClass
{
  MyClass(const std::string& s, const int x) : m_s(s), m_x(x) {}
  const std::string& GetS() const noexcept { return m_s; }
  int GetX() const noexcept { return m_x; }
  private:
  std::string m_s;
  int m_x;
};

bool operator<(const MyClass& lhs, const MyClass& rhs)
{
  return lhs.GetX() < rhs.GetX();
}

bool OrderByS(const MyClass& lhs, const MyClass& rhs)
{
  return lhs.GetS() < rhs.GetS();
}

int main()
{
  std::vector<MyClass> v;
  v.push_back(MyClass("five",5));
  v.push_back(MyClass("four",4));
  v.push_back(MyClass("one",1));
  v.push_back(MyClass("six",6));
  v.push_back(MyClass("three",3));
  v.push_back(MyClass("two",2));

  std::sort(v.begin(),v.end()); //Calls operator<

  assert(v[0].GetX() == 1);
  assert(v[1].GetX() == 2);
  assert(v[2].GetX() == 3);
  assert(v[3].GetX() == 4);
  assert(v[4].GetX() == 5);
  assert(v[5].GetX() == 6);

  std::sort(v.begin(),v.end(),OrderByS);

  assert(v[0].GetS() == "five");
  assert(v[1].GetS() == "four");
  assert(v[2].GetS() == "one");
  assert(v[3].GetS() == "six");
  assert(v[4].GetS() == "three");
  assert(v[5].GetS() == "two");
}
