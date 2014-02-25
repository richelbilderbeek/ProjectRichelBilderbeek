#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

int main()
{
  {
    boost::bimap<int,std::string> m;
    assert(m.left.find(0) == m.left.end());
    m.insert(boost::bimap<int,std::string>::value_type(0,"zero"));
    assert(m.left.find(0) != m.left.end());
  }

  {
    boost::bimap<char,std::string> m;

    assert(m.left.find('a') == m.left.end());
    m.insert(boost::bimap<char,std::string>::value_type('a',"a"));
    assert(m.left.find('a') != m.left.end());

    assert(m.left.find('?') == m.left.end());
    m.insert(boost::bimap<char,std::string>::value_type('?',"question mark"));
    assert(m.left.find('?') != m.left.end());

    assert(m.left.find('0') == m.left.end());
    m.insert(boost::bimap<char,std::string>::value_type('0',"zero"));
    assert(m.left.find('0') != m.left.end());

    assert(m.left.find(' ') == m.left.end());
    m.insert(boost::bimap<char,std::string>::value_type(' '," "));
    assert(m.left.find(' ') != m.left.end());
  }
}
