#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

int main()
{
  const boost::shared_ptr<std::string> x {
    boost::make_shared<std::string>("Hello world")
  };
  std::cout << (*x) << '\n';
}
