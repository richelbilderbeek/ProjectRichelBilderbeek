#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

struct MyClass
{
  MyClass(const std::string& s, const int x) : m_s(s), m_x(x) {}
  const std::string m_s;
  const int m_x;
};

//Order by x
bool operator<(const MyClass& lhs, const MyClass& rhs)
{
  return lhs.m_x < rhs.m_x;
}

//Display x first
std::ostream& operator<<(std::ostream& os, const MyClass& m)
{
  os << m.m_x << ' ' << m.m_s;
  return os;
}

int main()
{
  std::set<MyClass> s;
  //Insert ordered by s
  s.insert(MyClass("five",5));
  s.insert(MyClass("four",4));
  s.insert(MyClass("one",1));
  s.insert(MyClass("six",6));
  s.insert(MyClass("three",3));
  s.insert(MyClass("two",2));
  //Show that the set orders by MyClass their x
  std::copy(s.begin(),s.end(),std::ostream_iterator<MyClass>(std::cout,"\n"));
}

/* Screen output:

1 one
2 two
3 three
4 four
5 five
6 six
Press <RETURN> to close this window...

*/
