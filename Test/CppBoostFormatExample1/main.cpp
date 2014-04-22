#include <cstdio>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/format.hpp>
#pragma GCC diagnostic pop

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

/* Screen output

1
12
123
1234
12345
123456
1.23457
12.3457
123.457
1234.57
12345.7
123457
1.2
12
1.2e+002
1.2e+003
1.2e+004
1.2e+005
   +1
  +12
 +123
+1234
+12345
+123456

*/

