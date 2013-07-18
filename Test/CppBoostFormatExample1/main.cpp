#include <cstdio>
#include <iostream>
#include <boost/format.hpp>

int main()
{
  //Display integers, default
  std::cout << boost::format("%1%\n") % 1;
  std::cout << boost::format("%1%\n") % 12;
  std::cout << boost::format("%1%\n") % 123;
  std::cout << boost::format("%1%\n") % 1234;
  std::cout << boost::format("%1%\n") % 12345;
  std::cout << boost::format("%1%\n") % 123456;

  //Display doubles, default
  std::cout << boost::format("%1%\n") % 1.2345678;
  std::cout << boost::format("%1%\n") % 12.345678;
  std::cout << boost::format("%1%\n") % 123.45678;
  std::cout << boost::format("%1%\n") % 1234.5678;
  std::cout << boost::format("%1%\n") % 12345.678;
  std::cout << boost::format("%1%\n") % 123456.78;

  //Display doubles with two significant digits
  std::cout << boost::format("%1$.2d\n") % 1.2345678;
  std::cout << boost::format("%1$.2d\n") % 12.345678;
  std::cout << boost::format("%1$.2d\n") % 123.45678;
  std::cout << boost::format("%1$.2d\n") % 1234.5678;
  std::cout << boost::format("%1$.2d\n") % 12345.678;
  std::cout << boost::format("%1$.2d\n") % 123456.78;

  //Display sign
  //Pad to 5 digits
  std::cout << boost::format("%1$+5d\n") % 1;
  std::cout << boost::format("%1$+5d\n") % 12;
  std::cout << boost::format("%1$+5d\n") % 123;
  std::cout << boost::format("%1$+5d\n") % 1234;
  std::cout << boost::format("%1$+5d\n") % 12345;
  std::cout << boost::format("%1$+5d\n") % 123456;
}
