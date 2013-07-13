#include <iostream>
#include <boost/lexical_cast.hpp>

int main()
{
  if (boost::lexical_cast<std::string>(123) == "123")
  {
    std::cout << "Hello Boost" << '\n';
  }
}
