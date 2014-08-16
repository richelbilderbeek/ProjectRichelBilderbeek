#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/timer.hpp>
#pragma GCC diagnostic pop


int main()
{
  boost::timer t;

  for (int i=0; i>=0; ++i) {}

  std::cout << t.elapsed() << '\n';
}

/* Screen output

4.339
Press <RETURN> to close this window...

*/
