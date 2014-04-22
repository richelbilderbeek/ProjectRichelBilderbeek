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

//Prevent ordering sets by the pointers their addresses
bool operator<(const boost::shared_ptr<      MyClass> lhs, const boost::shared_ptr<      MyClass> rhs) = delete;
bool operator<(const boost::shared_ptr<      MyClass> lhs, const boost::shared_ptr<const MyClass> rhs) = delete;
bool operator<(const boost::shared_ptr<const MyClass> lhs, const boost::shared_ptr<      MyClass> rhs) = delete;
bool operator<(const boost::shared_ptr<const MyClass> lhs, const boost::shared_ptr<const MyClass> rhs) = delete;

//Display x first
std::ostream& operator<<(std::ostream& os, const MyClass& m)
{
  os << m.m_x << ' ' << m.m_s;
  return os;
}

struct MySuperClass
{
  MySuperClass(const std::string& s, const int x)
    : m_c(boost::shared_ptr<MyClass>(new MyClass(s,x))) {}
  const boost::shared_ptr<MyClass> m_c;
};

int main()
{
  //Put MySuperClass instances in std::vector
  std::vector<MySuperClass> v;
  v.push_back(MySuperClass("five",5));
  v.push_back(MySuperClass("four",4));
  v.push_back(MySuperClass("one",1));
  v.push_back(MySuperClass("six",6));
  v.push_back(MySuperClass("three",3));
  v.push_back(MySuperClass("two",2));

  //Create a std::set with a custom MyClass ordering
  std::set<boost::shared_ptr<MyClass>,std::function<bool(boost::shared_ptr<MyClass>,boost::shared_ptr<MyClass>)>> s(
    [](const boost::shared_ptr<MyClass> lhs, const boost::shared_ptr<MyClass> rhs)
    {
      return lhs->m_x < rhs->m_x;
    }
  );

  //Insert MyClass instances in std::map by extracting these from std::vector
  std::transform(v.begin(),v.end(),std::inserter(s,s.begin()),
    [](const MySuperClass& c)
    {
      return c.m_c;
    }
  );

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
