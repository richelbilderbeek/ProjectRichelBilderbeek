#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct MyClass
{
  MyClass(const std::string& s, const int x) : m_s(s), m_x(x) {}
  const std::string m_s;
  const int m_x;
};

bool operator<(const MyClass& lhs, const MyClass& rhs) = delete;

///Prevent ordering sets by the pointers their addresses
bool operator<(const boost::shared_ptr<      MyClass> lhs, const boost::shared_ptr<      MyClass> rhs) = delete;
bool operator<(const boost::shared_ptr<const MyClass> lhs, const boost::shared_ptr<      MyClass> rhs) = delete;
bool operator<(const boost::shared_ptr<      MyClass> lhs, const boost::shared_ptr<const MyClass> rhs) = delete;
bool operator<(const boost::shared_ptr<const MyClass> lhs, const boost::shared_ptr<const MyClass> rhs) = delete;

//Display x first
std::ostream& operator<<(std::ostream& os, const MyClass& m)
{
  os << m.m_x << ' ' << m.m_s;
  return os;
}

int main()
{
  std::set<boost::shared_ptr<MyClass>,std::function<bool(boost::shared_ptr<MyClass>,boost::shared_ptr<MyClass>)>> s(
    [](const boost::shared_ptr<MyClass> lhs, const boost::shared_ptr<MyClass> rhs)
    {
      return lhs->m_x < rhs->m_x;
    }
  );
  //Insert ordered by s
  s.insert(boost::shared_ptr<MyClass>(new MyClass("five",5)));
  s.insert(boost::shared_ptr<MyClass>(new MyClass("four",4)));
  s.insert(boost::shared_ptr<MyClass>(new MyClass("one",1)));
  s.insert(boost::shared_ptr<MyClass>(new MyClass("six",6)));
  s.insert(boost::shared_ptr<MyClass>(new MyClass("three",3)));
  s.insert(boost::shared_ptr<MyClass>(new MyClass("two",2)));
  //Show that the set orders by MyClass their x
  std::transform(s.begin(),s.end(),std::ostream_iterator<MyClass>(std::cout,"\n"),
    [](const boost::shared_ptr<MyClass> m) { return *m; }
  );
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
