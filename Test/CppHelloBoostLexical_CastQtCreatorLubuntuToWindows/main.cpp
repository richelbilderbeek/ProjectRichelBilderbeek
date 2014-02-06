#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

int main()
{
  const int x = 110;
  const int y = 0;
  const int z = 1;
  const std::string s
    = std::string("He")
    + boost::lexical_cast<std::string>(x)
    + std::string(" w")
    + boost::lexical_cast<std::string>(y)
    + std::string("r")
    + boost::lexical_cast<std::string>(z)
    + std::string("d");
  std::cout << s << '\n';
}

/* Screen output:

He110 w0r1d

*/
