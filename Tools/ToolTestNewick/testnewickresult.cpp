
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testnewickresult.h"
#pragma GCC diagnostic pop

std::ostream& operator<<(std::ostream& os, const TestNewickResult& r)
{
  os
    << r.newick << '\t'
    << r.theta << '\t'
    << r.test_name << '\t'
    << r.probability << '\t'
    << r.time;
  return os;
}


