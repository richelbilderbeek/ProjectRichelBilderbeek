#include <iostream>
#include <boost/regex.hpp>


int main()
{
  std::string s = "Hello World";
  s = boost::regex_replace(s,boost::regex("World"),std::string("Boost"));
  std::cout << s << '\n';
}
