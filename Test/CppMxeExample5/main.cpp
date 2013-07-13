#include <iostream>
#include <boost/regex.hpp>

int main(int argc, char* argv[])
{
  boost::regex r("Hello Boost.Regex");
  std::cout << r.str() << '\n';
}
