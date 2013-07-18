#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/xpressive/xpressive.hpp>
#pragma GCC diagnostic pop

int main()
{
  try
  {
    boost::xpressive::sregex::compile("\\d{4} [");
  }
  catch (boost::xpressive::regex_error& e)
  {
    std::cout << "OK\n";
    return 0;
  }
  return 1;
}
